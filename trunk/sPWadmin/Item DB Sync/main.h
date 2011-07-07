#include <wx/wx.h>
#include <wx/app.h>
#include <wx/txtstrm.h>
#include <wx/textfile.h>
#include <wx/protocol/http.h>

class pckApp : public wxApp
{
    public: virtual bool OnInit();
};
