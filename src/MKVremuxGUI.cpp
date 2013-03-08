#include "MKVremuxGUI.h"

//(*InternalHeaders(MKVremuxGUI)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(MKVremuxGUI)
const long MKVremuxGUI::ID_STATICTEXT1 = wxNewId();
const long MKVremuxGUI::ID_LISTBOX1 = wxNewId();
const long MKVremuxGUI::ID_BUTTON1 = wxNewId();
const long MKVremuxGUI::ID_BUTTON2 = wxNewId();
const long MKVremuxGUI::ID_STATICLINE1 = wxNewId();
const long MKVremuxGUI::ID_CHECKBOX1 = wxNewId();
const long MKVremuxGUI::ID_CHECKBOX4 = wxNewId();
const long MKVremuxGUI::ID_CHECKBOX2 = wxNewId();
const long MKVremuxGUI::ID_CHECKBOX3 = wxNewId();
const long MKVremuxGUI::ID_STATICLINE2 = wxNewId();
const long MKVremuxGUI::ID_BUTTON3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(MKVremuxGUI,wxDialog)
	//(*EventTable(MKVremuxGUI)
	//*)
END_EVENT_TABLE()

MKVremuxGUI::MKVremuxGUI(wxWindow* parent,wxWindowID id,const wxPoint& pos)
{
	//(*Initialize(MKVremuxGUI)
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, _("MKVstripGUI"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	Move(wxDefaultPosition);
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUBAR));
	wxIcon ico;
	wxMemoryInputStream* ResourceMemoryStream = new wxMemoryInputStream(RESOURCES::APP_ICO.data, RESOURCES::APP_ICO.length);
	ico.CopyFromBitmap(wxBitmap(wxImage(*ResourceMemoryStream, wxBITMAP_TYPE_ICO)));
	wxDELETE(ResourceMemoryStream);
	//ResourceMemoryStream = NULL;
	SetIcon(ico);
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Tasks"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	StaticText1->Disable();
	wxFont StaticText1Font(14,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
	StaticText1->SetFont(StaticText1Font);
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ListBoxTasks = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
	ListBoxTasks->SetMinSize(wxSize(360,240));
	FlexGridSizer1->Add(ListBoxTasks, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	ButtonAdd = new wxButton(this, ID_BUTTON1, _("Add Task(s)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer1->Add(ButtonAdd, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonRemove = new wxButton(this, ID_BUTTON2, _("Remove Task(s)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer1->Add(ButtonRemove, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer1, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 6);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	FlexGridSizer1->Add(StaticLine1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxButtons = new wxCheckBox(this, ID_CHECKBOX1, _("Remove Buttons"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	CheckBoxButtons->SetValue(true);
	FlexGridSizer1->Add(CheckBoxButtons, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxChapters = new wxCheckBox(this, ID_CHECKBOX4, _("Remove Chapters"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
	CheckBoxChapters->SetValue(true);
	FlexGridSizer1->Add(CheckBoxChapters, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxMetadata = new wxCheckBox(this, ID_CHECKBOX2, _("Remove Metadata"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
	CheckBoxMetadata->SetValue(true);
	FlexGridSizer1->Add(CheckBoxMetadata, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	CheckBoxAttachements = new wxCheckBox(this, ID_CHECKBOX3, _("Remove Attachements"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
	CheckBoxAttachements->SetValue(true);
	FlexGridSizer1->Add(CheckBoxAttachements, 1, wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
	FlexGridSizer1->Add(StaticLine2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonRemux = new wxButton(this, ID_BUTTON3, _("Remux"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer1->Add(ButtonRemux, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	Center();

	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MKVremuxGUI::OnButtonAddClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MKVremuxGUI::OnButtonRemoveClick);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&MKVremuxGUI::OnButtonRemuxClick);
	//*)
}

MKVremuxGUI::~MKVremuxGUI()
{
	//(*Destroy(MKVremuxGUI)
	//*)
}


void MKVremuxGUI::OnButtonAddClick(wxCommandEvent& event)
{

}

void MKVremuxGUI::OnButtonRemoveClick(wxCommandEvent& event)
{

}

void MKVremuxGUI::OnButtonRemuxClick(wxCommandEvent& event)
{
    for(unsigned int t=0; t<ListBoxTasks->GetCount(); t++)
    {
        // "mkvmerge -o"
        // output file
        // "/home/ronny/Desktop/bakemonogatari-clean.mkv"

        if(CheckBoxButtons->GetValue())
        {
            // " --no-buttons"
        }
        if(CheckBoxChapters->GetValue())
        {
            // " --no-chapters"
        }
        if(CheckBoxMetadata->GetValue())
        {
            // " --no-global-tags --no-track-tags"
        }
        if(CheckBoxAttachements->GetValue())
        {
            // " --no-attachments"
        }

        // input file
        // "/home/ronny/Desktop/bakemonogatari.mkv"
    }
}
