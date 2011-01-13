#pragma once

#include "gfxBlock.h"

namespace PW
{
	namespace Models
	{
		public ref class gfxBLOCK211 : gfxBLOCK
		{
			public: gfxBLOCK211(void)
			{
			}
			protected: ~gfxBLOCK211()
			{
			}

			public: virtual bool Fix(GfxFixOptions^ options) override
			{
				return false;
			}
		};
	}
}