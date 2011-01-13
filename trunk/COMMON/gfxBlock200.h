#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK200 : gfxBLOCK
{
	public: gfxBLOCK200(void)
	{
	}
	protected: ~gfxBLOCK200()
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

				if(line->StartsWith("PlaySpeed:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
			}
		}
		return true;
	}
};