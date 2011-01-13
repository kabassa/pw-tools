#pragma once

#include "gfxBlock.h"

namespace PW
{
	namespace Models
	{
		public ref class gfxBLOCK230 : gfxBLOCK
		{
			public: gfxBLOCK230(void)
			{
			}
			protected: ~gfxBLOCK230()
			{
			}

			public: virtual bool Fix(GfxFixOptions^ options) override
			{
				// Forsaken World Block, currently not present in PWI
				return false;
			}
		};
	}
}