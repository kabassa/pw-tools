#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK122 : gfxBLOCK
{
	public: gfxBLOCK122(void)
	{
	}
	protected: ~gfxBLOCK122()
	{
	}

	public: virtual bool Fix(Options^ options) override
	{
		if(options->gfxDowngrade)
		{
			FixBasicParameters();
			FixControlTypes();

			String^ line;

			for(int i=0; i<Parameters->Count; i++)
			{
				line = (String^)Parameters[i];

				if(line->StartsWith("RefModel:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("UseNormal:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("PerpToNormal:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("SkinIndex:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("SkinMeshIndex:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
			}
		}
		return true;
	}
};