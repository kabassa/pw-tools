#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK000 : gfxBLOCK
{
	public: gfxBLOCK000(void)
	{
	}
	protected: ~gfxBLOCK000()
	{
	}

	public: virtual bool Fix(Options^ options) override
	{
		return true;
	}
};