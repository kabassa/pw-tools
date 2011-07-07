#include "main.h"

wxArrayString LoadDB(wxString file)
{
    wxArrayString data;
    wxTextFile f;

    wxPrintf(wxT("Loading Items from File: ") + file + wxT("...\n\n"));

    f.Open(file);
    for(wxString line=f.GetFirstLine(); !f.Eof(); line=f.GetNextLine())
    {
        data.Add(line);
    }
    f.Close();

    wxUint16 valid = 0;
    for(wxUint16 i=data.Count()-1; i>=0; i--)
    {
        if(!data[i].Contains(wxT("Item not Found")))
        {
            valid = i;
            break;
        }
    }

    wxPrintf(wxString::Format(wxT("Total Items Found: %i\n"), data.Count()));
    wxPrintf(wxString::Format(wxT("Last Valid Item ID: %i\n\n"), valid));

    return data;
}

void SaveDB(wxArrayString data, wxString file)
{
    wxTextFile f;

    wxPrintf(wxT("Saving Items to File: ") + file + wxT("...\n\n"));

    f.Open(file);
    f.Clear();
    for(wxUint16 i=0; i<data.Count(); i++)
    {
        f.InsertLine(data[i], i);
    }
    f.Write();
    f.Close();

    return;
}

wxArrayString UpdateDB(wxArrayString data, wxString type, wxUint16 startID, wxUint16 endID)
{
    //wxArrayString newData;
    wxString item;

    // TODO: check if startID > data.Length and fill in empty spots

    try
    {
        wxHTTP webResponse;
        wxString host = wxT("www.pwdatabase.com");
        wxUint16 port = 80;

        if(webResponse.Connect(host, port))
        {
            for(wxUint16 i=startID; i<=endID; i++)
            {
                wxPrintf(wxString::Format(wxT("\rSynchronize with pwdatabase.com, Item ID: %i / %i-%i"), i, startID, endID));

                wxInputStream *httpStream = webResponse.GetInputStream(wxString::Format(wxT("/pwi/items/%i"), i));

                // set default item text
                item = wxT("<span class=\\'item_color0\\'>Item not Found</span>");

                if(webResponse.GetError() == wxPROTO_NOERR)
                {
                    wxTextInputStream sr(*httpStream);
                    wxString line;
                    while(!httpStream->Eof())
                    {
                        line = sr.ReadLine();
                        if(line.Contains(wxT("class=\"itemHeader\"")))
                        {
                            line = line.AfterFirst(L'>');
                            line.Replace(wxT("'"), wxT("\\'"), true);
                            item = line;
                            break;
                        }
                    }
                }

                data[i] = item;

                wxDELETE(httpStream);
            }

            webResponse.Close();
        }
    }
    catch(...)
    {
        // connection error;
    }

    wxPrintf(wxT("\n\n"));

    return data;
}

IMPLEMENT_APP(pckApp);

bool pckApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    if(wxsOK)
    {
        wxSystem(wxT("cls"));

        if(argc>2)
        {
            wxString dbPath(argv[1], wxConvUTF8);
            wxString dbType(argv[2], wxConvUTF8);

            if(wxFileExists(dbPath + wxT("\\") + dbType + wxT(".dat")))
            {
                wxArrayString db = LoadDB(dbPath + wxT("\\") + dbType + wxT(".dat"));
                if(argc>4)
                {
                    wxUint16 dbFirstItem = wxAtoi(wxString(argv[3], wxConvUTF8));
                    wxUint16 dbLastItem = wxAtoi(wxString(argv[4], wxConvUTF8));

                    db = UpdateDB(db, dbType, dbFirstItem, dbLastItem);

                    SaveDB(db, dbPath + wxT("\\") + dbType + wxT(".dat"));
                }
                wxPrintf(wxT("Operation Complete! Press Enter to Exit..."));
                wxScanf(new wxChar);
                exit(0);
            }
        }

        wxPrintf(wxT("Invalid (amount of) Arguments\nPress Enter to Exit..."));
        wxScanf(new wxChar);

    	wxsOK = false;
    }
    //*)
    return wxsOK;
}
