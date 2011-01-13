#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public ref class ConfigWindow : public System::Windows::Forms::Form
{
	public:
	ConfigWindow(void)
	{
		InitializeComponent();
	}

	protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~ConfigWindow()
	{
		if (components)
		{
			delete components;
		}
	}

	array<String^>^ listNames;
	array<int>^ listOffsets;
	array<array<String^>^>^ fieldNames;
	array<array<String^>^>^ fieldTypes;

	private: System::Windows::Forms::MenuStrip^  menuStrip_mainMenu;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  loadToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ComboBox^  comboBox_lists;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox_listName;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown_offset;
	private: System::Windows::Forms::DataGridView^  dataGridView_item;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip_row;
	private: System::Windows::Forms::ToolStripMenuItem^  addRowToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  deleteRowToolStripMenuItem;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label3;
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
		System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
		this->menuStrip_mainMenu = (gcnew System::Windows::Forms::MenuStrip());
		this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->loadToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->comboBox_lists = (gcnew System::Windows::Forms::ComboBox());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->textBox_listName = (gcnew System::Windows::Forms::TextBox());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->numericUpDown_offset = (gcnew System::Windows::Forms::NumericUpDown());
		this->dataGridView_item = (gcnew System::Windows::Forms::DataGridView());
		this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
		this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
		this->contextMenuStrip_row = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
		this->addRowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->deleteRowToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->button1 = (gcnew System::Windows::Forms::Button());
		this->button2 = (gcnew System::Windows::Forms::Button());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->menuStrip_mainMenu->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown_offset))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView_item))->BeginInit();
		this->contextMenuStrip_row->SuspendLayout();
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
		this->menuStrip_mainMenu->Size = System::Drawing::Size(232, 24);
		this->menuStrip_mainMenu->TabIndex = 1;
		this->menuStrip_mainMenu->Text = L"menuStrip1";
		// 
		// toolStripMenuItem1
		// 
		this->toolStripMenuItem1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->loadToolStripMenuItem, 
			this->saveToolStripMenuItem});
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
		this->loadToolStripMenuItem->Size = System::Drawing::Size(125, 22);
		this->loadToolStripMenuItem->Text = L"Load...";
		this->loadToolStripMenuItem->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		this->loadToolStripMenuItem->Click += gcnew System::EventHandler(this, &ConfigWindow::click_load);
		// 
		// saveToolStripMenuItem
		// 
		this->saveToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
		this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
		this->saveToolStripMenuItem->Size = System::Drawing::Size(125, 22);
		this->saveToolStripMenuItem->Text = L"Save As...";
		this->saveToolStripMenuItem->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
		this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &ConfigWindow::click_save);
		// 
		// comboBox_lists
		// 
		this->comboBox_lists->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
			| System::Windows::Forms::AnchorStyles::Right));
		this->comboBox_lists->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->comboBox_lists->FormattingEnabled = true;
		this->comboBox_lists->Location = System::Drawing::Point(2, 28);
		this->comboBox_lists->Name = L"comboBox_lists";
		this->comboBox_lists->Size = System::Drawing::Size(228, 21);
		this->comboBox_lists->TabIndex = 2;
		this->comboBox_lists->SelectedIndexChanged += gcnew System::EventHandler(this, &ConfigWindow::change_list);
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(-1, 87);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(57, 13);
		this->label1->TabIndex = 3;
		this->label1->Text = L"List Name:";
		// 
		// textBox_listName
		// 
		this->textBox_listName->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
		this->textBox_listName->Location = System::Drawing::Point(96, 84);
		this->textBox_listName->Name = L"textBox_listName";
		this->textBox_listName->Size = System::Drawing::Size(134, 20);
		this->textBox_listName->TabIndex = 4;
		this->textBox_listName->TextChanged += gcnew System::EventHandler(this, &ConfigWindow::change_listName);
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = System::Drawing::Point(-1, 112);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(67, 13);
		this->label2->TabIndex = 5;
		this->label2->Text = L"Offset Bytes:";
		// 
		// numericUpDown_offset
		// 
		this->numericUpDown_offset->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
		this->numericUpDown_offset->Location = System::Drawing::Point(96, 110);
		this->numericUpDown_offset->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {0, 1, 0, 0});
		this->numericUpDown_offset->Name = L"numericUpDown_offset";
		this->numericUpDown_offset->Size = System::Drawing::Size(134, 20);
		this->numericUpDown_offset->TabIndex = 6;
		this->numericUpDown_offset->ValueChanged += gcnew System::EventHandler(this, &ConfigWindow::change_listOffset);
		// 
		// dataGridView_item
		// 
		this->dataGridView_item->AllowUserToAddRows = false;
		this->dataGridView_item->AllowUserToDeleteRows = false;
		this->dataGridView_item->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
			| System::Windows::Forms::AnchorStyles::Left) 
			| System::Windows::Forms::AnchorStyles::Right));
		this->dataGridView_item->BackgroundColor = System::Drawing::SystemColors::Window;
		this->dataGridView_item->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
		this->dataGridView_item->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
		this->dataGridView_item->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {this->Column1, 
			this->Column2});
		this->dataGridView_item->ContextMenuStrip = this->contextMenuStrip_row;
		this->dataGridView_item->Location = System::Drawing::Point(2, 136);
		this->dataGridView_item->MultiSelect = false;
		this->dataGridView_item->Name = L"dataGridView_item";
		this->dataGridView_item->RowHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
		dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
		dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
		dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
		dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
		dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
		dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
		dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
		this->dataGridView_item->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
		this->dataGridView_item->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::AutoSizeToFirstHeader;
		this->dataGridView_item->RowTemplate->Height = 18;
		this->dataGridView_item->RowTemplate->Resizable = System::Windows::Forms::DataGridViewTriState::False;
		this->dataGridView_item->Size = System::Drawing::Size(228, 255);
		this->dataGridView_item->TabIndex = 7;
		this->dataGridView_item->CellValueChanged += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &ConfigWindow::change_row);
		// 
		// Column1
		// 
		this->Column1->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::AllCells;
		this->Column1->HeaderText = L"Name";
		this->Column1->Name = L"Column1";
		this->Column1->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
		this->Column1->Width = 40;
		// 
		// Column2
		// 
		this->Column2->AutoSizeMode = System::Windows::Forms::DataGridViewAutoSizeColumnMode::Fill;
		this->Column2->HeaderText = L"Type";
		this->Column2->Name = L"Column2";
		this->Column2->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
		// 
		// contextMenuStrip_row
		// 
		this->contextMenuStrip_row->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
		this->contextMenuStrip_row->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->addRowToolStripMenuItem, 
			this->deleteRowToolStripMenuItem});
		this->contextMenuStrip_row->Name = L"contextMenuStrip1";
		this->contextMenuStrip_row->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
		this->contextMenuStrip_row->ShowImageMargin = false;
		this->contextMenuStrip_row->Size = System::Drawing::Size(105, 48);
		// 
		// addRowToolStripMenuItem
		// 
		this->addRowToolStripMenuItem->Name = L"addRowToolStripMenuItem";
		this->addRowToolStripMenuItem->Size = System::Drawing::Size(104, 22);
		this->addRowToolStripMenuItem->Text = L"Add Row";
		this->addRowToolStripMenuItem->Click += gcnew System::EventHandler(this, &ConfigWindow::add_row);
		// 
		// deleteRowToolStripMenuItem
		// 
		this->deleteRowToolStripMenuItem->Name = L"deleteRowToolStripMenuItem";
		this->deleteRowToolStripMenuItem->Size = System::Drawing::Size(104, 22);
		this->deleteRowToolStripMenuItem->Text = L"Delete Row";
		this->deleteRowToolStripMenuItem->Click += gcnew System::EventHandler(this, &ConfigWindow::delete_row);
		// 
		// button1
		// 
		this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
		this->button1->Location = System::Drawing::Point(166, 55);
		this->button1->Name = L"button1";
		this->button1->Size = System::Drawing::Size(64, 23);
		this->button1->TabIndex = 8;
		this->button1->Text = L"Delete";
		this->button1->UseVisualStyleBackColor = true;
		this->button1->Click += gcnew System::EventHandler(this, &ConfigWindow::click_deleteList);
		// 
		// button2
		// 
		this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
		this->button2->Location = System::Drawing::Point(96, 55);
		this->button2->Name = L"button2";
		this->button2->Size = System::Drawing::Size(64, 23);
		this->button2->TabIndex = 9;
		this->button2->Text = L"Add New";
		this->button2->UseVisualStyleBackColor = true;
		this->button2->Click += gcnew System::EventHandler(this, &ConfigWindow::click_addList);
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = System::Drawing::Point(-1, 60);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(26, 13);
		this->label3->TabIndex = 10;
		this->label3->Text = L"List:";
		// 
		// ConfigWindow
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(232, 393);
		this->Controls->Add(this->dataGridView_item);
		this->Controls->Add(this->button2);
		this->Controls->Add(this->comboBox_lists);
		this->Controls->Add(this->label3);
		this->Controls->Add(this->button1);
		this->Controls->Add(this->numericUpDown_offset);
		this->Controls->Add(this->label2);
		this->Controls->Add(this->textBox_listName);
		this->Controls->Add(this->menuStrip_mainMenu);
		this->Controls->Add(this->label1);
		this->MaximizeBox = false;
		this->MinimizeBox = false;
		this->MinimumSize = System::Drawing::Size(240, 420);
		this->Name = L"ConfigWindow";
		this->ShowIcon = false;
		this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
		this->Text = L" Configuration Editor";
		this->menuStrip_mainMenu->ResumeLayout(false);
		this->menuStrip_mainMenu->PerformLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown_offset))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView_item))->EndInit();
		this->contextMenuStrip_row->ResumeLayout(false);
		this->ResumeLayout(false);
		this->PerformLayout();

	}
