#pragma once

#include "ColorExpansionBar.h"

using namespace Controls;

ColorExpansionBar::ColorExpansionBar(void)
{
	InitializeComponent();

	// Enable DoubleBuffer for Paint
	this->SetStyle(ControlStyles::DoubleBuffer | ControlStyles::UserPaint | ControlStyles::AllPaintingInWmPaint, true);
	this->UpdateStyles();

	pictureBox_SliderMax->Image = (Drawing::Bitmap^)((gcnew Resources::ResourceManager("sTOOLS.icons", Reflection::Assembly::GetExecutingAssembly()))->GetObject("sliderV"));
	pictureBox_SliderMin->Image = (Drawing::Bitmap^)((gcnew Resources::ResourceManager("sTOOLS.icons", Reflection::Assembly::GetExecutingAssembly()))->GetObject("sliderV"));

	minValue = 0;
	maxValue = 255;
	lowValue = minValue;
	highValue = maxValue;
	numericUpDown_lowValue->Minimum = Convert::ToDecimal(minValue);
	numericUpDown_lowValue->Maximum = Convert::ToDecimal(maxValue);
	numericUpDown_lowValue->Value = Convert::ToDecimal(lowValue);
	numericUpDown_highValue->Minimum = Convert::ToDecimal(minValue);
	numericUpDown_highValue->Maximum = Convert::ToDecimal(maxValue);
	numericUpDown_highValue->Value = Convert::ToDecimal(highValue);

	InitializeContextMenu();
	InitializeColorSchemes();
	ColorScheme = ColorSchemes[0];
}

ColorExpansionBar::~ColorExpansionBar()
{
	if (components)
	{
		delete components;
	}
}

