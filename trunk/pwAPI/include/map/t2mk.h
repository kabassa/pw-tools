#pragma once

namespace PW
{
	namespace Map
	{
		namespace T2MK
		{
			public ref struct t2mkBlock_1
			{
				int unknown_1;
				int seperator;
				int unknown_2;
				int unknown_3;
				float unknown_4;
				float unknown_5;
				int unknown_6;
			};

			public ref struct t2mkSubBlock
			{
				int id;
				int byte_position;
				int byte_length;
				array<unsigned char>^ byte_data;
			};

			public ref struct t2mkBlock_2
			{
				int subblock_count;
				array<t2mkSubBlock^>^ sub_blocks;
			};

			public ref struct mapT2mk
			{
				int version;
				int unknown_1;
				int count_1;
				int count_2;
				int unknown_2;

				array<int>^ byte_positions;
				array<t2mkBlock_1^>^ blocks_1;
				array<t2mkBlock_2^>^ blocks_2;
			};
		}
	}
}