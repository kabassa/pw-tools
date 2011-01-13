#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK130 : gfxBLOCK
{
	public: gfxBLOCK130(void)
	{
	}
	protected: ~gfxBLOCK130()
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