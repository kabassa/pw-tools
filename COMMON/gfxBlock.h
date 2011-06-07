#pragma once

public ref class gfxBLOCK abstract
{
	public: gfxBLOCK()
	{
	}
	protected: ~gfxBLOCK()
	{
	}

	// Global Variables
	public: ArrayList^ Parameters;
	public: unsigned int ElementID;
	public: unsigned int Type;
	public: String^ Name;
	public: int IsDummy;
	public: String^ DummyEle;
	public: String^ TexFile;
	public: String^ GfxPath; // only found in Block200

	public: void SetAllParameters(array<String^>^ Properties)
	{
		Parameters = gcnew ArrayList(Properties);

		ElementID = 0;
		Name = "";
		IsDummy = 0;
		DummyEle = "";
		TexFile = "";
		GfxPath = "";

		array<wchar_t>^ seperator = gcnew array<wchar_t>{':'};
		array<String^>^ pair;
		String^ key;
		String^ value;

		for(int i=0; i<Properties->Length; i++)
		{
			pair = (Properties[i]->Replace(": ", ":"))->Split(seperator);
			key = pair[0];
			if(pair->Length > 1)
			{
				value = pair[1];

				if(key == "GFXELEMENTID")
				{
					ElementID = Convert::ToUInt32(value);
				}
				if(key == "Name")
				{
					Name = value;
				}
				if(key == "IsDummy")
				{
					IsDummy = Convert::ToUInt32(value);
				}
				if(key == "TexFile")
				{
					TexFile = value;
				}
				if(key == "GfxPath")
				{
					GfxPath = value;
				}
				if(key == "DummyEle")
				{
					DummyEle = value;
				}
			}
		}
	}
	public: void FixBasicParameters()
	{
		String^ line;
		for(int i=0; i<Parameters->Count; i++)
		{
			line = (String^)Parameters[i];

			// replace with Priority to prevent case sensitivity trouble !
			if(line->StartsWith("priority:"))
			{
				Parameters[i] = line->Replace("priority:", "Priority:");
			}
			if(line->StartsWith("ResetLoopEnd:"))
			{
				Parameters->RemoveAt(i);
				i--;
			}
			if(line->StartsWith("TexAnimMaxTime:"))
			{
				Parameters->RemoveAt(i);
				i--;
			}
			if(line->StartsWith("ShaderFile:"))
			{
				Parameters->RemoveAt(i);
				i--;
			}
			if(line->StartsWith("ShaderTex: "))
			{
				Parameters->RemoveAt(i);
				i--;
			}
			if(line->StartsWith("PSConstCount:"))
			{
				Parameters->RemoveAt(i);
				i--;
			}
			if(line->StartsWith("PSConstIndex:"))
			{
				Parameters->RemoveAt(i);
				i--;
			}
			if(line->StartsWith("PSConstValue:"))
			{
				Parameters->RemoveAt(i);
				i--;
			}
			if(line->StartsWith("PSTargetCount:"))
			{
				Parameters->RemoveAt(i);
				i--;
			}
			if(line->StartsWith("PSInterval:"))
			{
				Parameters->RemoveAt(i);
				i--;
			}
			if(line->StartsWith("PSLoopCount:"))
			{
				Parameters->RemoveAt(i);
				i--;
			}
			if(line->StartsWith("CanDoFadeOut:"))
			{
				Parameters->RemoveAt(i);
				i--;
			}
		}
	}
	public: virtual bool Fix(Options^ options) abstract;
	public: void FixControlTypes()
	{
		String^ line;
		array<wchar_t>^ seperator = gcnew array<wchar_t>{' '};

		for(int i=0; i<Parameters->Count; i++)
		{
			line = (String^)Parameters[i];

			if(line->StartsWith("CtrlType: 108"))
			{
				// max. supported count is 5
				int count = Convert::ToInt32(((String^)Parameters[i+4])->Split(seperator)[1]);
				if(count > 5)
				{
					Parameters[i+4] = "Count: 5";

					// read all existing values
					array<int>^ colors = gcnew array<int>(count);
					array<double>^ times = gcnew array<double>(count);
					for(int n=0; n<count; n++)
					{
						// color value
						colors[n] = Convert::ToInt32(((String^)Parameters[i+5+2*n])->Split(seperator)[1]);
						// timespan value
						times[n] = Convert::ToDouble(((String^)Parameters[i+5+2*n+1])->Split(seperator)[1]);
						if(n>0)
						{
							times[n] = times[n-1] + times[n];
						}
					}

					// remove lines until there are only 5
					for(int n=0; n<count-5; n++)
					{
						Parameters->RemoveAt(i+5);
						Parameters->RemoveAt(i+5);
					}

					double map = Convert::ToDouble(count-1)/4.0;
					double time = 0.0;
					int index;

					// change the existing values by applying nearest neighbour mapping
					for(int n=0; n<5; n++)
					{
						index = Convert::ToInt32(Math::Round(map*n));
						// set color
						Parameters[i+5+2*n] = "Color: " + colors[index].ToString();
						// set timespan
						Parameters[i+5+2*n+1] = "TimeSpan: " + (times[index]-time).ToString("F6");
						time = times[index];
					}
				}
			}

			if(line->StartsWith("CtrlType: 111"))
			{
				// max. supported count is 9
				int count = Convert::ToInt32(((String^)Parameters[i+4])->Split(seperator)[1]); 
				if(count > 9)
				{
					Parameters[i+4] = "Count: 9";

					// read all existing values
					array<double>^ scales = gcnew array<double>(count);
					array<double>^ times = gcnew array<double>(count);
					for(int n=0; n<count; n++)
					{
						// scale value
						scales[n] = Convert::ToDouble(((String^)Parameters[i+5+2*n])->Split(seperator)[1]);
						// timespan value
						times[n] = Convert::ToDouble(((String^)Parameters[i+5+2*n+1])->Split(seperator)[1]);
						if(n>0)
						{
							times[n] = times[n-1] + times[n];
						}
					}

					// remove lines until there are only 9
					for(int n=0; n<count-9; n++)
					{
						Parameters->RemoveAt(i+5);
						Parameters->RemoveAt(i+5);
					}

					double map = Convert::ToDouble(count-1)/8.0;
					double time = 0.0;
					int index;

					// change the existing values by applying nearest neighbour mapping
					for(int n=0; n<9; n++)
					{
						index = Convert::ToInt32(Math::Round(map*n));
						// set scale
						Parameters[i+5+2*n] = "Scale: " + scales[index].ToString("F6");
						// set timespan
						Parameters[i+5+2*n+1] = "TimeSpan: " + (times[index]-time).ToString("F6");
						time = times[index];
					}
				}
			}

			if(line->StartsWith("AlphaOnly:"))
			{
				Parameters->RemoveAt(i);
				i--;
			}
		}
	}
	public: array<String^>^ GetAllParameters()
	{
		array<String^>^ temp = gcnew array<String^>(Parameters->Count);

		for(int i=0; i<temp->Length; i++)
		{
			temp[i] = (String^)Parameters[i];
		}

		return temp;
	}
};