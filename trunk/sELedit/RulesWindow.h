#pragma once

#include "..\COMMON\eListCollection.h"
#include "..\COMMON\DebugWindow.h"
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
	private: System::Windows::Forms::Button^  button_view;
	private: System::Windows::Forms::Button^  button_import;
	private: System::Windows::Forms::Button^  button_export;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
	private: System::Windows::Forms::DataGridViewCheckBoxColumn^  Column4;
	private: System::Windows::Forms::DataGridViewButtonColumn^  Column6;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column7;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column8;
	private: System::Windows::Forms::ToolTip^  toolTip;
	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(RulesWindow::typeid));
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
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
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridView_fields = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewCheckBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
			this->textBox_recentOffset = (gcnew System::Windows::Forms::TextBox());
			this->textBox_baseOffset = (gcnew System::Windows::Forms::TextBox());
			this->radioButton_recentOffset = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton_baseOffset = (gcnew System::Windows::Forms::RadioButton());
			this->checkBox_removeList = (gcnew System::Windows::Forms::CheckBox());
			this->comboBox_lists = (gcnew System::Windows::Forms::ComboBox());
			this->button_view = (gcnew System::Windows::Forms::Button());
			this->button_import = (gcnew System::Windows::Forms::Button());
			this->button_export = (gcnew System::Windows::Forms::Button());
			this->toolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
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
			this->groupBox1->Size = System::Drawing::Size(792, 75);
			this->groupBox1->TabIndex = 0;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Files";
			// 
			// button_browseRecent
			// 
			this->button_browseRecent->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button_browseRecent->Location = System::Drawing::Point(711, 46);
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
			this->button_browseBase->Location = System::Drawing::Point(711, 17);
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
			this->textBox_recentVersion->Location = System::Drawing::Point(669, 48);
			this->textBox_recentVersion->Name = L"textBox_recentVersion";
			this->textBox_recentVersion->Size = System::Drawing::Size(36, 20);
			this->textBox_recentVersion->TabIndex = 7;
			// 
			// textBox_baseVersion
			// 
			this->textBox_baseVersion->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox_baseVersion->Enabled = false;
			this->textBox_baseVersion->Location = System::Drawing::Point(669, 19);
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
			this->textBox_recentFile->Size = System::Drawing::Size(537, 20);
			this->textBox_recentFile->TabIndex = 5;
			// 
			// textBox_baseFile
			// 
			this->textBox_baseFile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_baseFile->Enabled = false;
			this->textBox_baseFile->Location = System::Drawing::Point(75, 19);
			this->textBox_baseFile->Name = L"textBox_baseFile";
			this->textBox_baseFile->Size = System::Drawing::Size(537, 20);
			this->textBox_baseFile->TabIndex = 4;
			// 
			// label4
			// 
			this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(618, 51);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(45, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Version:";
			// 
			// label3
			// 
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(618, 22);
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
			this->label2->Text = L"Recent File:";
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
			this->groupBox2->Size = System::Drawing::Size(792, 457);
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
			this->dataGridView_values->Location = System::Drawing::Point(488, 98);
			this->dataGridView_values->Name = L"dataGridView_values";
			this->dataGridView_values->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToDisplayedHeaders;
			this->dataGridView_values->Size = System::Drawing::Size(298, 353);
			this->dataGridView_values->TabIndex = 7;
			// 
			// Column7
			// 
			this->Column7->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::DisplayedCells;
			this->Column7->HeaderText = L"Base Values";
			this->Column7->Name = L"Column7";
			this->Column7->ReadOnly = true;
			this->Column7->Width = 91;
			// 
			// Column8
			// 
			this->Column8->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::DisplayedCells;
			this->Column8->HeaderText = L"Recent Values";
			this->Column8->Name = L"Column8";
			this->Column8->ReadOnly = true;
			this->Column8->Width = 102;
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
			this->dataGridView_fields->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToDisplayedHeaders;
			this->dataGridView_fields->Size = System::Drawing::Size(476, 353);
			this->dataGridView_fields->TabIndex = 6;
			this->toolTip->SetToolTip(this->dataGridView_fields, "Comparsion of fields from the selected list.\r\nIf recent file has more fields in this list then base file you have to remove some fields.\r\n\r\nMismatches compares all element values for the related field and count how many different values appears. Higher amount of mismatches might be an indicator for a new added field in the recent file's current list.\r\n\r\nDEL will remove the recent field and update the view (re-calculate mismatches related to the removed field).\r\n\r\nAnalyze wil show a detailed comparsion of all element values from base file and recent files for the related field in the current list.");
			this->dataGridView_fields->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &RulesWindow::change_field);
			this->dataGridView_fields->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &RulesWindow::click_field);
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
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleCenter;
			dataGridViewCellStyle3->BackColor = System::Drawing::SystemColors::Control;
			this->Column6->DefaultCellStyle = dataGridViewCellStyle3;
			this->Column6->HeaderText = L"Analyze";
			this->Column6->Name = L"Column6";
			this->Column6->Width = 50;
			// 
			// textBox_recentOffset
			// 
			this->textBox_recentOffset->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_recentOffset->Location = System::Drawing::Point(131, 72);
			this->textBox_recentOffset->Name = L"textBox_recentOffset";
			this->textBox_recentOffset->Size = System::Drawing::Size(655, 20);
			this->textBox_recentOffset->TabIndex = 5;
			// 
			// textBox_baseOffset
			// 
			this->textBox_baseOffset->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_baseOffset->Location = System::Drawing::Point(131, 46);
			this->textBox_baseOffset->Name = L"textBox_baseOffset";
			this->textBox_baseOffset->Size = System::Drawing::Size(655, 20);
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
			this->toolTip->SetToolTip(this->radioButton_recentOffset, L"Keep the list offsets from the recent file.\r\nSuspicious offsets are in lists: 0, 20, 100\r\n\r\nFor version 7 base file (1.2.6 server) you have to use base offsets from list 0, 20, 100 !!!");
			this->radioButton_recentOffset->UseVisualStyleBackColor = true;
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
			this->toolTip->SetToolTip(this->radioButton_baseOffset, "Use the list offsets from the base file instead from the recent file.\r\nSuspicious offsets are in lists: 0, 20, 100\r\n\r\nFor version 7 base file (1.2.6 server) you have to use base offsets from list 0, 20, 100 !!!");
			this->radioButton_baseOffset->UseVisualStyleBackColor = true;
			this->radioButton_baseOffset->CheckedChanged += gcnew System::EventHandler(this, &RulesWindow::check_offset);
			// 
			// checkBox_removeList
			// 
			this->checkBox_removeList->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->checkBox_removeList->AutoSize = true;
			this->checkBox_removeList->Location = System::Drawing::Point(701, 21);
			this->checkBox_removeList->Name = L"checkBox_removeList";
			this->checkBox_removeList->Size = System::Drawing::Size(85, 17);
			this->checkBox_removeList->TabIndex = 1;
			this->checkBox_removeList->Text = L"Remove List";
			this->toolTip->SetToolTip(this->checkBox_removeList, L"Remove the selected list.");
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
			this->comboBox_lists->Size = System::Drawing::Size(689, 21);
			this->comboBox_lists->TabIndex = 0;
			this->comboBox_lists->SelectedIndexChanged += gcnew System::EventHandler(this, &RulesWindow::change_list);
			// 
			// button_view
			// 
			this->button_view->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button_view->Location = System::Drawing::Point(346, 546);
			this->button_view->Name = L"button_view";
			this->button_view->Size = System::Drawing::Size(100, 23);
			this->button_view->TabIndex = 2;
			this->button_view->Text = L"View Rules...";
			this->button_view->UseVisualStyleBackColor = true;
			this->button_view->Click += gcnew System::EventHandler(this, &RulesWindow::click_viewRules);
			// 
			// button_import
			// 
			this->button_import->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button_import->Location = System::Drawing::Point(240, 546);
			this->button_import->Name = L"button_import";
			this->button_import->Size = System::Drawing::Size(100, 23);
			this->button_import->TabIndex = 2;
			this->button_import->Text = L"Import Rules...";
			this->button_import->UseVisualStyleBackColor = true;
			this->button_import->Click += gcnew System::EventHandler(this, &RulesWindow::click_importRules);
			// 
			// button_export
			// 
			this->button_export->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button_export->Location = System::Drawing::Point(452, 546);
			this->button_export->Name = L"button_export";
			this->button_export->Size = System::Drawing::Size(100, 23);
			this->button_export->TabIndex = 2;
			this->button_export->Text = L"Export Rules...";
			this->button_export->UseVisualStyleBackColor = true;
			this->button_export->Click += gcnew System::EventHandler(this, &RulesWindow::click_exportRules);
			// 
			// toolTip
			// 
			this->toolTip->AutomaticDelay = 0;
			this->toolTip->AutoPopDelay = 25000;
			this->toolTip->InitialDelay = 0;
			this->toolTip->ReshowDelay = 0;
			// 
			// RulesWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(792, 573);
			this->Controls->Add(this->button_view);
			this->Controls->Add(this->button_import);
			this->Controls->Add(this->button_export);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"RulesWindow";
			this->ShowIcon = false;
			this->Text = L"Element Structure Diff (Rules GUI)";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView_values))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView_fields))->EndInit();
			this->ResumeLayout(false);
			this->MinimumSize = System::Drawing::Size(860, 600);
		}