void ColorExpansionBar::InitializeContextMenu()
{
	context_color->Items->Clear();

	context_color->Items->Add(gcnew ToolStripLabel("Color Scheme:"));
	context_color->Items[0]->Font = gcnew Drawing::Font(this->Font, Drawing::FontStyle::Bold);

	context_color->Items->Add(gcnew ToolStripSeparator()); 

	for(int i=0; i<ColorSchemes->Length; i++)
	{
		context_color->Items->Add(gcnew ToolStripMenuItem());
		context_color->Items[i+2]->Text = ColorSchemes[i];
		context_color->Items[i+2]->Click += gcnew System::EventHandler(this, &ColorExpansionBar::click_ChangeColorScheme);
	}

	((ToolStripMenuItem^)context_color->Items[2])->Checked = true;
}
void ColorExpansionBar::InitializeColorSchemes()
{
	int tempvalue;

	// Initialize Black & White
	gray = gcnew array<int>(256);
	for(int i=0; i<gray->Length; i++)
	{
		gray[i] = i*(256*256 + 256 + 1);
	}

	// Initialize Matlab
	jet = gcnew array<int>(511);

	tempvalue = -129; // DarkBlue
	for(int n=0; n<128; n++)
	{
		tempvalue += (256+1);
		jet[n] = tempvalue;
	}
	// tempvalue = 32766 -> DeepSkyBlue ?
	for(int n=128; n<256; n++)
	{
		tempvalue += (256*256+256-1);
		jet[n] = tempvalue;
	}
	// tempvalue = 8388479 -> PaleGreen ?
	for(int n=256; n<383; n++)
	{
		tempvalue += (256*256-256-1);
		jet[n] = tempvalue;
	}
	// tempvalue = 16744065 -> DarkOrange ?
	for(int n=383; n<447; n++)
	{
		tempvalue -= (2*256);
		jet[n] = tempvalue;
	}
	// tempvalue = 16711680 -> Red
	for(int n=447; n<511; n++)
	{
		tempvalue -= (2*256*256);
		jet[n] = tempvalue;
	}
	// tempvalue = 8323072 -> DarkRed


	// Initialize Hot
	hot = gcnew array<int>(1021);

	tempvalue = -1; // Initilized Value
	for(int n=0; n<256; n++)
	{
		tempvalue += 256;
		hot[n] = tempvalue;
	}
	// tempvalue = 65535 -> Blue+Green
	for(int n=256; n<511; n++)
	{
		tempvalue -= 1;
		hot[n] = tempvalue;
	}
	// tempvalue = 65280 -> Green
	for(int n=511; n<766; n++)
	{
		hot[n] = tempvalue;
		tempvalue += 256*256;
	}
	// tempvalue = 16776960 -> Green+Red
	for(int n=766; n<1021; n++)
	{
		hot[n] =  tempvalue;
		tempvalue -= 256;
	}

	// Initialize Cold, as inverse Hot
	cold = gcnew array<int>(1021);
	for(int i=0; i<cold->Length; i++)
	{
		cold[i] = hot[cold->Length-1-i];
	}
}
array<Drawing::Color>^ ColorExpansionBar::Gradient::get(void)
{
	if(ColorScheme == "Jet")
	{
		return gcnew array<Drawing::Color>{Color::FromArgb(127, 0, 0), Color::FromArgb(255, 0, 0), Color::FromArgb(255, 127, 0), Color::FromArgb(191, 191, 64), Color::FromArgb(127, 255, 127), Color::FromArgb(64, 191, 191), Color::FromArgb(0, 127, 255), Color::FromArgb(0, 64, 191), Color::FromArgb(0, 0, 127)};
	}
	if(ColorScheme == "Hot")
	{
		return gcnew array<Drawing::Color>{Drawing::Color::Red, Drawing::Color::Yellow, Drawing::Color::LightGreen, Drawing::Color::Cyan, Drawing::Color::Blue};
	}
	if(ColorScheme == "Cold")
	{
		return gcnew array<Drawing::Color>{Drawing::Color::Blue, Drawing::Color::Cyan, Drawing::Color::LightGreen, Drawing::Color::Yellow, Drawing::Color::Red};
	}

	return gcnew array<Drawing::Color>{Drawing::Color::White, Drawing::Color::Black};
}
double ColorExpansionBar::MinValue::get(void)
{
	return Math::Round(minValue, 5);
}
void ColorExpansionBar::MinValue::set(double value)
{
	if(value != minValue)
	{
		double oldMin = minValue;
		if(value <= maxValue)
		{
			// Set Minimum to Decimal::Min, otherwise setting Minimum may change the numericupdown->Value (new min > numericupdown->Value)
			// or exception will be thrown (new min < minValue ... numericupdown->Value may be < numericupdown->Minimum)
			numericUpDown_highValue->Minimum = Decimal::MinValue;
			numericUpDown_lowValue->Minimum = Decimal::MinValue;
			// calculate new high & lowValue
			minValue = value;
			HighValue = maxValue;
			LowValue = minValue;
// Not sure if this is robust!
//HighValue = (maxValue - value) * (highValue - oldMin) / (maxValue - oldMin) + value;
//LowValue = (maxValue - value) * (lowValue - oldMin) / (maxValue - oldMin) + value;

			// Set new Limits
			numericUpDown_highValue->Minimum = Convert::ToDecimal(MinValue);
			numericUpDown_lowValue->Minimum = Convert::ToDecimal(MinValue);
		}
		else
		{
			//MessageBox::Show("New minimum value is greater than maximum, the old value was keept!");
			minValue = value;
			maxValue = value;
			// Set new Limits
			numericUpDown_highValue->Minimum = Convert::ToDecimal(MinValue);
			numericUpDown_lowValue->Minimum = Convert::ToDecimal(MinValue);
			numericUpDown_highValue->Maximum = Convert::ToDecimal(MaxValue);
			numericUpDown_lowValue->Maximum = Convert::ToDecimal(MaxValue);
			// calculate new high & lowValue
			HighValue = maxValue;
			LowValue = minValue;
// Not sure if this is robust!
//HighValue = (maxValue - value) * (highValue - oldMin) / (maxValue - oldMin) + value;
//LowValue = (maxValue - value) * (lowValue - oldMin) / (maxValue - oldMin) + value;
		}
	}
}
double ColorExpansionBar::MaxValue::get(void)
{
	return Math::Round(maxValue, 5);
}
void ColorExpansionBar::MaxValue::set(double value)
{
	if(value != maxValue)
	{
		double oldMax = maxValue;
		if(value >= minValue)
		{
			// Set Maximum to Decimal::Max, otherwise setting Maximum may change the numericupdown->Value (new max < numericupdown->Value)
			// or exception will be thrown (new max > maxValue ... numericupdown->Value may be > numericupdown->Maximum)
			numericUpDown_highValue->Maximum = Decimal::MaxValue;
			numericUpDown_lowValue->Maximum = Decimal::MaxValue;
			// calculate new high & lowValue
			maxValue = value;
			HighValue = maxValue;
			LowValue = minValue;
// Not sure if this is robust!
//HighValue = (value - minValue) * (highValue - minValue) / (oldMax - minValue) + minValue;
//LowValue = (value - minValue) * (lowValue - minValue) / (oldMax - minValue) + minValue;

			// Set new Limits
			numericUpDown_highValue->Maximum = Convert::ToDecimal(MaxValue);
			numericUpDown_lowValue->Maximum = Convert::ToDecimal(MaxValue);
		}
		else
		{
			//MessageBox::Show("New maximum value is smaller than minimum, the old value was keept!");
			minValue = value;
			maxValue = value;
			// Set new Limits
			numericUpDown_highValue->Minimum = Convert::ToDecimal(MinValue);
			numericUpDown_lowValue->Minimum = Convert::ToDecimal(MinValue);
			numericUpDown_highValue->Maximum = Convert::ToDecimal(MaxValue);
			numericUpDown_lowValue->Maximum = Convert::ToDecimal(MaxValue);
			// calculate new high & lowValue
			HighValue = maxValue;
			LowValue = minValue;
// Not sure if this is robust!
//HighValue = (value - minValue) * (highValue - minValue) / (oldMax - minValue) + minValue;
//LowValue = (value - minValue) * (lowValue - minValue) / (oldMax - minValue) + minValue;
		}
	}
}
double ColorExpansionBar::LowValue::get(void)
{
	// Round to 5 decimal places, because Conversation between decimal & doubles may be corrupted in 11 th decimal place
	// i.e. numericUpDown_highValue->Value = 1.0123456789 -> toDouble = 1.0123456785
	//      numericUpDown_lowValue->Value  = 1.0123456789 -> toDouble = 1.0123456788
	return Math::Round(lowValue, 5);
}
void ColorExpansionBar::LowValue::set(double value)
{
	if(value > highValue)
	{
		value = highValue;
	}
	if(value < minValue)
	{
		value = minValue;
	}
	// Round to 5 decimal places, because Conversation between decimal & doubles may be corrupted in 11 th decimal place
	// i.e. numericUpDown_highValue->Value = 1.0123456789 -> toDouble = 1.0123456785
	//      numericUpDown_lowValue->Value  = 1.0123456789 -> toDouble = 1.0123456788
	lowValue = value;
	this->numericUpDown_lowValue->ValueChanged -= gcnew System::EventHandler(this, &ColorExpansionBar::change_Bounds);
	numericUpDown_lowValue->Value = Convert::ToDecimal(LowValue);
	this->numericUpDown_lowValue->ValueChanged += gcnew System::EventHandler(this, &ColorExpansionBar::change_Bounds);
	update_Sliders();
	RangeChanged();
}
double ColorExpansionBar::HighValue::get(void)
{
	// Round to 5 decimal places, because Conversation between deimal & doubles may be corrupted in 11th decimal place
	// i.e. numericUpDown_highValue->Value = 1.0123456789 -> toDouble = 1.0123456785
	//      numericUpDown_lowValue->Value  = 1.0123456789 -> toDouble = 1.0123456788
	return Math::Round(highValue, 5);
}
void ColorExpansionBar::HighValue::set(double value)
{
	if(value < lowValue)
	{
		value = lowValue;
	}
	if(value > maxValue)
	{
		value = maxValue;
	}
	// Round to 5 decimal places, because Conversation between decimal & doubles may be corrupted in 11 th decimal place
	// i.e. numericUpDown_highValue->Value = 1.0123456789 -> toDouble = 1.0123456785
	//      numericUpDown_lowValue->Value  = 1.0123456789 -> toDouble = 1.0123456788
	highValue = value;
	this->numericUpDown_highValue->ValueChanged -= gcnew System::EventHandler(this, &ColorExpansionBar::change_Bounds);
	numericUpDown_highValue->Value = Convert::ToDecimal(HighValue);
	this->numericUpDown_highValue->ValueChanged += gcnew System::EventHandler(this, &ColorExpansionBar::change_Bounds);
	update_Sliders();
	RangeChanged();
}
void ColorExpansionBar::paint_Control(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
{
	try
	{
		if(this->Height > 12)
		{
			int x = pictureBox_SliderMax->Location.X+1;
			int w = pictureBox_SliderMax->Width-2;

			// Draw grid every 20~30 px
			double count = Math::Ceiling((this->Height-(2*margin+1)) / 30.0);
			double step = (this->Height-(2*margin+1)) / count;
			double position = Convert::ToDouble(margin);
			int p;
			Drawing::Font^ font = gcnew Drawing::Font("Arial", 7);
			String^ value;
			while(position < this->Height - margin)
			{
				p = Convert::ToInt32(position);
				e->Graphics->DrawLine(Pens::Black, x+w+1, p, x+w+3, p);
				value = ((p - margin) * (minValue - maxValue) / (Height-1 - 2*margin) + maxValue).ToString("F1");;
				e->Graphics->DrawString(value, font, Drawing::Brushes::Black, Convert::ToSingle(x+w+3), Convert::ToSingle(p-6)/*-6 >> center String*/);
				position += step;
			}

			// Draw Rectangle 1 (Solid)
			array<Drawing::Color>^ colors = Gradient;

			Drawing::Rectangle r;
			r = Drawing::Rectangle(x, margin, w, pictureBox_SliderMax->Location.Y - margin);
			e->Graphics->FillRectangle(gcnew Drawing::SolidBrush(colors[0]), r);

			// Draw Rectangle 2 (Gradient)
			r = Drawing::Rectangle(x, (pictureBox_SliderMax->Location.Y + pictureBox_SliderMax->Height-1), w, (pictureBox_SliderMin->Location.Y - pictureBox_SliderMax->Location.Y - pictureBox_SliderMax->Height + 2));
			if(r.Height > 0)
			{
				Drawing2D::LinearGradientBrush^ gradient = gcnew Drawing2D::LinearGradientBrush(r, Color::Black, Color::White, Drawing2D::LinearGradientMode::Vertical);
				array<float>^ positions = gcnew array<float>(colors->Length);
				for(int i=0; i<colors->Length; i++)
				{
					positions[i] = i * 1.0f/(colors->Length-1);
				}
				Drawing2D::ColorBlend^ blend = gcnew Drawing2D::ColorBlend();
				blend->Colors = colors;
				blend->Positions = positions;
				gradient->InterpolationColors = blend;
				e->Graphics->FillRectangle(gradient, r);
			}

			// Draw Rectangle 3 (Solid)
			r = Drawing::Rectangle(x, (pictureBox_SliderMin->Location.Y + pictureBox_SliderMin->Height-1), w, this->Height-margin - (pictureBox_SliderMin->Location.Y + pictureBox_SliderMax->Height) + 1);
			e->Graphics->FillRectangle(gcnew Drawing::SolidBrush(colors[colors->Length-1]), r);
		}
	}
	catch(...)
	{
		// Could not Draw Gradient, Perhaps Clipping Rectangle is 0,0,0,0
	}
}

void ColorExpansionBar::mouseDown_Slider(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	this->numericUpDown_lowValue->ValueChanged -= gcnew System::EventHandler(this, &ColorExpansionBar::change_Bounds);
	this->numericUpDown_highValue->ValueChanged -= gcnew System::EventHandler(this, &ColorExpansionBar::change_Bounds);
}
void ColorExpansionBar::mouseUp_Slider(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	this->numericUpDown_lowValue->ValueChanged += gcnew System::EventHandler(this, &ColorExpansionBar::change_Bounds);
	this->numericUpDown_highValue->ValueChanged += gcnew System::EventHandler(this, &ColorExpansionBar::change_Bounds);
	RangeChanged();
}
void ColorExpansionBar::mouseMove_Slider(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if(e->Button == ::MouseButtons::Left)
	{
		PictureBox^ pb = (PictureBox^)sender;
		Drawing::Point p(pb->Location.X, PointToClient(MousePosition).Y - pb->Height/2);

		pb->BringToFront();

		if(pb == pictureBox_SliderMax)
		{
			//if(p.Y >= margin - pb->Height/2 && p.Y <= pictureBox_SliderMin->Location.Y/* - pb->Height*/)
			//{
				//pb->Location = p;
				//paint_Control(nullptr, gcnew PaintEventArgs(this->CreateGraphics(), this->Bounds)); // Didn't work
				HighValue = (p.Y - margin + pictureBox_SliderMax->Height/2) * (minValue - maxValue) / (Height-1 - 2*margin) + maxValue;
			//}
		}
		if(pb == pictureBox_SliderMin)
		{
			//if(p.Y < Height - margin - pb->Height/2 && p.Y >= pictureBox_SliderMax->Location.Y/* + pb->Height*/)
			//{
				//pb->Location = p;
				//paint_Control(nullptr, gcnew PaintEventArgs(this->CreateGraphics(), this->Bounds)); // Didn't work
				LowValue = (p.Y - margin + pictureBox_SliderMin->Height/2) * (minValue - maxValue) / (Height-1 - 2*margin) + maxValue;
			//}
		}
	}
}
void ColorExpansionBar::change_Bounds(System::Object^  sender, System::EventArgs^  e)
{
	if(sender == numericUpDown_highValue)
	{
		if(numericUpDown_highValue->Value < numericUpDown_lowValue->Value)
		{
			numericUpDown_highValue->Value = numericUpDown_lowValue->Value;
		}
		pictureBox_SliderMax->BringToFront();
		HighValue = Convert::ToDouble(numericUpDown_highValue->Value);
	}

	if(sender == numericUpDown_lowValue)
	{
		if(numericUpDown_lowValue->Value > numericUpDown_highValue->Value)
		{
			numericUpDown_lowValue->Value = Convert::ToDecimal(highValue);
		}
		pictureBox_SliderMin->BringToFront();
		LowValue = Convert::ToDouble(numericUpDown_lowValue->Value);
	}
}
void ColorExpansionBar::update_Sliders()
{
	int l;
	int h;
	if(maxValue == minValue)
	{
		l = Convert::ToInt32(Height-1 - margin - pictureBox_SliderMin->Height/2);
		h = Convert::ToInt32(margin - pictureBox_SliderMax->Height/2);
	}
	else
	{
		l = Convert::ToInt32((lowValue - maxValue) * (Height-1 - 2*margin) / (minValue - maxValue)) - pictureBox_SliderMin->Height/2 + margin;
		h = Convert::ToInt32((highValue - maxValue) * (Height-1 - 2*margin) / (minValue - maxValue)) - pictureBox_SliderMax->Height/2 + margin;
	}

	Drawing::Point pl(pictureBox_SliderMin->Location.X, l);
	Drawing::Point ph(pictureBox_SliderMax->Location.X, h);

	if(ph.Y < margin - pictureBox_SliderMax->Height/2)
	{
		lowValue = minValue;
		ph.Y = margin - pictureBox_SliderMax->Height/2;
	}
	if(ph.Y > pl.Y - pictureBox_SliderMax->Height)
	{
		// ph.Y = pl.Y - pictureBox_SliderMax->Height;
		// Dont do anything
	}
	pictureBox_SliderMax->Location = ph;

	if(pl.Y > Height-1 - margin -pictureBox_SliderMin->Height/2)
	{
		highValue = maxValue;
		pl.Y = Height-1 - margin -pictureBox_SliderMin->Height/2;
	}
	if(pl.Y < ph.Y + pictureBox_SliderMax->Height)
	{
		// pl.Y = ph.Y + pictureBox_SliderMax->Height;
		// Dont do anything
	}
	pictureBox_SliderMin->Location = pl;

	//this->Invalidate();
	//this->Update();
	this->Refresh();
	//paint_Control(nullptr, gcnew PaintEventArgs(this->CreateGraphics(), this->Bounds)); // Didn't work
}
void ColorExpansionBar::resize_Control(System::Object^  sender, System::EventArgs^  e)
{
	update_Sliders();
}

void ColorExpansionBar::click_ChangeColorScheme(System::Object^  sender, System::EventArgs^  e)
{
	((ToolStripMenuItem^)sender)->Checked = true;
	
	for(int i=2; i<context_color->Items->Count; i++)
	{
		if(context_color->Items[i] != ((ToolStripMenuItem^)sender))
		{
			((ToolStripMenuItem^)context_color->Items[i])->Checked = false;
		}
	}
	ColorScheme = ((ToolStripMenuItem^)sender)->Text;

	Refresh();
	RangeChanged();
}
Drawing::Color^ ColorExpansionBar::mapValue(double value)
{
	if(ColorScheme == "Gray")
	{
		if(value <= lowValue)
		{
			return Drawing::Color::Black;
		}
		if(value >= highValue)
		{
			return Drawing::Color::White;
		}

		// Calculate the right color
		return Drawing::Color::FromArgb(gray[Convert::ToByte( (gray->Length-1) * (value-lowValue) / (highValue-lowValue) )]);
	}

	if(ColorScheme == "Jet")
	{
		if(value <= lowValue)
		{
			return Drawing::Color::DarkBlue;
		}
		if(value >= highValue)
		{
			return Drawing::Color::DarkRed;
		}

		// Calculate the right color
		return Drawing::Color::FromArgb(jet[Convert::ToUInt16( (jet->Length-1) * (value-lowValue) / (highValue-lowValue) )]);
	}

	if(ColorScheme == "Hot")
	{
		if(value <= lowValue)
		{
			return Drawing::Color::Blue;
		}
		if(value >= highValue)
		{
			return Drawing::Color::Red;
		}

		// Calculate the right color
		return Drawing::Color::FromArgb(hot[Convert::ToUInt16( (hot->Length-1) * (value-lowValue) / (highValue-lowValue) )]);
	}

	if(ColorScheme == "Cold")
	{
		if(value <= lowValue)
		{
			return Drawing::Color::Red;
		}
		if(value >= highValue)
		{
			return Drawing::Color::Blue;
		}

		// Calculate the right color
		return Drawing::Color::FromArgb(cold[Convert::ToUInt16( 1020 * (value-lowValue) / (highValue-lowValue) )]);
	}

	return  Drawing::Color::Black;
}