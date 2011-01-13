#pragma once

#include "gfxBlock.h"

namespace PW
{
	namespace Models
	{
		public ref class gfxBLOCK200 : gfxBLOCK
		{
			public: gfxBLOCK200(void)
			{
			}
			protected: ~gfxBLOCK200()
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

					if(line->StartsWith("PlaySpeed:"))
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