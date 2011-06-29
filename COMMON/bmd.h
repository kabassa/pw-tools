#pragma once

public ref struct Header
{
	unsigned char Type;
	array<unsigned char>^ Zeros;
	unsigned char BitOptions;
};

public ref struct Face
{
	unsigned short Vertex_1;
	unsigned short Vertex_2;
	unsigned short Vertex_3;
};

public ref struct Vert
{
	float X;
	float Y;
	float Z;
	array<unsigned char>^ unknown; // 4 Bytes
	float U;
	float V;
};

public ref struct Block_1
{
	float A;
	float B;
	float C;
};

public ref struct Block_2
{
	array<unsigned char>^ A; // 4 Bytes
	array<unsigned char>^ B; // 4 Bytes
};

public ref struct Material
{
	array<unsigned char>^ Signature; // 10 Bytes
	unsigned char Count; // ??? Length for Name ???
	// array<unsigned char>^ Name;
	array<float>^ Values;
	unsigned char Unknown;
};

public ref struct Obj
{
	Header^ Ident;
	array<unsigned char>^ Name; // 64 Bytes
	array<unsigned char>^ Texture; // 56 Bytes
	unsigned char Unknown;
	array<Vert^>^ Vertices;
	array<Face^>^ Faces;
	array<Block_1^>^ Block_1s;
	array<Block_2^>^ Block_2s;
	array<float>^ Properties; // 12 float values
	Material^ Materials;
};

public ref struct Number
{
	array<int>^ Values;
};

public ref struct SubBlock
{
	float A;
	float B;
	float C;
	float D;
	bool E;
};

public ref struct Block
{
	array<float>^ Properties; // 12 float values
	array<unsigned char>^ Seperator; // 4 Bytes
	array<SubBlock^>^ SubBlocks;
};

