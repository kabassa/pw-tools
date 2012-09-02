#include "sPATCHApp.h"

//(*AppHeaders
#include "sPATCHMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(sPATCHApp);

bool sPATCHApp::OnInit()
{
    if(argc == 2)
    {
        // Convert second parameter argv[1] from char* to wxString
        wxString patchDir(argv[1], wxConvUTF8);

        // Check if path is a valid directory
        if(wxDirExists(patchDir))
        {
            //wxProcess::Open(wxT("tools\\sPCK.exe -cp \"") + patchDir + wxT("\""), wxEXEC_NOHIDE);
            wxShell(wxString(argv[0]).BeforeLast('\\') + wxT("\\tools\\sPCK.exe -pw -cp \"") + patchDir + wxT("\""));
            return false;
        }
        else
        {
            wxMessageBox(wxT("Enter a valid directory to create a patch!"));
            return false;
        }
    }

    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	sPATCHDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;
}
