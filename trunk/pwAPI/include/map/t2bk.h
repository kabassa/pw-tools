#pragma once

namespace PW
{
	namespace Map
	{
		namespace T2BK
		{
			public ref struct mapT2bk
			{
				public: int Zone;
				public: int GlobalPixelPosition;
				public: float unknown_01;
				public: int PixelSize;

				public: array<unsigned char>^ Tile_hmap;
				public: array<unsigned char>^ Tile_2;
				public: array<unsigned char>^ Tile_3;
				public: array<unsigned char>^ Tile_4;
			};
		}
	}
}