#pragma once

#include "gfxBlock.h"

namespace PW
{
	namespace Models
	{
		public ref class gfxBLOCK100 : gfxBLOCK
		{
			public: gfxBLOCK100(void)
			{
			}
			protected: ~gfxBLOCK100()
			{
			}

			public: virtual bool Fix(GfxFixOptions^ options) override
			{
				FixBasicParameters();
				FixControlTypes();

				String^ line;

				for(int i=0; i<Parameters->Count; i++)
				{
					line = (String^)Parameters[i];

					if(line->StartsWith("SurfaceUseParentDir:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("YawEffect:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
				}

				return true;
			}
		};
	}
}