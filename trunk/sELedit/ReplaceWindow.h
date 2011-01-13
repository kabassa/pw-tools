#pragma once

#include "eListCollection.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public ref class ReplaceWindow : public System::Windows::Forms::Form
{
	public:
	ReplaceWindow(eListCollection^ ListCollection)
	{
		eLC = ListCollection;
		InitializeComponent();
	}

	protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~ReplaceWindow()
	{
		if (components)
		{
			delete components;
		}
	}

	eListCollection^ eLC;

	private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::TextBox^  textBox_list;
private: System::Windows::Forms::TextBox^  textBox_item;


	private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::TextBox^  textBox_field;

	private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::TextBox^  textBox_oldValue;

	private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::TextBox^  textBox_newValue;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Button^  button_replace;
	private: System::Windows::Forms::Button^  button_cancel;
	private: System::Windows::Forms::GroupBox^  groupBox1;
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
		this->textBox_list = (gcnew System::Windows::Forms::TextBox());
		this->textBox_item = (gcnew System::Windows::Forms::TextBox());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->textBox_field = (gcnew System::Windows::Forms::TextBox());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->textBox_oldValue = (gcnew System::Windows::Forms::TextBox());
		this->label4 = (gcnew System::Windows::Forms::Label());
		this->textBox_newValue = (gcnew System::Windows::Forms::TextBox());
		this->label5 = (gcnew System::Windows::Forms::Label());
		this->button_replace = (gcnew System::Windows::Forms::Button());
		this->button_cancel = (gcnew System::Windows::Forms::Button());
		this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
		this->groupBox1->SuspendLayout();
		this->SuspendLayout();
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(6, 22);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(51, 13);
		this->label1->TabIndex = 0;
		this->label1->Text = L"in List ID:";
		// 
		// textBox_list
		// 
		this->textBox_list->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
		this->textBox_list->Location = System::Drawing::Point(162, 19);
		this->textBox_list->Name = L"textBox_list";
		this->textBox_list->Size = System::Drawing::Size(100, 20);
		this->textBox_list->TabIndex = 1;
		this->textBox_list->Text = L"*";
		// 
		// textBox_item
		// 
		this->textBox_item->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
		this->textBox_item->Location = System::Drawing::Point(162, 45);
		this->textBox_item->Name = L"textBox_item";
		this->textBox_item->Size = System::Drawing::Size(100, 20);
		this->textBox_item->TabIndex = 3;
		this->textBox_item->Text = L"*";
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = System::Drawing::Point(6, 48);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(55, 13);
		this->label2->TabIndex = 2;
		this->label2->Text = L"in Item ID:";
		// 
		// textBox_field
		// 
		this->textBox_field->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
		this->textBox_field->Location = System::Drawing::Point(162, 71);
		this->textBox_field->Name = L"textBox_field";
		this->textBox_field->Size = System::Drawing::Size(100, 20);
		this->textBox_field->TabIndex = 5;
		this->textBox_field->Text = L"*";
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = System::Drawing::Point(6, 74);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(57, 13);
		this->label3->TabIndex = 4;
		this->label3->Text = L"in Field ID:";
		// 
		// textBox_oldValue
		// 
		this->textBox_oldValue->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
			| System::Windows::Forms::AnchorStyles::Right));
		this->textBox_oldValue->Location = System::Drawing::Point(88, 118);
		this->textBox_oldValue->Name = L"textBox_oldValue";
		this->textBox_oldValue->Size = System::Drawing::Size(174, 20);
		this->textBox_oldValue->TabIndex = 7;
		this->textBox_oldValue->Text = L"*";
		// 
		// label4
		// 
		this->label4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
		this->label4->AutoSize = true;
		this->label4->Location = System::Drawing::Point(6, 121);
		this->label4->Name = L"label4";
		this->label4->Size = System::Drawing::Size(56, 13);
		this->label4->TabIndex = 6;
		this->label4->Text = L"Old Value:";
		// 
		// textBox_newValue
		// 
		this->textBox_newValue->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
			| System::Windows::Forms::AnchorStyles::Right));
		this->textBox_newValue->Location = System::Drawing::Point(88, 144);
		this->textBox_newValue->Name = L"textBox_newValue";
		this->textBox_newValue->Size = System::Drawing::Size(174, 20);
		this->textBox_newValue->TabIndex = 9;
		this->textBox_newValue->Text = L"*";
		// 
		// label5
		// 
		this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
		this->label5->AutoSize = true;
		this->label5->Location = System::Drawing::Point(6, 147);
		this->label5->Name = L"label5";
		this->label5->Size = System::Drawing::Size(62, 13);
		this->label5->TabIndex = 8;
		this->label5->Text = L"New Value:";
		// 
		// button_replace
		// 
		this->button_replace->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
		this->button_replace->Location = System::Drawing::Point(12, 188);
		this->button_replace->Name = L"button_replace";
		this->button_replace->Size = System::Drawing::Size(131, 23);
		this->button_replace->TabIndex = 10;
		this->button_replace->Text = L"Replace";
		this->button_replace->UseVisualStyleBackColor = true;
		this->button_replace->Click += gcnew System::EventHandler(this, &ReplaceWindow::click_replace);
		// 
		// button_cancel
		// 
		this->button_cancel->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
		this->button_cancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		this->button_cancel->Location = System::Drawing::Point(149, 188);
		this->button_cancel->Name = L"button_close";
		this->button_cancel->Size = System::Drawing::Size(131, 23);
		this->button_cancel->TabIndex = 11;
		this->button_cancel->Text = L"Close";
		this->button_cancel->UseVisualStyleBackColor = true;
		this->button_cancel->Click += gcnew System::EventHandler(this, &ReplaceWindow::click_close);
		// 
		// groupBox1
		// 
		this->groupBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
			| System::Windows::Forms::AnchorStyles::Left) 
			| System::Windows::Forms::AnchorStyles::Right));
		this->groupBox1->Controls->Add(this->label1);
		this->groupBox1->Controls->Add(this->textBox_list);
		this->groupBox1->Controls->Add(this->label2);
		this->groupBox1->Controls->Add(this->textBox_newValue);
		this->groupBox1->Controls->Add(this->textBox_item);
		this->groupBox1->Controls->Add(this->label5);
		this->groupBox1->Controls->Add(this->label3);
		this->groupBox1->Controls->Add(this->textBox_oldValue);
		this->groupBox1->Controls->Add(this->textBox_field);
		this->groupBox1->Controls->Add(this->label4);
		this->groupBox1->Location = System::Drawing::Point(12, 12);
		this->groupBox1->Name = L"groupBox1";
		this->groupBox1->Size = System::Drawing::Size(268, 170);
		this->groupBox1->TabIndex = 0;
		this->groupBox1->TabStop = false;
		this->groupBox1->Text = L"Replace Settings";
		// 
		// ReplaceWindow
		// 
		this->AcceptButton = this->button_replace;
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->CancelButton = this->button_cancel;
		this->ClientSize = System::Drawing::Size(292, 223);
		this->ControlBox = false;
		this->Controls->Add(this->groupBox1);
		this->Controls->Add(this->button_cancel);
		this->Controls->Add(this->button_replace);
		this->MaximizeBox = false;
		this->MaximumSize = System::Drawing::Size(300, 250);
		this->MinimizeBox = false;
		this->MinimumSize = System::Drawing::Size(300, 250);
		this->Name = L"ReplaceWindow";
		this->ShowIcon = false;
		this->ShowInTaskbar = false;
		this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L" Logic Replace";
		this->groupBox1->ResumeLayout(false);
		this->groupBox1->PerformLayout();
		this->ResumeLayout(false);

	}
