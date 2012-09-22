#pragma once

public ref class gfxHEAD
{
	public: gfxHEAD()
	{
	}
	protected: ~gfxHEAD()
	{
	}

	public: ArrayList^ Parameters;

	public: void SetAllParameters(array<String^>^ Properties)
	{
		Parameters = gcnew ArrayList(Properties);
	}

	public: void Fix(Options^ options)
	{
		if(options->gfxDowngrade)
		{
			String^ line;

			for(int i=0; i<Parameters->Count; i++)
			{
				line = (String^)Parameters[i];

				if(line->StartsWith("MOXTVersion:"))
				{
					int version = Convert::ToInt32(line->Replace(": ", ":")->Split(gcnew array<wchar_t>{':'})[1]);
					if(version > 58)
					{
						Parameters[i] = "MOXTVersion: 58";
					}
				}
				if(line->StartsWith("IsAngelica3:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("AccurateAABB:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("ShakePeriod:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("ShakeByDistance:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("ShakeDamp:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("ShakeCamBlur:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("ShakeCamPixOff:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("PhysExist:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
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