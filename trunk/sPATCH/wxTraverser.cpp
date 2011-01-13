#include "wxTraverser.h"

//##############################################################################

wxDirTraverserFiles::wxDirTraverserFiles(wxArrayString& files) : m_files(files)
{
}
        
wxDirTraverseResult wxDirTraverserFiles::OnFile(const wxString& filename)
{
    m_files.Add(filename);
    return wxDIR_CONTINUE;
}

wxDirTraverseResult wxDirTraverserFiles::OnDir(const wxString& dirname)
{
    return wxDIR_CONTINUE;
}

//##############################################################################

wxDirTraverserDirectories::wxDirTraverserDirectories(wxArrayString& files) : m_files(files)
{
}
        
wxDirTraverseResult wxDirTraverserDirectories::OnFile(const wxString& filename)
{
    return wxDIR_CONTINUE;
}

wxDirTraverseResult wxDirTraverserDirectories::OnDir(const wxString& dirname)
{
    m_files.Add(dirname);
    return wxDIR_CONTINUE;
}

//##############################################################################

wxDirTraverserAll::wxDirTraverserAll(wxArrayString& files) : m_files(files)
{
}
        
wxDirTraverseResult wxDirTraverserAll::OnFile(const wxString& filename)
{
    m_files.Add(filename);
    return wxDIR_CONTINUE;
}

wxDirTraverseResult wxDirTraverserAll::OnDir(const wxString& dirname)
{
    m_files.Add(dirname);
    return wxDIR_CONTINUE;
}
