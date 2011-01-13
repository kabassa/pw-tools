#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Text;

public ref struct SMD_Block
{
	int actNameCharCount;
	array<unsigned char>^ actName; // GBK encoded
	float start_sample;
	float end_sample;
	int stckPathCharCount;
	array<unsigned char>^ stckPath;
};

public ref struct SMD
{
	array<unsigned char>^ signature; // 8 byte
	int version;
	int unknown;
	int block_count;
	array<unsigned char>^ zeros; // 68 byte
	int bonPathCharCount;
	array<unsigned char>^ bonPath; // GBK encoded
	int skiPathCharCount;
	array<unsigned char>^ skiPath; // GBK encoded
	int phyPathCharCount;
	array<unsigned char>^ phyPath; // GBK encoded
	int tckPathCharCount;
	array<unsigned char>^ tckPath; // GBK encoded
	array<SMD_Block^>^ blocks;
};

public ref struct STCK_Block
{
	int vector_count;
	int unk_count;
	int unknown_1;
	array<float>^ vectors; // 3*vector_count
	array<int>^ unks; // 4*unk_count
	int quaternion_count;
	int ukn_count;
	int unknown_2;
	array<float>^ quaternions; // 4*quaternion_count
	array<int>^ ukns; // 4*ukn_count
};

public ref struct STCK
{
	/*
	// can be skipped, not necessary for fix
	array<unsigned char>^ signature; // 8 byte GBK
	int version;
	*/
	int count;
	/*
	// can be skipped, not necessary for fix
	int_unk_1;
	int unk_2;
	int unk_3;
	*/
	array<STCK_Block^>^ blocks;
};

public ref struct BON_Bone
{
	int char_count;
	array<unsigned char>^ name; // char_count bytes GBK
	int unknown;
	int previous;
	int id;
	int connection_count;
	array<unsigned char>^ parameters; // 32 float values (4*32 byte)
	array<int>^ connections;
};

public ref struct BON_Ani
{
	int char_count;
	array<unsigned char>^ name; // char_count bytes GBK
	int previous;
	int id;
	int unknown;
	STCK_Block^ block; // only for bon version < 6
};

public ref struct BON_Hook
{
	int char_count;
	array<unsigned char>^ name; // char_count bytes GBK
	int unknown_1;
	int unknown_2;
	array<float>^ matrix; // 4x4 floats
};

public ref struct BON
{
	array<unsigned char>^ signature; // 8 byte GBK
	int version;
	int bone_count;
	int ani_count;
	int hook_count;
	int unknown_1;
	int samples;
	int unknown_3;
	array<unsigned char>^ zeros; // 64 byte
	array<BON_Bone^>^ bones;
	array<int>^ unknowns;
	array<BON_Ani^>^ anis;
	array<BON_Hook^>^ hooks;
};

// only for loading v1
STCK^ load_stck(String^ file)
{
	FileStream^ fs =File::OpenRead(file);
	BinaryReader^ br = gcnew BinaryReader(fs);

	STCK^ stck = gcnew STCK();

	br->ReadBytes(12);
	stck->count = br->ReadInt32();
	br->ReadBytes(12);
	stck->blocks = gcnew array<STCK_Block^>(stck->count);

	for(int b=0; b<stck->blocks->Length; b++)
	{
		br->ReadBytes(4);

		stck->blocks[b] = gcnew STCK_Block();
		stck->blocks[b]->vector_count = br->ReadInt32();
		stck->blocks[b]->unk_count = br->ReadInt32();
		stck->blocks[b]->unknown_1 = br->ReadInt32();
		stck->blocks[b]->vectors = gcnew array<float>(3*stck->blocks[b]->vector_count);
		for(int i=0; i<stck->blocks[b]->vectors->Length; i++)
		{
			stck->blocks[b]->vectors[i] = br->ReadSingle();
		}
		stck->blocks[b]->unks = gcnew array<int>(4*stck->blocks[b]->unk_count);
		for(int i=0; i<stck->blocks[b]->unks->Length; i++)
		{
			stck->blocks[b]->unks[i] = br->ReadInt32();
		}
		stck->blocks[b]->quaternion_count = br->ReadInt32();
		stck->blocks[b]->ukn_count = br->ReadInt32();
		stck->blocks[b]->unknown_2 = br->ReadInt32();
		stck->blocks[b]->quaternions = gcnew array<float>(4*stck->blocks[b]->quaternion_count);
		for(int i=0; i<stck->blocks[b]->quaternions->Length; i++)
		{
			stck->blocks[b]->quaternions[i] = br->ReadSingle();
		}
		stck->blocks[b]->ukns = gcnew array<int>(4*stck->blocks[b]->ukn_count);
		for(int i=0; i<stck->blocks[b]->ukns->Length; i++)
		{
			stck->blocks[b]->ukns[i] = br->ReadInt32();
		}
	}

	br->Close();
	fs->Close();

	return stck;
}

