#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

// 128 Bit (16 Byte)
public ref struct DDS_BLOCK
{
	public: unsigned short color_start;
	public: unsigned short color_end;
	public: BitArray^ color_indices;
	// opt DXT3 data
	public: array<unsigned char>^ alpha_values;
	// opt DXT5 data
	public: unsigned char alpha_start;
	public: unsigned char alpha_end;
	public: BitArray^ alpha_indices;
};
// 32 byte
public ref struct DDS_PIXELFORMAT
{
	public: int dwSize;
	public: int dwFlags;
	public: array<unsigned char>^ dwFourCC; // 4 byte
	public: String^ fourCC;
	public: int dwRGBBitCount;
	public: int dwRBitMask;
	public: int dwGBitMask;
	public: int dwBBitMask;
	public: int dwABitMask;
};

// 124 byte
public ref struct DDS_HEADER
{
	public: int dwSize;
	public: int dwHeaderFlags;
	public: int dwHeight;
	public: int dwWidth;
	public: int dwPitchOrLinearSize;
	public: int dwDepth;
	public: int dwMipMapCount;
	public: array<int>^ dwReserved1; // 11 integers
	public: DDS_PIXELFORMAT^ ddspf;
	public: int dwSurfaceFlags;
	public: int dwCubemapFlags;
	public: array<int>^ dwReserved2; // 3 integers
};

