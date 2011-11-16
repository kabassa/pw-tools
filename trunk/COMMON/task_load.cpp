#pragma once

#include "task.h"

Date^ ReadDate(int version, BinaryReader^ br)
{
	Date^ date = gcnew Date();

	date->year = br->ReadInt32();
	date->month = br->ReadInt32();
	date->day = br->ReadInt32();
	date->hour = br->ReadInt32();
	date->minute = br->ReadInt32();
	date->weekday = br->ReadInt32();

	return date;
}
DateSpan^ ReadDateSpan(int version, BinaryReader^ br)
{
	DateSpan^ date_span = gcnew DateSpan();

	date_span->from = ReadDate(version, br);
	date_span->to = ReadDate(version, br);

	return date_span;
}
Item^ ReadItem(int version, BinaryReader^ br)
{
	Item^ item = gcnew Item();

	item->id = br->ReadInt32();
	item->unknown = br->ReadBoolean();
	item->amount = br->ReadInt32();
	item->probability = br->ReadSingle();

	if(version >= 89)
	{
		item->expiration = br->ReadInt32();
	}
	else
	{
		item->expiration = 0;
	}

	return item;
}

ItemGroup^ ReadItemGroup(int version, BinaryReader^ br)
{
	ItemGroup^ item_group = gcnew ItemGroup();

	item_group->unknown = br->ReadBoolean();
	item_group->items_count = br->ReadInt32();
	item_group->items = gcnew array<Item^>(item_group->items_count);
	for(int n=0; n<item_group->items->Length; n++)
	{
		item_group->items[n] = ReadItem(version, br);
	}

	return item_group;
}

TeamMembers^ ReadTeamMembers(int version, BinaryReader^ br)
{
	TeamMembers^ team_member_group = gcnew TeamMembers();

	team_member_group->level_min = br->ReadInt32();
	team_member_group->level_max = br->ReadInt32();
	team_member_group->unknown_1 = br->ReadInt32();
	team_member_group->unknown_2 = br->ReadInt32();
	team_member_group->unknown_3 = br->ReadInt32();
	team_member_group->amount_min = br->ReadInt32();
	team_member_group->amount_max = br->ReadInt32();
	team_member_group->quest = br->ReadInt32();

	return team_member_group;
}

Chase^ ReadChase(int version, BinaryReader^ br)
{
	Chase^ chase = gcnew Chase();

	chase->id_monster = br->ReadInt32();
	chase->amount_monster = br->ReadInt32();
	chase->id_drop = br->ReadInt32();
	chase->amount_drop = br->ReadInt32();
	chase->unknown_1 = br->ReadByte();
	chase->probability = br->ReadSingle();
	chase->unknown_2 = br->ReadByte();

	if(version >= 92)
	{
		chase->unknown_3 = br->ReadBytes(8);
	}
	else
	{
		chase->unknown_3 = gcnew array<unsigned char>(8);
	}

	return chase;
}

Location^ ReadLocation(int version, BinaryReader^ br)
{
	Location^ location = gcnew Location();

	location->map_id = br->ReadInt32();
	location->x = br->ReadSingle();
	location->altitude = br->ReadSingle();
	location->z = br->ReadSingle();

	return location;
}

Span^ ReadSpan(int version, BinaryReader^ br)
{
	Span^ location_span = gcnew Span();

	location_span->east = br->ReadSingle();
	location_span->bottom = br->ReadSingle();
	location_span->south = br->ReadSingle();
	location_span->west = br->ReadSingle();
	location_span->top = br->ReadSingle();
	location_span->north = br->ReadSingle();

	return location_span;
}

