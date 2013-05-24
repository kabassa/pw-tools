#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;



	/// <summary>
	/// Summary for ReferencesWindow
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class ReferencesWindow : public System::Windows::Forms::Form
	{
	public:
		ReferencesWindow(void)
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
		~ReferencesWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::DataGridView^  dataGridView;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ListIDColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  ListColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  IDColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  NameColumn;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  FieldColumn;
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
			this->dataGridView = (gcnew System::Windows::Forms::DataGridView());
			this->ListIDColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->ListColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->IDColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->NameColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->FieldColumn = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView))->BeginInit();
			this->SuspendLayout();
			// 
			// dataGridView
			// 
			this->dataGridView->AllowUserToAddRows = false;
			this->dataGridView->AllowUserToDeleteRows = false;
			this->dataGridView->AllowUserToOrderColumns = true;
			this->dataGridView->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->dataGridView->BackgroundColor = System::Drawing::SystemColors::Window;
			this->dataGridView->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			this->dataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->dataGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {this->ListIDColumn, 
				this->ListColumn, this->IDColumn, this->NameColumn, this->FieldColumn});
			this->dataGridView->Location = System::Drawing::Point(12, 13);
			this->dataGridView->MultiSelect = false;
			this->dataGridView->Name = L"dataGridView";
			this->dataGridView->RowHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(134)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridView->RowHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->dataGridView->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dataGridView->Size = System::Drawing::Size(499, 619);
			this->dataGridView->TabIndex = 0;
			this->dataGridView->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &ReferencesWindow::dataGridView_MouseDoubleClick);
			// 
			// ListIDColumn
			// 
			this->ListIDColumn->HeaderText = L"ListID";
			this->ListIDColumn->Name = L"ListIDColumn";
			this->ListIDColumn->Visible = false;
			// 
			// ListColumn
			// 
			this->ListColumn->HeaderText = L"List";
			this->ListColumn->Name = L"ListColumn";
			this->ListColumn->ReadOnly = true;
			this->ListColumn->Width = 125;
			// 
			// IDColumn
			// 
			this->IDColumn->HeaderText = L"ID";
			this->IDColumn->Name = L"IDColumn";
			this->IDColumn->ReadOnly = true;
			this->IDColumn->Width = 50;
			// 
			// NameColumn
			// 
			this->NameColumn->HeaderText = L"Name";
			this->NameColumn->Name = L"NameColumn";
			this->NameColumn->ReadOnly = true;
			this->NameColumn->Width = 140;
			// 
			// FieldColumn
			// 
			this->FieldColumn->HeaderText = L"field";
			this->FieldColumn->Name = L"FieldColumn";
			this->FieldColumn->ReadOnly = true;
			this->FieldColumn->Width = 123;
			// 
			// ReferencesWindow
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(523, 644);
			this->Controls->Add(this->dataGridView);
			this->Name = L"ReferencesWindow";
			this->ShowIcon = false;
			this->Text = L"Results";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataGridView))->EndInit();
			this->ResumeLayout(false);

		}
		public: System::Void dataGridView_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  ea)
		{
			int l = int::Parse(Convert::ToString(dataGridView->Rows[dataGridView->CurrentCell->RowIndex]->Cells[0]->Value));
			int e = int::Parse(Convert::ToString(dataGridView->Rows[dataGridView->CurrentCell->RowIndex]->Cells[2]->Value));
			MessageBox::Show("Clickable in future");
		}

#pragma endregion
};