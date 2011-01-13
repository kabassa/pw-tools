#pragma once

public ref class ecmHEAD
{
	public: ecmHEAD()
	{
	}
	protected: ~ecmHEAD()
	{
	}

	public: ArrayList^ Parameters;

	public: void SetAllParameters(array<String^>^ Properties)
	{
		Parameters = gcnew ArrayList(Properties);
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
					Parameters->Insert(i, "");
					i++;
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