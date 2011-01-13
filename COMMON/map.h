using namespace System;
using namespace System::IO;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Text;

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

public ref struct mapT2bk
{
	int zone;
	int global_pixel_position;
	float unknown_01;
	int pixel_size;

	array<unsigned char>^ hmap;
	array<unsigned char>^ tile_2;
	array<unsigned char>^ tile_3;
	array<unsigned char>^ tile_4;
};

public ref struct hmap
{
	array<float>^ Heights;
	array<int>^ ColorScheme;
	ArrayList^ Selection;
	ArrayList^ SelectedHeights;
	array<unsigned char>^ FrameBytes;
	Image^ Overlay;
};

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
public ref struct water
{
	float center_x;
	float center_y;
	float span_x;
	float span_y;
	float altitude;
};
public ref struct wmap
{
	int version;
	float map_width;
	float map_height;
	int surface_count;
	array<water^>^ surfaces;
	Image^ Overlay;
};