#pragma endregion

	private: System::Void click_load(System::Object^  sender, System::EventArgs^  e)
	{
		OpenFileDialog^ cLoad = gcnew OpenFileDialog();
		cLoad->InitialDirectory = Application::StartupPath + "\\configs";
		cLoad->Filter = "EL Configuration File (*.cfg)|*.cfg|All Files (*.*)|*.*";
		if(cLoad->ShowDialog() == Windows::Forms::DialogResult::OK && File::Exists(cLoad->FileName))
		{
			StreamReader^ sr = gcnew StreamReader(cLoad->FileName);

			comboBox_lists->Items->Clear();

			int listCount = Convert::ToInt32(sr->ReadLine());

			listNames = gcnew array<String^>(listCount);
			listOffsets = gcnew array<int>(listCount);
			fieldNames = gcnew array<array<String^>^>(listCount);
			fieldTypes = gcnew array<array<String^>^>(listCount);

			String^ line;
			for(int i=0; i<listCount; i++)
			{
				while((line = sr->ReadLine()) == "")
				{
				}
				comboBox_lists->Items->Add("[" + i + "]: " + line);
				listNames[i] = line;
				listOffsets[i] = Convert::ToInt32(sr->ReadLine());
				fieldNames[i] = sr->ReadLine()->Split(gcnew array<wchar_t>{';'});
				fieldTypes[i] = sr->ReadLine()->Split(gcnew array<wchar_t>{';'});
			}
			sr->Close();
		}
	}

	private: System::Void click_save(System::Object^  sender, System::EventArgs^  e)
	{
		SaveFileDialog^ cSave = gcnew SaveFileDialog();
		cSave->InitialDirectory = Application::StartupPath + "\\configs";
		cSave->Filter = "EL Configuration File (*.cfg)|*.cfg|All Files (*.*)|*.*";
		if(cSave->ShowDialog() == Windows::Forms::DialogResult::OK && cSave->FileName != "")
		{
			StreamWriter^ sw = gcnew StreamWriter(cSave->FileName);

			int listCount = listNames->Length;

			sw->WriteLine(listCount);

			for(int i=0; i<listCount; i++)
			{
				sw->WriteLine();
				sw->WriteLine(listNames[i]);
				sw->WriteLine(listOffsets[i]);
				sw->WriteLine(String::Join(";", fieldNames[i]));
				sw->WriteLine(String::Join(";", fieldTypes[i]));
			}

			sw->Close();
		}
	}

	private: System::Void change_list(System::Object^  sender, System::EventArgs^  e)
	{
		if(comboBox_lists->SelectedIndex > -1)
		{
			textBox_listName->Text = listNames[comboBox_lists->SelectedIndex];
			numericUpDown_offset->Value = Convert::ToDecimal(listOffsets[comboBox_lists->SelectedIndex]);
			dataGridView_item->Rows->Clear();
			for(int i=0; i<fieldNames[comboBox_lists->SelectedIndex]->Length; i++)
			{
				dataGridView_item->Rows->Add(gcnew array<String^>{fieldNames[comboBox_lists->SelectedIndex][i], fieldTypes[comboBox_lists->SelectedIndex][i]});
				dataGridView_item->Rows[i]->HeaderCell->Value = i.ToString();
			}
		}
	}

	private: System::Void change_row(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e)
	{
		try
		{
			if(fieldNames && e->ColumnIndex == 0)
			{
				fieldNames[comboBox_lists->SelectedIndex][e->RowIndex] = dataGridView_item[e->ColumnIndex, e->RowIndex]->Value->ToString();
			}
			if(fieldTypes && e->ColumnIndex == 1)
			{
				fieldTypes[comboBox_lists->SelectedIndex][e->RowIndex] = dataGridView_item[e->ColumnIndex, e->RowIndex]->Value->ToString();
			}
		}
		catch(...)
		{
			MessageBox::Show("CHANGING ERROR!\nFailed changing value, this value seems to be invalid.");
		}
	}

	private: System::Void add_row(System::Object^  sender, System::EventArgs^  e)
	{
		if(comboBox_lists->SelectedIndex > -1)
		{
			array<String^>^ temp = gcnew array<String^>(fieldNames[comboBox_lists->SelectedIndex]->Length+1);
			Array::Copy(fieldNames[comboBox_lists->SelectedIndex], 0, temp, 0, dataGridView_item->CurrentCell->RowIndex);
			temp[dataGridView_item->CurrentCell->RowIndex] = "< NAME >";
			Array::Copy(fieldNames[comboBox_lists->SelectedIndex], dataGridView_item->CurrentCell->RowIndex, temp, dataGridView_item->CurrentCell->RowIndex+1, fieldNames[comboBox_lists->SelectedIndex]->Length - dataGridView_item->CurrentCell->RowIndex);
			fieldNames[comboBox_lists->SelectedIndex] = temp;

			temp = gcnew array<String^>(fieldTypes[comboBox_lists->SelectedIndex]->Length+1);
			Array::Copy(fieldTypes[comboBox_lists->SelectedIndex], 0, temp, 0, dataGridView_item->CurrentCell->RowIndex);
			temp[dataGridView_item->CurrentCell->RowIndex] = "< TYPE >";
			Array::Copy(fieldTypes[comboBox_lists->SelectedIndex], dataGridView_item->CurrentCell->RowIndex, temp, dataGridView_item->CurrentCell->RowIndex+1, fieldTypes[comboBox_lists->SelectedIndex]->Length - dataGridView_item->CurrentCell->RowIndex);
			fieldTypes[comboBox_lists->SelectedIndex] = temp;

			change_list(nullptr, nullptr);
		}
	}

	private: System::Void delete_row(System::Object^  sender, System::EventArgs^  e)
	{
		if(comboBox_lists->SelectedIndex > -1)
		{
			array<String^>^ temp = gcnew array<String^>(fieldNames[comboBox_lists->SelectedIndex]->Length-1);
			Array::Copy(fieldNames[comboBox_lists->SelectedIndex], 0, temp, 0, dataGridView_item->CurrentCell->RowIndex);
			Array::Copy(fieldNames[comboBox_lists->SelectedIndex], dataGridView_item->CurrentCell->RowIndex+1, temp, dataGridView_item->CurrentCell->RowIndex, fieldNames[comboBox_lists->SelectedIndex]->Length-1 - dataGridView_item->CurrentCell->RowIndex);
			fieldNames[comboBox_lists->SelectedIndex] = temp;

			temp = gcnew array<String^>(fieldTypes[comboBox_lists->SelectedIndex]->Length-1);
			Array::Copy(fieldTypes[comboBox_lists->SelectedIndex], 0, temp, 0, dataGridView_item->CurrentCell->RowIndex);
			Array::Copy(fieldTypes[comboBox_lists->SelectedIndex], dataGridView_item->CurrentCell->RowIndex+1, temp, dataGridView_item->CurrentCell->RowIndex, fieldTypes[comboBox_lists->SelectedIndex]->Length-1 - dataGridView_item->CurrentCell->RowIndex);
			fieldTypes[comboBox_lists->SelectedIndex] = temp;

			change_list(nullptr, nullptr);
		}
	}

	private: System::Void click_addList(System::Object^  sender, System::EventArgs^  e)
	{
		Array::Resize(listNames, listNames->Length+1);
		listNames[listNames->Length-1] = "< LIST >";
		Array::Resize(listOffsets, listOffsets->Length+1);
		listOffsets[listOffsets->Length-1] = 0;
		Array::Resize(fieldNames, fieldNames->Length+1);
		fieldNames[fieldNames->Length-1] = gcnew array<String^>{"< NAME >"};
		Array::Resize(fieldTypes, fieldTypes->Length+1);
		fieldTypes[fieldTypes->Length-1] = gcnew array<String^>{"< TYPE >"};

		comboBox_lists->Items->Add("[" + (listNames->Length-1) + "]: " + listNames[listNames->Length-1]);
		comboBox_lists->SelectedIndex = comboBox_lists->Items->Count-1;
	}

	private: System::Void click_deleteList(System::Object^  sender, System::EventArgs^  e)
	{
		if(comboBox_lists->SelectedIndex > -1)
		{
			int index = comboBox_lists->SelectedIndex;

			array<int>^ itemp = gcnew array<int>(listOffsets->Length-1);

			Array::Copy(listOffsets, 0, itemp, 0, index);
			Array::Copy(listOffsets, index+1, itemp, index, listOffsets->Length-1 - index);
			listOffsets = itemp;

			array<String^>^ stemp = gcnew array<String^>(listNames->Length-1);

			Array::Copy(listNames, 0, stemp, 0, index);
			Array::Copy(listNames, index+1, stemp, index, listNames->Length-1 - index);
			listNames = stemp;

			array<array<String^>^>^ astemp = gcnew array<array<String^>^>(fieldNames->Length-1);

			Array::Copy(fieldNames, 0, astemp, 0, index);
			Array::Copy(fieldNames, index+1, astemp, index, fieldNames->Length-1 - index);
			fieldNames = astemp;

			astemp = gcnew array<array<String^>^>(fieldTypes->Length-1);

			Array::Copy(fieldTypes, 0, astemp, 0, index);
			Array::Copy(fieldTypes, index+1, astemp, index, fieldTypes->Length-1 - index);
			fieldTypes = astemp;

			dataGridView_item->Rows->Clear();
			comboBox_lists->Items->Clear();

			for(int i=0; i<listNames->Length; i++)
			{
				comboBox_lists->Items->Add("[" + i + "]: " + listNames[i]);
			}

			index--;

			if(index < 0 && comboBox_lists->Items->Count > 0)
			{
				index++;
			}
			comboBox_lists->SelectedIndex = index;
		}
	}

	private: System::Void change_listName(System::Object^  sender, System::EventArgs^  e)
	{
		if(comboBox_lists->SelectedIndex > -1)
		{
			listNames[comboBox_lists->SelectedIndex] = textBox_listName->Text;
			comboBox_lists->Items[comboBox_lists->SelectedIndex] = "[" + comboBox_lists->SelectedIndex + "]: " + textBox_listName->Text;
		}
	}

	private: System::Void change_listOffset(System::Object^  sender, System::EventArgs^  e)
	{
		if(comboBox_lists->SelectedIndex > -1)
		{
			listOffsets[comboBox_lists->SelectedIndex] = Convert::ToInt32(numericUpDown_offset->Value);
		}
	}
};