Reward^ ReadReward(int version, BinaryReader^ br)
{
	Reward^ reward = gcnew Reward();

	reward->coins = br->ReadInt32();
	reward->experience = br->ReadInt32();
	reward->new_quest = br->ReadInt32();
	reward->spirit = br->ReadInt32();
	reward->reputation = br->ReadInt32();
	reward->cultivation = br->ReadInt32();
	reward->UNKNOWN_1 = br->ReadInt32();
	reward->storage_slots = br->ReadInt32();

	if(version >= 89)
	{
		reward->cupboard_slots = br->ReadInt32();
		reward->wardrobe_slots = br->ReadInt32();
		reward->account_stash_slots = br->ReadInt32();
	}

	reward->inventory_slots = br->ReadInt32();
	reward->petbag_slots = br->ReadInt32();
	reward->vigor = br->ReadInt32();
	reward->teleport = ReadLocation(version, br);
	reward->aiTrigger = br->ReadInt32();
	reward->UNKNOWN_2a = br->ReadBytes(3);

	if(version > 55)
	{
		reward->UNKNOWN_2b = br->ReadBytes(5);
	}
	else
	{
		reward->UNKNOWN_2b = gcnew array<unsigned char>(5);
	}

	reward->item_groups_count = br->ReadInt32();
	reward->SEPERATOR = br->ReadBytes(4);

	reward->pq = gcnew PQ_Reward();
	if(version >= 89)
	{
		reward->pq->chase_count = br->ReadInt32();
		reward->pq->unknown_1 = br->ReadBytes(19);
		reward->pq->unknown_quest = br->ReadInt32();
		reward->pq->unknown_2 = br->ReadBytes(4);
		reward->pq->unknown_level = br->ReadInt32();
		reward->pq->contribution_random_min = br->ReadInt32();
		reward->pq->contribution_random_max = br->ReadInt32();
		reward->pq->contribution_required = br->ReadInt32();
		reward->pq->unknown_3 = br->ReadBytes(8);
		reward->pq->item_count = br->ReadInt32();
		reward->pq->unknown_4 = br->ReadBytes(4);
		reward->pq->special_count = br->ReadInt32();
		reward->pq->unknown_5 = br->ReadBytes(29);
		reward->pq->script_count = br->ReadInt32();
		reward->pq->unknown_6 = br->ReadBytes(8);
		reward->pq->message_count = br->ReadInt32();
		reward->pq->unknown_7 = br->ReadBytes(4);
	}
	else
	{
		reward->pq->chase_count = 0;
		reward->pq->unknown_1 = gcnew array<unsigned char>(19);
		reward->pq->unknown_quest = 0;
		reward->pq->unknown_2 = gcnew array<unsigned char>(4);
		reward->pq->unknown_level = 0;
		reward->pq->contribution_random_min = 0;
		reward->pq->contribution_random_max = 0;
		reward->pq->contribution_required = 0;
		reward->pq->unknown_3 = gcnew array<unsigned char>(8);
		reward->pq->item_count = 0;
		reward->pq->unknown_4 = gcnew array<unsigned char>(4);
		reward->pq->special_count = 0;
		reward->pq->unknown_5 = gcnew array<unsigned char>(29);
		reward->pq->script_count = 0;
		reward->pq->unknown_6 = gcnew array<unsigned char>(8);
		reward->pq->message_count = 0;
		reward->pq->unknown_7 = gcnew array<unsigned char>(4);
	}
	// initialize values to prevent NULL exception
	{
		reward->pq->chase_unknown_1 = false;
		reward->pq->chase_unknown_2 = 0;
		reward->pq->chase_unknown_3 = false;
		reward->pq->chases = gcnew array<PQ_Chase^>(0);

		reward->pq->item_unknown_1 = false;
		reward->pq->items = gcnew array<PQ_Item^>(0);

		reward->pq->specials = gcnew array<PQ_Special^>(0);

		reward->pq->scripts = gcnew array<array<unsigned char>^>(0);
		reward->pq->messages = gcnew array<array<unsigned char>^>(0);
	}

	reward->item_groups = gcnew array<ItemGroup^>(reward->item_groups_count);

	for(int i=0; i<reward->item_groups->Length; i++)
	{
		reward->item_groups[i] = ReadItemGroup(version, br);
	}

	if(version >= 89)
	{
		if(reward->pq->chase_count>0)
		{
			reward->pq->chase_unknown_1 = br->ReadBoolean();
			reward->pq->chase_unknown_2 = br->ReadInt32();
			reward->pq->chase_unknown_3 = br->ReadBoolean();
			reward->pq->chases = gcnew array<PQ_Chase^>(reward->pq->chase_count);
			for(int i=0; i<reward->pq->chase_count; i++)
			{
				reward->pq->chases[i] = gcnew PQ_Chase();
				reward->pq->chases[i]->id_monster = br->ReadInt32();
				reward->pq->chases[i]->amount_monster = br->ReadInt32();
				reward->pq->chases[i]->probability = br->ReadSingle();
				reward->pq->chases[i]->amount_unknown = br->ReadInt32();
			}
		}

		if(reward->pq->item_count>0)
		{
			reward->pq->item_unknown_1 = br->ReadBoolean();
			reward->pq->items = gcnew array<PQ_Item^>(reward->pq->item_count);
			for(int i=0; i<reward->pq->item_count; i++)
			{
				reward->pq->items[i] = gcnew PQ_Item;
				reward->pq->items[i]->ranking_from = br->ReadInt32();
				reward->pq->items[i]->ranking_to = br->ReadInt32();
				reward->pq->items[i]->unknown_3 = br->ReadBoolean();
				reward->pq->items[i]->id = br->ReadInt32();
				reward->pq->items[i]->amount = br->ReadInt32();
				reward->pq->items[i]->probability =  br->ReadSingle();
			}
		}

		if(reward->pq->special_count>0)
		{
			reward->pq->specials = gcnew array<PQ_Special^>(reward->pq->special_count);
			for(int i=0; i<reward->pq->special_count; i++)
			{
				reward->pq->specials[i] = gcnew PQ_Special();
				reward->pq->specials[i]->id_pq = br->ReadInt32();
				reward->pq->specials[i]->unknown_2 = br->ReadInt32();
				reward->pq->specials[i]->unknown_3 = br->ReadByte();
			}
		}

		if(reward->pq->script_count>0)
		{
			reward->pq->scripts = gcnew array<array<unsigned char>^>(reward->pq->script_count);
			for(int i=0; i<reward->pq->script_count; i++)
			{
				reward->pq->scripts[i] = br->ReadBytes(576);
			}
		}

		if(reward->pq->message_count>0)
		{
			reward->pq->messages = gcnew array<array<unsigned char>^>(reward->pq->message_count);
			for(int i=0; i<reward->pq->message_count; i++)
			{
				reward->pq->messages[i] = br->ReadBytes(128);
			}
		}
	}

	return reward;
}

