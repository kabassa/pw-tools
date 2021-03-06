#pragma once

#include "..\COMMON\dds.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Summary for MainWindow
///
/// WARNING: If you change the name of this class, you will need to change the
///          'Resource File Name' property for the managed resource compiler tool
///          associated with all .resx files this class depends on.  Otherwise,
///          the designers will not be able to interact properly with localized
///          resources associated with this form.
/// </summary>
public ref class MainWindow : public System::Windows::Forms::Form
{
	public:
	MainWindow(void)
	{
		InitializeComponent();
		this->Icon = (Drawing::Icon^)((gcnew Resources::ResourceManager("sTools.icons", Reflection::Assembly::GetExecutingAssembly()))->GetObject("app"));
		pictureBox_tint->BackgroundImage = (Drawing::Image^)((gcnew Resources::ResourceManager("sTools.icons", Reflection::Assembly::GetExecutingAssembly()))->GetObject("checker"));
	}

	protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~MainWindow()
	{
		if (components)
		{
			delete components;
		}
	}

	DDS^ Texture;

	private: System::Windows::Forms::PictureBox^  pictureBox_tint;
	private: System::Windows::Forms::ListBox^  listBox_files;
	private: System::Windows::Forms::TextBox^  textBox_source;
	private: System::Windows::Forms::Button^  button_fixFashion;
	private: System::Windows::Forms::Button^  button_save;
	private: System::Windows::Forms::PictureBox^  pictureBox_mask;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox_target;
	private: System::Windows::Forms::Button^  button_browse;
	private: System::Windows::Forms::Button^  button_fixArmor;

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
			this->pictureBox_tint = (gcnew System::Windows::Forms::PictureBox());
			this->listBox_files = (gcnew System::Windows::Forms::ListBox());
			this->textBox_source = (gcnew System::Windows::Forms::TextBox());
			this->button_fixFashion = (gcnew System::Windows::Forms::Button());
			this->button_save = (gcnew System::Windows::Forms::Button());
			this->pictureBox_mask = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox_target = (gcnew System::Windows::Forms::TextBox());
			this->button_browse = (gcnew System::Windows::Forms::Button());
			this->button_fixArmor = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_tint))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_mask))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox_tint
			// 
			this->pictureBox_tint->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->pictureBox_tint->Location = System::Drawing::Point(243, 64);
			this->pictureBox_tint->Name = L"pictureBox_tint";
			this->pictureBox_tint->Size = System::Drawing::Size(383, 383);
			this->pictureBox_tint->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox_tint->TabIndex = 2;
			this->pictureBox_tint->TabStop = false;
			// 
			// listBox_files
			// 
			this->listBox_files->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom) 
				| System::Windows::Forms::AnchorStyles::Left));
			this->listBox_files->FormattingEnabled = true;
			this->listBox_files->Location = System::Drawing::Point(4, 66);
			this->listBox_files->Name = L"listBox_files";
			this->listBox_files->Size = System::Drawing::Size(233, 160);
			this->listBox_files->TabIndex = 5;
			this->listBox_files->SelectedIndexChanged += gcnew System::EventHandler(this, &MainWindow::select_file);
			// 
			// textBox_source
			// 
			this->textBox_source->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_source->Enabled = false;
			this->textBox_source->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox_source->Location = System::Drawing::Point(51, 12);
			this->textBox_source->Name = L"textBox_source";
			this->textBox_source->Size = System::Drawing::Size(575, 20);
			this->textBox_source->TabIndex = 1;
			this->textBox_source->Text = L"Drag Fashion Folder on this Window";
			this->textBox_source->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// button_fixFashion
			// 
			this->button_fixFashion->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button_fixFashion->Location = System::Drawing::Point(4, 395);
			this->button_fixFashion->Name = L"button_fixFashion";
			this->button_fixFashion->Size = System::Drawing::Size(113, 23);
			this->button_fixFashion->TabIndex = 6;
			this->button_fixFashion->Text = L"Fix Fashion";
			this->button_fixFashion->UseVisualStyleBackColor = true;
			this->button_fixFashion->Click += gcnew System::EventHandler(this, &MainWindow::click_fix);
			// 
			// button_save
			// 
			this->button_save->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button_save->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button_save->Location = System::Drawing::Point(4, 424);
			this->button_save->Name = L"button_save";
			this->button_save->Size = System::Drawing::Size(233, 23);
			this->button_save->TabIndex = 8;
			this->button_save->Text = L"Save";
			this->button_save->UseVisualStyleBackColor = true;
			this->button_save->Click += gcnew System::EventHandler(this, &MainWindow::click_save);
			// 
			// pictureBox_mask
			// 
			this->pictureBox_mask->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->pictureBox_mask->BackColor = System::Drawing::Color::Black;
			this->pictureBox_mask->Location = System::Drawing::Point(4, 232);
			this->pictureBox_mask->Name = L"pictureBox_mask";
			this->pictureBox_mask->Size = System::Drawing::Size(233, 157);
			this->pictureBox_mask->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox_mask->TabIndex = 6;
			this->pictureBox_mask->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(1, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Source:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(1, 41);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(41, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Target:";
			// 
			// textBox_target
			// 
			this->textBox_target->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->textBox_target->Enabled = false;
			this->textBox_target->Location = System::Drawing::Point(51, 38);
			this->textBox_target->Name = L"textBox_target";
			this->textBox_target->Size = System::Drawing::Size(506, 20);
			this->textBox_target->TabIndex = 3;
			// 
			// button_browse
			// 
			this->button_browse->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button_browse->Location = System::Drawing::Point(563, 38);
			this->button_browse->Name = L"button_browse";
			this->button_browse->Size = System::Drawing::Size(63, 20);
			this->button_browse->TabIndex = 4;
			this->button_browse->Text = L"Browse...";
			this->button_browse->UseVisualStyleBackColor = true;
			this->button_browse->Click += gcnew System::EventHandler(this, &MainWindow::click_browse);
			// 
			// button_fixArmor
			// 
			this->button_fixArmor->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button_fixArmor->Location = System::Drawing::Point(124, 395);
			this->button_fixArmor->Name = L"button_fixArmor";
			this->button_fixArmor->Size = System::Drawing::Size(113, 23);
			this->button_fixArmor->TabIndex = 7;
			this->button_fixArmor->Text = L"Fix Armor";
			this->button_fixArmor->UseVisualStyleBackColor = true;
			this->button_fixArmor->Click += gcnew System::EventHandler(this, &MainWindow::click_fix);
			// 
			// MainWindow
			// 
			this->AllowDrop = true;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(632, 453);
			this->Controls->Add(this->button_fixArmor);
			this->Controls->Add(this->button_browse);
			this->Controls->Add(this->textBox_target);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox_mask);
			this->Controls->Add(this->button_save);
			this->Controls->Add(this->button_fixFashion);
			this->Controls->Add(this->textBox_source);
			this->Controls->Add(this->listBox_files);
			this->Controls->Add(this->pictureBox_tint);
			this->MinimumSize = System::Drawing::Size(480, 352);
			this->Name = L"MainWindow";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L" sCLOTH";
			this->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &MainWindow::drop_path);
			this->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &MainWindow::drag_enter);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_tint))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_mask))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void drag_enter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
	{
		if(e->Data->GetDataPresent(DataFormats::FileDrop, false))
		{
			e->Effect = DragDropEffects::All;
		}
	}
	private: System::Void drop_path(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e)
	{
		Cursor = Cursors::AppStarting;

		textBox_source->Text = ((array<String^>^)e->Data->GetData(DataFormats::FileDrop))[0];

		listBox_files->Items->Clear();
		pictureBox_mask->Image = gcnew Bitmap(1, 1);
		pictureBox_tint->Image = gcnew Bitmap(1, 1);

		if(textBox_source->Text && Directory::Exists(textBox_source->Text))
		{
			String^ mask_file;
			array<String^>^ tint_files = Directory::GetFiles(textBox_source->Text, "rw_*.dds", SearchOption::AllDirectories);

			for(int i=0; i<tint_files->Length; i++)
			{
				mask_file = tint_files[i]->Replace("rw_", "nb_rw_");
				if(File::Exists(mask_file))
				{
					listBox_files->Items->Add(tint_files[i]->Replace(textBox_source->Text + "\\", ""));
				}
			}
		}

		Cursor = Cursors::Default;
	}

	private: System::Void click_browse(System::Object^  sender, System::EventArgs^  e)
	{
		FolderBrowserDialog^ dir = gcnew FolderBrowserDialog();
		if(dir->ShowDialog() == Windows::Forms::DialogResult::OK && Directory::Exists(dir->SelectedPath))
		{
			textBox_target->Text = dir->SelectedPath;
		}
	}
	private: System::Void select_file(System::Object^  sender, System::EventArgs^  e)
	{
		if(listBox_files->SelectedIndex > -1)
		{
			Cursor = Cursors::AppStarting;

			String^ tint_file = textBox_source->Text + "\\" + listBox_files->SelectedItem->ToString();
			if(File::Exists(tint_file))
			{
				DDS^ mask = gcnew DDS();
				mask->load(tint_file->Replace("rw_", "nb_rw_"));
				Bitmap^ m = gcnew Bitmap(mask->dwHeader->dwWidth, mask->dwHeader->dwHeight, Imaging::PixelFormat::Format32bppArgb);
				for(int y=0; y<m->Height; y++)
				{
					for(int x=0; x<m->Width; x++)
					{
						m->SetPixel(x, y, mask->GetColor(0, x, y));
					}
				}
				pictureBox_mask->Image = m;

				DDS^ tint = gcnew DDS();
				tint->load(tint_file);
				Bitmap^ t = gcnew Bitmap(tint->dwHeader->dwWidth, tint->dwHeader->dwHeight, Imaging::PixelFormat::Format32bppArgb);
				for(int y=0; y<t->Height; y++)
				{
					for(int x=0; x<t->Width; x++)
					{
						t->SetPixel(x, y, tint->GetColor(0, x, y));
					}
				}
				pictureBox_tint->Image = t;

				Texture = tint;

				if(t->Width > pictureBox_tint->Width)
				{
					this->Width += t->Width - pictureBox_tint->Width;
				}
				if(t->Height > pictureBox_tint->Height)
				{
					this->Height += t->Height - pictureBox_tint->Height;
				}
				GC::Collect();
			}

			Cursor = Cursors::Default;
		}
	}

	private: System::Void click_fix(System::Object^  sender, System::EventArgs^  e)
	{
		if(listBox_files->SelectedIndex > -1)
		{
			String^ tint_file = textBox_source->Text + "\\" + listBox_files->SelectedItem->ToString();
			String^ mask_file = tint_file->Replace("rw_", "nb_rw_");
			if(File::Exists(tint_file) && File::Exists(mask_file))
			{
				Cursor = Cursors::AppStarting;

				DDS^ tint = gcnew DDS();
				DDS^ mask = gcnew DDS();
				tint->load(tint_file);
				mask->load(mask_file);

				if(tint->dwHeader->dwMipMapCount != mask->dwHeader->dwMipMapCount)
				{
					Cursor = Cursors::Default;
					return;
				}

				for(int i=0; i<tint->dwHeader->dwMipMapCount; i++)
				{
					for(int y=0; y<tint->dwHeader->dwHeight; y++)
					{
						for(int x=0; x<tint->dwHeader->dwWidth; x++)
						{
							/*
							if(tint->GetColor(i, x, y).A < 10)
							{
								tint->SetAlpha(i, x, y, 0);
							}
							else
							{
								tint->SetAlpha(i, x, y, mask->GetColor(i, x, y).B);
							}
							*/
							if((Control^)sender == button_fixFashion)
							{
								// fashion uses blue channel from mask as tint map
								tint->SetAlpha(i, x, y, (mask->GetColor(i, x, y).B*tint->GetColor(i, x, y).A)/255);
							}
							if((Control^)sender == button_fixArmor)
							{
								// armor uses green channel from mask as metallic shine
								tint->SetAlpha(i, x, y, (mask->GetColor(i, x, y).G*tint->GetColor(i, x, y).A)/255);
							}
						}
					}
				}

				Bitmap^ bmp = gcnew Bitmap(tint->dwHeader->dwWidth, tint->dwHeader->dwHeight, Imaging::PixelFormat::Format32bppArgb);
				for(int y=0; y<bmp->Height; y++)
				{
					for(int x=0; x<bmp->Width; x++)
					{
						bmp->SetPixel(x, y, tint->GetColor(0, x, y));
					}
				}
				Texture = tint;
				pictureBox_tint->Image = bmp;
				GC::Collect();
				Cursor = Cursors::Default;
			}
		}
	}

	private: System::Void click_save(System::Object^  sender, System::EventArgs^  e)
	{
		if(Texture && Directory::Exists(textBox_target->Text))
		{
			Cursor = Cursors::AppStarting;

			String^ source_file = textBox_source->Text + "\\" + listBox_files->SelectedItem->ToString();
			String^ target_file = textBox_target->Text + textBox_source->Text->Substring(textBox_source->Text->LastIndexOf("\\")) + "\\" + listBox_files->SelectedItem->ToString();
			Directory::CreateDirectory(target_file->Substring(0, target_file->LastIndexOf("\\")));

			/*
			if(File::Exists(target_file + "_ORG.dds"))
			{
				File::Delete(target_file + "_ORG.dds");
			}
			File::Copy(source_file, target_file + "_ORG.dds");
			*/

			Texture->RecompressDXT5_alpha();
			Texture->save(target_file);

			Cursor = Cursors::Default;
		}
	}
};