// only for loading v5 and v6
BON^ load_bon(String^ file)
{
	FileStream^ fs =File::OpenRead(file);
	BinaryReader^ br = gcnew BinaryReader(fs);

	BON^ bon = gcnew BON();

	bon->signature = br->ReadBytes(8);
	bon->version = br->ReadInt32();
	bon->bone_count = br->ReadInt32();
	bon->ani_count = br->ReadInt32();
	bon->hook_count = br->ReadInt32();
	bon->unknown_1 = br->ReadInt32();
	bon->samples = br->ReadInt32();
	bon->unknown_3 = br->ReadInt32();
	bon->zeros = br->ReadBytes(64);
	bon->bones = gcnew array<BON_Bone^>(bon->bone_count);
	for(int b=0; b<bon->bones->Length; b++)
	{
		bon->bones[b] = gcnew BON_Bone();
		bon->bones[b]->char_count = br->ReadInt32();
		bon->bones[b]->name = br->ReadBytes(bon->bones[b]->char_count);
		bon->bones[b]->unknown = br->ReadInt32();
		bon->bones[b]->previous = br->ReadInt32();
		bon->bones[b]->id = br->ReadInt32();
		bon->bones[b]->connection_count = br->ReadInt32();
		bon->bones[b]->parameters = br->ReadBytes(128);
		bon->bones[b]->connections = gcnew array<int>(bon->bones[b]->connection_count);
		for(int i=0; i<bon->bones[b]->connections->Length; i++)
		{
			bon->bones[b]->connections[i] = br->ReadInt32();
		}
	}
	bon->unknowns = gcnew array<int>(bon->bone_count);
	for(int b=0; b<bon->unknowns->Length; b++)
	{
		bon->unknowns[b] = br->ReadInt32();
	}
	bon->anis = gcnew array<BON_Ani^>(bon->ani_count);
	for(int a=0; a<bon->anis->Length; a++)
	{
		bon->anis[a] = gcnew BON_Ani();
		bon->anis[a]->char_count = br->ReadInt32();
		bon->anis[a]->name = br->ReadBytes(bon->anis[a]->char_count);
		bon->anis[a]->previous = br->ReadInt32();
		bon->anis[a]->id = br->ReadInt32();
		bon->anis[a]->unknown = br->ReadInt32();
		if(bon->version < 6)
		{
			bon->anis[a]->block = gcnew STCK_Block();
			bon->anis[a]->block->vector_count = br->ReadInt32();
			bon->anis[a]->block->unk_count = br->ReadInt32();
			bon->anis[a]->block->unknown_1 = br->ReadInt32();
			bon->anis[a]->block->vectors = gcnew array<float>(3*bon->anis[a]->block->vector_count);
			for(int i=0; i<	bon->anis[a]->block->vectors->Length; i++)
			{
				bon->anis[a]->block->vectors[i] = br->ReadSingle();
			}
			bon->anis[a]->block->unks = gcnew array<int>(4*	bon->anis[a]->block->unk_count);
			for(int i=0; i<	bon->anis[a]->block->unks->Length; i++)
			{
				bon->anis[a]->block->unks[i] = br->ReadInt32();
			}
			bon->anis[a]->block->quaternion_count = br->ReadInt32();
			bon->anis[a]->block->ukn_count = br->ReadInt32();
			bon->anis[a]->block->unknown_2 = br->ReadInt32();
			bon->anis[a]->block->quaternions = gcnew array<float>(4*bon->anis[a]->block->quaternion_count);
			for(int i=0; i<	bon->anis[a]->block->quaternions->Length; i++)
			{
				bon->anis[a]->block->quaternions[i] = br->ReadSingle();
			}
			bon->anis[a]->block->ukns = gcnew array<int>(4*	bon->anis[a]->block->ukn_count);
			for(int i=0; i<	bon->anis[a]->block->ukns->Length; i++)
			{
				bon->anis[a]->block->ukns[i] = br->ReadInt32();
			}
		}
	}
	bon->hooks = gcnew array<BON_Hook^>(bon->hook_count);
	for(int h=0; h<bon->hooks->Length; h++)
	{
		bon->hooks[h] = gcnew BON_Hook();
		bon->hooks[h]->char_count = br->ReadInt32();
		bon->hooks[h]->name = br->ReadBytes(bon->hooks[h]->char_count);
		bon->hooks[h]->unknown_1 = br->ReadInt32();
		bon->hooks[h]->unknown_2 = br->ReadInt32();
		bon->hooks[h]->matrix = gcnew array<float>(16);
		for(int m=0; m<bon->hooks[h]->matrix->Length; m++)
		{
			bon->hooks[h]->matrix[m] = br->ReadSingle();
		}
	}

	br->Close();
	fs->Close();

	return bon;
}
// only for loading v6 and v8
SMD^ load_smd(String^ file)
{
	FileStream^ fs =File::OpenRead(file);
	BinaryReader^ br = gcnew BinaryReader(fs);

	SMD^ smd = gcnew SMD();

	smd->signature = br->ReadBytes(8);
	smd->version = br->ReadInt32();
	smd->unknown = br->ReadInt32();
	smd->block_count = br->ReadInt32();
	smd->zeros = br->ReadBytes(68);
	smd->bonPathCharCount = br->ReadInt32();
	smd->bonPath = br->ReadBytes(smd->bonPathCharCount);
	smd->skiPathCharCount = br->ReadInt32();
	smd->skiPath = br->ReadBytes(smd->skiPathCharCount);
	if(smd->unknown > 0)
	{
		smd->phyPathCharCount = br->ReadInt32();
		smd->phyPath = br->ReadBytes(smd->phyPathCharCount);
	}
	if(smd->version > 6)
	{
		smd->tckPathCharCount = br->ReadInt32();
		smd->tckPath = br->ReadBytes(smd->tckPathCharCount);
	}
	smd->blocks = gcnew array<SMD_Block^>(smd->block_count);
	for(int i=0; i<smd->blocks->Length; i++)
	{
		smd->blocks[i] = gcnew SMD_Block;
		smd->blocks[i]->actNameCharCount = br->ReadInt32();
		smd->blocks[i]->actName = br->ReadBytes(smd->blocks[i]->actNameCharCount);
		smd->blocks[i]->start_sample = br->ReadSingle();
		smd->blocks[i]->end_sample = br->ReadSingle();
		if(smd->version > 6)
		{
			smd->blocks[i]->stckPathCharCount = br->ReadInt32();
			smd->blocks[i]->stckPath = br->ReadBytes(smd->blocks[i]->stckPathCharCount);
		}
	}

	br->Close();
	fs->Close();

	return smd;
}

