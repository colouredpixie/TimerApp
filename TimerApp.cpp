#include "TimerApp.h"
#include "SDL.h"

wxIMPLEMENT_APP(TimerApp);

bool TimerApp::OnInit() {
    TimerFrame* frame = new TimerFrame();
    frame->Show(true);
    return true;
}

TimerFrame::TimerFrame()
    : wxFrame(NULL, wxID_ANY, "Hello World")
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &TimerFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &TimerFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &TimerFrame::OnExit, this, wxID_EXIT);    //Bind(wxEVT_MENU, [=](wxCommandEvent&) { Close(true); }, wxID_EXIT);
}

// event handlers. TODO: channnnge to lambdas?
void TimerFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void TimerFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

void TimerFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}


