#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK180 : gfxBLOCK
{
	public: gfxBLOCK180(void)
	{
	}
	protected: ~gfxBLOCK180()
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