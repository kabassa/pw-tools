#pragma once

#include "gfxBlock.h"

namespace PW
{
	namespace Models
	{
		public ref class gfxBLOCK151 : gfxBLOCK
		{
			public: gfxBLOCK151(void)
			{
			}
			protected: ~gfxBLOCK151()
			{
			}

			public: virtual bool Fix(GfxFixOptions^ options) override
			{
				// don't appear in version > v37
				return true;
			}
		};
	}
}