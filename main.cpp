#include "main.h"

bool compare(wxByte* buffer1, wxByte* buffer2, wxUint32 length)
{
    for(wxUint32 i=0; i<length; i++)
    {
        if(buffer1[i]!=buffer2[i])
        {
            return false;
        }
    }
    return true;
}

/*
    delete directory recursive
*/
void wxDeldir(wxString Directory)
{
    wxArrayString files;

    wxDirTraverserFiles fileTraverser(files);
    wxDir(Directory).Traverse(fileTraverser);

    for(wxUint32 i=0; i<files.Count(); i++)
    {
        wxRemoveFile(files[i]);
    }

    files.Clear();

    wxDirTraverserDirectories dirTraverser(files);
    wxDir(Directory).Traverse(dirTraverser);
    // Reverse Sort to make sure first delte folders without subfolders
    files.Sort(true);

    for(wxUint32 i=0; i<files.Count(); i++)
    {
        wxRmDir(files[i]);
    }

    wxRmDir(Directory);
}

wxByte* fillPath(wxByte* source)
{
    wxByte* target = new wxByte[260];

    bool end = false;

    for(wxUint32 i=0; i<260; i++)
    {
        if(!end && source[i]==0)
        {
            end = true;
        }
        if(end)
        {
            target[i] = 0;
        }
        else
        {
            target[i] = source[i];
        }
    }

    return target;
}

wxByte* deflate(wxByte* buffer, wxUint32 sizeCompressed, wxUint32 sizeDecompressed)
{
    wxByte* out = new wxByte[sizeDecompressed];
    wxMemoryInputStream mis(buffer, sizeCompressed);
    wxZlibInputStream* zis = new wxZlibInputStream(mis);
    zis->Read(out, sizeDecompressed);
    wxDELETE(zis);
    return out;
}

wxByte* inflate(wxByte* buffer, wxUint32 sizeDecompressed, wxUint32& sizeCompressed, wxUint32 compressionLevel)
{
    wxMemoryOutputStream mos;
    wxZlibOutputStream* zos = new wxZlibOutputStream(mos, compressionLevel);
    zos->Write(buffer, sizeDecompressed);
    wxDELETE(zos);
    sizeCompressed = mos.GetSize();
    wxByte* out = new wxByte[sizeCompressed];
    mos.CopyTo(out, sizeCompressed);
    return out;
}

/*
    deflate a patch file
*/
void decompress(wxString fileIn, wxString fileOut)
{
    if(!wxFile::Exists(fileOut))
    {
        wxFFileInputStream fis(fileIn);
        wxUint32 sizeDecompressed;
        fis.Read(&sizeDecompressed, 4);
        wxUint32 sizeCompressed = fis.GetSize()-4;
        wxByte* buffer = new wxByte[sizeCompressed];
        fis.Read(buffer, sizeCompressed);

        wxFFileOutputStream fos(fileOut);
        if(sizeCompressed < sizeDecompressed)
        {
            wxByte* zipBuffer = deflate(buffer, sizeCompressed, sizeDecompressed);
            fos.Write(zipBuffer, sizeDecompressed);
            wxDELETEA(zipBuffer);
        }
        else
        {
            fos.Write(buffer, sizeCompressed);
        }
        fos.Close();

        wxDELETEA(buffer);
    }
}

/*
    recursivly rename all files and directories to base64
*/
/*
void encodeBase64Entry(wxString path, wxCSConv encoding, bool isRoot)
{
    wxDir dir(path);
    wxString entry;
    wxString encoded;
    wxArrayString flatEntries;

    if(dir.GetFirst(&entry))
    {
        flatEntries.Add(entry);
    }
    while(dir.GetNext(&entry))
    {
        flatEntries.Add(entry);
    }

    for(wxUint32 i=0; i<flatEntries.Count(); i++)
    {
        entry = path + wxT("\\") + flatEntries[i];

        // if entry is a directory
        if(wxDir::Exists(entry))
        {
            encodeBase64Entry(entry, encoding, false);
        }
        // if entry is a file
        if(wxFile::Exists(entry))
        {
            encoded = entry.BeforeLast('\\') + wxT("\\") + Base64::Encode(flatEntries[i], encoding);
            wxRenameFile(entry, encoded);
        }
    }

    // encode the parent path (last directory)
    if(!isRoot)
    {
        encoded = path.BeforeLast('\\') + wxT("\\") + Base64::Encode(path.AfterLast('\\'), encoding);
        wxRenameFile(path, encoded);
    }
    else
    {
        wxRenameFile(path, path.BeforeLast('.').BeforeLast('.') + wxT(".pck.b64.files"));
    }
}
*/

