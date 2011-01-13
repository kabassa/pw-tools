#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK110 : gfxBLOCK
{
	public: gfxBLOCK110(void)
	{
	}
	protected: ~gfxBLOCK110()
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

				if(line->StartsWith("Spline:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
			}
		}
		return true;
	}
};