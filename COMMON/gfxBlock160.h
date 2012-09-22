#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK160 : gfxBLOCK
{
	public: gfxBLOCK160(void)
	{
	}
	protected: ~gfxBLOCK160()
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

				if(line->StartsWith("Use3DCam:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("FacingDir:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
			}
		}
		return true;
	}
};