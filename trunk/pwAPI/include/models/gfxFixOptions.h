#pragma once

namespace PW
{
	namespace Models
	{
		public ref struct GfxFixOptions
		{
			String^ fileIn;
			String^ fileOut;

			bool gfx152to150;
			bool gfx210to160;
			bool ecmSoulsphereHook;
		};
	}
}