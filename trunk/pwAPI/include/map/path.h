#pragma once

namespace PW
{
	namespace Map
	{
		namespace PATH
		{
			public ref struct path_point
			{
				float x;
				float altitude;
				float z;
				float direction_x;
				float direction_altitude;
				float direction_z;
			};

			public ref struct path_segment
			{
				float x_1;
				float altitude_1;
				float z_1;
				float x_2;
				float altitude_2;
				float z_2;
				int startpoint;
				int endpoint;
				float length;
			};
			public ref struct path
			{
				int unknown_1;
				int id;
				int seperator_1;
				int seperator_2;
				int count_points;
				array<path_point^>^ points;
				int count_segments;
				array<path_segment^>^ segments;
			};

			public ref struct pathCollection
			{
				int version;
				int count;
				array<path^>^ paths;
				array<unsigned char>^ FrameBytes;
			};
		}
	}
}