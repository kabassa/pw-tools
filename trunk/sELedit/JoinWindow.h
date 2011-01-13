#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

	/// <summary>
	/// Summary for JoinWindow
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class JoinWindow : public System::Windows::Forms::Form
	{
	public:
		JoinWindow(void)
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
		~JoinWindow()
		{
			if (components)
			{
				delete components;
			}
		}

		private: String^ fileName;
		public: property String^ FileName 
		{ 
			String^ get(void)
			{
				return fileName;
			}
			void set(String^ value)
			{
				fileName = value;
				//textBox_ElementFile->Text = fileName;
			}
		}
		private: String^ logDirectory;
		public: property String^ LogDirectory 
		{ 
			String^ get(void)
			{
				return logDirectory;
			}
			void set(String^ value)
			{
				logDirectory = value;
				//textBox_LogDir->Text = logDirectory;
			}
		}		
		public: bool AddNew;
		public: bool BackupNew;
		public: bool ReplaceChanged;
		public: bool BackupChanged;
		public: bool RemoveMissing;
		public: bool BackupMissing;

		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::Label^  label3;
		private: System::Windows::Forms::Label^  label4;
		private: System::Windows::Forms::Label^  label5;
		private: System::Windows::Forms::TextBox^  textBox_ElementFile;
		private: System::Windows::Forms::Button^  button_BrowseEL;
		private: System::Windows::Forms::TextBox^  textBox_LogDir;
		private: System::Windows::Forms::Button^  button_BrowseLog;
		private: System::Windows::Forms::CheckBox^  checkBox_AddNew;
		private: System::Windows::Forms::CheckBox^  checkBox_BackupNew;
		private: System::Windows::Forms::CheckBox^  checkBox_ReplaceChanged;
		private: System::Windows::Forms::CheckBox^  checkBox_BackupChanged;
		private: System::Windows::Forms::CheckBox^  checkBox_RemoveMissing;
		private: System::Windows::Forms::CheckBox^  checkBox_BackupMissing;
		private: System::Windows::Forms::Button^  button_OK;
		private: System::Windows::Forms::Button^  button_Cancel;
		private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox_ElementFile = (gcnew System::Windows::Forms::TextBox());
			this->button_BrowseEL = (gcnew System::Windows::Forms::Button());
			this->textBox_LogDir = (gcnew System::Windows::Forms::TextBox());
			this->button_BrowseLog = (gcnew System::Windows::Forms::Button());
			this->checkBox_AddNew = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_BackupNew = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_ReplaceChanged = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_BackupChanged = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_RemoveMissing = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_BackupMissing = (gcnew System::Windows::Forms::CheckBox());
			this->button_OK = (gcnew System::Windows::Forms::Button());
			this->button_Cancel = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(89, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Join Element File:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 46);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(73, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Log Directory:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 93);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(60, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"New Items:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 116);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(81, 13);
			this->label4->TabIndex = 3;
			this->label4->Text = L"Changed Items:";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(12, 139);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(73, 13);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Missing Items:";
			// 
			// textBox_ElementFile
			// 
			this->textBox_ElementFile->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_ElementFile->Location = System::Drawing::Point(107, 14);
			this->textBox_ElementFile->Name = L"textBox_ElementFile";
			this->textBox_ElementFile->Size = System::Drawing::Size(304, 20);
			this->textBox_ElementFile->TabIndex = 5;
			// 
			// button_BrowseEL
			// 
			this->button_BrowseEL->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button_BrowseEL->Location = System::Drawing::Point(417, 12);
			this->button_BrowseEL->Name = L"button_BrowseEL";
			this->button_BrowseEL->Size = System::Drawing::Size(75, 23);
			this->button_BrowseEL->TabIndex = 6;
			this->button_BrowseEL->Text = L"Browse...";
			this->button_BrowseEL->UseVisualStyleBackColor = true;
			this->button_BrowseEL->Click += gcnew System::EventHandler(this, &JoinWindow::click_BrowseEL);
			// 
			// textBox_LogDir
			// 
			this->textBox_LogDir->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_LogDir->Location = System::Drawing::Point(107, 43);
			this->textBox_LogDir->Name = L"textBox_LogDir";
			this->textBox_LogDir->Size = System::Drawing::Size(304, 20);
			this->textBox_LogDir->TabIndex = 7;
			// 
			// button_BrowseLog
			// 
			this->button_BrowseLog->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button_BrowseLog->Location = System::Drawing::Point(417, 41);
			this->button_BrowseLog->Name = L"button_BrowseLog";
			this->button_BrowseLog->Size = System::Drawing::Size(75, 23);
			this->button_BrowseLog->TabIndex = 8;
			this->button_BrowseLog->Text = L"Browse...";
			this->button_BrowseLog->UseVisualStyleBackColor = true;
			this->button_BrowseLog->Click += gcnew System::EventHandler(this, &JoinWindow::click_BrowseLog);
			// 
			// checkBox_AddNew
			// 
			this->checkBox_AddNew->AutoSize = true;
			this->checkBox_AddNew->Checked = true;
			this->checkBox_AddNew->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox_AddNew->Location = System::Drawing::Point(107, 92);
			this->checkBox_AddNew->Name = L"checkBox_AddNew";
			this->checkBox_AddNew->Size = System::Drawing::Size(98, 17);
			this->checkBox_AddNew->TabIndex = 9;
			this->checkBox_AddNew->Text = L"Add New Items";
			this->checkBox_AddNew->UseVisualStyleBackColor = true;
			// 
			// checkBox_BackupNew
			// 
			this->checkBox_BackupNew->AutoSize = true;
			this->checkBox_BackupNew->Location = System::Drawing::Point(253, 92);
			this->checkBox_BackupNew->Name = L"checkBox_BackupNew";
			this->checkBox_BackupNew->Size = System::Drawing::Size(204, 17);
			this->checkBox_BackupNew->TabIndex = 10;
			this->checkBox_BackupNew->Text = L"Export Added Items into Log Directory";
			this->checkBox_BackupNew->UseVisualStyleBackColor = true;
			// 
			// checkBox_ReplaceChanged
			// 
			this->checkBox_ReplaceChanged->AutoSize = true;
			this->checkBox_ReplaceChanged->Location = System::Drawing::Point(107, 115);
			this->checkBox_ReplaceChanged->Name = L"checkBox_ReplaceChanged";
			this->checkBox_ReplaceChanged->Size = System::Drawing::Size(140, 17);
			this->checkBox_ReplaceChanged->TabIndex = 11;
			this->checkBox_ReplaceChanged->Text = L"Replace Changed Items";
			this->checkBox_ReplaceChanged->UseVisualStyleBackColor = true;
			// 
			// checkBox_BackupChanged
			// 
			this->checkBox_BackupChanged->AutoSize = true;
			this->checkBox_BackupChanged->Location = System::Drawing::Point(253, 115);
			this->checkBox_BackupChanged->Name = L"checkBox_BackupChanged";
			this->checkBox_BackupChanged->Size = System::Drawing::Size(219, 17);
			this->checkBox_BackupChanged->TabIndex = 12;
			this->checkBox_BackupChanged->Text = L"Export Replaced Items into Log Directory";
			this->checkBox_BackupChanged->UseVisualStyleBackColor = true;
			// 
			// checkBox_RemoveMissing
			// 
			this->checkBox_RemoveMissing->AutoSize = true;
			this->checkBox_RemoveMissing->Location = System::Drawing::Point(107, 138);
			this->checkBox_RemoveMissing->Name = L"checkBox_RemoveMissing";
			this->checkBox_RemoveMissing->Size = System::Drawing::Size(132, 17);
			this->checkBox_RemoveMissing->TabIndex = 13;
			this->checkBox_RemoveMissing->Text = L"Remove Missing Items";
			this->checkBox_RemoveMissing->UseVisualStyleBackColor = true;
			// 
			// checkBox_BackupMissing
			// 
			this->checkBox_BackupMissing->AutoSize = true;
			this->checkBox_BackupMissing->Location = System::Drawing::Point(253, 138);
			this->checkBox_BackupMissing->Name = L"checkBox_BackupMissing";
			this->checkBox_BackupMissing->Size = System::Drawing::Size(219, 17);
			this->checkBox_BackupMissing->TabIndex = 14;
			this->checkBox_BackupMissing->Text = L"Export Removed Items into Log Directory";
			this->checkBox_BackupMissing->UseVisualStyleBackColor = true;
			// 
			// button_OK
			// 
			this->button_OK->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button_OK->Location = System::Drawing::Point(174, 178);
			this->button_OK->Name = L"button_OK";
			this->button_OK->Size = System::Drawing::Size(75, 23);
			this->button_OK->TabIndex = 15;
			this->button_OK->Text = L"OK";
			this->button_OK->UseVisualStyleBackColor = true;
			this->button_OK->Click += gcnew System::EventHandler(this, &JoinWindow::click_OK);
			// 
			// button_Cancel
			// 
			this->button_Cancel->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->button_Cancel->Location = System::Drawing::Point(255, 178);
			this->button_Cancel->Name = L"button_Cancel";
			this->button_Cancel->Size = System::Drawing::Size(75, 23);
			this->button_Cancel->TabIndex = 16;
			this->button_Cancel->Text = L"Cancel";
			this->button_Cancel->UseVisualStyleBackColor = true;
			this->button_Cancel->Click += gcnew System::EventHandler(this, &JoinWindow::click_Cancel);
			// 
			// JoinWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(504, 213);
			this->ControlBox = false;
			this->Controls->Add(this->button_Cancel);
			this->Controls->Add(this->button_OK);
			this->Controls->Add(this->checkBox_BackupMissing);
			this->Controls->Add(this->checkBox_RemoveMissing);
			this->Controls->Add(this->checkBox_BackupChanged);
			this->Controls->Add(this->checkBox_ReplaceChanged);
			this->Controls->Add(this->checkBox_BackupNew);
			this->Controls->Add(this->checkBox_AddNew);
			this->Controls->Add(this->button_BrowseLog);
			this->Controls->Add(this->textBox_LogDir);
			this->Controls->Add(this->button_BrowseEL);
			this->Controls->Add(this->textBox_ElementFile);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->MaximumSize = System::Drawing::Size(512, 240);
			this->MinimumSize = System::Drawing::Size(512, 240);
			this->Name = L"JoinWindow";
			this->ShowIcon = false;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Join Settings";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void click_OK(System::Object^  sender, System::EventArgs^  e)
	{
		fileName = textBox_ElementFile->Text;
		logDirectory = textBox_LogDir->Text;
		AddNew = checkBox_AddNew->Checked;
		BackupNew = checkBox_BackupNew->Checked;
		ReplaceChanged = checkBox_ReplaceChanged->Checked;
		BackupChanged = checkBox_BackupChanged->Checked;
		RemoveMissing = checkBox_RemoveMissing->Checked;
		BackupMissing = checkBox_BackupMissing->Checked;

		this->DialogResult = Windows::Forms::DialogResult::OK;
		this->Close();
	}
	private: System::Void click_BrowseEL(System::Object^  sender, System::EventArgs^  e)
	{
		OpenFileDialog^ load = gcnew OpenFileDialog();
		load->Filter = "Elements File (*.data)|*.data|All Files (*.*)|*.*";
		if(load->ShowDialog() == Windows::Forms::DialogResult::OK && System::IO::File::Exists(load->FileName))
		{
			textBox_ElementFile->Text = load->FileName;
		}
	}
	private: System::Void click_BrowseLog(System::Object^  sender, System::EventArgs^  e)
	{
		FolderBrowserDialog^load = gcnew FolderBrowserDialog();
		if(load->ShowDialog() == Windows::Forms::DialogResult::OK && System::IO::Directory::Exists(load->SelectedPath))
		{
			textBox_LogDir->Text = load->SelectedPath;
		}
	}
	private: System::Void click_Cancel(System::Object^  sender, System::EventArgs^  e)
	{
		this->DialogResult = Windows::Forms::DialogResult::Cancel;
		this->Close();
	}
};