/*
    returns the base64 encoded entry
*/
wxString encodeBase64Entry(wxString decodedPath, wxCSConv encoding)
{
    wxString temp;
    wxString result = wxT("");

    while(decodedPath.Contains(wxT("\\")))
    {
        // attention: reversed order
        temp = decodedPath.AfterLast('\\');

        temp = Base64::Encode(temp, encoding);

        result = wxT("\\") + temp + result;

        decodedPath = decodedPath.BeforeLast('\\');
    }

    return(result);
}

/*
    returns the base64 decoded entry
*/
wxString decodeBase64Entry(wxString encodedPath, wxCSConv encoding)
{
    wxString temp;
    wxString result = wxT("");

    while(encodedPath.Contains(wxT("\\")))
    {
        // attention: reversed order
        temp = encodedPath.AfterLast('\\');

        temp = Base64::Decode(temp, encoding);

        result = wxT("\\") + temp + result;

        encodedPath = encodedPath.BeforeLast('\\');
    }

    return(result);
}

wxByte* writeTableEntry(fileTableEntry fte, wxUint32& sizeCompressed, bool compress)
{
    wxByte* buffer = new wxByte[276];
    wxMemoryOutputStream mos;
    wxDataOutputStream bos(mos);
    mos.Write(fte.filePath, 260);
    bos.Write32(fte.fileDataOffset);
    bos.Write32(fte.fileDataDecompressedSize);
    bos.Write32(fte.fileDataCompressedSize);
    bos.Write32(0);
    mos.CopyTo(buffer, 276);
    if(compress)
    {
        wxByte* pBuffer = buffer;
        buffer = inflate(buffer, 276, sizeCompressed, 1);
        wxDELETEA(pBuffer);
    }

    return buffer;
}

fileTableEntry readTableEntry(wxByte* buffer, wxUint32 size, bool compressed)
{
    fileTableEntry fte;
    fte.filePath = new wxByte[260];

    if(compressed)
    {
        wxByte* pBuffer = buffer;
        buffer = deflate(buffer, size, 276);
        wxDELETEA(pBuffer);
    }

    wxMemoryInputStream mis(buffer, 276);
    wxDataInputStream bis(mis);
    mis.Read(fte.filePath, 260);
    fte.fileDataOffset = bis.Read32();
    fte.fileDataDecompressedSize = bis.Read32();
    fte.fileDataCompressedSize = bis.Read32();
    return fte;
}

/*
    creates all directories from the given path, if they don't exist
*/
void createPath(wxString rootDirectory, wxString subPath)
{
    rootDirectory.Append(wxT("\\"));
    subPath.Replace(wxT("/"), wxT("\\"), true);

    while(subPath.Contains(wxT("\\")))
    {
        rootDirectory.Append(subPath.BeforeFirst('\\') + wxT("\\"));
        subPath = subPath.AfterFirst('\\');
        if(!wxDirExists(rootDirectory))
        {
            wxMkdir(rootDirectory);
        }
    }
}

