#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK120 : gfxBLOCK
{
	public: gfxBLOCK120(void)
	{
	}
	protected: ~gfxBLOCK120()
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

				if(line->StartsWith("IsUseParUV:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("IsStartOnGrnd:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("ParIniDir:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("IsUseHSVInterp:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
			}
		}
		return true;
	}
};