#pragma endregion

	private: System::Void click_replace(System::Object^  sender, System::EventArgs^  ea)
	{
		Cursor = Windows::Forms::Cursors::AppStarting;

		int replacementCount = 0;
		int l;
		int l_max;
		int e;
		int e_max;
		int v;
		int v_max;
		String^ oldValue = textBox_oldValue->Text;
		String^ newValue = textBox_newValue->Text;

		if(textBox_list->Text == "*")
		{
			l = 0;
			l_max = eLC->Lists->Length;
		}
		else
		{
			l = Convert::ToInt32(textBox_list->Text);
			l_max = Convert::ToInt32(textBox_list->Text)+1;
			if(l < 0 || l_max > eLC->Lists->Length)
			{
				MessageBox::Show("List Index Out of Range");
				return;
			}
		}
		for(l; l<l_max; l++)
		{
			if(textBox_item->Text == "*")
			{
				e = 0;
				e_max = eLC->Lists[l]->elementValues->Length;
			}
			else
			{
				e = Convert::ToInt32(textBox_item->Text);
				e_max = Convert::ToInt32(textBox_item->Text)+1;
				if(e < 0 || e_max > eLC->Lists[l]->elementValues->Length)
				{
					MessageBox::Show("Item Index Out of Range");
					return;
				}
			}
			for(e; e<e_max; e++)
			{
				if(textBox_field->Text == "*")
				{
					v = 0;
					v_max = eLC->Lists[l]->elementValues[e]->Length;
				}
				else
				{
					v = Convert::ToInt32(textBox_field->Text);
					v_max = Convert::ToInt32(textBox_field->Text)+1;
					if(v < 0 || v_max > eLC->Lists[l]->elementValues[e]->Length)
					{
						MessageBox::Show("Field Index Out of Range");
						return;
					}
				}
				for(v; v<v_max;v++)
				{
					if(oldValue == "*" || oldValue == eLC->GetValue(l, e, v)->Trim(gcnew array<wchar_t>{0}))
					{
						eLC->SetValue(l, e, v, newValue);
						replacementCount++;
					}
				}
			}
		}

		Cursor = Windows::Forms::Cursors::Default;

		MessageBox::Show(replacementCount + " Values Replaced");
	}
	private: System::Void click_close(System::Object^  sender, System::EventArgs^  e)
	{
		this->Close();
	}
};