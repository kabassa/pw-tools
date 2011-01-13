#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK101 : gfxBLOCK
{
	public: gfxBLOCK101(void)
	{
	}
	protected: ~gfxBLOCK101()
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

				if(line->StartsWith("SurfaceUseParentDir:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("YawEffect:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
			}
		}
		return true;
	}
};