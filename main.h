// RWPD decoding keys & signatures
#ifdef RWPD
#define FSIG_1 1305093103
#define FSIG_2 1453361591
#define KEY_1 711164174
#define KEY_2 839959661
#define ASIG_1 -1424846705
#define ASIG_2 -1289545470
#endif

// FW decoding keys & signatures
#ifdef FW
#define FSIG_1 1305093103
#define FSIG_2 1453361591
#define KEY_1 566434367
#define KEY_2 408690725
#define ASIG_1 -1526153788
#define ASIG_2 -2060097592
#endif

// ESO decoding keys & signatures
#ifdef ESO
#define FSIG_1 1305093103
#define FSIG_2 1453361591
#define KEY_1 -1228069623
#define KEY_2 1822409141
#define ASIG_1 1571301968
#define ASIG_2 2043846474
#endif

// JD decoding keys & signatures
#ifdef JD
#define FSIG_1 1305093103
#define FSIG_2 1453361591
#define KEY_1 -1466731422
#define KEY_2 -240896429
#define ASIG_1 -33685778
#define ASIG_2 -267534609
#endif

// PW decoding keys & signatures
#ifdef PW
#define FSIG_1 1305093103
#define FSIG_2 1453361591
#define KEY_1 -1466731422
#define KEY_2 -240896429
#define ASIG_1 -33685778
#define ASIG_2 -267534609
#endif

#include <wx/wx.h>
#include <wx/app.h>
#include <wx/datstrm.h>
#include <wx/wfstream.h>
#include <wx/mstream.h>
#include <wx/zstream.h>
#include <wx/buffer.h>
#include <wx/process.h>
#include <wx/textfile.h>
#include <wx/stdpaths.h>

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
