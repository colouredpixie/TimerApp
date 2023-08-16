#include "TimerApp.h"
#include <vector>
#include <string>
#include "Item.h"
#include "App.h"

TimerFrame::TimerFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{    
    createControls();
    BindEventHandlers();
    addSavedItems(); 
}

void TimerFrame::createControls()
{
    this->SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER)); // no resize window style

    wxFont headlineFont(wxFontInfo(wxSize(0, 24)).Bold());
    wxFont mainFont(wxFontInfo(wxSize(0, 12)));

    panel = new wxPanel(this);
    panel->SetFont(mainFont);

    headlineText = new wxStaticText(panel, wxID_ANY, "Your timers", wxPoint(0, 22), wxSize(450, -1), wxALIGN_CENTER_HORIZONTAL);
    headlineText->SetFont(headlineFont);

    inputField = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(25, 80), wxSize(300, 30), wxTE_PROCESS_ENTER);
    addButton = new wxButton(panel, wxID_ANY, "Add", wxPoint(325, 80), wxSize(100, 30));
    checkListBox = new wxCheckListBox(panel, wxID_ANY, wxPoint(25, 120), wxSize(400, 275)); //TODO: add timer, TODO: checklist to sort by time
    clearButton = new wxButton(panel, wxID_ANY, "Clear", wxPoint(25, 405), wxSize(100, 30));
    
    menuFile = new wxMenu;
    menuFile->Append(wxID_ABOUT);
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to the Timer App!");
}

void TimerFrame::BindEventHandlers()
{
    addButton->Bind(wxEVT_BUTTON, &TimerFrame::OnAddButtonClicked, this);
    inputField->Bind(wxEVT_TEXT_ENTER, &TimerFrame::OnInputEnter, this);
    
    checkListBox->Bind(wxEVT_KEY_DOWN, &TimerFrame::DeleteSelectedItem, this);
    
    clearButton->Bind(wxEVT_BUTTON, &TimerFrame::OnClearButtonClicked, this);

    this->Bind(wxEVT_CLOSE_WINDOW, &TimerFrame::OnWindowClosed, this);

    Bind(wxEVT_MENU, &TimerFrame::OnAbout, this, wxID_ABOUT);
    this->Bind(wxEVT_MENU, [=](wxCommandEvent&) { Close(true); }, wxID_EXIT); //Using lambda for a simple function binding  
}

void TimerFrame::addSavedItems()
{
    std::vector<Item> items = loadFromFile("data.txt");
    for (const Item& item : items ) {
        int index = checkListBox->GetCount();
        checkListBox->Insert(item.m_description, index);
        checkListBox->Check(index, item.m_done);
    }

}

void TimerFrame::OnAddButtonClicked(wxCommandEvent& event)
{
    AddTaskFromInput();
}

void TimerFrame::OnInputEnter(wxCommandEvent& event)
{
    AddTaskFromInput();
}

void TimerFrame::AddTaskFromInput()
{
    wxString description = inputField->GetValue();
    if (!description.IsEmpty()) {
        checkListBox->Insert(description, checkListBox->GetCount());
        inputField->Clear();
    }

    inputField->SetFocus();
}

void TimerFrame::DeleteSelectedItem(wxKeyEvent& event)
{
    int key = event.GetKeyCode();
    int selectedIndex = checkListBox->GetSelection();

    if (key == WXK_DELETE || key == WXK_NUMPAD_DELETE) {
        if (selectedIndex == wxNOT_FOUND) { return; }
        checkListBox->Delete(selectedIndex);
    }
    if (key == WXK_SPACE)
    {
        checkListBox->Check(selectedIndex, !checkListBox->IsChecked(selectedIndex));
    }
    if (key == WXK_DOWN)
    {
        if (checkListBox->GetSelection() < (checkListBox->GetCount() - 1)) // checkListBox->GetCount() returns number of items which is last index + 1
            checkListBox->SetSelection(selectedIndex + 1);
    }
    if (key == WXK_UP)
    {   
        if (checkListBox->GetSelection() > 0)
            checkListBox->SetSelection(selectedIndex - 1);
    }
}
void TimerFrame::OnClearButtonClicked(wxCommandEvent& event)
{
    if (checkListBox->IsEmpty()) { return; }

    wxMessageDialog dialog(this, "Are you sure you want to clear checked items?", "Clear", wxYES_NO);
    int result = dialog.ShowModal();
    // get count might return wrong number after clear?
    if (result == wxID_YES) {
        for (int i = 0; i < checkListBox->GetCount(); i++) {
            if (checkListBox->IsChecked(i)) {
                checkListBox->Delete(i);
            }
        }
        //checkListBox->Clear();
    }
}

void TimerFrame::OnWindowClosed(wxCloseEvent& event)
{
    std::vector<Item> items;

    for (int i = 0; i < checkListBox->GetCount(); i++) {
        std::string description = static_cast<std::string>(checkListBox->GetString(i));
        bool done = checkListBox->IsChecked(i);
        time_t startTime = 0;
        Item item(description, done, startTime);
        items.push_back(item);
    }

    saveToFile(items, "data.txt");
    event.Skip();
}

void TimerFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a simple timer app to note how much time has gone since the addition of an event",
        "About Timer App", wxOK | wxICON_INFORMATION);
}
