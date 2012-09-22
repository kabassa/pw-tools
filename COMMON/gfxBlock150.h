#pragma once

#include "gfxBlock.h"

#pragma once

public ref class gfxBLOCK150 : gfxBLOCK
{
	public: gfxBLOCK150(void)
	{
	}
	protected: ~gfxBLOCK150()
	{
	}

	public: virtual bool Fix(Options^ options) override
	{
		if(options->gfxDowngrade)
		{
			FixBasicParameters();
			FixControlTypes();

			String^ line;

			for(int i=0; i<Parameters->Count; i++)
			{
				line = (String^)Parameters[i];

				if(line->StartsWith("Filter:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("WaveMoving:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("WaveMovingSpeed:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("FixWaveLength:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("NumWaves:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
			}
		}
		return true;
	}
};