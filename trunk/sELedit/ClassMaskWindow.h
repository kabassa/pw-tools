#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


	/// <summary>
	/// Summary for ClassMaskWindow
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class ClassMaskWindow : public System::Windows::Forms::Form
	{
	public:
		ClassMaskWindow(void)
		{
			InitializeComponent();
			lockCheckBox = false;
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ClassMaskWindow()
		{
			if (components)
			{
				delete components;
			}
		}

		bool lockCheckBox;

	private: System::Windows::Forms::CheckBox^  checkBox_BM;
	private: System::Windows::Forms::CheckBox^  checkBox_WIZ;
	private: System::Windows::Forms::CheckBox^  checkBox_PSY;
	private: System::Windows::Forms::CheckBox^  checkBox_VEN;
	private: System::Windows::Forms::CheckBox^  checkBox_BAR;
	private: System::Windows::Forms::CheckBox^  checkBox_AS;
	private: System::Windows::Forms::CheckBox^  checkBox_AR;
	private: System::Windows::Forms::CheckBox^  checkBox_CLE;
	private: System::Windows::Forms::CheckBox^  checkBox_SE;
	private: System::Windows::Forms::CheckBox^  checkBox_MY;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown_mask;
	protected: 

	protected: 










	private: System::Windows::Forms::Label^  label1;
	protected: 

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
			this->checkBox_BM = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_WIZ = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_PSY = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_VEN = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_BAR = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_AS = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_AR = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_CLE = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_SE = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_MY = (gcnew System::Windows::Forms::CheckBox());
			this->numericUpDown_mask = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown_mask))->BeginInit();
			this->SuspendLayout();
			// 
			// checkBox_BM
			// 
			this->checkBox_BM->AutoSize = true;
			this->checkBox_BM->Location = System::Drawing::Point(12, 12);
			this->checkBox_BM->Name = L"checkBox_BM";
			this->checkBox_BM->Size = System::Drawing::Size(84, 17);
			this->checkBox_BM->TabIndex = 0;
			this->checkBox_BM->Text = L"Blademaster";
			this->checkBox_BM->UseVisualStyleBackColor = true;
			this->checkBox_BM->CheckedChanged += gcnew System::EventHandler(this, &ClassMaskWindow::change_Bin);
			// 
			// checkBox_WIZ
			// 
			this->checkBox_WIZ->AutoSize = true;
			this->checkBox_WIZ->Location = System::Drawing::Point(12, 35);
			this->checkBox_WIZ->Name = L"checkBox_WIZ";
			this->checkBox_WIZ->Size = System::Drawing::Size(59, 17);
			this->checkBox_WIZ->TabIndex = 1;
			this->checkBox_WIZ->Text = L"Wizard";
			this->checkBox_WIZ->UseVisualStyleBackColor = true;
			this->checkBox_WIZ->CheckedChanged += gcnew System::EventHandler(this, &ClassMaskWindow::change_Bin);
			// 
			// checkBox_PSY
			// 
			this->checkBox_PSY->AutoSize = true;
			this->checkBox_PSY->Location = System::Drawing::Point(12, 58);
			this->checkBox_PSY->Name = L"checkBox_PSY";
			this->checkBox_PSY->Size = System::Drawing::Size(63, 17);
			this->checkBox_PSY->TabIndex = 2;
			this->checkBox_PSY->Text = L"Psychic";
			this->checkBox_PSY->UseVisualStyleBackColor = true;
			this->checkBox_PSY->CheckedChanged += gcnew System::EventHandler(this, &ClassMaskWindow::change_Bin);
			// 
			// checkBox_VEN
			// 
			this->checkBox_VEN->AutoSize = true;
			this->checkBox_VEN->Location = System::Drawing::Point(12, 81);
			this->checkBox_VEN->Name = L"checkBox_VEN";
			this->checkBox_VEN->Size = System::Drawing::Size(86, 17);
			this->checkBox_VEN->TabIndex = 3;
			this->checkBox_VEN->Text = L"Venomancer";
			this->checkBox_VEN->UseVisualStyleBackColor = true;
			this->checkBox_VEN->CheckedChanged += gcnew System::EventHandler(this, &ClassMaskWindow::change_Bin);
			// 
			// checkBox_BAR
			// 
			this->checkBox_BAR->AutoSize = true;
			this->checkBox_BAR->Location = System::Drawing::Point(12, 104);
			this->checkBox_BAR->Name = L"checkBox_BAR";
			this->checkBox_BAR->Size = System::Drawing::Size(71, 17);
			this->checkBox_BAR->TabIndex = 4;
			this->checkBox_BAR->Text = L"Barbarian";
			this->checkBox_BAR->UseVisualStyleBackColor = true;
			this->checkBox_BAR->CheckedChanged += gcnew System::EventHandler(this, &ClassMaskWindow::change_Bin);
			// 
			// checkBox_AS
			// 
			this->checkBox_AS->AutoSize = true;
			this->checkBox_AS->Location = System::Drawing::Point(12, 127);
			this->checkBox_AS->Name = L"checkBox_AS";
			this->checkBox_AS->Size = System::Drawing::Size(67, 17);
			this->checkBox_AS->TabIndex = 5;
			this->checkBox_AS->Text = L"Assassin";
			this->checkBox_AS->UseVisualStyleBackColor = true;
			this->checkBox_AS->CheckedChanged += gcnew System::EventHandler(this, &ClassMaskWindow::change_Bin);
			// 
			// checkBox_AR
			// 
			this->checkBox_AR->AutoSize = true;
			this->checkBox_AR->Location = System::Drawing::Point(12, 150);
			this->checkBox_AR->Name = L"checkBox_AR";
			this->checkBox_AR->Size = System::Drawing::Size(57, 17);
			this->checkBox_AR->TabIndex = 6;
			this->checkBox_AR->Text = L"Archer";
			this->checkBox_AR->UseVisualStyleBackColor = true;
			this->checkBox_AR->CheckedChanged += gcnew System::EventHandler(this, &ClassMaskWindow::change_Bin);
			// 
			// checkBox_CLE
			// 
			this->checkBox_CLE->AutoSize = true;
			this->checkBox_CLE->Location = System::Drawing::Point(12, 173);
			this->checkBox_CLE->Name = L"checkBox_CLE";
			this->checkBox_CLE->Size = System::Drawing::Size(52, 17);
			this->checkBox_CLE->TabIndex = 7;
			this->checkBox_CLE->Text = L"Cleric";
			this->checkBox_CLE->UseVisualStyleBackColor = true;
			this->checkBox_CLE->CheckedChanged += gcnew System::EventHandler(this, &ClassMaskWindow::change_Bin);
			// 
			// checkBox_SE
			// 
			this->checkBox_SE->AutoSize = true;
			this->checkBox_SE->Location = System::Drawing::Point(12, 196);
			this->checkBox_SE->Name = L"checkBox_SE";
			this->checkBox_SE->Size = System::Drawing::Size(60, 17);
			this->checkBox_SE->TabIndex = 8;
			this->checkBox_SE->Text = L"Seeker";
			this->checkBox_SE->UseVisualStyleBackColor = true;
			this->checkBox_SE->CheckedChanged += gcnew System::EventHandler(this, &ClassMaskWindow::change_Bin);
			// 
			// checkBox_MY
			// 
			this->checkBox_MY->AutoSize = true;
			this->checkBox_MY->Location = System::Drawing::Point(12, 219);
			this->checkBox_MY->Name = L"checkBox_MY";
			this->checkBox_MY->Size = System::Drawing::Size(56, 17);
			this->checkBox_MY->TabIndex = 9;
			this->checkBox_MY->Text = L"Mystic";
			this->checkBox_MY->UseVisualStyleBackColor = true;
			this->checkBox_MY->CheckedChanged += gcnew System::EventHandler(this, &ClassMaskWindow::change_Bin);
			// 
			// numericUpDown_mask
			// 
			this->numericUpDown_mask->Location = System::Drawing::Point(12, 242);
			this->numericUpDown_mask->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1023, 0, 0, 0});
			this->numericUpDown_mask->Name = L"numericUpDown_mask";
			this->numericUpDown_mask->Size = System::Drawing::Size(84, 20);
			this->numericUpDown_mask->TabIndex = 10;
			this->numericUpDown_mask->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->numericUpDown_mask->ValueChanged += gcnew System::EventHandler(this, &ClassMaskWindow::change_Dec);
			// 
			// ClassMaskWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(107, 273);
			this->Controls->Add(this->numericUpDown_mask);
			this->Controls->Add(this->checkBox_MY);
			this->Controls->Add(this->checkBox_SE);
			this->Controls->Add(this->checkBox_CLE);
			this->Controls->Add(this->checkBox_AR);
			this->Controls->Add(this->checkBox_AS);
			this->Controls->Add(this->checkBox_BAR);
			this->Controls->Add(this->checkBox_VEN);
			this->Controls->Add(this->checkBox_PSY);
			this->Controls->Add(this->checkBox_WIZ);
			this->Controls->Add(this->checkBox_BM);
			this->MaximizeBox = false;
			this->MaximumSize = System::Drawing::Size(115, 300);
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(115, 300);
			this->Name = L"ClassMaskWindow";
			this->ShowIcon = false;
			this->Text = L"Class Mask";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown_mask))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void change_Dec(System::Object^  sender, System::EventArgs^  e)
	{
		lockCheckBox = true;

		unsigned short number = Convert::ToInt16(numericUpDown_mask->Value);

		if(number/512 > 0)
		{
			number = number%512;
			checkBox_MY->Checked = true;
		}
		else
		{
			checkBox_MY->Checked = false;
		}

		if(number/256 > 0)
		{
			number = number%256;
			checkBox_SE->Checked = true;
		}
		else
		{
			checkBox_SE->Checked = false;
		}

		if(number/128 > 0)
		{
			number = number%128;
			checkBox_CLE->Checked = true;
		}
		else
		{
			checkBox_CLE->Checked = false;
		}

		if(number/64 > 0)
		{
			number = number%64;
			checkBox_AR->Checked = true;
		}
		else
		{
			checkBox_AR->Checked = false;
		}

		if(number/32 > 0)
		{
			number = number%32;
			checkBox_AS->Checked = true;
		}
		else
		{
			checkBox_AS->Checked = false;
		}

		if(number/16 > 0)
		{
			number = number%16;
			checkBox_BAR->Checked = true;
		}
		else
		{
			checkBox_BAR->Checked = false;
		}

		if(number/8 > 0)
		{
			number = number%8;
			checkBox_VEN->Checked = true;
		}
		else
		{
			checkBox_VEN->Checked = false;
		}

		if(number/4 > 0)
		{
			number = number%4;
			checkBox_PSY->Checked = true;
		}
		else
		{
			checkBox_PSY->Checked = false;
		}

		if(number/2 > 0)
		{
			number = number%2;
			checkBox_WIZ->Checked = true;
		}
		else
		{
			checkBox_WIZ->Checked = false;
		}

		if(number/1 > 0)
		{
			number = number%1;
			checkBox_BM->Checked = true;
		}
		else
		{
			checkBox_BM->Checked = false;
		}

		lockCheckBox = false;
		
	}

	private: System::Void change_Bin(System::Object^  sender, System::EventArgs^  e)
	{
		if(!lockCheckBox)
		{
			unsigned short number = 0;
			if(checkBox_BM->Checked)
			{
				number += 1;
			}
			if(checkBox_WIZ->Checked)
			{
				number += 2;
			}
			if(checkBox_PSY->Checked)
			{
				number += 4;
			}
			if(checkBox_VEN->Checked)
			{
				number += 8;
			}
			if(checkBox_BAR->Checked)
			{
				number += 16;
			}
			if(checkBox_AS->Checked)
			{
				number += 32;
			}
			if(checkBox_AR->Checked)
			{
				number += 64;
			}
			if(checkBox_CLE->Checked)
			{
				number += 128;
			}
			if(checkBox_SE->Checked)
			{
				number += 256;
			}
			if(checkBox_MY->Checked)
			{
				number += 512;
			}

			numericUpDown_mask->Value = Convert::ToDecimal(number);
		}
	}
};