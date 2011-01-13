#include <wx/wx.h>
#include <wx/app.h>
#include <wx/datstrm.h>
#include <wx/wfstream.h>
#include <wx/mstream.h>
#include <wx/zstream.h>
#include <wx/buffer.h>
#include <wx/process.h>
#include <wx/textfile.h>

#include "base64.h"
#include "wxTraverser.h"

class pckApp : public wxApp
{
    public: virtual bool OnInit();
};

struct fileTableEntry
{
    //wxInt32 xorBlock1Size; // encoded with key 1
    //wxInt32 xorBlock2Size; // encoded with key 2
    wxByte *filePath; // 260 byte
    wxUint32 fileDataOffset;
    wxUint32 fileDataDecompressedSize;
    wxUint32 fileDataCompressedSize;
    //wxByte seperator[4]; // [00 00 00 00]
};