public ref class DDS
{
	public: DDS(void)
	{
	}

	protected: ~DDS()
	{
	}

	public: DDS_HEADER^ dwHeader;
	public: array<unsigned char>^ dwSignature;
	public: array<array<DDS_BLOCK^>^>^ dwMipMaps;
	private: array<array<Color>^>^ colorMaps;

	private: Color GetColorFromBlock(DDS_BLOCK^ block, int index)
	{
		unsigned short alpha, a0, a1, r0, g0, b0, r1, g1, b1;
		bool bit0, bit1, bit2;

		a0 = block->alpha_start;
		a1 = block->alpha_end;
		r0 = (block->color_start/2048) * 255 / 31;
		g0 = (block->color_start%2048/32) * 255 / 63;
		b0 = (block->color_start%32) * 255 / 31;
		r1 = (block->color_end/2048) * 255 / 31;
		g1 = (block->color_end%2048/32) * 255 / 63;
		b1 = (block->color_end%32) * 255 / 31;

		alpha = 255;

		if(dwHeader->ddspf->fourCC == "DXT3")
		{
			alpha = block->alpha_values[index/2];
			if(alpha%2 == 0)
			{
				alpha = alpha/16 * 17;
			}
			else
			{
				alpha = alpha%16 * 17;
			}
		}
		if(dwHeader->ddspf->fourCC == "DXT5")
		{
			// Reversed bit order
			bit2 = block->alpha_indices[3*index];
			bit1 = block->alpha_indices[3*index+1];
			bit0 = block->alpha_indices[3*index+2];
			if(a0 > a1)
			{
				if(!bit0 && !bit1 && !bit2) // 000
				{
					alpha = a0;
				}
				if(!bit0 && !bit1 && bit2) // 001
				{
					alpha = a1;
				}
				if(!bit0 && bit1 && !bit2) // 010
				{
					alpha = (6*a0+a1)/7;
				}
				if(!bit0 && bit1 && bit2) // 011
				{
					alpha = (5*a0+2*a1)/7;
				}
				if(bit0 && !bit1 && !bit2) // 100
				{
					alpha = (4*a0+3*a1)/7;
				}
				if(bit0 && !bit1 && bit2) // 101
				{
					alpha = (3*a0+4*a1)/7;
				}
				if(bit0 && bit1 && !bit2) // 110
				{
					alpha = (2*a0+5*a1)/7;
				}
				if(bit0 && bit1 && bit2) // 111
				{
					alpha = (a0+6*a1)/7;
				}
			}
			else
			{
				if(!bit0 && !bit1 && !bit2) // 000
				{
					alpha = a0;
				}
				if(!bit0 && !bit1 && bit2) // 001
				{
					alpha = a1;
				}
				if(!bit0 && bit1 && !bit2) // 010
				{
					alpha = (4*a0+a1)/5;
				}
				if(!bit0 && bit1 && bit2) // 011
				{
					alpha = (3*a0+2*a1)/5;
				}
				if(bit0 && !bit1 && !bit2) // 100
				{
					alpha = (2*a0+3*a1)/5;
				}
				if(bit0 && !bit1 && bit2) // 101
				{
					alpha = (a0+4*a1)/5;
				}
				if(bit0 && bit1 && !bit2) // 110
				{
					alpha = 0;
				}
				if(bit0 && bit1 && bit2) // 111
				{
					alpha = 255;
				}
			}
		}

		if(block->color_start > block->color_end)
		{
			// reversed bit order
			bit1 = block->color_indices[2*index];
			bit0 = block->color_indices[2*index+1];
			if(!bit0 && !bit1)
			{
				return Color::FromArgb(alpha, r0, g0, b0);
			}
			if(!bit0 && bit1)
			{
				return Color::FromArgb(alpha, r1, g1, b1);
			}
			if(bit0 && !bit1)
			{
				return Color::FromArgb(alpha, (2*r0+r1)/3, (2*g0+g1)/3, (2*b0+b1)/3);
			}
			if(bit0 && bit1)
			{
				return Color::FromArgb(alpha, (2*r1+r0)/3, (2*g1+g0)/3, (2*b1+b0)/3);
			}
		}
		// DXT1 special case compatiblity
		else
		{
			// reversed bit order
			bit1 = block->color_indices[2*index];
			bit0 = block->color_indices[2*index+1];
			if(!bit0 && !bit1)
			{
				return Color::FromArgb(r0, g0, b0);
			}
			if(!bit0 && bit1)
			{
				return Color::FromArgb(r1, g1, b1);
			}
			if(bit0 && !bit1)
			{
				return Color::FromArgb((r0+r1)/2, (g0+g1)/2, (b0+b1)/2);
			}
			if(bit0 && bit1)
			{
				return Color::FromArgb(0, (r0+r1)/2, (g0+g1)/2, (b0+b1)/2);
			}
		}

		return Color();
	}
	public: Color GetColor(int mipMapIndex, int x, int y)
	{
		int pos;

		if(dwHeader->ddspf->fourCC == "\0\0\0\0")
		{
			pos = y*dwHeader->dwWidth/Convert::ToInt32(Math::Pow(2, mipMapIndex)) + x;
		}

		if(dwHeader->ddspf->fourCC->Contains("DXT"))
		{
			pos = ((y/4)*4*dwHeader->dwWidth) + (y%4*4) + (x%4) + ((x/4)*16);
		}

		if(mipMapIndex<colorMaps->Length && pos<colorMaps[mipMapIndex]->Length)
		{
			return colorMaps[mipMapIndex][pos];
		}
		else
		{
			return Color();
		}
	}

	public: void SetAlpha(int mipMapIndex, int x, int y, int alpha)
	{
		int pos;

		if(dwHeader->ddspf->fourCC == "\0\0\0\0")
		{
			pos = y*dwHeader->dwWidth/Convert::ToInt32(Math::Pow(2, mipMapIndex)) + x;
		}

		if(dwHeader->ddspf->fourCC->Contains("DXT"))
		{
			pos = ((y/4)*4*dwHeader->dwWidth) + (y%4*4) + (x%4) + ((x/4)*16);
		}
		

		if(mipMapIndex<colorMaps->Length && pos<colorMaps[mipMapIndex]->Length)
		{
			colorMaps[mipMapIndex][pos] = Color::FromArgb(alpha, colorMaps[mipMapIndex][pos]);
		}
	}

	/*
		recompress alpha channel after fixing
		also convert DXT1/DXT3 to DXT5
	*/
	public: void RecompressDXT5_alpha()
	{
		// only do this DXT1, DXT3 or DXT5 compressed data
		// because for uncompressed data the values are directly saved from the updated colorMap array
		if(dwHeader->ddspf->fourCC->Contains("DXT"))
		{
			array<unsigned char>^ alpha_values = gcnew array<unsigned char>(16);
			double stepsize;
			int index;
			unsigned short temp;

			// change property to DXT5
			if(dwHeader->ddspf->fourCC = "DXT1")
			{
				dwHeader->dwPitchOrLinearSize = 2*dwHeader->dwPitchOrLinearSize;
			}
			(gcnew UTF8Encoding())->GetBytes("DXT5", 0, 4, dwHeader->ddspf->dwFourCC, 0);
			dwHeader->ddspf->fourCC = "DXT5";
			

			for(int i=0; i<dwMipMaps->Length; i++)
			{
				for(int b=0; b<dwMipMaps[i]->Length; b++)
				{
					// trans-casting colors from DXT1 to DXT5
					if(dwMipMaps[i][b]->color_start < dwMipMaps[i][b]->color_end)
					{
						temp = dwMipMaps[i][b]->color_start;
						dwMipMaps[i][b]->color_start = dwMipMaps[i][b]->color_end;
						dwMipMaps[i][b]->color_end = temp;
					}

					for(int c=0; c<16; c++)
					{
						alpha_values[c] = colorMaps[i][b*16+c].A;
					}

					Array::Sort(alpha_values);

					if(alpha_values[0] == 0 && alpha_values[15] == 255)
					{
						dwMipMaps[i][b]->alpha_start = alpha_values[1];
						dwMipMaps[i][b]->alpha_end = alpha_values[14];
						stepsize = (Convert::ToDouble(dwMipMaps[i][b]->alpha_end) - Convert::ToDouble(dwMipMaps[i][b]->alpha_start)) / 5;
					}
					if(alpha_values[0] == 0 && alpha_values[15] != 255)
					{
						dwMipMaps[i][b]->alpha_start = alpha_values[1];
						dwMipMaps[i][b]->alpha_end = alpha_values[15];
						stepsize = (Convert::ToDouble(dwMipMaps[i][b]->alpha_end) - Convert::ToDouble(dwMipMaps[i][b]->alpha_start)) / 5;
					}
					if(alpha_values[0] != 0 && alpha_values[15] == 255)
					{
						dwMipMaps[i][b]->alpha_start = alpha_values[0];
						dwMipMaps[i][b]->alpha_end = alpha_values[14];
						stepsize = (Convert::ToDouble(dwMipMaps[i][b]->alpha_end) - Convert::ToDouble(dwMipMaps[i][b]->alpha_start)) / 5;
					}
					if(alpha_values[0] != 0 && alpha_values[15] != 255)
					{
						dwMipMaps[i][b]->alpha_start = alpha_values[15];
						dwMipMaps[i][b]->alpha_end = alpha_values[0];
						stepsize = (Convert::ToDouble(dwMipMaps[i][b]->alpha_end) - Convert::ToDouble(dwMipMaps[i][b]->alpha_start)) / 7;
					}

					for(int c=0; c<16; c++)
					{
						if(stepsize == 0)
						{
							index = 0;
						}
						else
						{
							index = Convert::ToInt32(Math::Round((Convert::ToDouble(colorMaps[i][b*16+c].A)-Convert::ToDouble(dwMipMaps[i][b]->alpha_start)) / stepsize));
						}

						// all bits are reversed ordered!
						if(dwMipMaps[i][b]->alpha_start > dwMipMaps[i][b]->alpha_end)
						{
							if(index == 0)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = false;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = false;
								dwMipMaps[i][b]->alpha_indices[3*c] = false;
							}
							if(index == 1)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = false;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = true;
								dwMipMaps[i][b]->alpha_indices[3*c] = false;
							}
							if(index == 2)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = false;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = true;
								dwMipMaps[i][b]->alpha_indices[3*c] = true;
							}
							if(index == 3)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = true;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = false;
								dwMipMaps[i][b]->alpha_indices[3*c] = false;
							}
							if(index == 4)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = true;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = false;
								dwMipMaps[i][b]->alpha_indices[3*c] = true;
							}
							if(index == 5)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = true;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = true;
								dwMipMaps[i][b]->alpha_indices[3*c] = false;
							}
							if(index == 6)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = true;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = true;
								dwMipMaps[i][b]->alpha_indices[3*c] = true;
							}
							if(index == 7)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = false;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = false;
								dwMipMaps[i][b]->alpha_indices[3*c] = true;
							}
						}
						// all bits are reversed order
						else
						{
							if(index < 0)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = true;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = true;
								dwMipMaps[i][b]->alpha_indices[3*c] = false;
							}
							if(index == 0)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = false;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = false;
								dwMipMaps[i][b]->alpha_indices[3*c] = false;
							}
							if(index == 1)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = false;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = true;
								dwMipMaps[i][b]->alpha_indices[3*c] = false;
							}
							if(index == 2)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = false;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = true;
								dwMipMaps[i][b]->alpha_indices[3*c] = true;
							}
							if(index == 3)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = true;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = false;
								dwMipMaps[i][b]->alpha_indices[3*c] = false;
							}
							if(index == 4)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = true;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = false;
								dwMipMaps[i][b]->alpha_indices[3*c] = true;
							}
							if(index == 5)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = false;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = false;
								dwMipMaps[i][b]->alpha_indices[3*c] = true;
							}
							if(index > 5)
							{
								dwMipMaps[i][b]->alpha_indices[3*c+2] = true;
								dwMipMaps[i][b]->alpha_indices[3*c+1] = true;
								dwMipMaps[i][b]->alpha_indices[3*c] = true;
							}
						}
					}
				}
			}
		}
	}


	public: void load(String^ file)
	{
		FileStream^ fr = File::OpenRead(file);
		BinaryReader^ br = gcnew BinaryReader(fr);

		dwHeader = gcnew DDS_HEADER();
		dwHeader->dwReserved1 = gcnew array<int>(11);
		dwHeader->dwReserved2 = gcnew array<int>(3);
		dwHeader->ddspf = gcnew DDS_PIXELFORMAT();

		dwSignature = br->ReadBytes(4);
		dwHeader->dwSize = br->ReadInt32();
		dwHeader->dwHeaderFlags = br->ReadInt32();
		dwHeader->dwHeight = br->ReadInt32();
		dwHeader->dwWidth = br->ReadInt32();
		dwHeader->dwPitchOrLinearSize = br->ReadInt32();
		dwHeader->dwDepth = br->ReadInt32();
		dwHeader->dwMipMapCount = br->ReadInt32();
		for(int i=0; i<dwHeader->dwReserved1->Length; i++)
		{
			dwHeader->dwReserved1[i] = br->ReadInt32();
		}
		dwHeader->ddspf->dwSize = br->ReadInt32();
		dwHeader->ddspf->dwFlags = br->ReadInt32();
		dwHeader->ddspf->dwFourCC = br->ReadBytes(4);
		dwHeader->ddspf->fourCC = Encoding::UTF8->GetString(dwHeader->ddspf->dwFourCC);
		dwHeader->ddspf->dwRGBBitCount = br->ReadInt32();
		dwHeader->ddspf->dwRBitMask = br->ReadInt32();
		dwHeader->ddspf->dwGBitMask = br->ReadInt32();
		dwHeader->ddspf->dwBBitMask = br->ReadInt32();
		dwHeader->ddspf->dwABitMask = br->ReadInt32();
		dwHeader->dwSurfaceFlags = br->ReadInt32();
		dwHeader->dwCubemapFlags = br->ReadInt32();
		for(int i=0; i<dwHeader->dwReserved2->Length; i++)
		{
			dwHeader->dwReserved2[i] = br->ReadInt32();
		}

		dwMipMaps = gcnew array<array<DDS_BLOCK^>^>(dwHeader->dwMipMapCount);
		colorMaps = gcnew array<array<Color>^>(dwHeader->dwMipMapCount);

		// load uncompressed data
		if(dwHeader->ddspf->fourCC == "\0\0\0\0")
		{
			for(int i=0; i<colorMaps->Length; i++)
			{
				if(i > 0)
				{
					colorMaps[i] = gcnew array<Color>(colorMaps[i-1]->Length/4);
				}
				else
				{
					colorMaps[i] = gcnew array<Color>(dwHeader->dwWidth*dwHeader->dwHeight);
				}

				for(int p=0; p<colorMaps[i]->Length; p++)
				{
					// 32 bit ARGB value
					if(dwHeader->ddspf->dwRGBBitCount == 32)
					{
						colorMaps[i][p] = Color::FromArgb(br->ReadInt32());
					}
					else
					{
						colorMaps[i][p] = Color();
					}
				}
			}
		}

		// load DXT1, DXT3 or DXT5 compressed data
		if(dwHeader->ddspf->fourCC->Contains("DXT"))
		{
			int w = dwHeader->dwWidth;
			int h = dwHeader->dwHeight;
			int block_count;
			for(int i=0; i<dwMipMaps->Length; i++)
			{
				block_count = w*h/16;
				dwMipMaps[i] = gcnew array<DDS_BLOCK^>(block_count);
				colorMaps[i] = gcnew array<Color>(w*h);
				for(int b=0; b<block_count; b++)
				{
					dwMipMaps[i][b] = gcnew DDS_BLOCK();
					// Initialize DXT3 dummy
					dwMipMaps[i][b]->alpha_values = gcnew array<unsigned char>(8);
					// Initialize DXT5 dummy
					dwMipMaps[i][b]->alpha_indices = gcnew BitArray(48);

					if(dwHeader->ddspf->fourCC == "DXT5")
					{
						dwMipMaps[i][b]->alpha_start = br->ReadByte();
						dwMipMaps[i][b]->alpha_end = br->ReadByte();
						dwMipMaps[i][b]->alpha_indices = gcnew BitArray(br->ReadBytes(6));
					}
					if(dwHeader->ddspf->fourCC == "DXT3")
					{
						dwMipMaps[i][b]->alpha_values = br->ReadBytes(8);
					}
					dwMipMaps[i][b]->color_start = br->ReadUInt16();
					dwMipMaps[i][b]->color_end = br->ReadUInt16();
					dwMipMaps[i][b]->color_indices = gcnew BitArray(br->ReadBytes(4));

					for(int c=0; c<16; c++)
					{
						colorMaps[i][b*16+c] = GetColorFromBlock(dwMipMaps[i][b], c);
					}
				}
				w = Math::Max(4, w/2);
				h = Math::Max(4, h/2);
			}
		}

		br->Close();
		fr->Close();
	}

	public: void save(String^ file)
	{
		FileStream^ fw = File::OpenWrite(file);
		BinaryWriter^ bw = gcnew BinaryWriter(fw);

		bw->Write(dwSignature);
		bw->Write(dwHeader->dwSize);
		bw->Write(dwHeader->dwHeaderFlags);
		bw->Write(dwHeader->dwHeight);
		bw->Write(dwHeader->dwWidth);
		bw->Write(dwHeader->dwPitchOrLinearSize);
		bw->Write(dwHeader->dwDepth);
		bw->Write(dwHeader->dwMipMapCount);
		for(int i=0; i<dwHeader->dwReserved1->Length; i++)
		{
			bw->Write(dwHeader->dwReserved1[i]);
		}
		bw->Write(dwHeader->ddspf->dwSize);
		bw->Write(dwHeader->ddspf->dwFlags);
		bw->Write(dwHeader->ddspf->dwFourCC);
		bw->Write(dwHeader->ddspf->dwRGBBitCount);
		bw->Write(dwHeader->ddspf->dwRBitMask);
		bw->Write(dwHeader->ddspf->dwGBitMask);
		bw->Write(dwHeader->ddspf->dwBBitMask);
		bw->Write(dwHeader->ddspf->dwABitMask);
		bw->Write(dwHeader->dwSurfaceFlags);
		bw->Write(dwHeader->dwCubemapFlags);
		for(int i=0; i<dwHeader->dwReserved2->Length; i++)
		{
			bw->Write(dwHeader->dwReserved2[i]);
		}

		// save uncompressed data
		if(dwHeader->ddspf->fourCC == "\0\0\0\0")
		{
			for(int i=0; i<colorMaps->Length; i++)
			{
				for(int p=0; p<colorMaps[i]->Length; p++)
				{
					// save as 32 bit value
					bw->Write(colorMaps[i][p].ToArgb());
				}
			}
		}

		// save DXT1, DXT3 or DXT5 compressed data
		if(dwHeader->ddspf->fourCC->Contains("DXT"))
		{
			int w = dwHeader->dwWidth;
			int h = dwHeader->dwHeight;
			array<unsigned char>^ abytes = gcnew array<unsigned char>(6);
			array<unsigned char>^ cbytes = gcnew array<unsigned char>(4);

			for(int i=0; i<dwMipMaps->Length; i++)
			{
				for(int b=0; b<dwMipMaps[i]->Length; b++)
				{
					bw->Write(dwMipMaps[i][b]->alpha_start);
					bw->Write(dwMipMaps[i][b]->alpha_end);
					dwMipMaps[i][b]->alpha_indices->CopyTo(abytes, 0);
					bw->Write(abytes);
					bw->Write(dwMipMaps[i][b]->color_start);
					bw->Write(dwMipMaps[i][b]->color_end);
					dwMipMaps[i][b]->color_indices->CopyTo(cbytes, 0);
					bw->Write(cbytes);
				}
			}
		}

		bw->Close();
		fw->Close();
	}
};