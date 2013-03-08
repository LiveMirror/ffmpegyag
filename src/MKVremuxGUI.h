#ifndef MKVREMUXGUI_H
#define MKVREMUXGUI_H

//(*Headers(MKVremuxGUI)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/checkbox.h>
#include <wx/listbox.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/frame.h>
//*)

#include <wx/dialog.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/mstream.h>
#include <wx/icon.h>

#include "resource.h"

class MKVremuxGUI: public wxDialog
{
	public:

		MKVremuxGUI(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition);
		virtual ~MKVremuxGUI();

		//(*Declarations(MKVremuxGUI)
		wxButton* ButtonRemux;
		wxCheckBox* CheckBoxChapters;
		wxButton* ButtonRemove;
		wxCheckBox* CheckBoxMetadata;
		wxStaticText* StaticText1;
		wxCheckBox* CheckBoxAttachements;
		wxButton* ButtonAdd;
		wxStaticLine* StaticLine2;
		wxCheckBox* CheckBoxButtons;
		wxStaticLine* StaticLine1;
		wxListBox* ListBoxTasks;
		//*)

	protected:

		//(*Identifiers(MKVremuxGUI)
		static const long ID_STATICTEXT1;
		static const long ID_LISTBOX1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_STATICLINE1;
		static const long ID_CHECKBOX1;
		static const long ID_CHECKBOX4;
		static const long ID_CHECKBOX2;
		static const long ID_CHECKBOX3;
		static const long ID_STATICLINE2;
		static const long ID_BUTTON3;
		//*)

	private:

		//(*Handlers(MKVremuxGUI)
		void OnButtonAddClick(wxCommandEvent& event);
		void OnButtonRemoveClick(wxCommandEvent& event);
		void OnButtonRemuxClick(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
