/***************************************************************
 * Name:      sPATCHMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2010-03-26
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef SPATCHMAIN_H
#define SPATCHMAIN_H

//(*Headers(sPATCHDialog)
#include <wx/sizer.h>
#include <wx/bmpbuttn.h>
#include <wx/dialog.h>
#include <wx/timer.h>
#include <wx/html/htmlwin.h>
#include <wx/gauge.h>
//*)

class sPATCHDialog: public wxDialog
{
    public:

        sPATCHDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~sPATCHDialog();

    private:

        wxBitmap BackgroundImage;
        wxString PatchServer;
    	wxString cVersion;
    	wxArrayString aVersions;
    	wxString Status;

        void CheckVersion();
        void ApplyPatches();

        //(*Handlers(sPATCHDialog)
        void OnBitmapButton_PlayClick(wxCommandEvent& event);
        void OnBitmapButton_UpdateClick(wxCommandEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnBitmapButton_CloseClick(wxCommandEvent& event);
        void OnTimer_ProgressTrigger(wxTimerEvent& event);
        //*)

        //(*Identifiers(sPATCHDialog)
        static const long ID_BITMAPBUTTON4;
        static const long ID_HTMLWINDOW1;
        static const long ID_BITMAPBUTTON1;
        static const long ID_BITMAPBUTTON3;
        static const long ID_GAUGE1;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(sPATCHDialog)
        wxHtmlWindow* HtmlWindow_Notes;
        wxTimer Timer_Progress;
        wxBitmapButton* BitmapButton_Update;
        wxBitmapButton* BitmapButton_Close;
        wxGauge* Gauge_Progress;
        wxBitmapButton* BitmapButton_Play;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // SPATCHMAIN_H
