#pragma once

#include "gfxBlock.h"
#include "texture.h"

public ref class gfxBLOCK210 : gfxBLOCK
{
	public: gfxBLOCK210(void)
	{
	}
	protected: ~gfxBLOCK210()
	{
	}

	public: virtual bool Fix(Options^ options) override
	{
		if(options->gfxDowngrade)
		{
			if(!options->gfx210to160)
			{
				return false;
			}

			FixBasicParameters();
			FixControlTypes();

#pragma region File Preparations

			// some different gfx files are not unique and needs to be distinct
			// the whole path with underscores will be used as new directory
			String^ gfxFile = options->fileOut->Substring(options->fileOut->IndexOf("\\gfx\\")+5)->Replace("\\", "_");
			String^ modelPath = options->fileOut->Substring(0, options->fileOut->IndexOf("\\gfx\\")+5)  + "models\\210_FIX\\";

			IO::Directory::CreateDirectory(modelPath + "textures");

			// assumption: gfx names are unique -> a file will never exists twice
			String^ fileSMD = modelPath + gfxFile->Replace(".gfx", "_" + Name + ".smd");
			if(IO::File::Exists(fileSMD))
			{
				MessageBox::Show("File already exists:\n\n" + fileSMD);
			}
			String^ fileBON = modelPath + gfxFile->Replace(".gfx", "_" + Name + ".bon");
			if(IO::File::Exists(fileBON))
			{
				MessageBox::Show("File already exists:\n\n" + fileBON);
			}
			String^ fileSKI = modelPath + gfxFile->Replace(".gfx", "_" + Name + ".ski");
			if(IO::File::Exists(fileSKI))
			{
				MessageBox::Show("File already exists:\n\n" + fileSKI);
			}
			// create default texture name
			String^ fileTEX = modelPath + "textures\\" + gfxFile->Replace(".gfx", "_" + Name + ".dds");
			if(IO::File::Exists(fileTEX))
			{
				MessageBox::Show("File already exists:\n\n" + fileTEX);
			}

#pragma endregion

			String^ line;
			array<wchar_t>^ seperator = gcnew array<wchar_t>{' '};
			array<String^>^ values;
			bool tilemode;
			int tilerows;
			int tilecols;
			bool ureverse;
			bool vreverse;
			Texture^ texture;
			String^ fileTexIn;

			System::Text::Encoding^ enc = System::Text::Encoding::GetEncoding("GBK");
			IO::FileStream^ fs;
			IO::BinaryWriter^ bw;

			for(int i=0; i<Parameters->Count; i++)
			{
				line = (String^)Parameters[i];

				if(line->StartsWith("GFXELEMENTID: 210"))
				{
					Parameters[i] = line->Replace("210", "160");
					ElementID = 160;
				}
				if(line->StartsWith("TexFile:"))
				{
					// copy exisiting texture to our new model/texure path
					String^ fileTexName = line->Split(seperator)[1];
					fileTexIn = options->fileIn->Substring(0, options->fileIn->IndexOf("\\gfx\\")+5) + "textures\\" + fileTexName;
					Parameters[i] = "TexFile: ";
				}
				if(line->StartsWith("TileMode:"))
				{
					tilemode = Convert::ToBoolean(Convert::ToInt16(line->Split(seperator)[1]));
				}
				if(line->StartsWith("TexRow:"))
				{
					tilerows = Convert::ToInt32(Convert::ToInt16(line->Split(seperator)[1]));
				}
				if(line->StartsWith("TexCol:"))
				{
					tilecols = Convert::ToInt32(Convert::ToInt16(line->Split(seperator)[1]));
				}
				if(line->StartsWith("UReverse:"))
				{
					ureverse = Convert::ToBoolean(Convert::ToInt16(line->Split(seperator)[1]));
					Parameters[i] = "UReverse: 0";
				}
				if(line->StartsWith("VReverse:"))
				{
					vreverse = Convert::ToBoolean(Convert::ToInt16(line->Split(seperator)[1]));
					Parameters[i] = "VReverse: 0";
				}
				if(line->StartsWith("AffByScl:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("RotFromView:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("fOffsetHeight:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("wNumber:"))
				{
					try
					{
#pragma region Read Mesh
						int index;

						int wNumber = Convert::ToInt32(line->Split(seperator)[1]);
						line = (String^)Parameters[i+1];
						int hNumber = Convert::ToInt32(line->Split(seperator)[1]);

						double leftX, leftY, leftZ, rightX, rightY, rightZ, topX, topY, topZ, bottomX, bottomY, bottomZ;

						// we read the freeform parameters for the texture
						// into a 2 dimensional array for better imagination
						array<Vertex^, 2>^ points = gcnew array<Vertex^, 2>(hNumber, wNumber);

						// read the vertices and color
						for(int v=0; v<hNumber; v++)
						{
							for(int u=0; u<wNumber; u++)
							{
								line = (String^)Parameters[i+2 + 2*(v*wNumber+u)];
								line->Replace(",", "");
								values = line->Split(seperator);
								points[v, u] = gcnew Vertex();
								points[v, u]->X = Convert::ToDouble(values[0]);
								points[v, u]->Y = Convert::ToDouble(values[1]);
								points[v, u]->Z = Convert::ToDouble(values[2]);
								points[v, u]->U = Convert::ToDouble(u)/Convert::ToDouble(wNumber-1);
								points[v, u]->V = Convert::ToDouble(v)/Convert::ToDouble(hNumber-1);
								line = (String^)Parameters[i+3 + 2*(v*wNumber+u)];
								values = line->Split(seperator);
								while(values[1]->Length < 8)
								{
									values[1] = "0" + values[1];
								}
								points[v, u]->Color = System::Drawing::ColorTranslator::FromHtml("#" + values[1]);
							}
						}

						// calculate vertex normals depending on neighbour vertices
						// assumption: frontface / backface normals can be derived from the vertex ordering
						// this might be wrong as gfx210 don't use faces !!!
						for(int v=0; v<hNumber; v++)
						{
							for(int u=0; u<wNumber; u++)
							{
								// find the points to create vectors

								// left point coordinates
								if(u > 0)
								{
									leftX = points[v, u-1]->X;
									leftY = points[v, u-1]->Y;
									leftZ = points[v, u-1]->Z;
								}
								else
								{
									leftX = points[v, u]->X;
									leftY = points[v, u]->Y;
									leftZ = points[v, u]->Z;
								}
								// right point coordinates
								if(u < wNumber-1)
								{
									rightX = points[v, u+1]->X;
									rightY = points[v, u+1]->Y;
									rightZ = points[v, u+1]->Z;
								}
								else
								{
									rightX = points[v, u]->X;
									rightY = points[v, u]->Y;
									rightZ = points[v, u]->Z;
								}
								// top point coordinates
								if(v > 0)
								{
									topX = points[v-1, u]->X;
									topY = points[v-1, u]->Y;
									topZ = points[v-1, u]->Z;
								}
								else
								{
									topX = points[v, u]->X;
									topY = points[v, u]->Y;
									topZ = points[v, u]->Z;
								}
								// top point coordinates
								if(v < hNumber-1)
								{
									bottomX = points[v+1, u]->X;
									bottomY = points[v+1, u]->Y;
									bottomZ = points[v+1, u]->Z;
								}
								else
								{
									bottomX = points[v, u]->X;
									bottomY = points[v, u]->Y;
									bottomZ = points[v, u]->Z;
								}
								// calculate as cross product
								points[v, u]->NX = ((rightY-leftY)*(bottomZ-topZ)) - ((rightX-leftX)*(bottomY-topY));
								points[v, u]->NY = ((rightZ-leftZ)*(bottomX-topX)) - ((rightY-leftY)*(bottomZ-topZ));
								points[v, u]->NZ = ((rightX-leftX)*(bottomY-topY)) - ((rightZ-leftZ)*(bottomX-topX));
							}
						}

						// create frontfaces and backfaces (to disable culling)
						// number of quads: (hNumber-1) * (wNumber-1)
						// number of triangles: 2 * number_quads
						// number of front and bachface triangles: 2 * number_triangles

						// clockwise winding
						array<array<unsigned short>^>^ frontfaces = gcnew array<array<unsigned short>^>((hNumber-1)*(wNumber-1)*2);
						// counter-clockwise winding
						array<array<unsigned short>^>^ backfaces = gcnew array<array<unsigned short>^>((hNumber-1)*(wNumber-1)*2);
						for(int v=0; v<hNumber-1; v++)
						{
							for(int u=0; u<wNumber-1; u++)
							{
								// assumption: frontfaces / backfaces can be derived from the vertex ordering
								// this might be wrong as gfx210 don't use face based rendering !!!
								index = 2*(v*(wNumber-1)+u);

								// add two triangles for the current quad
								// clockwise winding
								frontfaces[index] = gcnew array<unsigned short>(3);
								frontfaces[index][0] = v*wNumber+u;
								frontfaces[index][1] = v*wNumber+u+1;
								frontfaces[index][2] = (v+1)*wNumber+u;
								frontfaces[index+1] = gcnew array<unsigned short>(3);
								frontfaces[index+1][0] = (v+1)*wNumber+u+1;
								frontfaces[index+1][1] = frontfaces[index][2];
								frontfaces[index+1][2] = frontfaces[index][1];

								// backfaces are just reversed rotated frontfaces
								// add two triangles for the current quad
								// counter clockwise winding
								backfaces[index] = gcnew array<unsigned short>(3);
								backfaces[index][0] = frontfaces[index][2];
								backfaces[index][1] = frontfaces[index][1];
								backfaces[index][2] = frontfaces[index][0];
								backfaces[index+1] = gcnew array<unsigned short>(3);
								backfaces[index+1][0] = frontfaces[index+1][2];
								backfaces[index+1][1] = frontfaces[index+1][1];
								backfaces[index+1][2] = frontfaces[index+1][0];
							}
						}
#pragma endregion
						// create tex, smd, bon and ski file in output model directory

						array<unsigned char>^ temp;

#pragma region Save TEX
						if(IO::File::Exists(fileTexIn))
						{
							texture = gcnew Texture(fileTexIn, ureverse, vreverse, tilemode, tilecols, tilerows);
						}
						else
						{
							// create a unique dummy texture for this gfx210 block, which is used for mesh color rendering
							texture = gcnew Texture();
							texture->Width = 128;
							texture->Height = 128;
							texture->Bytes = gcnew array<unsigned char>(4*texture->Width*texture->Height);
							for(int p=0; p<texture->Bytes->Length; p++)
							{
								texture->Bytes[p] = 255;
							}
						}

						// create color mesh texture
						Texture^ tint = gcnew Texture();
						tint->Width = texture->Width;
						tint->Height = texture->Height;
						tint->Bytes = gcnew array<unsigned char>(4*tint->Width*tint->Height);

						int left;
						int w;
						int top;
						int h;

						double a1;
						double a2;
						double a3;
						double a4;
						double divider;
						
						for(int v=0; v<hNumber-1; v++)
						{
							for(int u=0; u<wNumber-1; u++)
							{
								left = u*tint->Width / (wNumber-1);
								w = (u+1)*tint->Width / (wNumber-1) - left;
								top = v*tint->Height / (hNumber-1);
								h = (v+1)*tint->Height / (hNumber-1) - top;
								divider = Convert::ToDouble(w*h);

								for(int y=0; y<h; y++)
								{
									for(int x=0; x<w; x++)
									{
										int index = 4*((top+y)*tint->Width + (left+x));
										// weighted distances, weights based on area (x*y)
										a1 = (Convert::ToDouble((w-1-x)*w)/Convert::ToDouble(w-1)) * (Convert::ToDouble((h-1-y)*h)/Convert::ToDouble(h-1));
										a2 = (Convert::ToDouble((x)*w)/Convert::ToDouble(w-1)) * (Convert::ToDouble((h-1-y)*h)/Convert::ToDouble(h-1));
										a3 = (Convert::ToDouble((w-1-x)*w)/Convert::ToDouble(w-1)) * (Convert::ToDouble((y)*h)/Convert::ToDouble(h-1));
										a4 = (Convert::ToDouble((x)*w)/Convert::ToDouble(w-1)) * (Convert::ToDouble((y)*h)/Convert::ToDouble(h-1));
										tint->Bytes[index+3] = Convert::ToByte( (a1*points[v, u]->Color.A + a2*points[v, u+1]->Color.A + a3*points[v+1, u]->Color.A + a4*points[v+1, u+1]->Color.A) / divider );
										tint->Bytes[index+2] = Convert::ToByte( (a1*points[v, u]->Color.R + a2*points[v, u+1]->Color.R + a3*points[v+1, u]->Color.R + a4*points[v+1, u+1]->Color.R) / divider );
										tint->Bytes[index+1] = Convert::ToByte( (a1*points[v, u]->Color.G + a2*points[v, u+1]->Color.G + a3*points[v+1, u]->Color.G + a4*points[v+1, u+1]->Color.G) / divider );
										tint->Bytes[index+0] = Convert::ToByte( (a1*points[v, u]->Color.B + a2*points[v, u+1]->Color.B + a3*points[v+1, u]->Color.B + a4*points[v+1, u+1]->Color.B) / divider );
									}
								}
							}
						}

						// multiply texture with color mesh
						if(tint->Bytes->Length == texture->Bytes->Length)
						{
							for(int p=0; p<tint->Bytes->Length; p++)
							{
								tint->Bytes[p] = (tint->Bytes[p]*texture->Bytes[p])/255;
							}
						}

						// save the final texture
						tint->Save(fileTEX);
#pragma endregion

#pragma region Save SMD
						fs = gcnew IO::FileStream(fileSMD, IO::FileMode::Create, IO::FileAccess::Write);
						bw = gcnew IO::BinaryWriter(fs);
						bw->Write(gcnew array<unsigned char>{77,79,88,66,68,77,83,65,6,0,0,0,1,0,0,0});
						bw->Write(gcnew array<unsigned char>(72)); // write 72 zeros
						temp = enc->GetBytes(fileBON->Substring(fileBON->LastIndexOf("\\")+1));
						bw->Write(temp->Length);
						bw->Write(temp);
						temp = enc->GetBytes(fileSKI->Substring(fileSKI->LastIndexOf("\\")+1));
						bw->Write(temp->Length);
						bw->Write(temp);
						bw->Write((int)0);
						bw->Close();
						fs->Close();
#pragma endregion

#pragma region Save BON
						fs = gcnew IO::FileStream(fileBON, IO::FileMode::Create, IO::FileAccess::Write);
						bw = gcnew IO::BinaryWriter(fs);
						bw->Write(gcnew array<unsigned char>{77,79,88,66,69,75,83,65,5,0,0,0,1,0,0,0});
						temp = gcnew array<unsigned char>(236); // create 236 zeros
						temp[12] = 100;
						temp[16] = 30;
						temp[88] = 1;
						temp[92] = 255;
						temp[93] = 255;
						temp[94] = 255;
						temp[95] = 255;
						temp[106] = 128;
						temp[107] = 63;
						temp[126] = 128;
						temp[127] = 63;
						temp[146] = 128;
						temp[147] = 63;
						temp[166] = 128;
						temp[167] = 63;
						temp[170] = 128;
						temp[171] = 63;
						temp[190] = 128;
						temp[191] = 63;
						temp[210] = 128;
						temp[211] = 63;
						temp[230] = 128;
						temp[231] = 63;
						temp[232] = 15;
						bw->Write(temp);
						bw->Close();
						fs->Close();
#pragma endregion

#pragma region Save SKI
						fs = gcnew IO::FileStream(fileSKI, IO::FileMode::Create, IO::FileAccess::Write);
						bw = gcnew IO::BinaryWriter(fs);
						bw->Write(gcnew array<unsigned char>{77,79,88,66,73,75,83,65,8,0,0,0});
						temp = gcnew array<unsigned char>(96); // create 96 zeros
						temp[4] = 1;
						temp[16] = 1;
						temp[20] = 1;
						bw->Write(temp);
						temp = enc->GetBytes(fileTEX->Substring(fileTEX->LastIndexOf("\\")+1));
						bw->Write(temp->Length);
						bw->Write(temp);
						bw->Write(gcnew array<unsigned char>{77, 65, 84, 69, 82, 73, 65, 76, 58, 32, 0, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 63, 0, 0, 128, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
						bw->Write(points->Length);
						bw->Write(3*(frontfaces->Length + backfaces->Length));
						for(int v=0; v<hNumber; v++)
						{
							for(int u=0; u<wNumber; u++)
							{
								bw->Write(Convert::ToSingle(points[v, u]->X));
								bw->Write(Convert::ToSingle(points[v, u]->Y));
								bw->Write(Convert::ToSingle(points[v, u]->Z));
								bw->Write(Convert::ToSingle(points[v, u]->NX));
								bw->Write(Convert::ToSingle(points[v, u]->NY));
								bw->Write(Convert::ToSingle(points[v, u]->NZ));
								if(tilemode)
								{
									bw->Write(Convert::ToSingle(points[v, u]->U));
									bw->Write(Convert::ToSingle(points[v, u]->V));
								}
								else
								{
									// instead of a (tile) texture video we set the first tile as texture
									bw->Write(Convert::ToSingle(points[v, u]->U / Convert::ToDouble(tilecols)));
									bw->Write(Convert::ToSingle(points[v, u]->V / Convert::ToDouble(tilerows)));
								}
							}
						}
						for(int f=0; f<frontfaces->Length; f++)
						{
							bw->Write(frontfaces[f][0]);
							bw->Write(frontfaces[f][1]);
							bw->Write(frontfaces[f][2]);
						}
						for(int f=0; f<backfaces->Length; f++)
						{
							bw->Write(backfaces[f][0]);
							bw->Write(backfaces[f][1]);
							bw->Write(backfaces[f][2]);
						}

						fs->Close();
						bw->Close();
#pragma endregion

#pragma region Fix GFX Parameters
						// remove the lines
						for(int r=0; r<2+(2*wNumber*hNumber)+2; r++)
						{
							Parameters->RemoveAt(i);
						}
						// insert default gfx160 lines
						Parameters->Insert(i, "ModelPath: " + fileSMD->Substring(fileSMD->IndexOf("210_FIX")));
						Parameters->Insert(i+1, "ModelActName: ");
						Parameters->Insert(i+2, "Loops: -1");
						Parameters->Insert(i+3, "AlphaCmp: 0");
						Parameters->Insert(i+4, "WriteZ: 0");
#pragma endregion
					}
					catch(Exception^ e)
					{
						// error creating mesh, maybe -1.#QNAN0 was found in the gfx
						MessageBox::Show("210 Fix Error:\n" + e->Message + "\n\n" + options->fileIn);
						return false;
					}
				}
			}
		}
		return true;
	}
};