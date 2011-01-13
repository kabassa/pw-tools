#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

namespace Controls
{
///<summary>
///This class is a graphical control element for spreading values and turn them into colors by a selected color-scheme.
///</summary>
public ref class ColorExpansionBar : public System::Windows::Forms::UserControl
{
	///<summary>
	///Default constructor.
	///</summary>
	public: ColorExpansionBar(void);
	///<summary>
	///Default destructor.
	///</summary>
	protected: ~ColorExpansionBar();

    ///<summary>
	///Default constructor.
	///</summary>
	private: static int margin = 28;
	private: System::Windows::Forms::PictureBox^  pictureBox_SliderMax;
	private: System::Windows::Forms::PictureBox^  pictureBox_SliderMin;

	///<summary>
	///The name of the current selected color-scheme.
	///</summary>
	String^ ColorScheme;
	///<summary>
	///Contains a list of names for all available color-schemes.
	///</summary>
	static array<String^>^ ColorSchemes = {L"Gray", L"Jet", L"Hot", L"Cold"};

	///<summary>
	///Mapping array contains integer color values.
	///In this case the integer values describes gray values from 0-255.
	///</summary>
	array<int>^ gray;
	///<summary>
	///Mapping array contains integer color values.
	///In this case the integer values describes a color gradient in matlab style.
	///</summary>
	array<int>^ jet;
	///<summary>
	///Mapping array contains integer color values.
	///In this case the integer values describes a color gradient from blue to red.
	///</summary>
	array<int>^ hot;
	///<summary>
	///Mapping array contains integer color values.
	///In this case the integer values describes a color gradient from red to blue.
	///</summary>
	array<int>^ cold;

	///<summary>
	///Get an array of colors containing the key-colors of the currently selected color-scheme.
	///It is used to render the gradient colorbar.
	///</summary>
	property array<Drawing::Color>^ Gradient
	{
		array<Drawing::Color>^ get(void);
	}

	double minValue;
	double maxValue;
	double lowValue;
	double highValue;

	public: property double MinValue 
	{ 
		double get(void);
		void set(double value);
	}

	public: property double MaxValue 
	{ 
		double get(void);
		void set(double value);
	}

	public: property double LowValue 
	{ 
		double get(void);
		void set(double Value);
	}

	public: property double HighValue 
	{ 
		double get(void);
		void set(double Value);
	}

	private: System::Windows::Forms::NumericUpDown^  numericUpDown_highValue;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown_lowValue;
	private: System::Windows::Forms::ContextMenuStrip^  context_color;
	private: System::ComponentModel::IContainer^  components;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox_SliderMax = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox_SliderMin = (gcnew System::Windows::Forms::PictureBox());
			this->numericUpDown_highValue = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown_lowValue = (gcnew System::Windows::Forms::NumericUpDown());
			this->context_color = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_SliderMax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_SliderMin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown_highValue))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown_lowValue))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox_SliderMax
			// 
			this->pictureBox_SliderMax->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox_SliderMax->Location = System::Drawing::Point(2, 25);
			this->pictureBox_SliderMax->Name = L"pictureBox_SliderMax";
			this->pictureBox_SliderMax->Size = System::Drawing::Size(9, 11);
			this->pictureBox_SliderMax->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox_SliderMax->TabIndex = 0;
			this->pictureBox_SliderMax->TabStop = false;
			this->pictureBox_SliderMax->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &ColorExpansionBar::mouseDown_Slider);
			this->pictureBox_SliderMax->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &ColorExpansionBar::mouseMove_Slider);
			this->pictureBox_SliderMax->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &ColorExpansionBar::mouseUp_Slider);
			// 
			// pictureBox_SliderMin
			// 
			this->pictureBox_SliderMin->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox_SliderMin->Location = System::Drawing::Point(2, 74);
			this->pictureBox_SliderMin->Name = L"pictureBox_SliderMin";
			this->pictureBox_SliderMin->Size = System::Drawing::Size(9, 11);
			this->pictureBox_SliderMin->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox_SliderMin->TabIndex = 1;
			this->pictureBox_SliderMin->TabStop = false;
			this->pictureBox_SliderMin->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &ColorExpansionBar::mouseDown_Slider);
			this->pictureBox_SliderMin->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &ColorExpansionBar::mouseMove_Slider);
			this->pictureBox_SliderMin->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &ColorExpansionBar::mouseUp_Slider);
			// 
			// numericUpDown_highValue
			// 
			this->numericUpDown_highValue->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->numericUpDown_highValue->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->numericUpDown_highValue->DecimalPlaces = 1;
			this->numericUpDown_highValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->numericUpDown_highValue->Location = System::Drawing::Point(0, 0);
			this->numericUpDown_highValue->Name = L"numericUpDown_highValue";
			this->numericUpDown_highValue->Size = System::Drawing::Size(59, 18);
			this->numericUpDown_highValue->TabIndex = 1;
			this->numericUpDown_highValue->ValueChanged += gcnew System::EventHandler(this, &ColorExpansionBar::change_Bounds);
			// 
			// numericUpDown_lowValue
			// 
			this->numericUpDown_lowValue->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left) 
				| System::Windows::Forms::AnchorStyles::Right));
			this->numericUpDown_lowValue->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->numericUpDown_lowValue->DecimalPlaces = 1;
			this->numericUpDown_lowValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->numericUpDown_lowValue->Location = System::Drawing::Point(0, 92);
			this->numericUpDown_lowValue->Name = L"numericUpDown_lowValue";
			this->numericUpDown_lowValue->Size = System::Drawing::Size(59, 18);
			this->numericUpDown_lowValue->TabIndex = 2;
			this->numericUpDown_lowValue->ValueChanged += gcnew System::EventHandler(this, &ColorExpansionBar::change_Bounds);
			// 
			// context_color
			// 
			this->context_color->Name = L"context_color";
			this->context_color->Size = System::Drawing::Size(61, 4);
			// 
			// ColorExpansionBar
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ContextMenuStrip = this->context_color;
			this->Controls->Add(this->numericUpDown_lowValue);
			this->Controls->Add(this->numericUpDown_highValue);
			this->Controls->Add(this->pictureBox_SliderMin);
			this->Controls->Add(this->pictureBox_SliderMax);
			this->Margin = System::Windows::Forms::Padding(0);
			this->Name = L"ColorExpansionBar";
			this->Size = System::Drawing::Size(60, 110);
			this->Resize += gcnew System::EventHandler(this, &ColorExpansionBar::resize_Control);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &ColorExpansionBar::paint_Control);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_SliderMax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox_SliderMin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown_highValue))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown_lowValue))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		public: delegate void RangeEventHandler();
		public: event RangeEventHandler^ RangeChanged;

		private: System::Void InitializeContextMenu();
		private: System::Void InitializeColorSchemes();

		private: System::Void paint_Control(System::Object^, System::Windows::Forms::PaintEventArgs^);
		private: System::Void mouseMove_Slider(System::Object^, System::Windows::Forms::MouseEventArgs^);
		private: System::Void update_Sliders();
		private: System::Void resize_Control(System::Object^, System::EventArgs^);
		private: System::Void change_Bounds(System::Object^, System::EventArgs^);
		private: System::Void mouseDown_Slider(System::Object^, System::Windows::Forms::MouseEventArgs^);
		private: System::Void mouseUp_Slider(System::Object^, System::Windows::Forms::MouseEventArgs^);
		private: System::Void click_ChangeColorScheme(System::Object^, System::EventArgs^);
		// claculate  unsigned chars (RGB)
		public: Drawing::Color^ mapValue(double Value);
};
}