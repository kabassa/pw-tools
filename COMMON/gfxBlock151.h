#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK151 : gfxBLOCK
{
	public: gfxBLOCK151(void)
	{
	}
	protected: ~gfxBLOCK151()
	{
	}

	public: virtual bool Fix(Options^ options) override
	{
		// don't appear in version > v37
		return true;
	}
};