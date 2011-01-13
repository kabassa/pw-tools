#pragma once

#include "gfxBlock.h"

namespace PW
{
	namespace Models
	{
		public ref class gfxBLOCK140 : gfxBLOCK
		{
			public: gfxBLOCK140(void)
			{
			}
			protected: ~gfxBLOCK140()
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