#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK122 : gfxBLOCK
{
	public: gfxBLOCK122(void)
	{
	}
	protected: ~gfxBLOCK122()
	{
	}

	public: virtual bool Fix(Options^ options) override
	{
		// don't appear in version > v37
		return true;
	}
};