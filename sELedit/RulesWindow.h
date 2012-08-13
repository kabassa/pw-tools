#pragma once

#include "..\COMMON\eListCollection.h"
#include "RuleConfig.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


	/// <summary>
	/// Summary for RulesWindow
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class RulesWindow : public System::Windows::Forms::Form
	{
	public:
		RulesWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~RulesWindow()
		{
			if (components)
			{
				delete components;
			}
		}

		eListCollection^ eLC_base;
		eListCollection^ eLC_recent;
		array<RuleConfig^>^ eRules;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  button_browseRecent;
	private: System::Windows::Forms::Button^  button_browseBase;
	private: System::Windows::Forms::TextBox^  textBox_recentVersion;
	private: System::Windows::Forms::TextBox^  textBox_baseVersion;
	private: System::Windows::Forms::TextBox^  textBox_recentFile;
	private: System::Windows::Forms::TextBox^  textBox_baseFile;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::TextBox^  textBox_recentOffset;
	private: System::Windows::Forms::TextBox^  textBox_baseOffset;
	private: System::Windows::Forms::RadioButton^  radioButton_recentOffset;
	private: System::Windows::Forms::RadioButton^  radioButton_baseOffset;
	private: System::Windows::Forms::CheckBox^  checkBox_removeList;
	private: System::Windows::Forms::ComboBox^  comboBox_lists;
	private: System::Windows::Forms::DataGridView^  dataGridView_values;
	private: System::Windows::Forms::DataGridView^  dataGridView_fields;
	private: System::Windows::Forms::Button^  button_save;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column7;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column8;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
	private: System::Windows::Forms::DataGridViewCheckBoxColumn^  Column4;
	private: System::Windows::Forms::DataGridViewButtonColumn^  Column6;

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
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button_browseRecent = (gcnew System::Windows::Forms::Button());
			this->button_browseBase = (gcnew System::Windows::Forms::Button());
			this->textBox_recentVersion = (gcnew System::Windows::Forms::TextBox());
			this->textBox_baseVersion = (gcnew System::Windows::Forms::TextBox());
			this->textBox_recentFile = (gcnew System::Windows::Forms::TextBox());
			this->textBox_baseFile = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->dataGridView_values = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridView_fields = (gcnew System::Windows::Forms::DataGridView());
			this->textBox_recentOffset = (gcnew System::Windows::Forms::TextBox());
			this->textBox_baseOffset = (gcnew System::Windows::Forms::TextBox());
			this->radioButton_recentOffset = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton_baseOffset = (gcnew System::Windows::Forms::RadioButton());
			this->checkBox_removeList = (gcnew System::Windows::Forms::CheckBox());
			this->comboBox_lists = (gcnew System::Windows::Forms::ComboBox());
			this->button_save = (gcnew System::Windows::Forms::Button());
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView_values))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView_fields))->BeginInit();
			this->SuspendLayout();
			// 
			// groupBox1
			// 
			this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox1->Controls->Add(this->button_browseRecent);
			this->groupBox1->Controls->Add(this->button_browseBase);
			this->groupBox1->Controls->Add(this->textBox_recentVersion);
			this->groupBox1->Controls->Add(this->textBox_baseVersion);
			this->groupBox1->Controls->Add(this->textBox_recentFile);
			this->groupBox1->Controls->Add(this->textBox_baseFile);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(0, 2);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(632, 75);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Files";
			// 
			// button_browseRecent
			// 
			this->button_browseRecent->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button_browseRecent->Location = System::Drawing::Point(551, 46);
			this->button_browseRecent->Name = L"button_browseRecent";
			this->button_browseRecent->Size = System::Drawing::Size(75, 23);
			this->button_browseRecent->TabIndex = 9;
			this->button_browseRecent->Text = L"Browse...";
			this->button_browseRecent->UseVisualStyleBackColor = true;
			this->button_browseRecent->Click += gcnew System::EventHandler(this, &RulesWindow::click_browse);
			// 
			// button_browseBase
			// 
			this->button_browseBase->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button_browseBase->Location = System::Drawing::Point(551, 17);
			this->button_browseBase->Name = L"button_browseBase";
			this->button_browseBase->Size = System::Drawing::Size(75, 23);
			this->button_browseBase->TabIndex = 8;
			this->button_browseBase->Text = L"Browse...";
			this->button_browseBase->UseVisualStyleBackColor = true;
			this->button_browseBase->Click += gcnew System::EventHandler(this, &RulesWindow::click_browse);
			// 
			// textBox_recentVersion
			// 
			this->textBox_recentVersion->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox_recentVersion->Enabled = false;
			this->textBox_recentVersion->Location = System::Drawing::Point(509, 48);
			this->textBox_recentVersion->Name = L"textBox_recentVersion";
			this->textBox_recentVersion->Size = System::Drawing::Size(36, 20);
			this->textBox_recentVersion->TabIndex = 7;
			// 
			// textBox_baseVersion
			// 
			this->textBox_baseVersion->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox_baseVersion->Enabled = false;
			this->textBox_baseVersion->Location = System::Drawing::Point(509, 19);
			this->textBox_baseVersion->Name = L"textBox_baseVersion";
			this->textBox_baseVersion->Size = System::Drawing::Size(36, 20);
			this->textBox_baseVersion->TabIndex = 6;
			// 
			// textBox_recentFile
			// 
			this->textBox_recentFile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_recentFile->Enabled = false;
			this->textBox_recentFile->Location = System::Drawing::Point(75, 48);
			this->textBox_recentFile->Name = L"textBox_recentFile";
			this->textBox_recentFile->Size = System::Drawing::Size(377, 20);
			this->textBox_recentFile->TabIndex = 5;
			// 
			// textBox_baseFile
			// 
			this->textBox_baseFile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_baseFile->Enabled = false;
			this->textBox_baseFile->Location = System::Drawing::Point(75, 19);
			this->textBox_baseFile->Name = L"textBox_baseFile";
			this->textBox_baseFile->Size = System::Drawing::Size(377, 20);
			this->textBox_baseFile->TabIndex = 4;
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(458, 51);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(45, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Version:";
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(458, 22);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(45, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Version:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 51);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(63, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Resent File:";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(53, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Base File:";
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->groupBox2->Controls->Add(this->dataGridView_values);
			this->groupBox2->Controls->Add(this->dataGridView_fields);
			this->groupBox2->Controls->Add(this->textBox_recentOffset);
			this->groupBox2->Controls->Add(this->textBox_baseOffset);
			this->groupBox2->Controls->Add(this->radioButton_recentOffset);
			this->groupBox2->Controls->Add(this->radioButton_baseOffset);
			this->groupBox2->Controls->Add(this->checkBox_removeList);
			this->groupBox2->Controls->Add(this->comboBox_lists);
			this->groupBox2->Location = System::Drawing::Point(0, 83);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(632, 337);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Lists";
			// 
			// dataGridView_values
			// 
			this->dataGridView_values->AllowUserToAddRows = false;
			this->dataGridView_values->AllowUserToDeleteRows = false;
			this->dataGridView_values->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView_values->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {this->Column7, 
				this->Column8});
			this->dataGridView_values->Location = System::Drawing::Point(374, 98);
			this->dataGridView_values->Name = L"dataGridView_values";
			this->dataGridView_values->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dataGridView_values->Size = System::Drawing::Size(252, 233);
			this->dataGridView_values->TabIndex = 7;
			// 
			// dataGridView_fields
			// 
			this->dataGridView_fields->AllowUserToAddRows = false;
			this->dataGridView_fields->AllowUserToDeleteRows = false;
			this->dataGridView_fields->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView_fields->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {this->Column1, 
				this->Column2, this->Column3, this->Column4, this->Column6});
			this->dataGridView_fields->Location = System::Drawing::Point(6, 98);
			this->dataGridView_fields->Name = L"dataGridView_fields";
			this->dataGridView_fields->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dataGridView_fields->Size = System::Drawing::Size(362, 233);
			this->dataGridView_fields->TabIndex = 6;
			this->dataGridView_fields->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &RulesWindow::change_field);
			this->dataGridView_fields->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &RulesWindow::click_field);
			// 
			// textBox_recentOffset
			// 
			this->textBox_recentOffset->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_recentOffset->Location = System::Drawing::Point(131, 72);
			this->textBox_recentOffset->Name = L"textBox_recentOffset";
			this->textBox_recentOffset->Size = System::Drawing::Size(495, 20);
			this->textBox_recentOffset->TabIndex = 5;
			// 
			// textBox_baseOffset
			// 
			this->textBox_baseOffset->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_baseOffset->Location = System::Drawing::Point(131, 46);
			this->textBox_baseOffset->Name = L"textBox_baseOffset";
			this->textBox_baseOffset->Size = System::Drawing::Size(495, 20);
			this->textBox_baseOffset->TabIndex = 4;
			// 
			// radioButton_recentOffset
			// 
			this->radioButton_recentOffset->AutoSize = true;
			this->radioButton_recentOffset->Location = System::Drawing::Point(6, 73);
			this->radioButton_recentOffset->Name = L"radioButton_recentOffset";
			this->radioButton_recentOffset->Size = System::Drawing::Size(119, 17);
			this->radioButton_recentOffset->TabIndex = 3;
			this->radioButton_recentOffset->TabStop = true;
			this->radioButton_recentOffset->Text = L"Keep Recent Offset";
			this->radioButton_recentOffset->UseVisualStyleBackColor = true;
			this->radioButton_recentOffset->CheckedChanged += gcnew System::EventHandler(this, &RulesWindow::check_offset);
			// 
			// radioButton_baseOffset
			// 
			this->radioButton_baseOffset->AutoSize = true;
			this->radioButton_baseOffset->Location = System::Drawing::Point(6, 47);
			this->radioButton_baseOffset->Name = L"radioButton_baseOffset";
			this->radioButton_baseOffset->Size = System::Drawing::Size(102, 17);
			this->radioButton_baseOffset->TabIndex = 2;
			this->radioButton_baseOffset->TabStop = true;
			this->radioButton_baseOffset->Text = L"Use Base Offset";
			this->radioButton_baseOffset->UseVisualStyleBackColor = true;
			this->radioButton_baseOffset->CheckedChanged += gcnew System::EventHandler(this, &RulesWindow::check_offset);
			// 
			// checkBox_removeList
			// 
			this->checkBox_removeList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->checkBox_removeList->AutoSize = true;
			this->checkBox_removeList->Location = System::Drawing::Point(541, 21);
			this->checkBox_removeList->Name = L"checkBox_removeList";
			this->checkBox_removeList->Size = System::Drawing::Size(85, 17);
			this->checkBox_removeList->TabIndex = 1;
			this->checkBox_removeList->Text = L"Remove List";
			this->checkBox_removeList->UseVisualStyleBackColor = true;
			this->checkBox_removeList->CheckedChanged += gcnew System::EventHandler(this, &RulesWindow::check_removeList);
			// 
			// comboBox_lists
			// 
			this->comboBox_lists->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->comboBox_lists->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->comboBox_lists->FormattingEnabled = true;
			this->comboBox_lists->Location = System::Drawing::Point(6, 19);
			this->comboBox_lists->Name = L"comboBox_lists";
			this->comboBox_lists->Size = System::Drawing::Size(529, 21);
			this->comboBox_lists->TabIndex = 0;
			this->comboBox_lists->SelectedIndexChanged += gcnew System::EventHandler(this, &RulesWindow::change_list);
			// 
			// button_save
			// 
			this->button_save->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button_save->Location = System::Drawing::Point(264, 426);
			this->button_save->Name = L"button_save";
			this->button_save->Size = System::Drawing::Size(104, 23);
			this->button_save->TabIndex = 2;
			this->button_save->Text = L"Save as Rules";
			this->button_save->UseVisualStyleBackColor = true;
			// 
			// Column7
			// 
			this->Column7->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->Column7->HeaderText = L"Base Values";
			this->Column7->Name = L"Column7";
			this->Column7->ReadOnly = true;
			this->Column7->Width = 91;
			// 
			// Column8
			// 
			this->Column8->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
			this->Column8->HeaderText = L"Recent Values";
			this->Column8->Name = L"Column8";
			this->Column8->ReadOnly = true;
			this->Column8->Width = 102;
			// 
			// Column1
			// 
			this->Column1->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->Column1->HeaderText = L"Base Fields";
			this->Column1->Name = L"Column1";
			this->Column1->ReadOnly = true;
			this->Column1->Width = 86;
			// 
			// Column2
			// 
			this->Column2->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->Column2->HeaderText = L"Recent Fields";
			this->Column2->Name = L"Column2";
			this->Column2->ReadOnly = true;
			this->Column2->Width = 97;
			// 
			// Column3
			// 
			this->Column3->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
			this->Column3->HeaderText = L"Value Mismatches";
			this->Column3->Name = L"Column3";
			this->Column3->ReadOnly = true;
			// 
			// Column4
			// 
			this->Column4->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			this->Column4->HeaderText = L"DEL";
			this->Column4->Name = L"Column4";
			this->Column4->Width = 34;
			// 
			// Column6
			// 
			this->Column6->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::ColumnHeader;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			this->Column6->DefaultCellStyle = dataGridViewCellStyle1;
			this->Column6->HeaderText = L"Analyze";
			this->Column6->Name = L"Column6";
			this->Column6->Width = 50;
			// 
			// RulesWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(632, 453);
			this->Controls->Add(this->button_save);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(640, 480);
			this->Name = L"RulesWindow";
			this->ShowIcon = false;
			this->Text = L"Element Structure Diff";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView_values))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView_fields))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

	private: int count_mismatches(int listIndex, int baseFieldIndex, int recentFieldIndex)
	{
		int mismatches = 0;

		if(baseFieldIndex >= eLC_base->Lists[listIndex]->elementFields->Length)
		{
			return eLC_recent->Lists[listIndex]->elementValues->Length;
		}

		if(recentFieldIndex >= eLC_recent->Lists[listIndex]->elementFields->Length)
		{
			return eLC_base->Lists[listIndex]->elementValues->Length;
		}

		for(int e=0; e<eLC_recent->Lists[listIndex]->elementValues->Length; e++)
		{
			if(e >= eLC_base->Lists[listIndex]->elementValues->Length || e >= eLC_recent->Lists[listIndex]->elementValues->Length)
			{
				break;
			}

			if(eLC_base->GetValue(listIndex, e, baseFieldIndex) != eLC_recent->GetValue(listIndex, e, recentFieldIndex))
			{
				mismatches++;
			}
		}

		return mismatches;
	}

	private: System::Void click_browse(System::Object^  sender, System::EventArgs^  e)
	{
		OpenFileDialog^ eLoad = gcnew OpenFileDialog();
		eLoad->Filter = "Elements File (*.data)|*.data|All Files (*.*)|*.*";
		if(eLoad->ShowDialog() == Windows::Forms::DialogResult::OK && File::Exists(eLoad->FileName))
		{
			Cursor = Windows::Forms::Cursors::AppStarting;

			dataGridView_fields->Rows->Clear();
			dataGridView_values->Rows->Clear();
			comboBox_lists->Items->Clear();

			if(sender == (Object^)button_browseBase)
			{
				eLC_base = gcnew eListCollection(eLoad->FileName);
				textBox_baseFile->Text = eLoad->FileName;
				textBox_baseVersion->Text = eLC_base->Version.ToString();
			}

			if(sender == (Object^)button_browseRecent)
			{
				eLC_recent = gcnew eListCollection(eLoad->FileName);
				textBox_recentFile->Text = eLoad->FileName;
				textBox_recentVersion->Text = eLC_recent->Version.ToString();
			}

			if(eLC_base && eLC_recent && eLC_base->Lists->Length > 0 && eLC_recent->Lists->Length > 0)
			{
				// add list names from recent file
				eRules = gcnew array<RuleConfig^>(eLC_recent->Lists->Length);
				for(int l=0; l<eLC_recent->Lists->Length; l++)
				{
					comboBox_lists->Items->Add("[" + l + "]: " + eLC_recent->Lists[l]->listName + " (" + eLC_recent->Lists[l]->elementValues->Length + ")");
					eRules[l] = gcnew RuleConfig();
					eRules[l]->RemoveList = false;
					eRules[l]->ReplaceOffset = false;
					eRules[l]->Offset = "";
					eRules[l]->RemoveValues = gcnew array<bool>(eLC_recent->Lists[l]->elementFields->Length);
				}
			}

			Cursor = Windows::Forms::Cursors::Default;
		}
	}

	private: System::Void change_list(System::Object^  sender, System::EventArgs^  e)
	{
		Cursor = Windows::Forms::Cursors::AppStarting;

		dataGridView_fields->Rows->Clear();
		dataGridView_values->Rows->Clear();

		int l = comboBox_lists->SelectedIndex;

		if(l > -1)
		{
			if(eLC_base->Lists->Length > l && eLC_base->ConversationListIndex != l)
			{
				int baseFieldIndex = 0;
				int recentFieldIndex = 0;

				checkBox_removeList->Checked = eRules[l]->RemoveList;
				if(eRules[l]->ReplaceOffset)
				{
					radioButton_baseOffset->Checked = true;
					radioButton_recentOffset->Checked = false;
				}
				else
				{
					radioButton_baseOffset->Checked = false;
					radioButton_recentOffset->Checked = true;
				}
				textBox_baseOffset->Text = eLC_base->GetOffset(l);
				textBox_recentOffset->Text = eLC_recent->GetOffset(l);

				for(int f=0; f<eLC_recent->Lists[l]->elementFields->Length; f++)
				{
					if(eRules[l]->RemoveValues[f] || f >= eLC_base->Lists[l]->elementFields->Length)
					{
						baseFieldIndex--;
						dataGridView_fields->Rows->Add(gcnew array<String^>{"", eLC_recent->Lists[l]->elementTypes[recentFieldIndex], count_mismatches(l, baseFieldIndex, recentFieldIndex).ToString(), eRules[l]->RemoveValues[f].ToString(), "Details"});
					}
					else
					{
						dataGridView_fields->Rows->Add(gcnew array<String^>{eLC_base->Lists[l]->elementTypes[baseFieldIndex], eLC_recent->Lists[l]->elementTypes[recentFieldIndex], count_mismatches(l, baseFieldIndex, recentFieldIndex).ToString(), eRules[l]->RemoveValues[f].ToString(), "Details"});
					}
					baseFieldIndex++;
					recentFieldIndex++;

				}
			}
			else
			{
				// index out of accessable lists
			}
		}

		Cursor = Windows::Forms::Cursors::Default;
	}

	private: System::Void check_removeList(System::Object^  sender, System::EventArgs^  e)
	{
	}

	private: System::Void check_offset(System::Object^  sender, System::EventArgs^  e)
	{
	}

	private: System::Void change_field(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e)
	{
		MessageBox::Show(e->);
	}

	private: System::Void click_field(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e)
	{
		MessageBox::Show("Cell Click");
	}
};