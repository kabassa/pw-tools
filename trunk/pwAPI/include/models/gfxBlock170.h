#pragma once

#include "gfxBlock.h"

namespace PW
{
	namespace Models
	{
		public ref class gfxBLOCK170 : gfxBLOCK
		{
			public: gfxBLOCK170(void)
			{
			}
			protected: ~gfxBLOCK170()
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

					if(line->StartsWith("PathNum:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("VolMin:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("VolMax:"))
					{
						Parameters[i] = line->Replace("VolMax:", "Volume:");
					}
					if(line->StartsWith("PitchMin:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("PitchMax:"))
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