#include "sPATCHMain.h"
#include <wx/fs_inet.h>
#include <wx/msgdlg.h>
#include "wxTraverser.h"
#include <wx/dialog.h>
#include <wx/process.h>
#include <wx/sstream.h>
#include <wx/txtstrm.h>
#include <wx/textfile.h>
#include <wx/protocol/http.h>

//(*InternalHeaders(sPATCHDialog)
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

void wxDeldir(wxString Directory)
{
    wxArrayString files;

    wxDirTraverserFiles fileTraverser(files);
    wxDir(Directory).Traverse(fileTraverser);

    for(int i=0; i<(int)files.Count(); i++)
    {
        wxRemoveFile(files[i]);
    }

    files.Clear();

    wxDirTraverserDirectories dirTraverser(files);
    wxDir(Directory).Traverse(dirTraverser);
    // Reverse Sort to make sure first delte folders without subfolders
    files.Sort(true);

    for(int i=0; i<(int)files.Count(); i++)
    {
        wxRmDir(files[i]);
    }

    wxRmDir(Directory);
}

//(*IdInit(sPATCHDialog)
const long sPATCHDialog::ID_BITMAPBUTTON4 = wxNewId();
const long sPATCHDialog::ID_HTMLWINDOW1 = wxNewId();
const long sPATCHDialog::ID_BITMAPBUTTON1 = wxNewId();
const long sPATCHDialog::ID_BITMAPBUTTON3 = wxNewId();
const long sPATCHDialog::ID_GAUGE1 = wxNewId();
const long sPATCHDialog::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(sPATCHDialog,wxDialog)
    //(*EventTable(sPATCHDialog)
    //*)
END_EVENT_TABLE()

