#pragma once

#include "nvTT\include\nvtt.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

public ref struct Vertex
{
	double X;
	double Y;
	double Z;
	double NX;
	double NY;
	double NZ;
	double U;
	double V;
	Drawing::Color Color;
};

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
};

public ref class TGA
{
	public: TGA(void)
	{
	}

	protected: ~TGA()
	{
	}

	public: unsigned char IdFieldLength;
	public: unsigned char ColorMapType;
	public: unsigned char DataTypeCode;
	public: unsigned short ColorMapOrigin;
	public: unsigned short ColorMapLength;
	public: unsigned char ColorMapDepth;
	public: unsigned short OriginX;
	public: unsigned short OriginY;
	public: unsigned short Width;
	public: unsigned short Height;
	public: unsigned char BitsPerPixel;
	public: unsigned char ImageDescriptor;
	private: unsigned char BytesPerPixel;
	private: array<unsigned char>^ ImageData;

	public: Color GetColor(int x, int y)
	{
		if(OriginX > 0)
		{
			x = Width-1-x;
		}
		if(OriginY == 0)
		{
			y = Height-1-y;
		}

		int index = BytesPerPixel*(y*Width + x);

		if(BitsPerPixel == 24)
		{
			return Color::FromArgb(ImageData[index+2], ImageData[index+1], ImageData[index+0]);
		}
		if(BitsPerPixel == 32)
		{
			return Color::FromArgb(ImageData[index+3], ImageData[index+2], ImageData[index+1], ImageData[index+0]);
		}
		return Color::Transparent;
	}
	public: void load(String^ file)
	{
		FileStream^ fr = File::OpenRead(file);
		BinaryReader^ br = gcnew BinaryReader(fr);

		// read header
		IdFieldLength = br->ReadByte();
		ColorMapType = br->ReadByte();
		DataTypeCode = br->ReadByte();
		ColorMapOrigin = br->ReadUInt16();
		ColorMapLength = br->ReadUInt16();
		ColorMapDepth = br->ReadByte();
		OriginX = br->ReadUInt16();
		OriginY = br->ReadUInt16();
		Width = br->ReadUInt16();
		Height = br->ReadUInt16();
		BitsPerPixel = br->ReadByte();
		BytesPerPixel = BitsPerPixel/8;
		ImageDescriptor = br->ReadByte();

		// read image identification field
		br->ReadBytes(IdFieldLength);

		// read map data
		if(ColorMapType > 0)
		{
			MessageBox::Show("Unsupported TGA Format");
		}

		// uncompressed RGB
		if(DataTypeCode == 2)
		{
			ImageData = br->ReadBytes(Width*Height*BytesPerPixel);
		}

		// run length encoded RGB
		if(DataTypeCode == 10)
		{
			ImageData = gcnew array<unsigned char>(Width*Height*BytesPerPixel);
			int index = 0;
			unsigned char head;
			array<unsigned char>^ temp;

			while(index<ImageData->Length)
			{
				head = br->ReadByte();
				if(head < 128)
				{
					temp = br->ReadBytes(BytesPerPixel*(head+1));
					Array::Copy(temp, 0, ImageData, index, temp->Length);
					index += temp->Length;
				}
				else
				{
					temp = br->ReadBytes(BytesPerPixel);
					for(int n=0; n<head-127; n++)
					{
						Array::Copy(temp, 0, ImageData, index, temp->Length);
						index += temp->Length;
					}
				}
			}
		}

		br->Close();
		fr->Close();
	}
};

