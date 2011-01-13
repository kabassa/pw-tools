#pragma once

using namespace System;
using namespace System::Text;

array<unsigned char>^ getBytesGBK(String^ Value)
{
	Encoding^ enc = Encoding::GetEncoding("GBK");
	array<unsigned char>^ target = gcnew array<unsigned char>(128);
	array<unsigned char>^ source = enc->GetBytes(Value);
	if(target->Length > source->Length)
	{
		Array::Copy(source, target, source->Length);
	}
	else
	{
		Array::Copy(source, target, target->Length);
	}
	return target;
}
public ref struct CreatureGroup
{
	int id;
	int amount;
	int respawn;
	int unknown_2;
	int unknown_3;
	int unknown_4;
	int unknown_5;
	int unknown_6;
	int unknown_7;
	int unknown_8;
	bool unknown_9;
	bool unknown_10;
	bool unknown_11;
	bool unknown_12;
	int unknown_13;
	int unknown_14;
	int unknown_15;
	int unknown_16;
};

public ref struct CreatureSet
{
	int spawn_mode;
	int creature_groups_count;
	float spawn_x;
	float spawn_alt;
	float spawn_z;
	float rot_1;
	float rot_2;
	float rot_3;
	float spread_x;
	float spread_alt;
	float spread_z;
	int unknown_7;
	int unknown_8;
	bool unknown_9;
	bool unknown_10;
	bool unknown_11;
	int unknown_12;
	int trigger;
	int unknown_14;
	int unknown_15;
	array<CreatureGroup^>^ creature_groups;
};

public ref struct ResourceGroup
{
	int unknown_1;
	int id;
	int respawn;
	int amount;
	int unknown_2;
};
public ref struct ResourceSet
{
	float spawn_x;
	float spawn_alt;
	float spawn_z;
	float spread_x;
	float spread_z;
	int resource_groups_count;
	bool unknown_1;
	bool unknown_2;
	bool unknown_3;
	int unknown_4;
	unsigned char  unknown_5a;
	unsigned char unknown_5b;
	unsigned char unknown_5c;
	int unknown_trigger;
	unsigned char unknown_6;
	bool unknown_7;
	bool unknown_8;
	bool unknown_9;
	array<ResourceGroup^>^ resource_groups;
};

public ref struct Dynamic
{
	int id;
	float spawn_x;
	float spawn_alt;
	float spawn_z;
	unsigned char unknown_5;
	unsigned char unknown_6;
	unsigned char unknown_7;
	int trigger;
	unsigned char unknown_8;
};

public ref struct Trigger
{
	int unknown_1;
	int unknown_2;
	array<unsigned char>^ name;
	bool unknown_3;
	int unknown_4;
	int unknown_5;
	bool unknown_6;
	bool unknown_7;
	int year_1;
	int month_1;
	int week_day_1;
	int day_1;
	int hour_1;
	int minute_1;
	int year_2;
	int month_2;
	int week_day_2;
	int day_2;
	int hour_2;
	int minute_2;
	int duration;
};

public ref struct NPCGEN
{
	int version;
	int creature_sets_count;
	int resource_sets_count;
	int dynamics_count;
	int triggers_count;

	array<CreatureSet^>^ creature_sets;
	array<ResourceSet^>^ resource_sets;
	array<Dynamic^>^ dynamics;
	array<Trigger^>^ triggers;
};