#pragma once

public ref class ecmHEAD
{
	public: ecmHEAD()
	{
	}
	protected: ~ecmHEAD()
	{
	}

	public: int Version;
	public: String^ SkinModelPath;
	public: ArrayList^ Parameters;

	public: void SetAllParameters(array<String^>^ Properties)
	{
		Parameters = gcnew ArrayList(Properties);
		Version = -1;
		if(Properties[0]->StartsWith("MOXTVersion:"))
		{
			Version = Convert::ToInt32(Properties[0]->Split(gcnew array<wchar_t>{' '})[1]);
		}
		SkinModelPath = "";
		if(Properties[1]->StartsWith("SkinModelPath:"))
		{
			SkinModelPath = Properties[1]->Split(gcnew array<wchar_t>{' '})[1];
		}
		while(((String^)Parameters[Parameters->Count-1]) == "")
		{
			Parameters->RemoveAt(Parameters->Count-1);
		}
	}

	public: void Fix(Options^ options)
	{
		if(options->ecmDowngrade)
		{
			String^ line;

			for(int i=0; i<Parameters->Count; i++)
			{
				line = (String^)Parameters[i];

				if(line->StartsWith("MOXTVersion:"))
				{
					Parameters[i] = "MOXTVersion: 32";
				}
				if(line->StartsWith("AutoUpdata:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("EmissiveCol:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("CanCastShadow:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("RenderModel:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("RenderEdge:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("DefSpeed:"))
				{
					// if we don't have remove empty entries,
					// then the "" entry before DefSpeed is still available
					/*
					Parameters->Insert(i, "");
					i++;
					*/
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