public ref class Texture
{
	public: Texture()
	{
	}

	public: Texture(String^ file, bool UReverse, bool VReverse, bool TileMode, int TileColumns, int TileRows)
	{
		if(file->EndsWith(".bmp") || file->EndsWith(".png") || file->EndsWith(".jpg"))
		{
			loadBitmap(file, UReverse, VReverse);
		}
		if(file->EndsWith(".dds"))
		{
			loadDDraw(file, UReverse, VReverse);
		}
		if(file->EndsWith(".tga"))
		{
			loadTarga(file, UReverse, VReverse);
		}

		if(TileMode && (TileColumns>1 || TileRows>1))
		{
			// Tile Texture
			int w = Width*TileColumns;
			int h = Height*TileRows;

			array<unsigned char>^ temp = Bytes;
			Bytes = gcnew array<unsigned char>(Bytes->Length*TileColumns*TileRows);

			for(int y=0; y<h; y++)
			{
				for(int c=0; c<TileColumns; c++)
				{
					Array::Copy(temp, 4*((y%Height)*Width), Bytes, 4*((y*w)+(c*Width)), 4*Width);
				}
			}
			Width = w;
			Height = h;
		}
	}

	protected: ~Texture()
	{
	}

	public: int Width;
	public: int Height;
	public: array<unsigned char>^ Bytes;

	private: void loadBitmap(String^ fileIn, bool UReverse, bool VReverse)
	{
		Bitmap^ temp = gcnew Bitmap(fileIn);

		Width = temp->Width;
		Height = temp->Height;
		Bytes = gcnew array<unsigned char>(4*Width*Height);

		// convert any pixelformat to 32bit
		Bitmap^ img = gcnew Bitmap(Width, Height, Imaging::PixelFormat::Format32bppArgb);
		if(UReverse)
		{
			img->RotateFlip(RotateFlipType::RotateNoneFlipX);
		}
		if(VReverse)
		{
			img->RotateFlip(RotateFlipType::RotateNoneFlipY);
		}
		Graphics::FromImage(img)->DrawImage(temp, 0, 0);
		Drawing::Imaging::BitmapData^ imgData = img->LockBits(Rectangle(0, 0, img->Width, img->Height), Drawing::Imaging::ImageLockMode::ReadOnly, img->PixelFormat);
		int bytes = Math::Abs(imgData->Stride)*img->Height;

		Runtime::InteropServices::Marshal::Copy(imgData->Scan0, Bytes, 0, bytes);
		img->UnlockBits(imgData);
	}

	// supported formats: uncompressed/compressed RGB (2 & 10 | 24bpp & 32bpp)
	private: void loadTarga(String^ fileIn, bool UReverse, bool VReverse)
	{
		int index;
		Color^ c;
		TGA^ surface = gcnew TGA();
		surface->load(fileIn);

		Width = surface->Width;
		Height = surface->Height;
		Bytes = gcnew array<unsigned char>(4*Width*Height);
		for(int y=0; y<Height; y++)
		{
			for(int x=0; x<Width; x++)
			{
				index = 4*(y*Width+x);
				if(!UReverse && !VReverse)
				{
					c = surface->GetColor(x, y);
				}
				if(UReverse && !VReverse)
				{
					c = surface->GetColor(Width-1-x, y);
				}
				if(!UReverse && VReverse)
				{
					c = surface->GetColor(x, Height-1-y);
				}
				if(UReverse && VReverse)
				{
					c = surface->GetColor(Width-1-x, Height-1-y);
				}
				Bytes[index+3] = c->A;
				Bytes[index+2] = c->R;
				Bytes[index+1] = c->G;
				Bytes[index+0] = c->B;
			}
		}
	}

	// supported formats: Uncompressed, DXT1, DXT3 & DXT5
	private: void loadDDraw(String^ fileIn, bool UReverse, bool VReverse)
	{
		int index;
		Color^ c;
		DDS^ surface = gcnew DDS();
		surface->load(fileIn);
		Width = surface->dwHeader->dwWidth;
		Height = surface->dwHeader->dwHeight;
		Bytes = gcnew array<unsigned char>(4*Width*Height);
		for(int y=0; y<Height; y++)
		{
			for(int x=0; x<Width; x++)
			{
				index = 4*(y*Width+x);
				if(!UReverse && !VReverse)
				{
					c = surface->GetColor(0, x, y);
				}
				if(UReverse && !VReverse)
				{
					c = surface->GetColor(0, Width-1-x, y);
				}
				if(!UReverse && VReverse)
				{
					c = surface->GetColor(0, x, Height-1-y);
				}
				if(UReverse && VReverse)
				{
					c = surface->GetColor(0, Width-1-x, Height-1-y);
				}
				Bytes[index+3] = c->A;
				Bytes[index+2] = c->R;
				Bytes[index+1] = c->G;
				Bytes[index+0] = c->B;
			}
		}
	}
	public: void Save(String^ fileOut)
	{
		if(fileOut->EndsWith(".png"))
		{
			savePNG(fileOut);
		}
		if(fileOut->EndsWith(".dds"))
		{
			saveDDS(fileOut);
		}
	}
	// save texture as PNG
	private: void savePNG(String^ fileOut)
	{
		Bitmap^ img = gcnew Bitmap(Width, Height, Drawing::Imaging::PixelFormat::Format32bppArgb);
		Drawing::Imaging::BitmapData^ imgData = img->LockBits(Rectangle(0, 0, img->Width, img->Height), Drawing::Imaging::ImageLockMode::WriteOnly, img->PixelFormat);
		int byteCount = Math::Abs(imgData->Stride)*img->Height;

		if(byteCount == Bytes->Length)
		{
			Runtime::InteropServices::Marshal::Copy(Bytes, 0, imgData->Scan0, Bytes->Length);
		}

		img->UnlockBits(imgData);
		img->Save(fileOut, Drawing::Imaging::ImageFormat::Png);

	}
	// save texture as DDS (DXT5)
	private: void saveDDS(String^ fileOut)
	{
		// unicode file names are not supported, so we have to create a temp file
		String^ fileTemp = "_temp.dds"; //fileOut->Substring(0, fileOut->LastIndexOf("\\")+1) + "_temp.dds";

		nvtt::InputOptions optIn;
		optIn.setTextureLayout(nvtt::TextureType_2D, Width, Height);
		unsigned char* b = new unsigned char[Bytes->Length];
		for(int i=0; i<Bytes->Length; i++)
		{
			b[i] = Bytes[i];
		}
		optIn.setMipmapData(b, Width, Height);
		delete[] b;
		optIn.setMipmapGeneration(true, -1);
		optIn.setMipmapFilter(nvtt::MipmapFilter_Box);

		nvtt::CompressionOptions optComp;
		optComp.setFormat(nvtt::Format_BC3); // DXT5
		optComp.setQuality(nvtt::Quality_Normal);

		nvtt::OutputOptions optOut;
		char* pFile = (char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileTemp).ToPointer();
		optOut.setFileName(pFile);
		Runtime::InteropServices::Marshal::FreeHGlobal(IntPtr(pFile));

		nvtt::Compressor compressor;
		compressor.process(optIn, optComp, optOut);

		File::Move(fileTemp, fileOut);
	}
};