#pragma once

namespace PW
{
	namespace Map
	{
		namespace HMAP
		{
			public ref struct hmap
			{
				array<float>^ Heights;
				array<int>^ ColorScheme;
				ArrayList^ Selection;
				ArrayList^ SelectedHeights;
				array<unsigned char>^ FrameBytes;
				Image^ Overlay;
			};
		}
	}
}