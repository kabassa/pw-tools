#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK190 : gfxBLOCK
{
	public: gfxBLOCK190(void)
	{
	}
	protected: ~gfxBLOCK190()
	{
	}

	public: virtual bool Fix(Options^ options) override
	{
		if(options->gfxDowngrade)
		{
			FixBasicParameters();
			FixControlTypes();

			// no new unique parameters since v58
		}
		return true;
	}
};