/*
    Extract the pck file to a directory
    corresponding to the filename
*/
void extract(wxString file)
{
    wxPrintf(wxT("Operation Mode: Extract Files\n\n") + file + wxT("\n\n"));

    wxCSConv enc(wxFONTENCODING_GB2312);
    wxString rootPath = file + wxT(".files");
    wxString subPath;
    wxFFileInputStream fis(file);
    wxDataInputStream bis(fis);
    fis.SeekI(-8, wxFromEnd);
    wxUint32 entryCount = bis.Read32();
    fis.SeekI(-272, wxFromEnd);
    wxUint32 fileTableOffset = bis.Read32() xor KEY_1;
    fis.SeekI(fileTableOffset, wxFromStart);
    fileTableEntry fileTable[entryCount];
    wxUint32 entrySize;
    wxByte* buffer;
    wxByte* zipBuffer;

    // read file entries
    for(wxUint32 i=0; i<entryCount; i++)
    {
        wxPrintf(wxString::Format(wxT("\rReading File Entries: %i/%i"), (i+1), entryCount));

        entrySize = bis.Read32() xor KEY_1;
        entrySize = bis.Read32() xor KEY_2;

        buffer = new wxByte[entrySize];
        fis.Read(buffer, entrySize);

        // use zlib decompression if compressed_size < decompressed_size
        if(entrySize < 276)
        {
            fileTable[i] = readTableEntry(buffer, entrySize, true);
        }
        // no zlib
        else
        {
            fileTable[i] = readTableEntry(buffer, entrySize, false);
        }

        //wxDELETEA(buffer);
    }

    wxPrintf(wxT("\n"));

    if(!wxDirExists(rootPath))
    {
        wxMkdir(rootPath);
    }

    for(wxUint32 i=0; i<entryCount; i++)
    {
        wxPrintf(wxString::Format(wxT("\rExtracting Files: %i/%i"), (i+1), entryCount));

        subPath = wxString((char*)fileTable[i].filePath, enc);
        createPath(rootPath, subPath);

        buffer = new wxByte[fileTable[i].fileDataCompressedSize];

        wxFFileOutputStream fos(rootPath + wxT("\\") + subPath);
        fis.SeekI(fileTable[i].fileDataOffset, wxFromStart);
        fis.Read(buffer, fileTable[i].fileDataCompressedSize);

        // use zlib decompression if compressed_size < decompressed_size
        if(fileTable[i].fileDataCompressedSize < fileTable[i].fileDataDecompressedSize)
        {
            zipBuffer = deflate(buffer, fileTable[i].fileDataCompressedSize, fileTable[i].fileDataDecompressedSize);
            fos.Write(zipBuffer, fileTable[i].fileDataDecompressedSize);
            wxDELETEA(zipBuffer);
        }
        // no zlib
        else
        {
            fos.Write(buffer, fileTable[i].fileDataCompressedSize);
        }

        wxDELETEA(buffer);
    }
}