void Task::Load(int version, BinaryReader^ br, int stream_position, TreeNodeCollection^ nodes)
{
	br->BaseStream->Position = stream_position;

// ################# GENERAL #############################

	id = br->ReadInt32();
	name = br->ReadBytes(60);
	author_mode = br->ReadBoolean();
	UNKNOWN_001a = br->ReadBytes(4);
	type = br->ReadInt32();
	time_limit = br->ReadInt32();

	if(version >= 89)
	{
		UNKNOWN_001b = br->ReadBytes(2);
		date_fail = ReadDate(version, br);
		UNKNOWN_001c = br->ReadBytes(1);	
	}
	else
	{
		UNKNOWN_001b = gcnew array<unsigned char>(2);
		date_fail = gcnew Date();
		date_fail->year = 0;
		date_fail->month = 0;
		date_fail->day = 0;
		date_fail->hour = 0;
		date_fail->minute = 0;
		date_fail->weekday = 0;
		UNKNOWN_001c = gcnew array<unsigned char>(1);
	}

	UNKNOWN_002 = br->ReadBytes(1);
	date_spans_count = br->ReadInt32();
	UNKNOWN_EVENT = br->ReadBytes(4);
	UNKNOWN_ZEROS = br->ReadBytes(8);

	if(version >= 89)
	{
		UNKNOWN_ZEROS_a = br->ReadBytes(12);
	}
	else
	{
		UNKNOWN_ZEROS_a = gcnew array<unsigned char>(12);
	}

	date_unknown = br->ReadBytes(8);
	UNKNOWN_FLAGS_1 = br->ReadBytes(4);

	if(version >= 89)
	{
		UNKNOWN_FLAGS_1a = br->ReadBytes(4);
	}
	else
	{
		UNKNOWN_FLAGS_1a = gcnew array<unsigned char>(4);
	}

	UNKNOWN_FLAGS_2 = br->ReadBytes(5);
	can_give_up = br->ReadBoolean();
	repeatable = br->ReadBoolean();
	repeatable_after_failure = br->ReadBoolean();
	UNKNOWN_004 = br->ReadBytes(8);

	quest_trigger_locations = gcnew LocationSpan();
	quest_trigger_locations->map_id = br->ReadInt32();
	if(version >= 89)
	{
		quest_trigger_locations->count = br->ReadInt32();
		quest_trigger_locations->spans = gcnew array<Span^>(quest_trigger_locations->count);
	}
	else
	{
		quest_trigger_locations->count = 1;
		quest_trigger_locations->spans = gcnew array<Span^>(quest_trigger_locations->count);
		quest_trigger_locations->spans[0] = ReadSpan(version, br);
	}

	quest_unknown_locations_1 = gcnew LocationSpan();
	quest_valid_locations = gcnew LocationSpan();
	if(version >= 89)
	{
		UNKNOWN_004a = br->ReadBytes(5);
		quest_unknown_locations_1->map_id = br->ReadInt32();
		quest_unknown_locations_1->count = br->ReadInt32();
		quest_unknown_locations_1->spans = gcnew array<Span^>(quest_unknown_locations_1->count);
		UNKNOWN_004b = br->ReadBytes(5);
		quest_valid_locations->map_id = br->ReadInt32();
		quest_valid_locations->count = br->ReadInt32();
		quest_valid_locations->spans = gcnew array<Span^>(quest_valid_locations->count);
		UNKNOWN_004c = br->ReadBytes(4);
	}
	else
	{
		UNKNOWN_004a = gcnew array<unsigned char>(5);
		quest_unknown_locations_1->map_id = 0;
		quest_unknown_locations_1->count = 0;
		quest_unknown_locations_1->spans = gcnew array<Span^>(0);
		UNKNOWN_004b = gcnew array<unsigned char>(5);
		quest_valid_locations->map_id = 0;
		quest_valid_locations->count = 0;
		quest_valid_locations->spans = gcnew array<Span^>(0);
		UNKNOWN_004c = gcnew array<unsigned char>(4);
	}

	UNKNOWN_005a_1 = br->ReadBytes(1);
	instant_teleport_location = ReadLocation(version, br);
	ai_trigger = br->ReadInt32();
	UNKNOWN_005a_3 = br->ReadBytes(3);

	if(version >= 89)
	{
		UNKNOWN_005a_4 = br->ReadBytes(2);
	}
	else
	{
		UNKNOWN_005a_4 = gcnew array<unsigned char>(2);
	}

	UNKNOWN_005b = br->ReadBytes(1);
	UNKNOWN_LEVEL = br->ReadInt32();
	UNKNOWN_005c = br->ReadBytes(2);
	quest_npc = br->ReadInt32();
	reward_npc = br->ReadInt32();
	UNKNOWN_006 = br->ReadBytes(4);

	pq = gcnew PQ_Audit();
	if(version >= 89)
	{
		pq->script_info_count = br->ReadInt32();
		pq->unknown_1 = br->ReadBytes(12);
		pq->unknown_2 = br->ReadInt32();
		pq->unknown_3 = br->ReadBytes(15);
		pq->script_count = br->ReadInt32();
		pq->unknown_4 = br->ReadBytes(8);
		pq->unknown_5 = br->ReadBytes(1);
		pq->unknown_6 = br->ReadBytes(1);
		pq->chase_count = br->ReadInt32();
		pq->unknown_7 = br->ReadBytes(4);
		pq->unknown_8 = br->ReadBytes(5);

		// correct position not confirmed
		if(version >= 92)
		{
			pq->unknown_9 = br->ReadBytes(5);
		}
		else
		{
			pq->unknown_9 = gcnew array<unsigned char>(5);
		}

		pq->unknown_10 = br->ReadBytes(5);
	}
	else
	{
		pq->script_info_count = 0;
		pq->unknown_1 = gcnew array<unsigned char>(12);
		pq->unknown_2 = 0;
		pq->unknown_3 = gcnew array<unsigned char>(15);
		pq->script_count = 0;
		pq->unknown_4 = gcnew array<unsigned char>(8);
		pq->unknown_5 = gcnew array<unsigned char>(1);
		pq->unknown_6 = gcnew array<unsigned char>(1);
		pq->chase_count = 0;
		pq->unknown_7 = gcnew array<unsigned char>(4);
		pq->unknown_8 = gcnew array<unsigned char>(5);
		pq->unknown_9 = gcnew array<unsigned char>(5);
		pq->unknown_10 = gcnew array<unsigned char>(5);
	}
	pq->script_infos = gcnew array<PQ_AuditScriptInfo^>(pq->script_info_count);
	pq->scripts = gcnew array<PQ_AuditScript^>(pq->script_count);
	pq->chases = gcnew array<PQ_AuditChase^>(pq->chase_count);

	level_min = br->ReadInt32();
	level_max = br->ReadInt32();
	UNKNOWN_007 = br->ReadBytes(1);
	required_items_count = br->ReadInt32();
	required_items_unknown = br->ReadBytes(4);
	UNKNOWN_008_ = br->ReadBytes(1);
	given_items_count = br->ReadInt32();
	GIVEN_UNKNOWN_INTEGERS = br->ReadBytes(8);
	given_items_unknown = br->ReadBytes(4);
	instant_pay_coins = br->ReadInt32();
	UNKNOWN_009b = br->ReadBytes(1);
	required_reputation = br->ReadInt32();
	UNKNOWN_010 = br->ReadBytes(5);
	required_quests_done_count = br->ReadInt32();
	required_quests_done = gcnew array<int>(5);
	for(int i=0; i<required_quests_done->Length; i++)
	{
		required_quests_done[i] = br->ReadInt32();
	}

	if(version >= 90)
	{
		UNKNOWN_011_1 = br->ReadBytes(60);
	}
	else
	{
		UNKNOWN_011_1 = gcnew array<unsigned char>(60);
	}

	UNKNOWN_011_1a = br->ReadBytes(1);

	if(version >= 90)
	{
		UNKNOWN_011_1ab = br->ReadInt32();
	}
	else
	{
		UNKNOWN_011_1ab = 0;
	}

	UNKNOWN_011_1ba = br->ReadBytes(9);

	if(version >= 93)
	{
		UNKNOWN_011_1bb = br->ReadInt32();
	}
	else
	{
		UNKNOWN_011_1bb = 0;
	}

	UNKNOWN_011_1bc = br->ReadBytes(1);
	required_gender = br->ReadInt32();
	UNKNOWN_011_2 = br->ReadBytes(1);

	if(version >= 89)
	{
		required_occupations = gcnew array<int>(10);
	}
	else
	{
		required_occupations = gcnew array<int>(8);
	}
	required_occupations_count = br->ReadInt32();
	for(int i=0; i<required_occupations->Length; i++)
	{
		required_occupations[i] = br->ReadInt32();
	}

	UNKNOWN_011_a2 = br->ReadBytes(5);

	if(version >= 89)
	{
		UNKNOWN_011_a3 = br->ReadBytes(19);
		unknown_date = ReadDate(version, br);
		UNKNOWN_011_a4 = br->ReadBytes(5);	
	}
	else
	{
		UNKNOWN_011_a3 = gcnew array<unsigned char>(19);
		unknown_date = gcnew Date();
		unknown_date->year = 0;
		unknown_date->month = 0;
		unknown_date->day = 0;
		unknown_date->weekday = 0;
		unknown_date->hour = 0;
		unknown_date->minute = 0;
		UNKNOWN_011_a4 = gcnew array<unsigned char>(5);
	}

	UNKNOWN_011_b = br->ReadBytes(7);
	required_quests_undone_count = br->ReadInt32();
	required_quests_undone = gcnew array<int>(5);
	for(int i=0; i<required_quests_undone->Length; i++)
	{
		required_quests_undone[i] = br->ReadInt32();
	}
	required_blacksmith_level = br->ReadInt32();
	required_tailor_level = br->ReadInt32();
	required_craftsman_level = br->ReadInt32();
	required_apothecary_level = br->ReadInt32();
	TEAM_MEMBER_REQUIREMENT = br->ReadBytes(32);

	if(version >= 89)
	{
		UNKNOWN_012 = br->ReadBytes(3);
	}
	else
	{
		UNKNOWN_012 = gcnew array<unsigned char>(3);
	}

	required_team_member_groups_count = br->ReadInt32();
	required_team_member_groups_unknown = br->ReadBytes(4);
	UNKNOWN_012_a = br->ReadBytes(1);

	if(version >= 89)
	{
		UNKNOWN_012_a1 = br->ReadBytes(9);
		resource_pq_audit_id = br->ReadInt32();
		UNKNOWN_012_a2 = br->ReadInt32();
		UNKNOWN_012_a3 = br->ReadInt32();
		required_pq_contribution = br->ReadInt32();
		UNKNOWN_012_a4 = br->ReadBytes(20);
	}
	else
	{
		UNKNOWN_012_a1 = gcnew array<unsigned char>(9);
		resource_pq_audit_id = 0;
		UNKNOWN_012_a2 = 0;
		UNKNOWN_012_a3 = 0;
		required_pq_contribution = br->ReadInt32();
		UNKNOWN_012_a4 = gcnew array<unsigned char>(20);
	}

	UNKNOWN_012_b = br->ReadBytes(8);
	required_chases_count = br->ReadInt32();
	required_chases_unknown = br->ReadBytes(4);
	required_get_items_count = br->ReadInt32();
	required_get_items_unknown = br->ReadBytes(4);
	required_coins = br->ReadInt32();
	UNKNOWN_015 = br->ReadBytes(16);

	if(version >= 89)
	{
		UNKNOWN_015a = br->ReadBytes(12);
	}
	else
	{
		UNKNOWN_015a = gcnew array<unsigned char>(12);
	}

	required_reach_locations = gcnew LocationSpan();
	if(version >= 89)
	{
		required_reach_locations->count = br->ReadInt32();
		required_reach_locations->spans = gcnew array<Span^>(required_reach_locations->count);
	}
	else
	{
		required_reach_locations->count = 1;
		required_reach_locations->spans = gcnew array<Span^>(required_reach_locations->count);
		required_reach_locations->spans[0] = ReadSpan(version, br);
	}
	required_reach_locations->map_id = br->ReadInt32();

	required_wait_time = br->ReadInt32();

	// At this place the v89 positions must be guessed due to leak of informations...

	pq->leave_area = gcnew PQ_AuditExitArea();
	pq->leave_area->location = gcnew LocationSpan();

	if(version >= 89)
	{
		pq->leave_area->unknown_1 = br->ReadBytes(4);
		pq->leave_area->location->map_id = br->ReadInt32();
		pq->leave_area->location->count = br->ReadInt32();
		pq->leave_area->unknown_2 = br->ReadInt32();
		pq->leave_area->unknown_3 = br->ReadBytes(5);
		pq->leave_area->id_script = br->ReadInt32();
		pq->leave_area->unknown_4 = br->ReadInt32();
		pq->leave_area->unknown_5 = br->ReadInt32();
		pq->leave_area->unknown_6 = br->ReadInt32();
		pq->leave_area->unknown_7 = br->ReadBytes(20);
		pq->leave_area->script_count = br->ReadInt32();
		pq->leave_area->unknown_8 = br->ReadBytes(4);
		pq->leave_area->unknown_9 = br->ReadBytes(4);
		pq->leave_area->message_count = br->ReadInt32();
		pq->leave_area->unknown_10 = br->ReadBytes(4);
	}
	else
	{
		pq->leave_area->unknown_1 = gcnew array<unsigned char>(4);
		pq->leave_area->location->map_id = 0;
		pq->leave_area->location->count = 0;
		pq->leave_area->unknown_2 = 0;
		pq->leave_area->unknown_3 = gcnew array<unsigned char>(5);
		pq->leave_area->id_script = 0;
		pq->leave_area->unknown_4 = 0;
		pq->leave_area->unknown_5 = 0;
		pq->leave_area->unknown_6 = 0;
		pq->leave_area->unknown_7 = gcnew array<unsigned char>(20);
		pq->leave_area->script_count = 0;
		pq->leave_area->unknown_8 = gcnew array<unsigned char>(4);
		pq->leave_area->unknown_9 = gcnew array<unsigned char>(4);
		pq->leave_area->message_count = 0;
		pq->leave_area->unknown_10 = gcnew array<unsigned char>(4);
	}

	pq->leave_area->location->spans = gcnew array<Span^>(pq->leave_area->location->count);
	pq->leave_area->scripts = gcnew array<PQ_AuditScript^>(pq->leave_area->script_count);
	pq->leave_area->messages = gcnew array<array<unsigned char>^>(pq->leave_area->message_count);

	// Need to checked if contains something != 0
	UNKNOWN_016_b = br->ReadBytes(8);
	UNKNOWN_016_c = br->ReadBytes(24);
	parent_quest = br->ReadInt32();
	previous_quest = br->ReadInt32();
	next_quest = br->ReadInt32();
	sub_quest_first = br->ReadInt32();

	if(version >= 89)
	{
		UNKNOWN_016_d = br->ReadBoolean();
		UNKNOWN_016_e = br->ReadBytes(4);
	}

// ################# AUTHOR TEXT #############################

	author_text = gcnew array<unsigned char>(0);
	if(author_mode)
	{
		author_text = br->ReadBytes(60);
	}

// ################# DATES #############################

	date_spans = gcnew array<DateSpan^>(date_spans_count);
	for(int i=0; i<date_spans->Length; i++)
	{
		date_spans[i] = ReadDateSpan(version, br);
	}

// ################# V89 DONT LEAVE LOCATIONS #############################

	if(version >= 89)
	{
		for(int m=0; m<quest_unknown_locations_1->count; m++)
		{
			quest_unknown_locations_1->spans[m] = ReadSpan(version, br);
		}

		for(int m=0; m<quest_valid_locations->count; m++)
		{
			quest_valid_locations->spans[m] = ReadSpan(version, br);
		}
	}

// ################# GROOVE AUDIT SCRIPTS #############################

	if(version >= 89)
	{
		for(int i=0; i<pq->script_info_count; i++)
		{
			pq->script_infos[i] = gcnew PQ_AuditScriptInfo();
			pq->script_infos[i]->id = br->ReadInt32();
			pq->script_infos[i]->unknown_1 = br->ReadInt32();
			pq->script_infos[i]->unknown_2 = br->ReadBytes(1);
		}

		for(int i=0; i<pq->script_count; i++)
		{
			pq->scripts[i] = gcnew PQ_AuditScript();
			pq->scripts[i]->name = br->ReadBytes(64);
			pq->scripts[i]->count = br->ReadInt32();
			pq->scripts[i]->id = br->ReadSingle();
			pq->scripts[i]->seperator = br->ReadBytes(4);
			pq->scripts[i]->reference_id = br->ReadSingle();
			pq->scripts[i]->code = br->ReadBytes(496);
		}

		for(int i=0; i<pq->chase_count; i++)
		{
			pq->chases[i] = gcnew PQ_AuditChase();
			pq->chases[i]->id_monster = br->ReadInt32();
			pq->chases[i]->amount_1 = br->ReadInt32();
			pq->chases[i]->amount_2 = br->ReadInt32();
			pq->chases[i]->amount_3 = br->ReadInt32();
		}

		for(int i=0; i<pq->leave_area->script_count; i++)
		{
			pq->leave_area->scripts[i] = gcnew PQ_AuditScript();
			pq->leave_area->scripts[i]->name = br->ReadBytes(64);
			pq->leave_area->scripts[i]->count = br->ReadInt32();
			pq->leave_area->scripts[i]->id = br->ReadSingle();
			pq->leave_area->scripts[i]->seperator = br->ReadBytes(4);
			pq->leave_area->scripts[i]->reference_id = br->ReadSingle();
			pq->leave_area->scripts[i]->code = br->ReadBytes(496);
		}

		for(int i=0; i<pq->leave_area->message_count; i++)
		{
			pq->leave_area->messages[i] = br->ReadBytes(128);
		}
	}

// ################# QUEST LOCATIONS #############################

	if(version >= 89)
	{
		for(int m=0; m<quest_trigger_locations->count; m++)
		{
			quest_trigger_locations->spans[m] = ReadSpan(version, br);
		}

		for(int m=0; m<required_reach_locations->count;m++)
		{
			required_reach_locations->spans[m] = ReadSpan(version, br);
		}

		for(int m=0; m<pq->leave_area->location->count; m++)
		{
			pq->leave_area->location->spans[m] = ReadSpan(version, br);
		}
	}

// ################# REQUIRED ITEMS #############################

	required_items = gcnew array<Item^>(required_items_count);
	for(int i=0; i<required_items->Length; i++)
	{
		required_items[i] = ReadItem(version, br);
	}

// ################# GIVEN ITEMS #############################

	given_items = gcnew array<Item^>(given_items_count);
	for(int i=0; i<given_items->Length; i++)
	{
		given_items[i] = ReadItem(version, br);
	}

// ################# TEAM MEMBERS #############################

	required_team_member_groups = gcnew array<TeamMembers^>(required_team_member_groups_count);
	for(int i=0; i<required_team_member_groups->Length; i++)
	{
		required_team_member_groups[i] = ReadTeamMembers(version, br);
	}

// ################# CHASE #############################

	required_chases = gcnew array<Chase^>(required_chases_count);
	for(int i=0; i<required_chases->Length; i++)
	{
		required_chases[i] = ReadChase(version, br);
	}

// ################# GET ITEMS #############################

	required_get_items = gcnew array<Item^>(required_get_items_count);
	for(int i=0; i<required_get_items->Length; i++)
	{
		required_get_items[i] = ReadItem(version, br);
	}

// ################# SUCCESS REWARDS #############################

	reward_success = ReadReward(version, br);

// ################# FAILED REWARDS #############################

	reward_failed = ReadReward(version, br);

// ################# TIMED REWARDS #############################

	rewards_timed_count = br->ReadInt32();
	rewards_timed_factors = gcnew array<float>(5);
	for(int i=0; i<rewards_timed_factors->Length; i++)
	{
		rewards_timed_factors[i] = br->ReadSingle();
	}
	rewards_timed = gcnew array<Reward^>(rewards_timed_count);
	for(int i=0; i<rewards_timed->Length; i++)
	{
		rewards_timed[i] = ReadReward(version, br);
	}

// ################# UNKNOWN REWARDS ??? #############################

	UNKNOWN_025 = br->ReadBytes(80); //REWARD_UNKNOWN = ReadReward(version, br);

// ################# CONVERSATION #############################

	conversation = gcnew Conversation();
	conversation->crypt_key = id;
	conversation->prompt_character_count = br->ReadInt32();
	conversation->prompt_text = br->ReadBytes(2*conversation->prompt_character_count);
	conversation->seperator = br->ReadBytes(8);
	conversation->general_character_count = br->ReadInt32();
	conversation->general_text = br->ReadBytes(2*conversation->general_character_count);
	conversation->dialogs = gcnew array<Dialog^>(5);
	for(int d=0; d<conversation->dialogs->Length; d++)
	{
		conversation->dialogs[d] = gcnew Dialog();
		conversation->dialogs[d]->crypt_key = id;
		conversation->dialogs[d]->unknown = br->ReadInt32();
		conversation->dialogs[d]->dialog_text = br->ReadBytes(128);
		conversation->dialogs[d]->question_count = br->ReadInt32();
		conversation->dialogs[d]->questions = gcnew array<Question^>(conversation->dialogs[d]->question_count);
		for(int q=0; q<conversation->dialogs[d]->questions->Length; q++)
		{
			conversation->dialogs[d]->questions[q] = gcnew Question();
			conversation->dialogs[d]->questions[q]->crypt_key = id;
			conversation->dialogs[d]->questions[q]->question_id = br->ReadInt32();
			conversation->dialogs[d]->questions[q]->previous_question = br->ReadInt32();
			conversation->dialogs[d]->questions[q]->question_character_count = br->ReadInt32();
			conversation->dialogs[d]->questions[q]->question_text = br->ReadBytes(2*conversation->dialogs[d]->questions[q]->question_character_count);
			conversation->dialogs[d]->questions[q]->answer_count = br->ReadInt32();
			conversation->dialogs[d]->questions[q]->answers = gcnew array<Answer^>(conversation->dialogs[d]->questions[q]->answer_count);
			for(int a=0; a<conversation->dialogs[d]->questions[q]->answer_count; a++)
			{
				conversation->dialogs[d]->questions[q]->answers[a] = gcnew Answer();
				conversation->dialogs[d]->questions[q]->answers[a]->crypt_key = id;
				conversation->dialogs[d]->questions[q]->answers[a]->question_link = br->ReadInt32();
				conversation->dialogs[d]->questions[q]->answers[a]->answer_text = br->ReadBytes(128);
				conversation->dialogs[d]->questions[q]->answers[a]->task_link = br->ReadInt32();
			}
		}
	}

// ################# ADD TREE-NODE #############################

// substring problem task 9442

	Drawing::Color c = Drawing::Color::White;
	String^ node = Name;

	if(node->StartsWith("^"))
	{
		try
		{
			c = Drawing::Color::FromArgb(int::Parse(node->Substring(1, 6), Globalization::NumberStyles::HexNumber));
			node = node->Substring(7);
		}
		catch(...)
		{
			c = Drawing::Color::White;
		}
	}

	nodes->Add(id.ToString() + " - " + node);
	nodes[nodes->Count-1]->ForeColor = c;

// ################# SUB TASKS #############################

	sub_quest_count = br->ReadInt32();
	sub_quests = gcnew array<Task^>(sub_quest_count);

	for(int i=0; i<sub_quest_count; i++)
	{
		sub_quests[i] = gcnew Task(version, br, (int)br->BaseStream->Position, nodes[nodes->Count-1]->Nodes);
	}
}