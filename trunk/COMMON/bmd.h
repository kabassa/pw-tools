#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Collections;

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

public ref struct Obj
{
	array<unsigned char>^ Unknown; // 4 Bytes
	array<unsigned char>^ Name; // 64 Bytes
	array<unsigned char>^ Texture; // 56 Bytes
	array<Vert^>^ Vertices;
	array<Face^>^ Faces;
	array<Block_1^>^ Block_1s;
	array<Block_2^>^ Block_2s;
	array<float>^ Properties; // 12 float values
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
	public: array<unsigned char>^ Ident; // 4 byte
	private: array<float>^ Unknown_01; // 12 floats
	private: array<Obj^>^ Objects;
	private: array<Number^>^ Numbers;
	private: array<Block^>^ Blocks;

	public: void Load(String^ File)
	{
		FileStream^ fs =File::OpenRead(File);
		BinaryReader^ br = gcnew BinaryReader(fs);

		Signature = br->ReadBytes(4);
		Ident = br->ReadBytes(4);

		Unknown_01 = gcnew array<float>(12);
		for(int i=0; i<Unknown_01->Length; i++)
		{
			Unknown_01[i] = br->ReadSingle();
		}

		int ObjectCount = br->ReadInt32();
		Objects = gcnew array<Obj^>(ObjectCount);
		for(int i=0; i<Objects->Length; i++)
		{
			Objects[i] = gcnew Obj();
			Objects[i]->Unknown = br->ReadBytes(4);
			Objects[i]->Name = br->ReadBytes(64);
			Objects[i]->Texture = br->ReadBytes(256);

			int VertexCount = br->ReadInt32();
			int FacesCount = br->ReadInt32();

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
	}

	public: void Save(String^ File)
	{
		FileStream^ fs = gcnew FileStream(File, FileMode::Create, FileAccess::Write);
		BinaryWriter^ bw = gcnew BinaryWriter(fs);

		bw->Write(Signature);
		bw->Write(Ident);
		/*
		for(int i=0; i<12; i++)
		{
			bw->Write(Unknown_01[i]);
		}
		*/
		bw->Close();
		fs->Close();
	}
};