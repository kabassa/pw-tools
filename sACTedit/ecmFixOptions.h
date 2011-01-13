#pragma once

namespace PW
{
	namespace Models
	{
		public ref struct EcmFixOptions
		{
			String^ fileIn;
			String^ fileOut;

			bool ecmSoulsphereHook;
			double ecmSoulsphereHookTX;
			double ecmSoulsphereHookTY;
			double ecmSoulsphereHookTZ;
		};
	}
}