sPATCHDialog::sPATCHDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(sPATCHDialog)
    wxFlexGridSizer* FlexGridSizer_Main;
    wxGridSizer* GridSizer_Buttons;

    Create(parent, wxID_ANY, _("Perfect World Patcher"), wxDefaultPosition, wxDefaultSize, 0, _T("wxID_ANY"));
    FlexGridSizer_Main = new wxFlexGridSizer(5, 1, 0, 0);
    BitmapButton_Close = new wxBitmapButton(this, ID_BITMAPBUTTON4, wxBitmap(wxImage(_T("skin/btn_close.png"))), wxDefaultPosition, wxSize(16,14), 0, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
    BitmapButton_Close->SetBitmapDisabled(wxBitmap(wxImage(_T("skin/btn_close_bw.png"))));
    BitmapButton_Close->SetBitmapSelected(wxBitmap(wxImage(_T("skin/btn_close_ck.png"))));
    BitmapButton_Close->SetDefault();
    BitmapButton_Close->Disable();
    FlexGridSizer_Main->Add(BitmapButton_Close, 1, wxTOP|wxBOTTOM|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    HtmlWindow_Notes = new wxHtmlWindow(this, ID_HTMLWINDOW1, wxDefaultPosition, wxSize(384,216), 0, _T("ID_HTMLWINDOW1"));
    HtmlWindow_Notes->Hide();
    FlexGridSizer_Main->Add(HtmlWindow_Notes, 1, wxLEFT|wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    GridSizer_Buttons = new wxGridSizer(2, 0, 0, 0);
    BitmapButton_Update = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxBitmap(wxImage(_T("skin/btn_update.png"))), wxDefaultPosition, wxSize(95,27), 0, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
    BitmapButton_Update->SetBitmapDisabled(wxBitmap(wxImage(_T("skin/btn_update_bw.png"))));
    BitmapButton_Update->SetBitmapSelected(wxBitmap(wxImage(_T("skin/btn_update_ck.png"))));
    BitmapButton_Update->SetDefault();
    BitmapButton_Update->Disable();
    GridSizer_Buttons->Add(BitmapButton_Update, 1, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BitmapButton_Play = new wxBitmapButton(this, ID_BITMAPBUTTON3, wxBitmap(wxImage(_T("skin/btn_play.png"))), wxDefaultPosition, wxSize(95,27), 0, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
    BitmapButton_Play->SetBitmapDisabled(wxBitmap(wxImage(_T("skin/btn_play_bw.png"))));
    BitmapButton_Play->SetBitmapSelected(wxBitmap(wxImage(_T("skin/btn_play_ck.png"))));
    BitmapButton_Play->SetDefault();
    BitmapButton_Play->Disable();
    GridSizer_Buttons->Add(BitmapButton_Play, 1, wxTOP|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 4);
    FlexGridSizer_Main->Add(GridSizer_Buttons, 1, wxRIGHT|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    Gauge_Progress = new wxGauge(this, ID_GAUGE1, 100, wxDefaultPosition, wxSize(300,8), 0, wxDefaultValidator, _T("ID_GAUGE1"));
    Gauge_Progress->SetForegroundColour(wxColour(0,255,0));
    Gauge_Progress->SetBackgroundColour(wxColour(0,0,64));
    FlexGridSizer_Main->Add(Gauge_Progress, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer_Main);
    Timer_Progress.SetOwner(this, ID_TIMER1);
    Timer_Progress.Start(100, true);
    FlexGridSizer_Main->Fit(this);
    FlexGridSizer_Main->SetSizeHints(this);
    Center();

    Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&sPATCHDialog::OnBitmapButton_CloseClick);
    Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&sPATCHDialog::OnBitmapButton_UpdateClick);
    Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&sPATCHDialog::OnBitmapButton_PlayClick);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&sPATCHDialog::OnTimer_ProgressTrigger);
    Connect(wxID_ANY,wxEVT_PAINT,(wxObjectEventFunction)&sPATCHDialog::OnPaint);
    //*)

    BackgroundImage = wxBitmap(wxT("skin/window.png"), wxBITMAP_TYPE_PNG);
    //HtmlWindow_Notes->SetBackgroundImage(wxBitmap(wxT("skin/index/background.jpg", wxBITMAP_TYPE_JPEG));
    SetIcon(wxIcon(wxT("skin/window.ico"), wxBITMAP_TYPE_ICO));

    // Add support for handling files starting with http: or ftp:
    wxFileSystem::AddHandler(new wxInternetFSHandler);

    CheckVersion();
}

sPATCHDialog::~sPATCHDialog()
{
    //(*Destroy(sPATCHDialog)
    //*)

    // TODO (#1#): Avoiding Memory Leaks: http://wiki.wxwidgets.org/Avoiding_Memory_Leaks
    /*
    // It seems wx objects don't nee to be deleted...
    delete &BackgroundImage;
    delete &PatchServer;
    delete &cVersion;
    delete &aVersions;
    delete &Status;
    */
}

void sPATCHDialog::CheckVersion()
{
    Timer_Progress.Start();

    try
    {
        Status = wxT("Checking for Updates ...");
        this->Refresh();

        wxTextFile f;
        f.Open(wxT("version.sw"));
        cVersion = f.GetFirstLine();
        f.Close();

        f.Open(wxT("patcher.ini"));
        for(wxString line=f.GetFirstLine(); !f.Eof(); line=f.GetNextLine())
        {
            if(line.StartsWith(wxT("patch_server=")))
            {
                if(line.AfterFirst(L'=').StartsWith(wxT("http://")))
                {
                    line.AfterFirst(L'=').StartsWith(wxT("http://"), &PatchServer);
                }
                else
                {
                    PatchServer = line.AfterFirst(L'=');
                }
            }

            if(line.StartsWith(wxT("patch_notes=")))
            {
                if(HtmlWindow_Notes->LoadPage(line.AfterFirst(L'=')))
                {
                    HtmlWindow_Notes->Show();
                    this->GetSizer()->Fit(this);
                    this->Center();
                }
            }
        }
        f.Close();

        wxHTTP webResponse;
        wxString host = PatchServer.BeforeFirst(L'/');
        wxUint16 port = 80;

        if(host.Contains(wxT(":")))
        {
            port = wxAtoi(host.AfterLast(':'));
            host = host.BeforeLast(':');
        }

        if(webResponse.Connect(host, port))
        {
            wxInputStream *httpStream = webResponse.GetInputStream(wxT("/") + PatchServer.AfterFirst(L'/') + wxT("versions.sw"));

            if(webResponse.GetError() == wxPROTO_NOERR)
            {
                wxTextInputStream sr(*httpStream);
                wxString line;
                while(!httpStream->Eof())
                {
                    line = sr.ReadLine();
                    if(line.Contains(wxT("=")))
                    {
                        aVersions.Add(line);
                    }
                }
                Status = wxT("Update Check Complete!");
            }
            else
            {
                Status = wxT("Loading Server Patch-List Failed!");
            }

            wxDELETE(httpStream);
            webResponse.Close();
        }
        else
        {
            Status = wxT("Connecting to Host Failed!");
        }
    }
    catch(...)
    {
        Status = wxT("Unknown Connection Error!");
    }

    if(aVersions.Count()>0 && wxAtoi(cVersion)<wxAtoi(aVersions[aVersions.Count()-1]))
    {
        BitmapButton_Update->Enable(true);
    }

    Timer_Progress.Stop();
    BitmapButton_Close->Enable(true);
    BitmapButton_Play->Enable(true);
    Gauge_Progress->SetValue(100);
}

void sPATCHDialog::ApplyPatches()
{
    if(wxDirExists(wxT("PATCHES")))
    {
        wxArrayString files;
        wxDirTraverserFiles fileTraverser(files);
        wxDirTraverserDirectories dirTraverser(files);

        //######################################################################
        //##### EXTRACT PATCHES ################################################
        //######################################################################

        if(wxDirExists(wxT("FILES")))
        {
            wxDeldir(wxT("FILES"));
        }
        wxMkdir(wxT("FILES"));

        files.Clear();
        wxDir(wxT("PATCHES")).Traverse(fileTraverser, wxT("*.xup"), wxDIR_DEFAULT);
        for(int i=0; i<(int)files.Count(); i++)
    	{
            if(files[i].EndsWith(wxT(".xup")))
            {
                Status = wxT("Extracting Patch (") + files[i].AfterLast(L'\\') + wxT(") ...");
                this->Refresh();
                wxProcess::Open(wxT("tools\\sza.exe x \"") + files[i] + wxT("\" -o\"FILES\" -y"), wxEXEC_SYNC | wxEXEC_NODISABLE);
            }
        }

        wxDeldir(wxT("PATCHES"));

        //######################################################################
        //##### MOVING FILES ###################################################
        //######################################################################

        Status = wxT("Patching Client Files ...");
        this->Refresh();
        wxProcess::Open(wxT("tools\\rcopy.exe \"FILES\" \"..\" /MOVE /S /IS"), wxEXEC_SYNC | wxEXEC_NODISABLE);

        // rcopy removes "FILES" directory automatically
        //wxDeldir(wxT("FILES");

        //######################################################################
        //##### UPDATING PCK ###################################################
        //######################################################################

        files.Clear();
        wxDir(wxT("..\\element")).Traverse(dirTraverser, wxT("*.files"), wxDIR_DEFAULT);
        for(int i=0; i<(int)files.Count(); i++)
    	{
            if(files[i].EndsWith(wxT(".files")))
            {
                if(files[i].EndsWith(wxT(".pck.files")))
                {
                    Status = wxT("Updating PCK File (") + files[i].AfterLast('\\').BeforeLast('.') + wxT(") ...");
                    wxProcess::Open(wxT("tools\\sPCK.exe -pw -a \"..\\element\\") + files[i].AfterLast(L'\\') + wxT("\""), wxEXEC_SYNC | wxEXEC_NODISABLE);
                }
                if(files[i].EndsWith(wxT(".pck.b64.files")))
                {
                    Status = wxT("Updating PCK File (") + files[i].AfterLast('\\').BeforeLast('.').BeforeLast('.') + wxT(") ...");
                    wxProcess::Open(wxT("tools\\sPCK.exe -pw -ap \"..\\element\\") + files[i].AfterLast(L'\\') + wxT("\""), wxEXEC_SYNC | wxEXEC_NODISABLE);
                }
                this->Refresh();
                wxDeldir(files[i]);
            }
        }
    }
}

void sPATCHDialog::OnBitmapButton_UpdateClick(wxCommandEvent& event)
{
    if(aVersions.Count()>0 && wxAtoi(cVersion)<wxAtoi(aVersions[aVersions.Count()-1]))
    {
        Timer_Progress.Start();

        BitmapButton_Close->Enable(false);
        BitmapButton_Update->Enable(false);
        BitmapButton_Play->Enable(false);

        try
        {
            //######################################################################
            //##### DOWNLOAD PATCHES ###############################################
            //######################################################################

            if(wxDirExists(wxT("PATCHES")))
            {
                wxDeldir(wxT("PATCHES"));
            }
            wxMkdir(wxT("PATCHES"));

            int version = wxAtoi(cVersion);

            for(int i=0; i<(int)aVersions.Count(); i++)
            {
                if(version < wxAtoi(aVersions[i].BeforeFirst(L'=')))
                {
                    Status = wxT("Downloading (") + aVersions[i].AfterFirst(L'=') + wxT(") ...");
                    this->Refresh();
                    wxProcess::Open(wxT("tools\\wget.exe -q -O \"PATCHES\\") + wxString::Format(wxT("%08i"), i) + wxT(".xup\" \"") + PatchServer + aVersions[i].AfterFirst('=') + wxT("\""), wxEXEC_SYNC | wxEXEC_NODISABLE);
                }
            }

            //######################################################################
            //##### APPLY UPDATE ###################################################
            //######################################################################

            ApplyPatches();

            //######################################################################
            //##### FINISHING UPDATE ###############################################
            //######################################################################

            cVersion = aVersions[aVersions.Count()-1].BeforeFirst(L'=');

            wxTextFile f;
            f.Open(wxT("version.sw"));
            f.Clear();
            f.AddLine(cVersion);
            f.Write(wxTextFileType_None);
            f.Close();

            Status = wxT("Update Complete!");
        }
        catch(...)
        {
            Status = wxT("Update Failed!");
            BitmapButton_Update->Enable(true);
        }

        BitmapButton_Close->Enable(true);
        BitmapButton_Play->Enable(true);
        Timer_Progress.Stop();
        Gauge_Progress->SetValue(100);
        this->Refresh();
    }
}

void sPATCHDialog::OnPaint(wxPaintEvent& event)
{
    int origin = this->GetSize().GetHeight()-84;

	wxPaintDC dc(this);

	/* TODO (#1#): Drawing a Bitmap on the Background causes flickr */

    dc.DrawBitmap(BackgroundImage, 0, 0, FALSE);

    dc.SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT(""), wxFONTENCODING_DEFAULT));

    // Draw Text Shadows
    dc.SetTextForeground(wxColour(0, 0, 0));
	dc.DrawText(wxT("Client Version:"), 7, 5+origin);
	dc.DrawText(wxT("Available Version:"), 7, 25+origin);
	// Draw Text
    dc.SetTextForeground(wxColour(255, 255, 192));
	dc.DrawText(wxT("Client Version:"), 6, 4+origin);
	dc.DrawText(wxT("Available Version:"), 6, 24+origin);

	dc.SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT(""), wxFONTENCODING_DEFAULT));

	// Draw Text Shadows
    dc.SetTextForeground(wxColour(0, 0, 0));
    dc.DrawText(cVersion, 125, 5+origin);
	if(aVersions.Count() > 0)
	{
        dc.DrawText(aVersions[aVersions.Count()-1].BeforeFirst('='), 125, 25+origin);
	}
	else
	{
	    dc.DrawText(wxT("unknown"), 125, 25+origin);
	}
    // Draw Text
    dc.SetTextForeground(wxColour(255, 255, 192));

	dc.DrawText(cVersion, 124, 4+origin);
	if(aVersions.Count() > 0)
	{
        dc.DrawText(aVersions[aVersions.Count()-1].BeforeFirst('='), 124, 24+origin);
	}
	else
	{
	    dc.DrawText(wxT("unknown"), 124, 24+origin);
	}

	dc.SetFont(wxFont(8, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT(""), wxFONTENCODING_DEFAULT));

    // Draw Text Shadows
    dc.SetTextForeground(wxColour(0, 0, 0));
    dc.DrawText(Status, 7, 55+origin);
    // Draw Text
    dc.SetTextForeground(wxColour(255, 255, 192));
	dc.DrawText(Status, 6, 54+origin);
}

void sPATCHDialog::OnBitmapButton_PlayClick(wxCommandEvent& event)
{
    wxFileName::SetCwd(wxT("..\\element"));
    wxExecute(wxT("elementclient.exe game:cpw console:1"));
    //wxProcess::Open(wxT("..\\element\\elementclient.exe game:cpw console:1", wxEXEC_ASYNC | wxEXEC_NODISABLE);
    Close();
}

void sPATCHDialog::OnTimer_ProgressTrigger(wxTimerEvent& event)
{
    Gauge_Progress->Pulse();
}

void sPATCHDialog::OnBitmapButton_CloseClick(wxCommandEvent& event)
{
    Close();
}