public ref class BMD
{
	public: BMD()
	{
	}

	protected: ~BMD()
	{
	}

	public: array<unsigned char>^ Signature; // 4 byte
	public: Header^ Ident; // 4 byte
	public: unsigned char IdentSplit;
	public: Header^ IdentExtension; // 4 byte
	public: array<float>^ Unknown; // 12 floats
	public: array<Obj^>^ Objects;
	public: array<Number^>^ Numbers;
	public: array<Block^>^ Blocks;

	public: void Load(String^ File)
	{
		FileStream^ fs =File::OpenRead(File);
		BinaryReader^ br = gcnew BinaryReader(fs);

		Signature = br->ReadBytes(4);
		/*
		// 4 Byte HEADER Explained:
		// in CN 1.3.6 ver[0] = 1 || 2
		// in PWI 1.4.4 ver[0] = 1 || 2
		// in CN 1.3.6 ver[1] = 0
		// in PWI 1.4.4 ver[1] = 0
		// in CN 1.3.6 ver[2] = 0
		// in PWI 1.4.4 ver[2] = 0
		// in CN 1.3.6 ver[3] = 16 || 128 (seems to depend on ver[0])
		// in PWI 1.4.4 ver[3] = 16 || 128 (seems to depend on ver[0])
		// possible combinations for all versions: [1,0,0,128] || [2,0,0,16]
		*/
		Ident = gcnew Header();
		Ident->Type = br->ReadByte();
		Ident->Zeros = br->ReadBytes(2);
		Ident->BitOptions = br->ReadByte();

		if(Ident->Type == 1)
		{
			IdentSplit = br->ReadByte();
			IdentExtension = gcnew Header();
			IdentExtension->Type = br->ReadByte();
			IdentExtension->Zeros = br->ReadBytes(2);
			IdentExtension->BitOptions = br->ReadByte();
		}

		Unknown = gcnew array<float>(12);
		for(int i=0; i<Unknown->Length; i++)
		{
			Unknown[i] = br->ReadSingle();
		}

		int ObjectCount = br->ReadInt32();
		Objects = gcnew array<Obj^>(ObjectCount);
		for(int i=0; i<Objects->Length; i++)
		{
			Objects[i] = gcnew Obj();
			Objects[i]->Ident = gcnew Header();
			Objects[i]->Ident->Type = br->ReadByte();
			Objects[i]->Ident->Zeros = br->ReadBytes(2);
			Objects[i]->Ident->BitOptions = br->ReadByte();
			Objects[i]->Name = br->ReadBytes(64);
			Objects[i]->Texture = br->ReadBytes(256);

			int VertexCount = br->ReadInt32();
			int FacesCount = br->ReadInt32();

			if(Objects[i]->Ident->Type > 5)
			{
				Objects[i]->Unknown = br->ReadByte();
			}

			Objects[i]->Vertices = gcnew array<Vert^>(VertexCount);
			for(int v=0; v<Objects[i]->Vertices->Length; v++)
			{
				Objects[i]->Vertices[v] = gcnew Vert();
				Objects[i]->Vertices[v]->X = br->ReadSingle();
				Objects[i]->Vertices[v]->Y = br->ReadSingle();
				Objects[i]->Vertices[v]->Z = br->ReadSingle();
				Objects[i]->Vertices[v]->unknown = br->ReadBytes(4);
				Objects[i]->Vertices[v]->U = br->ReadSingle();
				Objects[i]->Vertices[v]->V = br->ReadSingle();
			}

			Objects[i]->Faces = gcnew array<Face^>(FacesCount);
			for(int f=0; f<Objects[i]->Faces->Length; f++)
			{
				Objects[i]->Faces[f] = gcnew Face();
				Objects[i]->Faces[f]->Vertex_1 = br->ReadUInt16();
				Objects[i]->Faces[f]->Vertex_2 = br->ReadUInt16();
				Objects[i]->Faces[f]->Vertex_3 = br->ReadUInt16();
			}

			Objects[i]->Block_1s = gcnew array<Block_1^>(VertexCount);
			for(int b1=0; b1<Objects[i]->Block_1s->Length; b1++)
			{
				Objects[i]->Block_1s[b1] = gcnew Block_1();
				Objects[i]->Block_1s[b1]->A = br->ReadSingle();
				Objects[i]->Block_1s[b1]->B = br->ReadSingle();
				Objects[i]->Block_1s[b1]->C = br->ReadSingle();
			}

			Objects[i]->Block_2s = gcnew array<Block_2^>(VertexCount);
			for(int b2=0; b2<Objects[i]->Block_2s->Length; b2++)
			{
				Objects[i]->Block_2s[b2] = gcnew Block_2();
				Objects[i]->Block_2s[b2]->A = br->ReadBytes(4);
				Objects[i]->Block_2s[b2]->B = br->ReadBytes(4);
			}

			Objects[i]->Properties = gcnew array<float>(12);
			for(int p=0; p<Objects[i]->Properties->Length; p++)
			{
				Objects[i]->Properties[p] = br->ReadSingle();
			}

			if(Objects[i]->Ident->Type > 4)
			{
				// Load Material
				Objects[i]->Materials = gcnew Material();
				Objects[i]->Materials->Signature = br->ReadBytes(10);
				Objects[i]->Materials->Count = br->ReadByte();
				Objects[i]->Materials->Values = gcnew array<float>(17);
				for(int m=0; m<Objects[i]->Materials->Values->Length; m++)
				{
					Objects[i]->Materials->Values[m] = br->ReadSingle();
				}
				Objects[i]->Materials->Unknown = br->ReadByte();
			}
		}

		int BlockCount = br->ReadInt32();

		Numbers = gcnew array<Number^>(BlockCount);
		for(int i=0; i<Numbers->Length; i++)
		{
			Numbers[i] = gcnew Number();
			Numbers[i]->Values = gcnew array<int>(br->ReadInt32());
			for(int n=0; n<Numbers[i]->Values->Length; n++)
			{
				Numbers[i]->Values[n] = br->ReadInt32();
			}
		}

		Blocks = gcnew array<Block^>(BlockCount);
		for(int i=0; i<Blocks->Length; i++)
		{
			Blocks[i] = gcnew Block();
			Blocks[i]->Properties = gcnew array<float>(12);
			for(int p=0; p<Blocks[i]->Properties->Length; p++)
			{
				Blocks[i]->Properties[p] = br->ReadSingle();
			}
			Blocks[i]->Seperator = br->ReadBytes(4);
			Blocks[i]->SubBlocks = gcnew array<SubBlock^>(br->ReadInt32());
			for(int b=0; b<Blocks[i]->SubBlocks->Length; b++)
			{
				Blocks[i]->SubBlocks[b] = gcnew SubBlock();
				Blocks[i]->SubBlocks[b]->A = br->ReadSingle();
				Blocks[i]->SubBlocks[b]->B = br->ReadSingle();
				Blocks[i]->SubBlocks[b]->C = br->ReadSingle();
				Blocks[i]->SubBlocks[b]->D = br->ReadSingle();
				Blocks[i]->SubBlocks[b]->E = br->ReadBoolean();
			}
		}

		br->Close();
		fs->Close();
	}

	public: void Fix(Options^ options)
	{
		// sweep through all objects and change ident->type of object to 5 (if > 5)
		// save(file) will automatically remove unsupported parameters depending on version
		for(int i=0; i<Objects->Length; i++)
		{
			if(Objects[i]->Ident->Type > 5)
			{
				Objects[i]->Ident->Type = 5;
				//Objects[i]->Ident->Unknown = 0;
			}
		}
	}

	public: void Save(String^ File)
	{
		FileStream^ fs = gcnew FileStream(File, FileMode::Create, FileAccess::Write);
		BinaryWriter^ bw = gcnew BinaryWriter(fs);

		bw->Write(Signature);
		bw->Write(Ident->Type);
		bw->Write(Ident->Zeros);
		bw->Write(Ident->BitOptions);

		if(Ident->Type == 1)
		{
			bw->Write(IdentSplit);
			bw->Write(IdentExtension->Type);
			bw->Write(IdentExtension->Zeros);
			bw->Write(IdentExtension->BitOptions);
		}

		for(int i=0; i<Unknown->Length; i++)
		{
			bw->Write(Unknown[i]);
		}

		bw->Write(Objects->Length);

		for(int i=0; i<Objects->Length; i++)
		{
			bw->Write(Objects[i]->Ident->Type);
			bw->Write(Objects[i]->Ident->Zeros);
			bw->Write(Objects[i]->Ident->BitOptions);
			bw->Write(Objects[i]->Name);
			bw->Write(Objects[i]->Texture);

			bw->Write(Objects[i]->Vertices->Length);
			bw->Write(Objects[i]->Faces->Length);

			if(Objects[i]->Ident->Type > 5)
			{
				bw->Write(Objects[i]->Unknown);
			}

			for(int v=0; v<Objects[i]->Vertices->Length; v++)
			{
				bw->Write(Objects[i]->Vertices[v]->X);
				bw->Write(Objects[i]->Vertices[v]->Y);
				bw->Write(Objects[i]->Vertices[v]->Z);
				bw->Write(Objects[i]->Vertices[v]->unknown);
				bw->Write(Objects[i]->Vertices[v]->U);
				bw->Write(Objects[i]->Vertices[v]->V);
			}

			for(int f=0; f<Objects[i]->Faces->Length; f++)
			{
				bw->Write(Objects[i]->Faces[f]->Vertex_1);
				bw->Write(Objects[i]->Faces[f]->Vertex_2);
				bw->Write(Objects[i]->Faces[f]->Vertex_3);
			}

			for(int b1=0; b1<Objects[i]->Block_1s->Length; b1++)
			{
				bw->Write(Objects[i]->Block_1s[b1]->A);
				bw->Write(Objects[i]->Block_1s[b1]->B);
				bw->Write(Objects[i]->Block_1s[b1]->C);
			}

			for(int b2=0; b2<Objects[i]->Block_2s->Length; b2++)
			{
				bw->Write(Objects[i]->Block_2s[b2]->A);
				bw->Write(Objects[i]->Block_2s[b2]->B);
			}

			for(int p=0; p<Objects[i]->Properties->Length; p++)
			{
				bw->Write(Objects[i]->Properties[p]);
			}

			if(Objects[i]->Ident->Type > 4)
			{
				// Save Material
				bw->Write(Objects[i]->Materials->Signature);
				bw->Write(Objects[i]->Materials->Count);
				for(int m=0; m<Objects[i]->Materials->Values->Length; m++)
				{
					bw->Write(Objects[i]->Materials->Values[m]);
				}
				bw->Write(Objects[i]->Materials->Unknown);
			}
		}

		bw->Write(Blocks->Length);

		for(int i=0; i<Numbers->Length; i++)
		{
			bw->Write(Numbers[i]->Values->Length);
			for(int n=0; n<Numbers[i]->Values->Length; n++)
			{
				bw->Write(Numbers[i]->Values[n]);
			}
		}

		for(int i=0; i<Blocks->Length; i++)
		{
			for(int p=0; p<Blocks[i]->Properties->Length; p++)
			{
				bw->Write(Blocks[i]->Properties[p]);
			}
			bw->Write(Blocks[i]->Seperator);
			bw->Write(Blocks[i]->SubBlocks->Length);
			for(int b=0; b<Blocks[i]->SubBlocks->Length; b++)
			{
				bw->Write(Blocks[i]->SubBlocks[b]->A);
				bw->Write(Blocks[i]->SubBlocks[b]->B);
				bw->Write(Blocks[i]->SubBlocks[b]->C);
				bw->Write(Blocks[i]->SubBlocks[b]->D);
				bw->Write(Blocks[i]->SubBlocks[b]->E);
			}
		}

		bw->Close();
		fs->Close();
	}
};