// convert v8 to v6
SMD^ fix_smd(SMD^ smd)
{
	if(smd->version > 6)
	{
		smd->version = 6;
		// recalculate act times for new fixed bon file
		// local sample-spans to global samples
		for(int i=1; i<smd->blocks->Length; i++)
		{
			smd->blocks[i]->start_sample = smd->blocks[i-1]->end_sample+1;
			smd->blocks[i]->end_sample += smd->blocks[i]->start_sample;
		}
	}

	return smd;
}

// only for saving v6 and v8
void save_smd(SMD^ smd, String^ file)
{
	FileStream^ fs = gcnew FileStream(file, FileMode::Create, FileAccess::Write);
	BinaryWriter^ bw = gcnew BinaryWriter(fs);

	bw->Write(smd->signature);
	bw->Write(smd->version);
	bw->Write(smd->unknown);
	bw->Write(smd->block_count);
	bw->Write(smd->zeros);
	bw->Write(smd->bonPathCharCount);
	bw->Write(smd->bonPath);
	bw->Write(smd->skiPathCharCount);
	bw->Write(smd->skiPath);
	if(smd->unknown > 0)
	{
		bw->Write(smd->phyPathCharCount);
		bw->Write(smd->phyPath);
	}
	if(smd->version > 6)
	{
		bw->Write(smd->tckPathCharCount);
		bw->Write(smd->tckPath);
	}
	for(int i=0; i<smd->blocks->Length; i++)
	{
		bw->Write(smd->blocks[i]->actNameCharCount);
		bw->Write(smd->blocks[i]->actName);
		bw->Write(smd->blocks[i]->start_sample);
		bw->Write(smd->blocks[i]->end_sample);
		if(smd->version > 6)
		{
			bw->Write(smd->blocks[i]->stckPathCharCount);
			bw->Write(smd->blocks[i]->stckPath);
		}
	}

	bw->Close();
	fs->Close();
}

