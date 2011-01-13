#pragma once

#include "gfxBlock.h"

namespace PW
{
	namespace Models
	{
		public ref class gfxBLOCK000 : gfxBLOCK
		{
			public: gfxBLOCK000(void)
			{
			}
			protected: ~gfxBLOCK000()
			{
			}

			public: virtual bool Fix(GfxFixOptions^ options) override
			{
				return true;
			}
		};
	}
}