#pragma endregion

	private: int count_mismatches(int listIndex, int baseFieldIndex, int recentFieldIndex)
	{
		int mismatches = 0;

		if(eRules[listIndex]->RemoveValues[recentFieldIndex])
		{
			return -1;
		}

		if(baseFieldIndex >= eLC_base->Lists[listIndex]->elementFields->Length)
		{
			return -1; //eLC_recent->Lists[listIndex]->elementValues->Length;
		}

		if(recentFieldIndex >= eLC_recent->Lists[listIndex]->elementFields->Length)
		{
			return -1; //eLC_base->Lists[listIndex]->elementValues->Length;
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
			this->Column1->HeaderText = "Base Fields";
			this->Column2->HeaderText = "Recent Fields";
			this->Column7->HeaderText = L"Base Values";
			this->Column8->HeaderText = L"Recent Values";
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
					for(int f=0; f<eRules[l]->RemoveValues->Length; f++)
					{
						eRules[l]->RemoveValues[f] = false;
					}
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
		this->Column1->HeaderText = "Base Fields";
		this->Column2->HeaderText = "Recent Fields";
		this->Column7->HeaderText = L"Base Values";
		this->Column8->HeaderText = L"Recent Values";

		int l = comboBox_lists->SelectedIndex;

		if(l > -1)
		{
			checkBox_removeList->Checked = eRules[l]->RemoveList;

			if(eLC_base->Lists->Length > l && eLC_base->ConversationListIndex != l)
			{
				this->Column1->HeaderText = "Base Fields (" + eLC_base->Lists[l]->elementFields->Length.ToString() + ")";
				this->Column2->HeaderText = "Recent Fields (" + eLC_recent->Lists[l]->elementFields->Length.ToString() + ")";

				int baseFieldIndex = 0;
				int recentFieldIndex = 0;

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
					if(eRules[l]->RemoveValues[f])
					{
						baseFieldIndex--;
					}

					if(eRules[l]->RemoveValues[f] || baseFieldIndex >= eLC_base->Lists[l]->elementFields->Length)
					{
						dataGridView_fields->Rows->Add(gcnew array<String^>{"", eLC_recent->Lists[l]->elementTypes[recentFieldIndex], count_mismatches(l, baseFieldIndex, recentFieldIndex).ToString(), eRules[l]->RemoveValues[f].ToString(), "Details"});
					}
					else
					{
						dataGridView_fields->Rows->Add(gcnew array<String^>{eLC_base->Lists[l]->elementTypes[baseFieldIndex], eLC_recent->Lists[l]->elementTypes[recentFieldIndex], count_mismatches(l, baseFieldIndex, recentFieldIndex).ToString(), eRules[l]->RemoveValues[f].ToString(), "Details"});
					}
					dataGridView_fields->Rows[dataGridView_fields->Rows->Count-1]->HeaderCell->Value = f.ToString();
					baseFieldIndex++;
					recentFieldIndex++;
				}
			}
			else
			{
				//
			}
		}

		Cursor = Windows::Forms::Cursors::Default;
	}

	private: System::Void check_removeList(System::Object^  sender, System::EventArgs^  e)
	{
		int l = comboBox_lists->SelectedIndex;
		if(l > -1)
		{
			eRules[l]->RemoveList = checkBox_removeList->Checked;
		}
	}

	private: System::Void check_offset(System::Object^  sender, System::EventArgs^  e)
	{
		int l = comboBox_lists->SelectedIndex;
		if(l > -1)
		{
			if(radioButton_baseOffset->Checked)
			{
				eRules[l]->ReplaceOffset = true;
				eRules[l]->Offset = eLC_base->GetOffset(l);
			}
			else
			{
				eRules[l]->ReplaceOffset = false;
				eRules[l]->Offset = "";
			}
		}
	}

	private: System::Void change_field(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e)
	{
	}

	private: System::Void click_field(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e)
	{
		int l = comboBox_lists->SelectedIndex;
		if(l > -1 && e->ColumnIndex == 3 && e->RowIndex > -1)
		{
			int displayRow = dataGridView_fields->FirstDisplayedCell->RowIndex;
			int displayCol = dataGridView_fields->FirstDisplayedCell->ColumnIndex;
			// click event don't has new state, we need to access next state property: EditedFormattedValue
			eRules[l]->RemoveValues[e->RowIndex] = Convert::ToBoolean(dataGridView_fields->Rows[e->RowIndex]->Cells[e->ColumnIndex]->EditedFormattedValue);
			change_list(nullptr, nullptr);
			dataGridView_fields->FirstDisplayedCell = dataGridView_fields->Rows[displayRow]->Cells[displayCol];
		}

		if(l > -1 && e->ColumnIndex == 4 && e->RowIndex > -1/* && !eRules[l]->RemoveValues[e->RowIndex]*/)
		{
			Cursor = Windows::Forms::Cursors::AppStarting;

			dataGridView_values->Rows->Clear();
			this->Column7->HeaderText = L"Base Values";
			this->Column8->HeaderText = L"Recent Values";

			int baseFieldIndex = 0;
			int recentFieldIndex = 0;

			for(int f=0; f<e->RowIndex; f++)
			{
				if(eRules[l]->RemoveValues[f])
				{
					baseFieldIndex--;
				}
				baseFieldIndex++;
				recentFieldIndex++;
			}

			if(recentFieldIndex < eLC_recent->Lists[l]->elementFields->Length)
			{
				this->Column7->HeaderText = L"Base Values (" + eLC_base->Lists[l]->elementValues->Length.ToString() + ")";
				this->Column8->HeaderText = L"Recent Values (" + eLC_recent->Lists[l]->elementValues->Length.ToString() + ")";

				for(int i=0; i<eLC_recent->Lists[l]->elementValues->Length; i++)
				{
					if(i < eLC_base->Lists[l]->elementValues->Length && baseFieldIndex < eLC_base->Lists[l]->elementFields->Length && !eRules[l]->RemoveValues[recentFieldIndex])
					{
						dataGridView_values->Rows->Add(gcnew array<String^>{eLC_base->GetValue(l, i, baseFieldIndex), eLC_recent->GetValue(l, i, recentFieldIndex)});
					}
					else
					{
						dataGridView_values->Rows->Add(gcnew array<String^>{"", eLC_recent->GetValue(l, i, recentFieldIndex)});
					}
					dataGridView_values->Rows[dataGridView_values->Rows->Count-1]->HeaderCell->Value = i.ToString();
				}
			}

			Cursor = Windows::Forms::Cursors::Default;
		}
	}
	private: System::Void click_viewRules(System::Object^  sender, System::EventArgs^  e)
	{
		if(eRules)
		{
			String^ message = "";
			message += "##############################\r\n";
			message += "#### RULES FOR v" + eLC_recent->Version.ToString() + " -> v" + eLC_base->Version.ToString() + " ####\r\n";
			message += "##############################\r\n";

			message += "\r\nSETVERSION|" + eLC_base->Version.ToString();
			message += "\r\nSETSIGNATURE|" + eLC_base->Signature.ToString() + "\r\n";

			// find all remove lists
			for(int l=0; l<eRules->Length; l++)
			{
				if(eRules[l]->RemoveList)
				{
					message += "\r\nREMOVELIST:" + l.ToString();
				}
			}

			message += "\r\n";

			// find all replace offsets
			for(int l=0; l<eRules->Length; l++)
			{
				if(eRules[l]->ReplaceOffset)
				{
					message += "\r\nREPLACEOFFSET:" + l.ToString() + "|" + eRules[l]->Offset;
				}
			}

			// find all remove values
			bool breakLine = true;
			for(int l=0; l<eRules->Length; l++)
			{
				if(breakLine)
				{
					message += "\r\n";
					breakLine = false;
				}

				for(int f=0; f<eRules[l]->RemoveValues->Length; f++)
				{
					if(eRules[l]->RemoveValues[f])
					{
						message += "\r\nREMOVEVALUE:" + l.ToString() + ":" + f.ToString();
						breakLine = true;
					}
				}
			}

			gcnew DebugWindow("Rules v" + eLC_recent->Version.ToString() + " -> v" + eLC_base->Version.ToString(), message);
		}
	}
	private: System::Void click_importRules(System::Object^  sender, System::EventArgs^  e)
	{
		if(eRules)
		{
			OpenFileDialog^ rLoad = gcnew OpenFileDialog();
			rLoad->Filter = "Rules File (*.rules)|*.rules|All Files (*.*)|*.*";
			if(rLoad->ShowDialog() == Windows::Forms::DialogResult::OK && File::Exists(rLoad->FileName))
			{
				Cursor = Windows::Forms::Cursors::AppStarting;

				StreamReader^ sr = gcnew StreamReader(rLoad->FileName);

				array<String^>^ values;
				String^ line;
				while((line = sr->ReadLine()))
				{
					System::Windows::Forms::Application::DoEvents();

					if(line != "" && !line->StartsWith("#"))
					{
						// use SETVERSION & SETSIGNATURE from eLC_base instead from rules
						/*
						if(line->StartsWith("SETVERSION|"))
						{
						}
						if(line->StartsWith("SETSIGNATURE|"))
						{
						}
						*/
						if(line->StartsWith("REMOVELIST:"))
						{
							values = line->Split(gcnew array<wchar_t>{':'});
							eRules[Convert::ToInt32(values[1])]->RemoveList = true;
						}
						if(line->StartsWith("REPLACEOFFSET:"))
						{
							values = line->Split(gcnew array<wchar_t>{':', '|'});
							int l = Convert::ToInt32(values[1]);
							eRules[l]->ReplaceOffset = true;
							// use offset from eLC_base instead the one from rules
							eRules[l]->Offset = eLC_base->GetOffset(l); // eRules[l]->Offset = values[2];
						}
						if(line->StartsWith("REMOVEVALUE:"))
						{
							values = line->Split(gcnew array<wchar_t>{':'});
							eRules[Convert::ToInt32(values[1])]->RemoveValues[Convert::ToInt32(values[2])] = true;
						}
					}
				}

				sr->Close();

				change_list(nullptr, nullptr);

				Cursor = Windows::Forms::Cursors::Default;
			}
		}
	}
	private: System::Void click_exportRules(System::Object^  sender, System::EventArgs^  e)
	{
		if(eRules)
		{
			SaveFileDialog^ rSave = gcnew SaveFileDialog();
			rSave->Filter = "Rules File (*.rules)|*.rules|All Files (*.*)|*.*";
			rSave->FileName = "PW_v" + eLC_recent->Version.ToString() + " = PW_v" + eLC_base->Version.ToString() + ".rules";
			if(rSave->ShowDialog() == Windows::Forms::DialogResult::OK)
			{
				Cursor = Windows::Forms::Cursors::AppStarting;

				StreamWriter^ sw = gcnew StreamWriter(rSave->FileName);

				sw->WriteLine("##############################");
				sw->WriteLine("#### RULES FOR v" + eLC_recent->Version.ToString() + " -> v" + eLC_base->Version.ToString() + " ####");
				sw->WriteLine("##############################");

				sw->WriteLine();

				sw->WriteLine("SETVERSION|" + eLC_base->Version.ToString());
				sw->WriteLine("SETSIGNATURE|" + eLC_base->Signature.ToString());

				sw->WriteLine();

				// find all remove lists
				for(int l=0; l<eRules->Length; l++)
				{
					if(eRules[l]->RemoveList)
					{
						sw->WriteLine("REMOVELIST:" + l.ToString());
					}
				}

				sw->WriteLine();

				// find all replace offsets
				for(int l=0; l<eRules->Length; l++)
				{
					if(eRules[l]->ReplaceOffset)
					{
						sw->WriteLine("REPLACEOFFSET:" + l.ToString() + "|" + eRules[l]->Offset);
					}
				}

				// find all remove values
				bool breakLine = true;
				for(int l=0; l<eRules->Length; l++)
				{
					if(breakLine)
					{
						sw->WriteLine();
						breakLine = false;
					}

					for(int f=0; f<eRules[l]->RemoveValues->Length; f++)
					{
						if(eRules[l]->RemoveValues[f])
						{
							sw->WriteLine("REMOVEVALUE:" + l.ToString() + ":" + f.ToString());
							breakLine = true;
						}
					}
				}

				sw->Close();

				Cursor = Windows::Forms::Cursors::Default;
			}
		}
	}
};