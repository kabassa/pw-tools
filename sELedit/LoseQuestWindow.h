#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


	/// <summary>
	/// Summary for LoseQuestWindow
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class LoseQuestWindow : public System::Windows::Forms::Form
	{
	public:
		LoseQuestWindow(void)
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
		~LoseQuestWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected: 
	private: System::Windows::Forms::Label^  label2;
	public: System::Windows::Forms::ListBox^  listBox_Receive;
	private: 
	public: System::Windows::Forms::ListBox^  listBox_Activate;
	private: System::Windows::Forms::WebBrowser^  webBrowser;
	public: 

	public: 





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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->listBox_Receive = (gcnew System::Windows::Forms::ListBox());
			this->listBox_Activate = (gcnew System::Windows::Forms::ListBox());
			this->webBrowser = (gcnew System::Windows::Forms::WebBrowser());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(-3, 3);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Receive:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(-3, 318);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(58, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Activate:";
			// 
			// listBox_Receive
			// 
			this->listBox_Receive->FormattingEnabled = true;
			this->listBox_Receive->Location = System::Drawing::Point(0, 19);
			this->listBox_Receive->Name = L"listBox_Receive";
			this->listBox_Receive->Size = System::Drawing::Size(200, 277);
			this->listBox_Receive->TabIndex = 2;
			this->listBox_Receive->SelectedIndexChanged += gcnew System::EventHandler(this, &LoseQuestWindow::select_quest);
			// 
			// listBox_Activate
			// 
			this->listBox_Activate->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->listBox_Activate->FormattingEnabled = true;
			this->listBox_Activate->Location = System::Drawing::Point(0, 334);
			this->listBox_Activate->Name = L"listBox_Activate";
			this->listBox_Activate->Size = System::Drawing::Size(200, 277);
			this->listBox_Activate->TabIndex = 3;
			// 
			// webBrowser
			// 
			this->webBrowser->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->webBrowser->Location = System::Drawing::Point(206, 3);
			this->webBrowser->MinimumSize = System::Drawing::Size(20, 20);
			this->webBrowser->Name = L"webBrowser";
			this->webBrowser->Size = System::Drawing::Size(785, 608);
			this->webBrowser->TabIndex = 4;
			this->webBrowser->Url = (gcnew System::Uri(L"http://www.pwdatabase.com/pwi/quests", System::UriKind::Absolute));
			// 
			// LoseQuestWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(992, 613);
			this->Controls->Add(this->webBrowser);
			this->Controls->Add(this->listBox_Activate);
			this->Controls->Add(this->listBox_Receive);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(1000, 640);
			this->Name = L"LoseQuestWindow";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Lost Quests (1.4.3 -> 1.3.6)";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void select_quest(System::Object^  sender, System::EventArgs^  e)
	{
		if(((ListBox^)sender)->SelectedIndex > -1 && !((ListBox^)sender)->SelectedItem->ToString()->StartsWith("+"))
		{
			webBrowser->Url = gcnew Uri("http://www.pwdatabase.com/pwi/quest/" + ((ListBox^)sender)->SelectedItem->ToString());
		}
	}
};