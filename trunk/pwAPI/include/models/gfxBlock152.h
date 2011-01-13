#pragma once

#include "gfxBlock.h"

namespace PW
{
	namespace Models
	{
		public ref class gfxBLOCK152 : gfxBLOCK
		{
			public: gfxBLOCK152(void)
			{
			}
			protected: ~gfxBLOCK152()
			{
			}

			public: virtual bool Fix(GfxFixOptions^ options) override
			{
				if(!options->gfx152to150)
				{
					return false;
				}

				FixBasicParameters();
				FixControlTypes();

				String^ line;

				for(int i=0; i<Parameters->Count; i++)
				{
					line = (String^)Parameters[i];

					if(line->StartsWith("GFXELEMENTID: 152"))
					{
						Parameters[i] = line->Replace("152", "150");
						ElementID = 150;
					}
					if(line->StartsWith("Filter:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("isappend:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("renderside:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("istaildisappear:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("vertslife:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("tailfadeout:"))
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