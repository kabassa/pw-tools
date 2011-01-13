#pragma once

namespace PW
{
	namespace Map
	{
		namespace RMAP
		{
			public ref struct rmap
			{
				int Version;
				int ByteCount;
				int LineSize;
				int MapWidth;
				int MapHeight;
				int LineCount;
				float Unknown;
				array<BitArray^>^ Lines;
				ArrayList^ Selection;
				ArrayList^ SelectedBits;
				array<unsigned char>^ FrameBytes;
				Image^ Overlay;
			};
		}
	}
}