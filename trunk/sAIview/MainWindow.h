#pragma once

#include "LoadingScreen.h"
#include "TranslatorService.h"
#include "..\pwAPI\include\pw.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Summary for MainWindow
///
/// WARNING: If you change the name of this class, you will need to change the
///          'Resource File Name' property for the managed resource compiler tool
///          associated with all .resx files this class depends on.  Otherwise,
///          the designers will not be able to interact properly with localized
///          resources associated with this form.
/// </summary>
public ref class MainWindow : public System::Windows::Forms::Form
{
	public:
		MainWindow(void)
		{
			InitializeComponent();
			this->Icon = (Drawing::Icon^)((gcnew Resources::ResourceManager("sTools.icons", Reflection::Assembly::GetExecutingAssembly()))->GetObject("app"));

			Cursor = Windows::Forms::Cursors::WaitCursor;
			LoadingScreen^ initialize = gcnew LoadingScreen();
			initialize->Show();
			Application::DoEvents();

			skillReplace = loadSkillReplace("sAIview\\skill_replace.txt");
			GUID = 1;

			try
			{
				soap = gcnew TranslatorService::Soap();
				appID = "763743C8043FA427227700179E653860B731D443";
				from = "zh-CHS";
				to = "en";
				comboBox_language->Items->AddRange(soap->GetLanguagesForTranslate(appID));
				comboBox_language->SelectedItem = "en";
			}
			catch(...)
			{
				soap = nullptr;
				textBox_translation->Text = "TRANSLATION SERVICE UNAVAILABLE";
			}
			initialize->Close();
			Cursor = Windows::Forms::Cursors::Default;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}

		TranslatorService::Soap^ soap;
		String^ appID;
		String^ from;
		String^ to;
		Collections::SortedList^ skillReplace;

		private: PW::Data::AiPolicy::AiPolicy^ AI;
		private: int GUID;

		private: System::Windows::Forms::MenuStrip^  menuStrip_mainMenu;
		private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
		private: System::Windows::Forms::ToolStripMenuItem^  loadToolStripMenuItem;
		private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
		private: System::Windows::Forms::ListBox^  listBox_ActionController;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::ListBox^  listBox_ActionSet;
		private: System::Windows::Forms::Label^  label3;
		private: System::Windows::Forms::Label^  label4;
		private: System::Windows::Forms::ListBox^  listBox_Procedures;
		private: System::Windows::Forms::GroupBox^  groupBox1;
		private: System::Windows::Forms::GroupBox^  groupBox2;
		private: System::Windows::Forms::TextBox^  textBox_Condition;
		private: System::Windows::Forms::ComboBox^  comboBox_language;
		private: System::Windows::Forms::TextBox^  textBox_translation;
		private: System::Windows::Forms::Label^  label6;
		private: System::Windows::Forms::Button^  button_search;
		private: System::Windows::Forms::TextBox^  textBox_pattern;
		private: System::Windows::Forms::ComboBox^  comboBox_subCat;
		private: System::Windows::Forms::ComboBox^  comboBox_cat;
		private: System::Windows::Forms::Label^  label5;
		private: System::Windows::Forms::ToolStripMenuItem^  createDebug136ToolStripMenuItem;

		private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip_mainMenu = (gcnew System::Windows::Forms::MenuStrip());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->createDebug136ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->listBox_ActionController = (gcnew System::Windows::Forms::ListBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->listBox_ActionSet = (gcnew System::Windows::Forms::ListBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->listBox_Procedures = (gcnew System::Windows::Forms::ListBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox_Condition = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->comboBox_cat = (gcnew System::Windows::Forms::ComboBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->button_search = (gcnew System::Windows::Forms::Button());
			this->textBox_pattern = (gcnew System::Windows::Forms::TextBox());
			this->comboBox_subCat = (gcnew System::Windows::Forms::ComboBox());
			this->comboBox_language = (gcnew System::Windows::Forms::ComboBox());
			this->textBox_translation = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->menuStrip_mainMenu->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip_mainMenu
			// 
			this->menuStrip_mainMenu->BackColor = System::Drawing::SystemColors::Control;
			this->menuStrip_mainMenu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->toolStripMenuItem1});
			this->menuStrip_mainMenu->Location = System::Drawing::Point(0, 0);
			this->menuStrip_mainMenu->Name = L"menuStrip_mainMenu";
			this->menuStrip_mainMenu->Padding = System::Windows::Forms::Padding(0, 2, 2, 2);
			this->menuStrip_mainMenu->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->menuStrip_mainMenu->Size = System::Drawing::Size(632, 24);
			this->menuStrip_mainMenu->TabIndex = 0;
			this->menuStrip_mainMenu->Text = L"menuStrip1";
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->loadToolStripMenuItem, 
				this->saveToolStripMenuItem, this->createDebug136ToolStripMenuItem});
			this->toolStripMenuItem1->ImageScaling = System::Windows::Forms::ToolStripItemImageScaling::None;
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Padding = System::Windows::Forms::Padding(0);
			this->toolStripMenuItem1->Size = System::Drawing::Size(27, 20);
			this->toolStripMenuItem1->Text = L"File";
			this->toolStripMenuItem1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// loadToolStripMenuItem
			// 
			this->loadToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->loadToolStripMenuItem->Name = L"loadToolStripMenuItem";
			this->loadToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->loadToolStripMenuItem->Text = L"Load...";
			this->loadToolStripMenuItem->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->loadToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::click_load);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->saveToolStripMenuItem->Text = L"Export (1.3.6 Server)...";
			this->saveToolStripMenuItem->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::click_export);
			// 
			// createDebug136ToolStripMenuItem
			// 
			this->createDebug136ToolStripMenuItem->Name = L"createDebug136ToolStripMenuItem";
			this->createDebug136ToolStripMenuItem->Size = System::Drawing::Size(202, 22);
			this->createDebug136ToolStripMenuItem->Text = L"Generate Debug (1.3.6)...";
			this->createDebug136ToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::click_exportDebug);
			// 
			// listBox_ActionController
			// 
			this->listBox_ActionController->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->listBox_ActionController->FormattingEnabled = true;
			this->listBox_ActionController->Location = System::Drawing::Point(3, 58);
			this->listBox_ActionController->Name = L"listBox_ActionController";
			this->listBox_ActionController->Size = System::Drawing::Size(70, 303);
			this->listBox_ActionController->TabIndex = 2;
			this->listBox_ActionController->SelectedIndexChanged += gcnew System::EventHandler(this, &MainWindow::change_ActionController);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(76, 42);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(76, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Action Sets:";
			// 
			// listBox_ActionSet
			// 
			this->listBox_ActionSet->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->listBox_ActionSet->FormattingEnabled = true;
			this->listBox_ActionSet->HorizontalScrollbar = true;
			this->listBox_ActionSet->Location = System::Drawing::Point(79, 58);
			this->listBox_ActionSet->Name = L"listBox_ActionSet";
			this->listBox_ActionSet->Size = System::Drawing::Size(180, 303);
			this->listBox_ActionSet->TabIndex = 4;
			this->listBox_ActionSet->SelectedIndexChanged += gcnew System::EventHandler(this, &MainWindow::change_ActionSet);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(3, 16);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(64, 13);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Condition:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(3, 90);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(75, 13);
			this->label4->TabIndex = 2;
			this->label4->Text = L"Procedures:";
			// 
			// listBox_Procedures
			// 
			this->listBox_Procedures->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->listBox_Procedures->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->listBox_Procedures->FormattingEnabled = true;
			this->listBox_Procedures->HorizontalScrollbar = true;
			this->listBox_Procedures->ItemHeight = 16;
			this->listBox_Procedures->Location = System::Drawing::Point(6, 106);
			this->listBox_Procedures->Name = L"listBox_Procedures";
			this->listBox_Procedures->Size = System::Drawing::Size(352, 196);
			this->listBox_Procedures->TabIndex = 3;
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->textBox_Condition);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->listBox_Procedures);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Location = System::Drawing::Point(265, 53);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(364, 308);
			this->groupBox1->TabIndex = 5;
			this->groupBox1->TabStop = false;
			// 
			// textBox_Condition
			// 
			this->textBox_Condition->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_Condition->Cursor = System::Windows::Forms::Cursors::Default;
			this->textBox_Condition->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox_Condition->Location = System::Drawing::Point(6, 32);
			this->textBox_Condition->Multiline = true;
			this->textBox_Condition->Name = L"textBox_Condition";
			this->textBox_Condition->ScrollBars = System::Windows::Forms::ScrollBars::Horizontal;
			this->textBox_Condition->Size = System::Drawing::Size(352, 44);
			this->textBox_Condition->TabIndex = 1;
			this->textBox_Condition->WordWrap = false;
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->Controls->Add(this->comboBox_cat);
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->button_search);
			this->groupBox2->Controls->Add(this->textBox_pattern);
			this->groupBox2->Controls->Add(this->comboBox_subCat);
			this->groupBox2->Location = System::Drawing::Point(3, 393);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(626, 57);
			this->groupBox2->TabIndex = 8;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Search";
			// 
			// comboBox_cat
			// 
			this->comboBox_cat->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->comboBox_cat->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_cat->FormattingEnabled = true;
			this->comboBox_cat->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"Procedures", L"Conditions", L"AI Control Link"});
			this->comboBox_cat->Location = System::Drawing::Point(9, 27);
			this->comboBox_cat->Name = L"comboBox_cat";
			this->comboBox_cat->Size = System::Drawing::Size(98, 21);
			this->comboBox_cat->TabIndex = 0;
			this->comboBox_cat->SelectedIndexChanged += gcnew System::EventHandler(this, &MainWindow::change_searchCat);
			// 
			// label6
			// 
			this->label6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(263, 30);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(60, 13);
			this->label6->TabIndex = 2;
			this->label6->Text = L"Containing:";
			// 
			// button_search
			// 
			this->button_search->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button_search->Location = System::Drawing::Point(542, 25);
			this->button_search->Name = L"button_search";
			this->button_search->Size = System::Drawing::Size(75, 23);
			this->button_search->TabIndex = 4;
			this->button_search->Text = L"Find Next";
			this->button_search->UseVisualStyleBackColor = true;
			this->button_search->Click += gcnew System::EventHandler(this, &MainWindow::click_search);
			// 
			// textBox_pattern
			// 
			this->textBox_pattern->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_pattern->Location = System::Drawing::Point(329, 27);
			this->textBox_pattern->Name = L"textBox_pattern";
			this->textBox_pattern->Size = System::Drawing::Size(207, 20);
			this->textBox_pattern->TabIndex = 3;
			// 
			// comboBox_subCat
			// 
			this->comboBox_subCat->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->comboBox_subCat->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_subCat->FormattingEnabled = true;
			this->comboBox_subCat->Location = System::Drawing::Point(113, 27);
			this->comboBox_subCat->Name = L"comboBox_subCat";
			this->comboBox_subCat->Size = System::Drawing::Size(144, 21);
			this->comboBox_subCat->TabIndex = 1;
			// 
			// comboBox_language
			// 
			this->comboBox_language->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->comboBox_language->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_language->FormattingEnabled = true;
			this->comboBox_language->Location = System::Drawing::Point(3, 367);
			this->comboBox_language->Name = L"comboBox_language";
			this->comboBox_language->Size = System::Drawing::Size(70, 21);
			this->comboBox_language->TabIndex = 6;
			// 
			// textBox_translation
			// 
			this->textBox_translation->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_translation->Location = System::Drawing::Point(79, 367);
			this->textBox_translation->Name = L"textBox_translation";
			this->textBox_translation->Size = System::Drawing::Size(550, 20);
			this->textBox_translation->TabIndex = 7;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(0, 42);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(71, 13);
			this->label5->TabIndex = 9;
			this->label5->Text = L"Controllers:";
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(632, 453);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->textBox_translation);
			this->Controls->Add(this->comboBox_language);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->listBox_ActionSet);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->listBox_ActionController);
			this->Controls->Add(this->menuStrip_mainMenu);
			this->Name = L"MainWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L" sAIview";
			this->menuStrip_mainMenu->ResumeLayout(false);
			this->menuStrip_mainMenu->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		Collections::SortedList^ loadSkillReplace(String^ file)
		{
			Collections::SortedList^ skillTable = gcnew Collections::SortedList();

			String^ debug = Application::StartupPath + "\\" + file;
			StreamReader^ sr = gcnew StreamReader(Application::StartupPath + "\\" + file);

			String^ line;
			array<String^>^ pair;
			array<String^>^ seperator = gcnew array<String^>{"="};
			while(!sr->EndOfStream)
			{
				line = sr->ReadLine();
				if(!line->StartsWith("#") && line->Contains("="))
				{
					pair = line->Split(seperator, StringSplitOptions::RemoveEmptyEntries);
					if(pair->Length == 2)
					{
						skillTable->Add(Convert::ToInt32(pair[0]), Convert::ToInt32(pair[1]));
					}
				}
			}

			sr->Close();

			return skillTable;
		}


		private: System::Void click_load(System::Object^  sender, System::EventArgs^  e)
		{
			OpenFileDialog^ load = gcnew OpenFileDialog();
			load->Filter = "AI Policy (*.data)|*.data|All Files (*.*)|*.*";
			if(load->ShowDialog() == Windows::Forms::DialogResult::OK && File::Exists(load->FileName))
			{
				try
				{
					Cursor = Windows::Forms::Cursors::WaitCursor;

					listBox_ActionController->Items->Clear();
					listBox_ActionSet->Items->Clear();
					textBox_Condition->Clear();
					listBox_Procedures->Items->Clear();

					AI = gcnew PW::Data::AiPolicy::AiPolicy();
					AI->Load(load->FileName);

					for(int ac=0; ac<AI->action_controllers->Length; ac++)
					{
						listBox_ActionController->Items->Add(AI->action_controllers[ac]->id.ToString());
					}

					Cursor = Windows::Forms::Cursors::Default;
				}
				catch(Exception^ e)
				{
					Cursor = Windows::Forms::Cursors::Default;
					MessageBox::Show("IMPORT ERROR!\n\n" + e->Message);
				}
			}
		}

		private: System::Void click_export(System::Object^  sender, System::EventArgs^  e)
		{
			SaveFileDialog^ save = gcnew SaveFileDialog();
			save->Filter = "AI Policy (*.data)|*.data|All Files (*.*)|*.*";
			if(AI && save->ShowDialog() == Windows::Forms::DialogResult::OK && save->FileName != "")
			{
				Cursor = Windows::Forms::Cursors::WaitCursor;

				AI->GetFixedAiPolicy(skillReplace)->Save(save->FileName);

				Cursor = Windows::Forms::Cursors::Default;
			}
		}
		private: System::Void change_ActionController(System::Object^  sender, System::EventArgs^  e)
		{
			if(AI && listBox_ActionController->SelectedIndex > -1)
			{
				int ac = listBox_ActionController->SelectedIndex;

				listBox_ActionSet->Items->Clear();
				for(int i=0; i<AI->action_controllers[ac]->action_sets->Length; i++)
				{
					listBox_ActionSet->Items->Add("[" + AI->action_controllers[ac]->action_sets[i]->id.ToString() + "] " + AI->action_controllers[ac]->action_sets[i]->Name);
				}
				textBox_Condition->Clear();
				listBox_Procedures->Items->Clear();
			}
		}
		private: System::Void change_ActionSet(System::Object^  sender, System::EventArgs^  e)
		{
			if(AI && listBox_ActionController->SelectedIndex > -1 && listBox_ActionSet->SelectedIndex > -1)
			{
				int ac = listBox_ActionController->SelectedIndex;
				int as = listBox_ActionSet->SelectedIndex;

				textBox_Condition->Text = "IF{ " + AI->action_controllers[ac]->action_sets[as]->conditions->GetExpression() + " }";
				
				listBox_Procedures->Items->Clear();
				for(int i=0; i<AI->action_controllers[ac]->action_sets[as]->procedures->Length; i++)
				{
					listBox_Procedures->Items->Add("[" + i.ToString() + "] " + AI->action_controllers[ac]->action_sets[as]->procedures[i]->GetExpression());
				}

				if(soap && listBox_ActionSet->SelectedItem)
				{
					Cursor = Windows::Forms::Cursors::AppStarting;
					to = comboBox_language->SelectedItem->ToString();
					try
					{
						textBox_translation->Text = soap->Translate(appID, listBox_ActionSet->SelectedItem->ToString()->Split(gcnew array<wchar_t>{'\0'})[0], from, to);
					}
					catch(...)
					{
						textBox_translation->Text = "TRANSLATION FAILED";
					}
					Cursor = Windows::Forms::Cursors::Default;
				}
			}
		}
		private: System::Void change_searchCat(System::Object^  sender, System::EventArgs^  e)
		{
			if(comboBox_cat->SelectedIndex > -1)
			{
				comboBox_subCat->Items->Clear();

				if(comboBox_cat->SelectedItem->ToString() == "Conditions")
				{
					comboBox_subCat->Items->Add("All");
					comboBox_subCat->SelectedIndex = 0;
				}

				if(comboBox_cat->SelectedItem->ToString() == "AI Control Link")
				{
					comboBox_subCat->Items->AddRange
					(
						gcnew array<String^>
						{
							"Task",
							"Element NPC"
						}
					);
					comboBox_subCat->SelectedIndex = 0;
				}

				if(comboBox_cat->SelectedItem->ToString() == "Procedures")
				{
					comboBox_subCat->Items->AddRange
					(
						gcnew array<String^>
						{
							"Attack",
							"Cast_Skill",
							"Broadcast_Message",
							"Reset_Aggro",
							"Execute_ActionSet",
							"Disable_ActionSet",
							"Enable_ActionSet",
							"Create_Timer",
							"Remove_Timer",
							"Run_Away",
							"Be_Taunted",
							"Fade_Target",
							"Fade_Aggro",
							"Break",
							"NPC_Generator",
							"Initialize_Public_Counter",
							"Increment_Public_Counter",
							"Player_Aimed_NPC_Spawn"
						}
					);
					comboBox_subCat->SelectedIndex = 0;
				}
			}
		}
		private: System::Void click_search(System::Object^  sender, System::EventArgs^  e)
		{
			if(AI && comboBox_cat->SelectedIndex > -1)
			{
				// get initial search start
				int ac = 0;
				int as = 0;
				int pc = 0;

				if(listBox_ActionController->SelectedIndex > -1)
				{
					ac = listBox_ActionController->SelectedIndex;
				}
				if(listBox_ActionSet->SelectedIndex > -1)
				{
					as = listBox_ActionSet->SelectedIndex;
					if(comboBox_cat->SelectedItem->ToString() == "Conditions")
					{
						as++;
					}					
				}
				if(listBox_Procedures->SelectedIndex > -1)
				{
					pc = listBox_Procedures->SelectedIndex;
					if(comboBox_cat->SelectedItem->ToString() == "Procedures")
					{
						pc++;
					}	
				}

				for(ac; ac<AI->action_controllers->Length; ac++)
				{	
					if(comboBox_cat->SelectedItem->ToString() == "AI Control Link")
					{
						if(comboBox_subCat->SelectedIndex > -1 && textBox_pattern->Text != "")
						{
							int id = 0;
							if(comboBox_subCat->SelectedItem->ToString() == "Task")
							{
								MessageBox::Show("Task AI Control Link decryption currently not discovered...");
								return;
								id = Convert::ToInt32(textBox_pattern->Text)-55;
							}
							if(comboBox_subCat->SelectedItem->ToString() == "Element NPC")
							{
								id = Convert::ToInt32(textBox_pattern->Text);
							}
							if(AI->action_controllers[ac]->id == id)
							{
								listBox_ActionController->SelectedIndex = ac;
								return;
							}
						}
					}
					for(as; as<AI->action_controllers[ac]->action_sets->Length; as++)
					{
						if(comboBox_cat->SelectedItem->ToString() == "Conditions")
						{
							if(textBox_pattern->Text != "" && AI->action_controllers[ac]->action_sets[as]->conditions->GetExpression()->Contains(textBox_pattern->Text))
							{
								listBox_ActionController->SelectedIndex = ac;
								listBox_ActionSet->SelectedIndex = as;
								return;
							}
						}

						if(comboBox_cat->SelectedItem->ToString() == "Procedures" && comboBox_subCat->SelectedIndex > -1)
						{
							for(pc; pc<AI->action_controllers[ac]->action_sets[as]->procedures->Length; pc++)
							{
								if(AI->action_controllers[ac]->action_sets[as]->procedures[pc]->type == comboBox_subCat->SelectedIndex)
								{
									if(textBox_pattern->Text == "" || AI->action_controllers[ac]->action_sets[as]->procedures[pc]->GetExpression()->Contains(textBox_pattern->Text))
									{
										listBox_ActionController->SelectedIndex = ac;
										listBox_ActionSet->SelectedIndex = as;
										listBox_Procedures->SelectedIndex = pc;
										return;
									}
								}
							}
							pc = 0;
						}
					}
					as = 0;
				}
			}
			MessageBox::Show("Search reached End of File without Result!");
		}
		private: System::Void click_exportDebug(System::Object^  sender, System::EventArgs^  e)
		{
			SaveFileDialog^ save = gcnew SaveFileDialog();
			save->Filter = "AI Policy (*.data)|*.data|All Files (*.*)|*.*";
			if(save->ShowDialog() == Windows::Forms::DialogResult::OK && save->FileName != "")
			{
				Cursor = Windows::Forms::Cursors::WaitCursor;

				FileStream^ fw = gcnew FileStream(save->FileName, FileMode::Create, FileAccess::Write);
				BinaryWriter^ bw = gcnew BinaryWriter(fw);

				int action_controller_count = 2000;

				bw->Write(0); // 0
				bw->Write(action_controller_count);
				for(int ac=0; ac<action_controller_count; ac++)
				{
					bw->Write(0); // 0
					bw->Write(ac+1); // id
					bw->Write(1); // actionset count

					// write action set
					bw->Write(1); // version = 1
					bw->Write(0); // action set id
					bw->Write(gcnew array<unsigned char>{1, 0, 0}); // flags
					bw->Write(gcnew array<unsigned char>(128)); // name
					// write condition
					bw->Write(5); // operator id
					bw->Write(0); // argument bytes
					bw->Write(2); // condition type
						// rite right hand condition
						bw->Write(1); // operator id
						bw->Write(4); // argument bytes
						bw->Write((float)0.1); // argument value
						bw->Write(3); // condition type
						// return to parent condition
					bw->Write(4); // subnode2
					
					// write procedure
					bw->Write(1); // procedure count

					bw->Write(2); // broadcast
					bw->Write(46); // char count
					String^ message = "AI CONTROLLER ID: " + (ac+1).ToString("D5");
					bw->Write(Encoding::Unicode->GetBytes(message)); // unicode chars
					bw->Write(0); // target
					// no extra
				}

				bw->Close();
				fw->Close();;

				Cursor = Windows::Forms::Cursors::Default;
			}
		}
};