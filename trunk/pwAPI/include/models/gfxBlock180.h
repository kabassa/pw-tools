#pragma once

#include "gfxBlock.h"

namespace PW
{
	namespace Models
	{
		public ref class gfxBLOCK180 : gfxBLOCK
		{
			public: gfxBLOCK180(void)
			{
			}
			protected: ~gfxBLOCK180()
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