///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include "visualisation.h"
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/combobox.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/menu.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class MainWindowGen
///////////////////////////////////////////////////////////////////////////////
class MainWindowGen : public wxFrame
{
	private:
		wxBoxSizer* bSizer1;

	protected:
		VisualisationControl* visualiser;
		wxButton* stopButton;
		wxStaticText* m_staticText4;
		wxComboBox* deviceCombo;
		wxStaticText* m_staticText5;
		wxComboBox* fluxSourceSinkCombo;
		wxStaticText* m_staticText51;
		wxChoice* formatChoice;
		wxCheckBox* highDensityToggle;
		wxStaticText* m_staticText7;
		wxTextCtrl* cylindersText;
		wxStaticText* m_staticText9;
		wxTextCtrl* headsText;
		wxButton* readFluxButton;
		wxButton* readImageButton;
		wxButton* writeFluxButton;
		wxButton* writeImageButton;
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;

		// Virtual event handlers, override them in your derived class
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnExit( wxCommandEvent& event ) { event.Skip(); }


	public:

		MainWindowGen( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 466,528 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~MainWindowGen();

};

