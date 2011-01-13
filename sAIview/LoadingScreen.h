#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


	/// <summary>
	/// Summary for LoadingScreen
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class LoadingScreen : public System::Windows::Forms::Form
	{
	public:
		LoadingScreen(void)
		{
			InitializeComponent();
			this->Icon = (Drawing::Icon^)((gcnew Resources::ResourceManager("sTools.icons", Reflection::Assembly::GetExecutingAssembly()))->GetObject("app"));
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LoadingScreen()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ProgressBar^  progressBar1;

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
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(27, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(259, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Initializing Bing Translation Online Service...";
			// 
			// progressBar1
			// 
			this->progressBar1->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->progressBar1->Location = System::Drawing::Point(12, 25);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(288, 19);
			this->progressBar1->Style = System::Windows::Forms::ProgressBarStyle::Marquee;
			this->progressBar1->TabIndex = 1;
			// 
			// LoadingScreen
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(312, 56);
			this->ControlBox = false;
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->label1);
			this->MaximumSize = System::Drawing::Size(320, 64);
			this->MinimumSize = System::Drawing::Size(320, 64);
			this->Name = L"LoadingScreen";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};