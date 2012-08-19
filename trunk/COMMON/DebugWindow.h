#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public ref class DebugWindow : public System::Windows::Forms::Form
{
	public: DebugWindow(void)
	{
		InitializeComponent();
	}

	public: DebugWindow(String^ Title, String^ Message)
	{
		InitializeComponent();
		this->Text = Title;
		this->message->Text = Message;
		this->message->SelectionStart = 0;
		this->message->SelectionLength = 0;
		this->Show();
	}

	protected: ~DebugWindow()
	{
		if (components)
		{
			delete components;
		}
	}
	private: System::Windows::Forms::TextBox^  message;

	private: System::ComponentModel::Container ^components;

	#pragma region Windows Form Designer generated code
	/// <summary>
	/// Required method for Designer support - do not modify
	/// the contents of this method with the code editor.
	/// </summary>
	void InitializeComponent(void)
	{
		this->message = (gcnew System::Windows::Forms::TextBox());
		this->SuspendLayout();
		// 
		// message
		// 
		this->message->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
			| System::Windows::Forms::AnchorStyles::Left) 
			| System::Windows::Forms::AnchorStyles::Right));
		this->message->Font = (gcnew System::Drawing::Font(L"Lucida Console", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
			static_cast<System::Byte>(0)));
		this->message->Location = System::Drawing::Point(0, 2);
		this->message->Multiline = true;
		this->message->Name = L"message";
		this->message->ScrollBars = System::Windows::Forms::ScrollBars::Both;
		this->message->Size = System::Drawing::Size(320, 478);
		this->message->TabIndex = 0;
		this->message->WordWrap = false;
		// 
		// DebugWindow
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(320, 480);
		this->Controls->Add(this->message);
		this->Name = L"DebugWindow";
		this->ShowIcon = false;
		this->Text = L"DebugWindow";
		this->ResumeLayout(false);
		this->PerformLayout();

	}
	#pragma endregion
};