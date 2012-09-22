#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK170 : gfxBLOCK
{
	public: gfxBLOCK170(void)
	{
	}
	protected: ~gfxBLOCK170()
	{
	}

	public: virtual bool Fix(Options^ options) override
	{
		if(options->gfxDowngrade)
		{
			FixBasicParameters();
			FixControlTypes();

			String^ line;
			bool path = 0;
			bool minDist = 0;
			bool maxDist = 0;

			for(int i=0; i<Parameters->Count; i++)
			{
				line = (String^)Parameters[i];

				if(line->StartsWith("PathNum:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("VolMin:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("VolMax:"))
				{
					Parameters[i] = line->Replace("VolMax:", "Volume:");
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
				if(line->StartsWith("Path:"))
				{
					if(!path)
					{
						path=1;
					}
					else
					{
						Parameters->RemoveAt(i);
						i--;
					}
				}
				if(line->StartsWith("UseCustom:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("MinDist:"))
				{
					if(!minDist)
					{
						minDist=1;
					}
					else
					{
						Parameters->RemoveAt(i);
						i--;
					}
				}
				if(line->StartsWith("MaxDist:"))
				{
					if(!maxDist)
					{
						maxDist=1;
					}
					else
					{
						Parameters->RemoveAt(i);
						i--;
					}
				}
			}
		}
		return true;
	}
};