// convert v6 to v5
BON^ fix_bon(BON^ bon, array<STCK^>^ stcks, float smd_samples)
{
	if(bon->version > 5)
	{
		bon->version = (int)5;
		bon->samples = Convert::ToInt32(smd_samples);

		for(int a=0; a<bon->anis->Length; a++)
		{
			bon->anis[a]->block = gcnew STCK_Block();
			bon->anis[a]->block->vector_count = 0;
			bon->anis[a]->block->unk_count = 0;
			bon->anis[a]->block->unknown_1 = -1;
			bon->anis[a]->block->quaternion_count = 0;
			bon->anis[a]->block->ukn_count = 0;
			bon->anis[a]->block->unknown_2 = -1;

			for(int i=0; i<stcks->Length; i++)
			{
				if(bon->anis->Length != stcks[i]->blocks->Length)
				{
					bon->version = (int)6;
					return bon;
// 1 failed
				}
				bon->anis[a]->block->vector_count += stcks[i]->blocks[a]->vector_count;
				bon->anis[a]->block->unk_count += stcks[i]->blocks[a]->unk_count;
				bon->anis[a]->block->unknown_1 = Math::Max(bon->anis[a]->block->unknown_1, stcks[i]->blocks[a]->unknown_1);
				bon->anis[a]->block->quaternion_count += stcks[i]->blocks[a]->quaternion_count;
				bon->anis[a]->block->ukn_count += stcks[i]->blocks[a]->ukn_count;
				bon->anis[a]->block->unknown_2 = Math::Max(bon->anis[a]->block->unknown_2, stcks[i]->blocks[a]->unknown_2);
			}

			bon->anis[a]->block->vectors = gcnew array<float>(3*bon->anis[a]->block->vector_count);
			bon->anis[a]->block->unks = gcnew array<int>(4*bon->anis[a]->block->unk_count);
			bon->anis[a]->block->quaternions = gcnew array<float>(4*bon->anis[a]->block->quaternion_count);
			bon->anis[a]->block->ukns = gcnew array<int>(4*bon->anis[a]->block->ukn_count);

			int vector_offset = 0;
			int unk_offset = 0;
			int quaternion_offset = 0;
			int ukn_offset = 0;

			for(int i=0; i<stcks->Length; i++)
			{
				for(int n=0; n<stcks[i]->blocks[a]->vectors->Length; n++)
				{
					bon->anis[a]->block->vectors[vector_offset] = stcks[i]->blocks[a]->vectors[n];
					vector_offset++;
				}
				for(int n=0; n<stcks[i]->blocks[a]->unks->Length; n++)
				{
					bon->anis[a]->block->unks[unk_offset] = stcks[i]->blocks[a]->unks[n];
					unk_offset++;
				}
				for(int n=0; n<stcks[i]->blocks[a]->quaternions->Length; n++)
				{
					bon->anis[a]->block->quaternions[quaternion_offset] = stcks[i]->blocks[a]->quaternions[n];
					quaternion_offset++;
				}
				for(int n=0; n<stcks[i]->blocks[a]->ukns->Length; n++)
				{
					bon->anis[a]->block->ukns[ukn_offset] = stcks[i]->blocks[a]->ukns[n];
					ukn_offset++;
				}
			}
		}
	}

	return bon;
}

