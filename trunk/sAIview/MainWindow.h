#pragma once

#include "..\COMMON\aipolicy.h"
#include "LoadingScreen.h"
#include "TranslatorService.h"

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

			skillReplace = loadSkillReplace("skill_replace.txt");
			blockDisable = loadBlockDisable("block_disable.txt");
			GUID = 1;

			try
			{
				soap = gcnew TranslatorService::SoapService();
				appID = "763743C8043FA427227700179E653860B731D443";
				from = "zh-CHS";
				to = "en";
				comboBox_language->Items->AddRange(soap->GetLanguagesForTranslate(appID));
				comboBox_language->SelectedItem = "en";
			}
			catch(Exception^ e)
			{
				soap = nullptr;
				textBox_translation->Text = "TRANSLATION SERVICE UNAVAILABLE";
				MessageBox::Show(e->Message);
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

		TranslatorService::SoapService^ soap;
		String^ appID;
		String^ from;
		String^ to;
		Collections::SortedList^ skillReplace;
		ArrayList^ blockDisable;

		private: AIPolicy^ AI;
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
			this->comboBox_cat->Size = System::Drawing::Size(103, 21);
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
			this->comboBox_subCat->Location = System::Drawing::Point(118, 27);
			this->comboBox_subCat->Name = L"comboBox_subCat";
			this->comboBox_subCat->Size = System::Drawing::Size(139, 21);
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


		/*
		*/
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

		ArrayList^ loadBlockDisable(String^ file)
		{
			ArrayList^ blockTable = gcnew ArrayList();

			String^ debug = Application::StartupPath + "\\" + file;
			StreamReader^ sr = gcnew StreamReader(Application::StartupPath + "\\" + file);

			String^ line;
			array<String^>^ pair;
			array<String^>^ seperator = gcnew array<String^>{":"};
			while(!sr->EndOfStream)
			{
				line = sr->ReadLine();
				if(!line->StartsWith("#") && line->Contains(":"))
				{
					pair = line->Split(seperator, StringSplitOptions::RemoveEmptyEntries);
					if(pair->Length == 2)
					{
						blockTable->Add(pair[0] + ":" + pair[1]);
					}
				}
			}

			sr->Close();

			return blockTable;
		}
		/*
			get target
		*/
		String^ procedure_ext(int ext)
		{
			if(ext == 0)
			{
				return "AGGRO_FIRST";
			}
			if(ext == 1)
			{
				return "AGGRO_SECOND";
			}
			if(ext == 2)
			{
				return "AGGRO_SECOND_RAND";
			}
			if(ext == 3)
			{
				return "MOST_HP";
			}
			if(ext == 4)
			{
				return "MOST_MP";
			}
			if(ext == 5)
			{
				return "LEAST_HP";
			}
			if(ext == 6)
			{
				return "COMBO";
			}
			if(ext == 7)
			{
				return "SELF";
			}
			return "?";
		}
		/*
			Get the condition property as string representation
		*/
		String^ condition_name(int operator_id)
		{
			if(operator_id == 0)
			{
				return "Is_Timer_Ticking";
			}
			if(operator_id == 1)
			{
				return "Is_HP_Less";
			}
			if(operator_id == 2)
			{
				return "Is_Combat_Started";
			}
			if(operator_id == 3)
			{
				return "Randomize";
			}
			if(operator_id == 4)
			{
				return "Is_Target_Killed";
			}
			if(operator_id == 5)
			{
				return "!"; // NOT
			}
			if(operator_id == 6)
			{
				return "||"; // OR
			}
			if(operator_id == 7)
			{
				return "&&"; // AND
			}
			if(operator_id == 8)
			{
				return "Is_Dead";
			}
// ---------- following condition types are > 1.3.6 Server -----------------
			if(operator_id == 9)
			{
				return "+"; // SUM
			}
			if(operator_id == 10)
			{
				return "-"; // MINUS ?
			}
			if(operator_id == 11)
			{
				return "=="; // EQUALS ?
			}
			if(operator_id == 12)
			{
				return ">"; // ?
			}
			if(operator_id == 13)
			{
				return ">="; // GREATER EQUALS ?
			}
			if(operator_id == 14)
			{
				return "<"; // LESS THEN
			}
			if(operator_id == 15)
			{
				return ">"; // GREATER THEN
			}
			if(operator_id == 16)
			{
				return "Public_Counter"; // A property/counter that holds a public/shared value
			}
			if(operator_id == 17)
			{
				return "Value"; // defines a value for operator comparsion i.e. value of score, minutes, level, ...
			}
			if(operator_id == 18)
			{
				return "Is_Event?";
			}
			return "?";
		}
		/*
			Get the condition value depending on condition type
		*/
		String^ condition_value(Condition^ c)
		{
			if(c->operator_id == 0)
			{
				return BitConverter::ToInt32(c->value, 0).ToString();
			}
			if(c->operator_id == 1)
			{
				return BitConverter::ToSingle(c->value, 0).ToString("F2");
			}
			if(c->operator_id == 2)
			{
				return "";
			}
			if(c->operator_id == 3)
			{
				return BitConverter::ToSingle(c->value, 0).ToString("F2");
			}
			if(c->operator_id == 4)
			{
				return "";
			}
			if(c->operator_id == 5)
			{
				return "NOT";
			}
			if(c->operator_id == 6)
			{
				return "";
			}
			if(c->operator_id == 7)
			{
				return "";
			}
			if(c->operator_id == 8)
			{
				return "";
			}
// ---------- following condition types are > 1.3.6 Server -----------------
			if(c->operator_id == 9)
			{
				return "";
			}
			if(c->operator_id == 10)
			{
				return "";
			}
			if(c->operator_id == 11)
			{
				return "";
			}
			if(c->operator_id == 12)
			{
				return "";
			}
			if(c->operator_id == 13)
			{
				return "";
			}
			if(c->operator_id == 14)
			{
				return "";
			}
			if(c->operator_id == 15)
			{
				return "";
			}
			if(c->operator_id == 16)
			{
				return BitConverter::ToInt32(c->value, 0).ToString();
			}
			if(c->operator_id == 17)
			{
				return BitConverter::ToInt32(c->value, 0).ToString();
			}
			if(c->operator_id == 18)
			{
				return "";
			}
			return "?";
		}
		/*
			Converts condition to a human readable expression
		*/
		String^ condition_expression(Condition^ c)
		{
			String^ expression = "";

			if(c->condition_type == 1)
			{
				expression += "(";
				expression += condition_expression(c->condition_left);
				expression += " " + condition_name(c->operator_id) + " ";
				expression += condition_expression(c->condition_right);
				expression += ")";
			}
			if(c->condition_type == 2)
			{
				expression += condition_name(c->operator_id);
				expression += "(";
				expression += condition_expression(c->condition_right);
				expression += ")";
			}
			if(c->condition_type > 2)
			{
				expression += condition_name(c->operator_id);
				expression += "(";
				if(c->argument_bytes > 0)
				{
					expression += condition_value(c);
				}
				expression += ")";
			}

			return expression;
		}
		/*
			Returns the procedure name for an ID
		*/
		String^ procedure_expression(Procedure^ p)
		{
			String^ expression = "";

			if(p->type == 0)
			{
				expression = "Attack(";
				expression += ((int)p->parameters[0]).ToString();
				expression += ")";
			}
			if(p->type == 1)
			{
				expression = "Cast_Skill(";
				expression += ((int)p->parameters[0]).ToString() + ", ";
				expression += ((int)p->parameters[1]).ToString();
				expression += ")";
			}
			if(p->type == 2)
			{
				expression = "Broadcast_Message(";
				expression += ((int)p->parameters[0]).ToString() + ", ";
				expression += "\"" + (Encoding::Unicode)->GetString((array<unsigned char>^)p->parameters[1])->Replace("\0", "") + "\"";
				expression += ")";
			}
			if(p->type == 3)
			{
				expression = "Reset_Aggro()";
			}
			if(p->type == 4)
			{
				expression = "Execute_ActionSet(";
				expression += ((int)p->parameters[0]).ToString();
				expression += ")";
			}
			if(p->type == 5)
			{
				expression = "Disable_ActionSet(";
				expression += ((int)p->parameters[0]).ToString();
				expression += ")";
			}
			if(p->type == 6)
			{
				expression = "Enable_ActionSet(";
				expression += ((int)p->parameters[0]).ToString();
				expression += ")";
			}
			if(p->type == 7)
			{
				expression = "Create_Timer(";
				expression += ((int)p->parameters[0]).ToString() + ", ";
				expression += ((int)p->parameters[1]).ToString() + ", ";
				expression += ((int)p->parameters[2]).ToString();
				expression += ")";
			}
			if(p->type == 8)
			{
				expression = "Remove_Timer(";
				expression += ((int)p->parameters[0]).ToString();
				expression += ")";
			}
			if(p->type == 9)
			{
				expression = "Run_Away()";
			}
			if(p->type == 10)
			{
				expression = "Be_Taunted()";
			}
			if(p->type == 11)
			{
				expression = "Fade_Target()";
			}
			if(p->type == 12)
			{
				expression = "Fade_Aggro()";
			}
			if(p->type == 13)
			{
				expression = "Break()";
			}
			if(p->type == 14)
			{
				expression = "NPC_Generator(";
				expression += ((int)p->parameters[0]).ToString() + ", ";
				expression += ((int)p->parameters[1]).ToString();
				expression += ")";
			}
// ---------- following procedure types are > 1.3.6 Server -----------------
			if(p->type == 15)
			{
				expression = "Initialize_Public_Counter(";
				expression += ((int)p->parameters[0]).ToString() + ", ";
				expression += ((int)p->parameters[1]).ToString() + ", ";
				expression += ((int)p->parameters[2]).ToString();
				expression += ")";
			}
			if(p->type == 16)
			{
				expression = "Increment_Public_Counter(";
				expression += ((int)p->parameters[0]).ToString() + ", ";
				expression += ((int)p->parameters[1]).ToString();
				expression += ")";
			}
			if(p->type == 17)
			{
				expression = "Player_Aimed_NPC_Spawn(";
				expression += ((int)p->parameters[0]).ToString() + ", "; // NPC ID
				expression += ((int)p->parameters[1]).ToString() + ", ";
				expression += ((int)p->parameters[2]).ToString() + ", "; // LifeTime
				expression += ((int)p->parameters[3]).ToString() + ", ";
				expression += ((int)p->parameters[4]).ToString() + ", ";
				expression += ((int)p->parameters[5]).ToString();
				expression += ")";
			}
			expression += " EXT(" + procedure_ext(p->target);
			if(p->target == 6)
			{
				expression += ", " + p->extra.ToString();
			}
			expression += ")";
			return expression;
		}

		/*
			Returns the parameters of a procedure, depending on the procedure type
		*/
		array<Object^>^ read_parameters(int type, BinaryReader^ br)
		{
			if(type == 0)
			{
				return gcnew array<Object^>{br->ReadInt32()}; // Attack
			}
			if(type == 1)
			{
				return gcnew array<Object^>{br->ReadInt32(), br->ReadInt32()}; // Cast Skill
			}
			if(type == 2)
			{
				int count = br->ReadInt32();
				return gcnew array<Object^>{count, br->ReadBytes(count)}; // Broadcast Message
			}
			if(type == 3)
			{
				return gcnew array<Object^>{}; // Break
			}
			if(type == 4)
			{
				return gcnew array<Object^>{br->ReadInt32()}; // Execute Trigger
			}
			if(type == 5)
			{
				return gcnew array<Object^>{br->ReadInt32()}; // Disable Trigger
			}
			if(type == 6)
			{
				return gcnew array<Object^>{br->ReadInt32()}; // Enable Trigger
			}
			if(type == 7)
			{
				return gcnew array<Object^>{br->ReadInt32(), br->ReadInt32(), br->ReadInt32()}; // Create Timer
			}
			if(type == 8)
			{
				return gcnew array<Object^>{br->ReadInt32()}; // Remove Timer
			}
			if(type == 9)
			{
				return gcnew array<Object^>{}; // Run Away (AGGRO_FIRST)
			}
			if(type == 10)
			{
				return gcnew array<Object^>{}; // Be Taunted (COMBO, int)
			}
			if(type == 11)
			{
				return gcnew array<Object^>{}; // Fade Target (AGGRO_SECOND)
			}
			if(type == 12)
			{
				return gcnew array<Object^>{}; // Fade Aggro ()
			}
			if(type == 13)
			{
				return gcnew array<Object^>{}; // Break
			}
			if(type == 14)
			{
				return gcnew array<Object^>{br->ReadInt32(), br->ReadInt32()}; // NPC Generator
			}
// ---------- following procedure types are > 1.3.6 Server -----------------
			if(type == 15)
			{
				return gcnew array<Object^>{br->ReadInt32(), br->ReadInt32(), br->ReadInt32()};
			}
			if(type == 16)
			{
				return gcnew array<Object^>{br->ReadInt32(), br->ReadInt32()};
			}
			if(type == 17)
			{
				return gcnew array<Object^>{br->ReadInt32(), br->ReadInt32(), br->ReadInt32(), br->ReadInt32(), br->ReadInt32(), br->ReadInt32()};
			}
			return gcnew array<Object^>(0);
		}
		/*
			Writes the parameters of a procedure depending of the procedure type into the stream (file)
		*/
		void write_parameters(int type, array<Object^>^ Parameters, BinaryWriter^ bw)
		{
			if(type == 0)
			{
				bw->Write((int)Parameters[0]);
			}
			if(type == 1)
			{
				bw->Write((int)Parameters[0]);
				bw->Write((int)Parameters[1]);
			}
			if(type == 2)
			{
				int count = (int)Parameters[0];
				bw->Write(count);
				bw->Write((array<unsigned char>^)Parameters[1]);
			}
			if(type == 4)
			{
				bw->Write((int)Parameters[0]);
			}
			if(type == 5)
			{
				bw->Write((int)Parameters[0]);
			}
			if(type == 6)
			{
				bw->Write((int)Parameters[0]);
			}
			if(type == 7)
			{
				bw->Write((int)Parameters[0]);
				bw->Write((int)Parameters[1]);
				bw->Write((int)Parameters[2]);
			}
			if(type == 8)
			{
				bw->Write((int)Parameters[0]);
			}
			if(type == 14)
			{
				bw->Write((int)Parameters[0]);
				bw->Write((int)Parameters[1]);
			}
// ---------- following procedure types are > 1.3.6 Server -----------------
			if(type == 15)
			{
				bw->Write((int)Parameters[0]);
				bw->Write((int)Parameters[1]);
				bw->Write((int)Parameters[2]);
			}
			if(type == 16)
			{
				bw->Write((int)Parameters[0]);
				bw->Write((int)Parameters[1]);
			}
			if(type == 17)
			{
				bw->Write((int)Parameters[0]);
				bw->Write((int)Parameters[1]);
				bw->Write((int)Parameters[2]);
				bw->Write((int)Parameters[3]);
				bw->Write((int)Parameters[4]);
				bw->Write((int)Parameters[5]);
			}
		}

		/*
			Returns the recursive condition tree from a stream (file)
			conditions are like nodes, they have properties and also can have sub-conditions...
			it seems to be some kind of if then else tree structure
		*/
		Condition^ load_condition(BinaryReader^ br)
		{
			Condition^ c = gcnew Condition();

			c->operator_id = br->ReadInt32();
			c->argument_bytes = br->ReadInt32();
			//if(c->argument_bytes == 4)
			//{
				c->value = br->ReadBytes(c->argument_bytes);
			//}
			c->condition_type = br->ReadInt32(); // 1 || 2 || 3
			if(c->condition_type == 1)
			{
				c->condition_left = load_condition(br);
				c->subnode_2 = br->ReadInt32(); // always 2
				//if(c->subnode_2 == 2)
				//{
					c->condition_right = load_condition(br);
					c->subnode_3 = br->ReadInt32(); // always 4
				//}
			}

			if(c->condition_type == 2)
			{
				c->condition_right = load_condition(br);
				c->subnode_2 = br->ReadInt32(); // always 4
			}

			return c;
		}

		/*
			Writes the condition (and sub-conditions) to the stream (file)
		*/
		void save_condition(Condition^ c, BinaryWriter^ bw)
		{
			bw->Write(c->operator_id);
			bw->Write(c->argument_bytes);
			if(c->argument_bytes == 4)
			{
				bw->Write(c->value);
			}

			bw->Write(c->condition_type);

			if(c->condition_type == 1)
			{
				save_condition(c->condition_left, bw);
				bw->Write(c->subnode_2);
				if(c->subnode_2 == 2)
				{
					save_condition(c->condition_right, bw);
					bw->Write(c->subnode_3);
				}
			}

			if(c->condition_type == 2)
			{
				save_condition(c->condition_right, bw);
				bw->Write(c->subnode_2);
			}
		}

		/*
			load an aipolicy.data file into the global AI structure
		*/
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

					FileStream^ fr = File::OpenRead(load->FileName);
					BinaryReader^ br = gcnew BinaryReader(fr);

					AI = gcnew AIPolicy();

					AI->signature = br->ReadInt32();
					AI->action_controllers_count = br->ReadInt32();
					AI->action_controllers = gcnew array<ActionController^>(AI->action_controllers_count);
					for(int ac=0; ac<AI->action_controllers->Length; ac++)
					{
						AI->action_controllers[ac] = gcnew ActionController();
						AI->action_controllers[ac]->signature = br->ReadInt32();
						AI->action_controllers[ac]->id = br->ReadInt32();
						AI->action_controllers[ac]->action_sets_count = br->ReadInt32();
						AI->action_controllers[ac]->action_sets = gcnew array<ActionSet^>(AI->action_controllers[ac]->action_sets_count);
						listBox_ActionController->Items->Add(AI->action_controllers[ac]->id.ToString());
						for(int as=0; as<AI->action_controllers[ac]->action_sets->Length; as++)
						{
							AI->action_controllers[ac]->action_sets[as] = gcnew ActionSet();
							AI->action_controllers[ac]->action_sets[as]->version = br->ReadInt32();
							AI->action_controllers[ac]->action_sets[as]->id = br->ReadInt32();
							AI->action_controllers[ac]->action_sets[as]->flags = br->ReadBytes(3);
							AI->action_controllers[ac]->action_sets[as]->name = br->ReadBytes(128);
							AI->action_controllers[ac]->action_sets[as]->conditions = load_condition(br);
							AI->action_controllers[ac]->action_sets[as]->procedures_count = br->ReadInt32();
							AI->action_controllers[ac]->action_sets[as]->procedures = gcnew array<Procedure^>(AI->action_controllers[ac]->action_sets[as]->procedures_count);
							for(int p=0; p<AI->action_controllers[ac]->action_sets[as]->procedures->Length; p++)
							{
								AI->action_controllers[ac]->action_sets[as]->procedures[p] = gcnew Procedure();
								AI->action_controllers[ac]->action_sets[as]->procedures[p]->type = br->ReadInt32();
								AI->action_controllers[ac]->action_sets[as]->procedures[p]->parameters = read_parameters(AI->action_controllers[ac]->action_sets[as]->procedures[p]->type, br);
								AI->action_controllers[ac]->action_sets[as]->procedures[p]->target = br->ReadInt32();
								if(AI->action_controllers[ac]->action_sets[as]->procedures[p]->target == 6)
								{
									AI->action_controllers[ac]->action_sets[as]->procedures[p]->extra = br->ReadInt32();
								}
							}
						}
					}

					br->Close();
					fr->Close();;

					Cursor = Windows::Forms::Cursors::Default;
				}
				catch(Exception^ e)
				{
					Cursor = Windows::Forms::Cursors::Default;
					MessageBox::Show("IMPORT ERROR!\n\n" + e->Message);
				}
			}
		}

		/*
			Export the currently loaded AI structure to an 1.3.6 compatible aipolicy.data file
			Currently the export only works for AI <= 1.3.9, for 1.4.2 it only works until Controller[923]->ActionSet[9]
		*/
		private: System::Void click_export(System::Object^  sender, System::EventArgs^  e)
		{
			SaveFileDialog^ save = gcnew SaveFileDialog();
			save->Filter = "AI Policy (*.data)|*.data|All Files (*.*)|*.*";
			if(AI && save->ShowDialog() == Windows::Forms::DialogResult::OK && save->FileName != "")
			{
				Cursor = Windows::Forms::Cursors::WaitCursor;

				AI = convert(AI);

				FileStream^ fw = gcnew FileStream(save->FileName, FileMode::Create, FileAccess::Write);
				BinaryWriter^ bw = gcnew BinaryWriter(fw);

				bw->Write(AI->signature);
				bw->Write(AI->action_controllers_count);
				for(int ac=0; ac<AI->action_controllers->Length; ac++)
				{
					bw->Write(AI->action_controllers[ac]->signature);
					bw->Write(AI->action_controllers[ac]->id);
					bw->Write(AI->action_controllers[ac]->action_sets_count);
					for(int as=0; as<AI->action_controllers[ac]->action_sets->Length; as++)
					{
						bw->Write(AI->action_controllers[ac]->action_sets[as]->version);
						bw->Write(AI->action_controllers[ac]->action_sets[as]->id);
						bw->Write(AI->action_controllers[ac]->action_sets[as]->flags);
						bw->Write(AI->action_controllers[ac]->action_sets[as]->name);
						// Write conditions
						save_condition(AI->action_controllers[ac]->action_sets[as]->conditions, bw);
						
						bw->Write(AI->action_controllers[ac]->action_sets[as]->procedures_count);
						for(int p=0; p<AI->action_controllers[ac]->action_sets[as]->procedures->Length; p++)
						{
							bw->Write(AI->action_controllers[ac]->action_sets[as]->procedures[p]->type);
							write_parameters(AI->action_controllers[ac]->action_sets[as]->procedures[p]->type, AI->action_controllers[ac]->action_sets[as]->procedures[p]->parameters, bw);
							bw->Write(AI->action_controllers[ac]->action_sets[as]->procedures[p]->target);
							if(AI->action_controllers[ac]->action_sets[as]->procedures[p]->target == 6)
							{
								bw->Write(AI->action_controllers[ac]->action_sets[as]->procedures[p]->extra);
							}
						}
					}
				}

				bw->Close();
				fw->Close();;

				Cursor = Windows::Forms::Cursors::Default;
			}
		}

		/*
			Rebuild the condition tree
			If conditions are based on property ID's > 8, then this condition will be set to NULL
		*/
		Condition^ fix_conditions(Condition^ c)
		{
			if(c->operator_id > 8)
			{
				// try to replace operator id with a valid condition_(chain)

				// remove condition
				return nullptr;
			}
			else
			{
				if(c->condition_type == 1)
				{
					c->condition_left = fix_conditions(c->condition_left);
					c->condition_right = fix_conditions(c->condition_right);

					if(c->condition_left && c->condition_right)
					{
						// everything is OK
						return c;
					}
					if(!c->condition_left && c->condition_right)
					{
						// left condition is broken, no need to operate between both conditions
						// right condition replaces the current operator condition i.e. AND
						return c->condition_right;
					}
					if(c->condition_left && !c->condition_right)
					{
						// right condition is broken, no need to operate between both conditions
						// left condition replaces the current operator condition i.e. AND
						return c->condition_left;
					}
					if(!c->condition_left && !c->condition_right)
					{
						// both conditions for this operator condition are broken
						// completely drop this condition
						return nullptr;
					}
				}
				if(c->condition_type == 2)
				{
					c->condition_right = fix_conditions(c->condition_right);

					if(c->condition_right)
					{
						return c;
					}
					else
					{
						return nullptr;
					}
				}
				//if(c->condition_type > 2)
				return c;
			}
		}

		/*
			Rebuild procedure list by removing all procedure types >= 15,
			or remove procedures that calls monster skills with id >= 887
		*/
		array<Procedure^>^ fix_procedures(array<Procedure^>^ p)
		{
			int count = 0;
			for(int i=0; i<p->Length; i++)
			{
				// count supported procedures
				if(p[i]->type != 15 && p[i]->type != 16)
				{
					count++;
				}
			}

			array<Procedure^>^ result = gcnew array<Procedure^>(count);
			count = 0;

			for(int i=0; i<p->Length; i++)
			{
				// only keep supported procedures 
				if(p[i]->type != 15 && p[i]->type != 16)
				{
					result[count] = gcnew Procedure();
					result[count]->type = p[i]->type;
					result[count]->parameters = p[i]->parameters;
					// replace skill if possible
					if(p[i]->type == 1 && skillReplace->ContainsKey((int)p[i]->parameters[0]))
					{
						result[count]->parameters[0] = (int)skillReplace[(int)p[i]->parameters[0]];
					}

					if(p[i]->type == 2 && ((array<unsigned char>^)result[count]->parameters[1])[0] == '$')
					{
						// remove whitespace after macro
						if(((array<unsigned char>^)result[count]->parameters[1])[4] == ' ')
						{
							array<unsigned char>^ _old = ((array<unsigned char>^)result[count]->parameters[1]);
							array<unsigned char>^ _new = gcnew array<unsigned char>(_old->Length-2);

							int n=0;
							for(int i=0; i<_new->Length; i++)
							{
								if(n == 4)
								{
									n = 6;
								}
								_new[i] = _old[n];
								n++;
							}

							result[count]->parameters[1] = _new;
							result[count]->parameters[0] = _new->Length;
						}

						// replace $S macro (no-name, color?) with $B macro (no-name, gold)
						if(((array<unsigned char>^)result[count]->parameters[1])[2] == 'S')
						{
							((array<unsigned char>^)result[count]->parameters[1])[2] = 'B';
						}

						// replace $I macro (no-name, red?) with $B macro (no-name, gold)
						if(((array<unsigned char>^)result[count]->parameters[1])[2] == 'I')
						{
							((array<unsigned char>^)result[count]->parameters[1])[2] = 'B';
						}
					}
					result[count]->target = p[i]->target;
					result[count]->extra = p[i]->extra;

					// replace player_aimed_npc_spawn with a simple npc_generator
					if(p[i]->type == 17)
					{
						result[count]->type = 14;
						// using i as unifier to prevent multiple npc_generator() with same id's in the same action set
						int creature_builder_id = (GUID*1000000 + (int)p[i]->parameters[0]);
						GUID++;
						int start = 0; // 0: start, 1: stop
						result[count]->parameters = gcnew array<Object^>{creature_builder_id, start};
						result[count]->target = 0;
						result[count]->extra = 0;
					}

					count++;
				}
			}

			// if result is length 0 we have to add a dummy procedure, or action set will crash map
			if(result->Length < 1)
			{
				result = gcnew array<Procedure^>(1);
				result[0] = gcnew Procedure();
				result[0]->type = 2;
				result[0]->parameters = gcnew array<Object^>{6, Encoding::Unicode->GetBytes("...")};
				result[0]->target = 0;
				result[0]->extra = 0;
			}

			return result;
		}

		/*
			try to convert any AI structure to a 1.3.6 compatible server version
			+ replace signature and versions for file, collections and sets
			+ remove unsupported conditions (condition->property > 8) and rebuild condition tree
			+ remove unsupported procedures (procedure->id > 14)
			+ remove procedures that are using monster skills with id > 887
		*/
		AIPolicy^ convert(AIPolicy^ source_ai)
		{
			// a countr for creating unique creature builder id's
			// when replacing player_aimed_npc_spawn() procedure with npc_generate() procedure
			GUID = 1;

			AIPolicy^ result = gcnew AIPolicy();
			result->signature = (int)0; // signature = 0 for <= 1.3.6
			result->action_controllers_count = source_ai->action_controllers_count;
			result->action_controllers = gcnew array<ActionController^>(result->action_controllers_count);

			for(int ac=0; ac<result->action_controllers->Length; ac++)
			{
				result->action_controllers[ac] = gcnew ActionController();
				result->action_controllers[ac]->signature = (int)0; // signature = 0 for <= 1.3.6
				result->action_controllers[ac]->id = source_ai->action_controllers[ac]->id;
				result->action_controllers[ac]->action_sets_count = source_ai->action_controllers[ac]->action_sets_count;
				result->action_controllers[ac]->action_sets = gcnew array<ActionSet^>(result->action_controllers[ac]->action_sets_count);

				for(int as=0; as<result->action_controllers[ac]->action_sets->Length; as++)
				{
					result->action_controllers[ac]->action_sets[as] = gcnew ActionSet();
					result->action_controllers[ac]->action_sets[as]->version = (int)1; // signature = 1 for <= 1.3.6
					result->action_controllers[ac]->action_sets[as]->id = source_ai->action_controllers[ac]->action_sets[as]->id;
					result->action_controllers[ac]->action_sets[as]->flags = source_ai->action_controllers[ac]->action_sets[as]->flags; // 3 Bytes
					result->action_controllers[ac]->action_sets[as]->name = source_ai->action_controllers[ac]->action_sets[as]->name; // 128 Bytes
					// convert conditions
					result->action_controllers[ac]->action_sets[as]->conditions = fix_conditions(source_ai->action_controllers[ac]->action_sets[as]->conditions);
					// convert procedures
					result->action_controllers[ac]->action_sets[as]->procedures = fix_procedures(source_ai->action_controllers[ac]->action_sets[as]->procedures);
					result->action_controllers[ac]->action_sets[as]->procedures_count = result->action_controllers[ac]->action_sets[as]->procedures->Length;

					// check for nullptr conditions after conversion
					// because it could happen that condition only consists
					// of properties > 1.3.6, this will cause in complete useless of condition tree 1.3.6
					if(!result->action_controllers[ac]->action_sets[as]->conditions)
					{
						// Removing an actionset can leads to dead links, if a link from a procedure is pointing to this actionset id
						// instead of removing this actionset, we create a default condition that is common false,
						// but will be executed when linked by an execute_actionset() procedure
						// for this behaviour we are using randomize(1.00)
						result->action_controllers[ac]->action_sets[as]->conditions = gcnew Condition();
						result->action_controllers[ac]->action_sets[as]->conditions->operator_id = 3;
						result->action_controllers[ac]->action_sets[as]->conditions->argument_bytes = 4;
						if(blockDisable->Contains(source_ai->action_controllers[ac]->id + ":" + source_ai->action_controllers[ac]->action_sets[as]->id))
						{
							result->action_controllers[ac]->action_sets[as]->conditions->value = gcnew array<unsigned char>{0, 0, 0, 0};
						}
						else
						{
							result->action_controllers[ac]->action_sets[as]->conditions->value = gcnew array<unsigned char>{0, 0, 128, 63};
						}
						result->action_controllers[ac]->action_sets[as]->conditions->subnode_2 = 0;
						result->action_controllers[ac]->action_sets[as]->conditions->subnode_3 = 0;
						result->action_controllers[ac]->action_sets[as]->conditions->condition_type = 3;
					}
				}
			}

			return result;
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

				textBox_Condition->Text = "IF{ " + condition_expression(AI->action_controllers[ac]->action_sets[as]->conditions) + " }";
				
				listBox_Procedures->Items->Clear();
				for(int i=0; i<AI->action_controllers[ac]->action_sets[as]->procedures->Length; i++)
				{
					listBox_Procedures->Items->Add("[" + i.ToString() + "] " + procedure_expression(AI->action_controllers[ac]->action_sets[as]->procedures[i]));
				}

				if(soap && listBox_ActionSet->SelectedItem)
				{
					Cursor = Windows::Forms::Cursors::AppStarting;
					to = comboBox_language->SelectedItem->ToString();
					try
					{
						textBox_translation->Text = soap->Translate(appID, listBox_ActionSet->SelectedItem->ToString()->Split(gcnew array<wchar_t>{'\0'})[0], from, to, "text/plain", "general");
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
							if(textBox_pattern->Text != "" && condition_expression(AI->action_controllers[ac]->action_sets[as]->conditions)->Contains(textBox_pattern->Text))
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
									if(textBox_pattern->Text == "" || procedure_expression(AI->action_controllers[ac]->action_sets[as]->procedures[pc])->Contains(textBox_pattern->Text))
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