/*
    Compress all files from this directory (recursively)
    to the pck file corresponding to the path name
*/
void compress(wxString directory)
{
    wxPrintf(wxT("Operation Mode: Compress Files\n\n") + directory + wxT("\n\n"));

    wxArrayString files;
    wxDirTraverserFiles fileTraverser(files);
    wxDir(directory).Traverse(fileTraverser);

    wxCSConv enc(wxFONTENCODING_GB2312);
    wxByte* buffer;
    wxByte* zipBuffer;
    wxUint32 entryCount = files.Count();
    wxUint32 fileTableOffset;
    fileTableEntry fileTable[entryCount];
    wxUint32 entrySize;

    wxFFileOutputStream fos(directory.BeforeLast('.'));
    wxDataOutputStream bos(fos);
    bos.Write32(FSIG_1);
    bos.Write32(0); // placeholder for filesize
    bos.Write32(FSIG_2);

    for(wxUint32 i=0; i<entryCount; i++)
    {
        wxPrintf(wxString::Format(wxT("\rCompressing Files: %i/%i"), (i+1), entryCount));

        fileTable[i].filePath = fillPath((wxByte*)files[i].Mid(directory.Length()+1).mb_str(enc).release());

        fileTable[i].fileDataOffset = fos.TellO();
        wxFFileInputStream fis(files[i]);
        fileTable[i].fileDataDecompressedSize = fis.GetSize();
        buffer = new wxByte[fileTable[i].fileDataDecompressedSize];
        fis.Read(buffer, fileTable[i].fileDataDecompressedSize);

        zipBuffer = inflate(buffer, fileTable[i].fileDataDecompressedSize, fileTable[i].fileDataCompressedSize, 1);

        // use zlib compression if compressed_size < decompressed_size
        if(fileTable[i].fileDataCompressedSize < fileTable[i].fileDataDecompressedSize)
        {
            fos.Write(zipBuffer, fileTable[i].fileDataCompressedSize);
        }
        // no zlib
        else
        {
            fos.Write(buffer, fileTable[i].fileDataDecompressedSize);
            fileTable[i].fileDataCompressedSize = fileTable[i].fileDataDecompressedSize;
        }

        wxDELETEA(zipBuffer);
        wxDELETEA(buffer);
    }

    fileTableOffset = fos.TellO();

    wxPrintf(wxT("\n"));

    // write file entries
    for(wxUint32 i=0; i<entryCount; i++)
    {
        wxPrintf(wxString::Format(wxT("\rWriting File Entries: %i/%i"), (i+1), entryCount));

        zipBuffer = writeTableEntry(fileTable[i], entrySize, true);

        if(entrySize > 272)
        {
            entrySize = 272;
        }

        bos.Write32(entrySize xor KEY_1);
        bos.Write32(entrySize xor KEY_2);

        // use zlib compression if compressed_size < decompressed_size
        if(entrySize < 272)
        {
            fos.Write(zipBuffer, entrySize);
        }
        // no zlib
        else
        {
            buffer = writeTableEntry(fileTable[i], entrySize, false);
            fos.Write(buffer, entrySize);
            wxDELETEA(buffer);
        }

        wxDELETEA(zipBuffer);
    }

    bos.Write32(ASIG_1);
    bos.Write16(2);
    bos.Write16(2);
    bos.Write32(fileTableOffset xor KEY_1);
    bos.Write32(0); // write int=0 for newer versions (seperator)
    fos.Write("Angelica File Package, Perfect World.", 37);
    wxByte* zeros = new wxByte[215]; //write only 215 zeros instead of 219 for newer versions
    for(wxUint32 i=0; i<215; i++)
    {
        zeros[i] = 0;
    }
    fos.Write(zeros, 215);
    wxDELETEA(zeros);
    bos.Write32(ASIG_2);
    bos.Write32(entryCount);
    bos.Write16(2);
    bos.Write16(2);

    wxUint32 fileSize = fos.TellO();
    fos.SeekO(4, wxFromStart);
    bos.Write32(fileSize);
}