// only for saving v5 and v6
void save_bon(BON^ bon, String^ file)
{
	FileStream^ fs = gcnew FileStream(file, FileMode::Create, FileAccess::Write);
	BinaryWriter^ bw = gcnew BinaryWriter(fs);

	bw->Write(bon->signature);
	bw->Write(bon->version);
	bw->Write(bon->bone_count);
	bw->Write(bon->ani_count);
	bw->Write(bon->hook_count);
	bw->Write(bon->unknown_1);
	bw->Write(bon->samples);
	bw->Write(bon->unknown_3);
	bw->Write(bon->zeros);
	for(int b=0; b<bon->bones->Length; b++)
	{
		bw->Write(bon->bones[b]->char_count);
		bw->Write(bon->bones[b]->name);
		bw->Write(bon->bones[b]->unknown);
		bw->Write(bon->bones[b]->previous);
		bw->Write(bon->bones[b]->id);
		bw->Write(bon->bones[b]->connection_count);
		bw->Write(bon->bones[b]->parameters);
		for(int i=0; i<bon->bones[b]->connections->Length; i++)
		{
			bw->Write(bon->bones[b]->connections[i]);
		}
	}
	for(int b=0; b<bon->unknowns->Length; b++)
	{
		bw->Write(bon->unknowns[b]);
	}
	for(int a=0; a<bon->anis->Length; a++)
	{
		bw->Write(bon->anis[a]->char_count);
		bw->Write(bon->anis[a]->name);
		bw->Write(bon->anis[a]->previous);
		bw->Write(bon->anis[a]->id);
		bw->Write(bon->anis[a]->unknown);
		if(bon->version < 6)
		{
			bw->Write(bon->anis[a]->block->vector_count);
			bw->Write(bon->anis[a]->block->unk_count);
			bw->Write(bon->anis[a]->block->unknown_1);
			for(int i=0; i<	bon->anis[a]->block->vectors->Length; i++)
			{
				bw->Write(bon->anis[a]->block->vectors[i]);
			}
			for(int i=0; i<	bon->anis[a]->block->unks->Length; i++)
			{
				bw->Write(bon->anis[a]->block->unks[i]);
			}
			bw->Write(bon->anis[a]->block->quaternion_count);
			bw->Write(bon->anis[a]->block->ukn_count);
			bw->Write(bon->anis[a]->block->unknown_2);
			for(int i=0; i<	bon->anis[a]->block->quaternions->Length; i++)
			{
				bw->Write(bon->anis[a]->block->quaternions[i]);
			}
			for(int i=0; i<	bon->anis[a]->block->ukns->Length; i++)
			{
				bw->Write(bon->anis[a]->block->ukns[i]);
			}
		}
	}
	for(int h=0; h<bon->hooks->Length; h++)
	{
		bw->Write(bon->hooks[h]->char_count);
		bw->Write(bon->hooks[h]->name);
		bw->Write(bon->hooks[h]->unknown_1);
		bw->Write(bon->hooks[h]->unknown_2);
		for(int m=0; m<bon->hooks[h]->matrix->Length; m++)
		{
			bw->Write(bon->hooks[h]->matrix[m]);
		}
	}

	bw->Close();
	fs->Close();
}