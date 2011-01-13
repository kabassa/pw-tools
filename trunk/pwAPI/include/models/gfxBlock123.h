#pragma once

#include "gfxBlock.h"

namespace PW
{
	namespace Models
	{
		public ref class gfxBLOCK123 : gfxBLOCK
		{
			public: gfxBLOCK123(void)
			{
			}
			protected: ~gfxBLOCK123()
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

					if(line->StartsWith("IsUseParUV:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("IsStartOnGrnd:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("ParIniDir:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("IsUseHSVInterp:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("IsAvgGen:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("AlphaSeg:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("BetaSeg:"))
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