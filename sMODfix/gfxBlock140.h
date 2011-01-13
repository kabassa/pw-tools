#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK140 : gfxBLOCK
{
	public: gfxBLOCK140(void)
	{
	}
	protected: ~gfxBLOCK140()
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