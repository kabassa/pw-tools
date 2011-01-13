#pragma once

#include "dds.h"
#include "tga.h"
#include "..\nvtt\nvtt.h"

namespace PW
{
	namespace Texture
	{
		public ref class Texture
		{
			public: Texture()
			{
			}

			protected: ~Texture()
			{
			}

			public: int Width;
			public: int Height;
			public: array<unsigned char>^ Bytes;

			public: void Load(String^ File)
			{
				Load(File, false, false, false, 1, 1);
			}

			public: void Load(String^ File, bool UReverse, bool VReverse, bool TileMode, int TileColumns, int TileRows)
			{
				if(File->EndsWith(".bmp") || File->EndsWith(".png") || File->EndsWith(".jpg"))
				{
					loadBitmap(File, UReverse, VReverse);
				}
				if(File->EndsWith(".dds"))
				{
					loadDDraw(File, UReverse, VReverse);
				}
				if(File->EndsWith(".tga"))
				{
					loadTarga(File, UReverse, VReverse);
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
				TGA^ surface  = gcnew TGA();
				surface->Load(fileIn);

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
				surface->Load(fileIn);
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
	}
}