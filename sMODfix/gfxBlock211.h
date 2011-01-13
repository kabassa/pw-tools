#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK211 : gfxBLOCK
{
	public: gfxBLOCK211(void)
	{
	}
	protected: ~gfxBLOCK211()
	{
	}

	public: virtual bool Fix(Options^ options) override
	{
		return false;
	}
};