#include <wx/wx.h>

class Base64
{
    public: static wxString Decode(wxString data, wxCSConv encoding);
    public: static wxString Encode(wxString data, wxCSConv encoding);
};