/*
    Add all files from this directory (recursively)
    to the pck file corresponding to the path name
*/
void add(wxString directory, bool isBase64)
{
    wxPrintf(wxT("Operation Mode: Add Files\n\n") + directory + wxT("\n\n"));

    wxArrayString files;
    wxDirTraverserFiles fileTraverser(files);
    wxDir(directory).Traverse(fileTraverser);
    wxUint32 entryCountAdd = files.Count();
    wxCSConv enc(wxFONTENCODING_GB2312);
    wxString pckFile = directory.BeforeLast('.');
    pckFile.Replace(wxT(".b64"), wxT(""));
    wxFFileOutputStream fout(pckFile, wxT("r+b"));
    wxDataOutputStream bout(fout);
    wxFFileInputStream fin(pckFile, wxT("r+b"));
    wxDataInputStream bin(fin);
    fin.SeekI(-8, wxFromEnd);
    wxUint32 entryCountOld = bin.Read32();
    fin.SeekI(-272, wxFromEnd);
    wxUint32 fileTableOffset = bin.Read32() xor KEY_1;
    wxUint32 entryCount = entryCountOld+entryCountAdd;
    fileTableEntry fileTable[entryCount];
    wxUint32 entrySize;
    wxByte* buffer;
    wxByte* zipBuffer;

    fin.SeekI(fileTableOffset, wxFromStart);
    // read file entries from pck
    for(wxUint32 i=0; i<entryCountOld; i++)
    {
        wxPrintf(wxString::Format(wxT("\rReading File Entries: %i/%i"), (i+1), entryCountOld));

        entrySize = bin.Read32() xor KEY_1;
        entrySize = bin.Read32() xor KEY_2;

        buffer = new wxByte[entrySize];
        fin.Read(buffer, entrySize);

        // use zlib decompression if compressed_size < decompressed_size
        if(entrySize < 276)
        {
            fileTable[i] = readTableEntry(buffer, entrySize, true);
        }
        // no zlib
        else
        {
            fileTable[i] = readTableEntry(buffer, entrySize, false);
        }

        //wxDELETEA(buffer);
    }

    wxPrintf(wxT("\n"));

    fout.SeekO(fileTableOffset, wxFromStart);
    // add new files and file entries from directory
    for(wxUint32 i=entryCountOld; i<entryCount; i++)
    {
        wxPrintf(wxString::Format(wxT("\rAdding Files: %i/%i"), (i-entryCountOld+1), entryCountAdd));

        if(isBase64)
        {
            fileTable[i].filePath = fillPath((wxByte*)decodeBase64Entry(wxT("\\") + files[i-entryCountOld].Mid(directory.Length()+1), enc).mb_str(enc).release());
        }
        else
        {
            fileTable[i].filePath = fillPath((wxByte*)files[i-entryCountOld].Mid(directory.Length()+1).mb_str(enc).release());
        }
        fileTable[i].fileDataOffset = fout.TellO();
        wxFFileInputStream fis(files[i-entryCountOld]);
        fileTable[i].fileDataDecompressedSize = fis.GetSize();
        buffer = new wxByte[fileTable[i].fileDataDecompressedSize];
        fis.Read(buffer, fileTable[i].fileDataDecompressedSize);

        zipBuffer = inflate(buffer, fileTable[i].fileDataDecompressedSize, fileTable[i].fileDataCompressedSize, 1);

        // use zlib compression if compressed_size < decompressed_size
        if(fileTable[i].fileDataCompressedSize < fileTable[i].fileDataDecompressedSize)
        {
            fout.Write(zipBuffer, fileTable[i].fileDataCompressedSize);
        }
        // no zlib
        else
        {
            fout.Write(buffer, fileTable[i].fileDataDecompressedSize);
            fileTable[i].fileDataCompressedSize = fileTable[i].fileDataDecompressedSize;
        }

        wxDELETEA(zipBuffer);
        wxDELETEA(buffer);
    }

    wxPrintf(wxT("\n"));
    wxUint32 replacedCount = 0;
    fileTableOffset = fout.TellO();

    // write file entries
    for(wxUint32 i=0; i<entryCount; i++)
    {
        // check if the current file entry was replaced by a newer one
        //for(wxUint32 n=0; n<entryCountAdd; n++)
        for(wxUint32 n=entryCountOld; n<entryCount; n++)
        {
            //if(i<entryCountOld && files[n].Mid(directory.Length()+1).CmpNoCase(wxString((char*)fileTable[i].filePath, enc))==0)
            if(i<entryCountOld && compare(fileTable[n].filePath, fileTable[i].filePath, 260))
            {
                // this entry was replaced and will not be written
                replacedCount++;
                break;
            }
            if(i>=entryCountOld || n==entryCount-1)
            {
                zipBuffer = writeTableEntry(fileTable[i], entrySize, true);

                if(entrySize > 272)
                {
                    entrySize = 272;
                }

                bout.Write32(entrySize xor KEY_1);
                bout.Write32(entrySize xor KEY_2);

                // use zlib compression if compressed_size < decompressed_size
                if(entrySize < 272)
                {
                    fout.Write(zipBuffer, entrySize);
                }
                // no zlib
                else
                {
                    buffer = writeTableEntry(fileTable[i], entrySize, false);
                    fout.Write(buffer, entrySize);
                    wxDELETEA(buffer);
                }

                wxDELETEA(zipBuffer);
                break;
            }
        }

        wxPrintf(wxString::Format(wxT("\rRe-Writing File Entries: %i/%i (%i Replacements)"), (i+1-replacedCount), entryCount, replacedCount));
    }

    bout.Write32(ASIG_1);
    bout.Write16(2);
    bout.Write16(2);
    bout.Write32(fileTableOffset xor KEY_1);
    bout.Write32(0); // write int=0 for newer versions (seperator)
    fout.Write("Angelica File Package, Perfect World.", 37);
    wxByte* zeros = new wxByte[215]; //write only 215 zeros instead of 219 for newer versions
    for(wxUint32 i=0; i<215; i++)
    {
        zeros[i] = 0;
    }
    fout.Write(zeros, 215);
    wxDELETEA(zeros);
    bout.Write32(ASIG_2);
    bout.Write32(entryCount-replacedCount);
    bout.Write16(2);
    bout.Write16(2);

    wxUint32 fileSize = fout.TellO();
    fout.SeekO(4, wxFromStart);
    bout.Write32(fileSize);
}

