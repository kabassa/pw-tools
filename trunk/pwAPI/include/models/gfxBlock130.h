#pragma once

#include "gfxBlock.h"

namespace PW
{
	namespace Models
	{
		public ref class gfxBLOCK130 : gfxBLOCK
		{
			public: gfxBLOCK130(void)
			{
			}
			protected: ~gfxBLOCK130()
			{
			}

			public: virtual bool Fix(GfxFixOptions^ options) override
			{
				FixBasicParameters();
				FixControlTypes();

				// no new unique parameters since v58

				return true;
			}
		};
	}
}