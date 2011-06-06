#pragma once

public ref class ecmTYPE
{
	public: ecmTYPE()
	{
	}
	protected: ~ecmTYPE()
	{
	}

	public: int Version;
	public: ArrayList^ Parameters;

	public: void SetAllParameters(array<String^>^ Properties)
	{
		Version = Convert::ToInt32(Properties[0]->Split(gcnew array<wchar_t>{' '})[1]);
		Parameters = gcnew ArrayList(Properties);
	}

	public: void Fix(Options^ options)
	{
		if(options->ecmDowngrade)
		{
			String^ line;
			array<wchar_t>^ seperator = gcnew array<wchar_t>{' '};

			for(int i=0; i<Parameters->Count; i++)
			{
				line = (String^)Parameters[i];

				if(line->StartsWith("FxFileNum:"))
				{
					int count = Convert::ToInt32(line->Split(seperator)[1]);
					if(count == 0)
					{
						Parameters[i] = "FxFilePath: ";
					}
					if(count == 1)
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(count > 1)
					{
						MessageBox::Show("DEBUG: FxFileNum > 1");
					}
				}
				if(line == "HookName: HH_shang")
				{
					if(options->ecmSoulsphereHook/* && options->fileIn->Contains("weapons")*/)
					{
						Parameters[i] = "HookName: CC_weapon";
						line = (String^)Parameters[i+1];
						array<String^>^ hookOffset = line->Replace(", ", " ")->Split(seperator);
						line = hookOffset[0];
						line += " " + (Convert::ToDouble(hookOffset[1]) + options->ecmSoulsphereHookTX).ToString("F6");
						line += ", " + (Convert::ToDouble(hookOffset[2]) + options->ecmSoulsphereHookTZ).ToString("F6");
						line += ", " + (Convert::ToDouble(hookOffset[3]) + options->ecmSoulsphereHookTY).ToString("F6");
						Parameters[i+1] = line;
					}
				}
				if(line->StartsWith("GfxRelToECM:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("GfxDelayTime:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("FadeOut:"))
				{
					int time = Convert::ToInt32(line->Split(seperator)[1]);
					if(time > 1)
					{
						Parameters[i] = "FadeOut: 1";
					}
				}
				if(line->StartsWith("SoundVer:"))
				{
					Parameters[i] = "SoundVer: 1";
				}
				if(line->StartsWith("VolMin:"))
				{
					Parameters[i] = "Volume: " + ((Convert::ToInt32(((String^)Parameters[i])->Split(seperator)[1]) + Convert::ToInt32(((String^)Parameters[i+1])->Split(seperator)[1])) / 2).ToString();
				}
				if(line->StartsWith("VolMax:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("PitchMin:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("PitchMax:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("TransTime:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("CustomPath:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
// not necessary because EventType: 104 will be removed...
//{
/*
				if(line->StartsWith("AtkUseDelay:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("AtkDelayNum:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("AtkDelayTime:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
*/
//}
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