/*
    Extract a cup file to a directory
    corresponding to the filename

    After extraction the filenames are decoded
    and the file contents are deflated
*/
void decode(wxString directory)
{
    wxPrintf(wxT("Operation Mode: Extract Patch\n\n") + directory + wxT("\n"));

    wxCSConv enc(wxT("UTF-8"));
    wxString directoryOut = directory.BeforeLast('.') + wxT(".decoded");
    if(!wxDir::Exists(directoryOut))
    {
        wxMkdir(directoryOut);
    }

    // reading the file list from all v-*.inc files
    wxArrayString v_incs;
    wxDir::GetAllFiles(directory, &v_incs, wxT("*.inc"), wxDIR_DEFAULT);

    wxString line;
    wxString chDir = wxT("\\");
    wxString fileBase64;
    wxString fileDecoded;

    wxTextFile f;

    // we want to extract all content, so we just have to find the v-*.inc with largest revision number
    for(wxUint32 n=0; n<v_incs.Count(); n++)
    {
        wxPrintf(wxT("\nProcessing Index File: ") + v_incs.Item(n).AfterLast('\\') + wxT("\n"));

        f.Open(v_incs.Item(n));

        wxUint32 i=0;
        while(!f.Eof())
        {
            line = f.GetNextLine();
            if(line.StartsWith(wxT("!")) || line.StartsWith(wxT("+")))
            {
                //filesMD5.Add(line.Mid(1).BeforeFirst(' '));
                line = line.AfterFirst(' ');
                line.Replace(wxT("/"), wxT("\\"), true);

                // currently file path' are using a "change dir" based system
                // we need to add the root path to all files that are listed after a change dir command
                if(line.StartsWith(wxT("\\")))
                {
                    chDir = line.BeforeLast('\\') + wxT("\\");
                    fileBase64 = line;
                }
                else
                {
                    fileBase64 = chDir + line;
                }

                // check if this file exists
                if(wxFile::Exists(directory + wxT("\\element") + fileBase64))
                {
                    fileDecoded = decodeBase64Entry(fileBase64, enc);

                    // create the directory structure for the output file
                    createPath(directoryOut, wxT("element") + fileDecoded);

                    // deflate the encoded file to the new path
                    decompress(directory + wxT("\\element") + fileBase64, directoryOut + wxT("\\element") + fileDecoded);
                }

                wxPrintf(wxString::Format(wxT("\rDecompressing Files: %i"), (i+1)));

                i++;
            }
        }

        f.Close();
    }
}

/*
    Create a xup file from a directory
    corresponding to the filename

    After compression the filenames are encoded
    and the file contents are enflated
*/
void encode(wxString directory)
{
    wxPrintf(wxT("Operation Mode: Create Patch\n\n") + directory + wxT("\n\n"));
/*
    wxCSConv enc(wxFONTENCODING_GB2312);
    wxArrayString directories;
    wxDirTraverserDirectories dirTraverser(directories);
    wxDir(directory).Traverse(dirTraverser, wxT("*.pck.files"), wxDIR_DEFAULT);

    for(wxUint32 i=0; i<directories.Count(); i++)
    {
        if(directories[i].EndsWith(wxT(".pck.files")))
        {
            encodeBase64Entry(directories[i], enc, true);
        }
    }
*/
    wxCSConv enc(wxFONTENCODING_GB2312);
    wxArrayString files;
    wxDirTraverserFiles fileTraverser(files);
    wxDir(directory).Traverse(fileTraverser, wxT("*.*"), wxDIR_DEFAULT);

    // create a temp directory for patch
    wxString targetDir = directory + wxT(".TMP");
    if(!wxDir::Exists(targetDir))
    {
        wxMkdir(targetDir);
    }

    wxString decodedFile;
    for(wxUint32 i=0; i<files.Count(); i++)
    {
        wxPrintf(wxString::Format(wxT("\rCreating Temp Files: %i/%i"), (i+1), files.Count()));

        decodedFile = files[i];
        decodedFile.Replace(directory + wxT("\\"), wxT(""));

        if(decodedFile.Contains(wxT(".pck.files")))
        {
            decodedFile.Replace(wxT("element\\"), wxT(""));
            decodedFile.Replace(wxT(".pck.files"), wxT(".pck.b64.files"));
            decodedFile = wxT("element\\") + decodedFile.BeforeFirst('\\') + encodeBase64Entry(wxT("\\") + decodedFile.AfterFirst('\\'), enc);
        }

        // create target directory structure
        createPath(targetDir, decodedFile);

        // copy source file to target file...
        wxCopyFile(files[i], targetDir + wxT("\\") + decodedFile);
    }

    // compress
    wxPrintf(wxT("\nCompressing Files..."));
    wxProcess::Open(wxT("sza.exe a -t7z -mx9 -r \"") + targetDir.BeforeLast('\\') + wxT("\\ec_patch_0-0.xup\" \"") + targetDir + wxT("\\*\""), wxEXEC_SYNC);

    // delete temp directory recursive
    wxPrintf(wxT("\nDeleting Temp Files..."));
    wxDeldir(targetDir);
}

