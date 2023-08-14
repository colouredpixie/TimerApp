#pragma once

#include "resource.h"
#include <wx/wx.h>

enum
{
    ID_Hello = 1
};

class TimerApp : public wxApp
{
public:
    virtual bool OnInit();
};

class TimerFrame : public wxFrame
{
public:
    TimerFrame();

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};