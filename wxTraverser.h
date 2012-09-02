#include <wx/wx.h>
#include <wx/dir.h>

class wxDirTraverserFiles : public wxDirTraverser
{
    public:
        wxDirTraverserFiles(wxArrayString& files);
    private:
        wxArrayString& m_files;
    virtual wxDirTraverseResult OnFile(const wxString& filename);
    virtual wxDirTraverseResult OnDir(const wxString& dirname);
};

class wxDirTraverserDirectories : public wxDirTraverser
{
    public:
        wxDirTraverserDirectories(wxArrayString& files);
    private:
        wxArrayString& m_files;
    virtual wxDirTraverseResult OnFile(const wxString& filename);
    virtual wxDirTraverseResult OnDir(const wxString& dirname);
};

class wxDirTraverserAll : public wxDirTraverser
{
    public:
        wxDirTraverserAll(wxArrayString& files);
    private:
        wxArrayString& m_files;
    virtual wxDirTraverseResult OnFile(const wxString& filename);
    virtual wxDirTraverseResult OnDir(const wxString& dirname);
};