IMPLEMENT_APP(pckApp);

bool pckApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    if(wxsOK)
    {
        wxSystem(wxT("cls"));

        // check if amount of command line arguments is correct
        // first parameter is the execuable file itself
        // second is the instruction
        // third is the file/directory

        if(argc<3)
        {
            wxPrintf(wxT("Invalid amount of arguments\nPress Enter to exit"));
            wxScanf(new wxChar);
            exit(1);
        }

        // Convert second parameter argv[1] from char* to wxString
        wxString instruction(argv[1], wxConvUTF8);
        // Convert third parameter argv[2] from char* to wxString
        wxString path(argv[2], wxConvUTF8);

        if(instruction != wxT("-x") && instruction != wxT("-c") && instruction != wxT("-a") && instruction != wxT("-ap") && instruction != wxT("-xp") && instruction != wxT("-cp"))
        {
            wxPrintf(wxT("First argument is not a valid instruction\nPress Enter to exit"));
            wxScanf(new wxChar);
            exit(2);
        }

        if(instruction == wxT("-x"))
        {
            // Check if path is a valid file
            if(!wxFileExists(path))
            {
                wxPrintf(wxT("Second argument is not a valid file\nPress Enter to exit"));
                wxScanf(new wxChar);
                exit(3);
            }
            else
            {
                extract(path);
            }
        }

        if(instruction == wxT("-c"))
        {
            // Check if path is a valid directory
            if(!wxDirExists(path) && path.EndsWith(wxT(".pck.files")))
            {
                wxPrintf(wxT("Second argument is not a valid directory\nPress Enter to exit"));
                wxScanf(new wxChar);
                exit(4);
            }
            else
            {
                compress(path);
            }
        }

        if(instruction == wxT("-a"))
        {
            // Check if path is a valid directory
            if(!wxDirExists(path))
            {
                wxPrintf(wxT("Second argument is not a valid directory\nPress Enter to exit"));
                wxScanf(new wxChar);
                exit(5);
            }
            else
            {
                add(path, false);
            }
        }

        if(instruction == wxT("-ap"))
        {
            // Check if path is a valid directory
            if(!wxDirExists(path))
            {
                wxPrintf(wxT("Second argument is not a valid directory\nPress Enter to exit"));
                wxScanf(new wxChar);
                exit(5);
            }
            else
            {
                add(path, true);
            }
        }

        if(instruction == wxT("-xp"))
        {
            // Check if path is a valid file
            if(!wxFileExists(path))
            {
                wxPrintf(wxT("Second argument is not a valid file\nPress Enter to exit"));
                wxScanf(new wxChar);
                exit(6);
            }
            else
            {
                extract(path);
                wxPrintf(wxT("\n\n\n"));
                decode(path + wxT(".files"));
            }
        }

        if(instruction == wxT("-cp"))
        {
            // Check if path is a valid directory
            if(!wxDirExists(path))
            {
                wxPrintf(wxT("Second argument is not a valid directory\nPress Enter to exit"));
                wxScanf(new wxChar);
                exit(7);
            }
            else
            {
                encode(path);
            }
        }

    	wxsOK = false;
    }
    //*)
    return wxsOK;
}
