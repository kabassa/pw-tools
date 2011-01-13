#pragma once

namespace PW
{
	namespace Texture
	{
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
			public: void Load(String^ file)
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
	}
}