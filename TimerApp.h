#pragma once

#include "resource.h"
#include <wx/wx.h>

class TimerFrame : public wxFrame
{
public:
    TimerFrame(const wxString& title);

private:
    wxPanel* panel;
    wxStaticText* headlineText;
    wxTextCtrl* inputField;
    wxButton* addButton;
    wxCheckListBox* checkListBox;
    wxButton* clearButton;

    wxMenu* menuFile;
    wxMenuBar* menuBar;

    void createControls();
    void BindEventHandlers();
    void addSavedItems();

    void OnAddButtonClicked(wxCommandEvent& event);
    void OnInputEnter(wxCommandEvent& event);
    void AddTaskFromInput();

    void DeleteSelectedItem(wxKeyEvent& event);

    void OnClearButtonClicked(wxCommandEvent& event);

    void OnWindowClosed(wxCloseEvent& event);

    void OnAbout(wxCommandEvent& event);
};