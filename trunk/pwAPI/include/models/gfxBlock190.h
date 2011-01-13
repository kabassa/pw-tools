#pragma once

#include "gfxBlock.h"

namespace PW
{
	namespace Models
	{
		public ref class gfxBLOCK190 : gfxBLOCK
		{
			public: gfxBLOCK190(void)
			{
			}
			protected: ~gfxBLOCK190()
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