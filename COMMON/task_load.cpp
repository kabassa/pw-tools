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
		br->ReadBytes(4);
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
LocationSpan^ ReadLocationSpan(int version, BinaryReader^ br, bool reverse)
{
	LocationSpan^ location_span = gcnew LocationSpan();

	if(!reverse)
	{
		location_span->map_id = br->ReadInt32();
	}
	location_span->east = br->ReadSingle();
	location_span->bottom = br->ReadSingle();
	location_span->south = br->ReadSingle();
	location_span->west = br->ReadSingle();
	location_span->top = br->ReadSingle();
	location_span->north = br->ReadSingle();
	if(reverse)
	{
		location_span->map_id = br->ReadInt32();
	}

	return location_span;
}
Reward^ ReadReward(int version, BinaryReader^ br)
{
	int v79_Count_1 = 0;
	int v79_Count_2 = 0;
	int v79_Count_3 = 0;
	int v79_Count_4 = 0;
	int v79_Count_5 = 0;

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
		br->ReadInt32(); // Cupboard Slots
		br->ReadInt32(); // Wardrobe Slots
		br->ReadInt32(); // Account Stash Slots
	}

	reward->inventory_slots = br->ReadInt32();
	reward->petbag_slots = br->ReadInt32();
	reward->vigor = br->ReadInt32();
	reward->teleport = ReadLocation(version, br);
	reward->aiTrigger = br->ReadInt32();

	if(version <= 55)
	{
		reward->UNKNOWN_2 = gcnew array<unsigned char>(8);
		reward->UNKNOWN_2[0] = br->ReadByte();
		reward->UNKNOWN_2[1] = br->ReadByte();
		reward->UNKNOWN_2[2] = br->ReadByte();
	}
	else
	{
		reward->UNKNOWN_2 = br->ReadBytes(8);
	}

	reward->item_groups_count = br->ReadInt32();
	reward->SEPERATOR = br->ReadBytes(4);

	// Public Quest Rewards
	if(version >= 89)
	{
		v79_Count_1 = br->ReadInt32(); // public reward chases count
		br->ReadBytes(19);
		br->ReadInt32(); // New Quest ???
		br->ReadBytes(4);
		br->ReadInt32(); // Level ???
		br->ReadInt32(); // random contribution min
		br->ReadInt32(); // random contribution max
		br->ReadInt32(); // required reward contribution
		br->ReadBytes(8);
		v79_Count_2 = br->ReadInt32(); // public reward items count
		br->ReadBytes(4);
		v79_Count_3 = br->ReadInt32(); // public reward specials count
		br->ReadBytes(29);
		v79_Count_4 = br->ReadInt32(); // public reward scripts count
		br->ReadBytes(8);
		v79_Count_5 = br->ReadInt32(); // public reward messages count
		br->ReadBytes(4);
	}

	reward->item_groups = gcnew array<ItemGroup^>(reward->item_groups_count);

	for(int i=0; i<reward->item_groups->Length; i++)
	{
		reward->item_groups[i] = ReadItemGroup(version, br);
	}

	if(version >= 89)
	{
		if(v79_Count_1>0)
		{
			br->ReadBytes(1);
			br->ReadInt32();
			br->ReadBytes(1);
			for(int i=0; i<v79_Count_1; i++)
			{
				br->ReadInt32(); // Mob ID ???
				br->ReadInt32(); // Amount_1
				br->ReadSingle(); // Probability
				br->ReadInt32(); // Amount_2
			}
		}

		if(v79_Count_2>0)
		{
			br->ReadBytes(1);
			for(int i=0; i<v79_Count_2; i++)
			{
				br->ReadInt32();
				br->ReadInt32();
				br->ReadBytes(1);
				br->ReadInt32(); // Item ID
				br->ReadInt32();
				br->ReadBytes(4);
			}
		}

		if(v79_Count_3>0)
		{
			for(int i=0; i<v79_Count_3; i++)
			{
				br->ReadInt32();
				br->ReadInt32();
				br->ReadBytes(1);
			}
		}

		if(v79_Count_4>0)
		{
			for(int i=0; i<v79_Count_4; i++)
			{
				br->ReadBytes(576);
			}
		}

		if(v79_Count_5>0)
		{
			for(int i=0; i<v79_Count_5; i++)
			{
				br->ReadBytes(128);
			}
		}
	}

	return reward;
}

void Task::Load(int version, BinaryReader^ br, int stream_position, TreeNodeCollection^ nodes)
{
	br->BaseStream->Position = stream_position;

	int v89_Trigger_Location_Count;
	int v89_Required_Reach_Location_Count;
	int v89_Unknown_Location_1_Count;
	int v89_Unknown_Location_2_Count;
	int v89_Unknown_Location_3_Count;
	int v79_Public_Count_1; // Unknown Count
	int v79_Public_Count_2; // Scripts Count
	int v79_Public_Count_3; // Sub Scripts Count
	int v79_Public_Count_4; // Kills Count
	int v79_Public_Count_5; // Messages Count

// ################# GENERAL #############################

	id = br->ReadInt32();
	name = br->ReadBytes(60);
	author_mode = br->ReadBoolean();
	UNKNOWN_001a = br->ReadBytes(4);
	type = br->ReadInt32();
	time_limit = br->ReadInt32();

	if(version >= 89)
	{
		br->ReadBytes(2);
		ReadDate(version, br);
		br->ReadBytes(1);	
	}

	UNKNOWN_002 = br->ReadBytes(1);
	date_spans_count = br->ReadInt32();
	UNKNOWN_EVENT = br->ReadBytes(4);
	UNKNOWN_ZEROS = br->ReadBytes(8);

	if(version >= 89)
	{
		br->ReadBytes(12);
	}

	date_unknown = br->ReadBytes(8);
	UNKNOWN_FLAGS_1 = br->ReadBytes(4);

	if(version >= 89)
	{
		br->ReadBytes(4);
	}

	UNKNOWN_FLAGS_2 = br->ReadBytes(5);
	can_give_up = br->ReadBoolean();
	repeatable = br->ReadBoolean();
	repeatable_after_failure = br->ReadBoolean();
	UNKNOWN_004 = br->ReadBytes(8);

	if(version >= 89)
	{
		quest_trigger_location = gcnew LocationSpan();
		quest_trigger_location->map_id = br->ReadInt32();
		v89_Trigger_Location_Count = br->ReadInt32();
	}
	else
	{
		quest_trigger_location = ReadLocationSpan(version, br, false);
	}

	if(version >= 89)
	{
		br->ReadBytes(5);
		br->ReadInt32(); // unknown map id
		v89_Unknown_Location_1_Count = br->ReadInt32();
		br->ReadBytes(5);
		br->ReadInt32(); // unknown map id
		v89_Unknown_Location_2_Count = br->ReadInt32();
		br->ReadBytes(4);
	}

	UNKNOWN_005a_1 = br->ReadBytes(1);
	instant_teleport_location = ReadLocation(version, br);
	ai_trigger = br->ReadInt32();
	UNKNOWN_005a_3 = br->ReadBytes(3);

	if(version >= 89)
	{
		br->ReadBytes(2);
	}

	UNKNOWN_005b = br->ReadBytes(1);
	UNKNOWN_LEVEL = br->ReadInt32();
	UNKNOWN_005c = br->ReadBytes(2);
	quest_npc = br->ReadInt32();
	reward_npc = br->ReadInt32();
	UNKNOWN_006 = br->ReadBytes(4);

	if(version >= 89)
	{
		v79_Public_Count_1 = br->ReadInt32();
		br->ReadBytes(12);
		br->ReadInt32();
		br->ReadBytes(15);
		v79_Public_Count_2 = br->ReadInt32();
		br->ReadBytes(8);
		br->ReadBytes(1);
		br->ReadBytes(1);
		v79_Public_Count_4 = br->ReadInt32();
		br->ReadBytes(14);
	}

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
	UNKNOWN_011_1 = br->ReadBytes(11);
	required_gender = br->ReadInt32();
	UNKNOWN_011_2 = br->ReadBytes(1);
	required_occupations_count = br->ReadInt32();
	required_occupations = gcnew array<int>(8);
	for(int i=0; i<required_occupations->Length; i++)
	{
		required_occupations[i] = br->ReadInt32();
	}

	if(version >= 89)
	{
		br->ReadInt32(); // occupation 9
		br->ReadInt32(); // occupation 10
	}

	UNKNOWN_011_a2 = br->ReadBytes(5);

	if(version >= 89)
	{
		br->ReadBytes(19);
		ReadDate(version, br);
		br->ReadBytes(5);	
	}

	UNKNOWN_011_b = br->ReadBytes(7);
	required_quests_undone_count = br->ReadInt32();
	required_quests_undone = gcnew array<int>(5);
	for(int i=0; i<required_quests_undone->Length; i++)
	{
		required_quests_undone[i] = br->ReadInt32();
	}
	TEAM_MEMBER_REQUIREMENTS = br->ReadBytes(48);

	if(version >= 89)
	{
		br->ReadBytes(3);
	}

	required_team_member_groups_count = br->ReadInt32();
	required_team_member_groups_unknown = br->ReadBytes(4);
	UNKNOWN_012_a = br->ReadBytes(1);

	if(version >= 89)
	{
		br->ReadBytes(9);
		br->ReadInt32(); // Script ID
		br->ReadInt32();
		br->ReadInt32();
		br->ReadInt32();
		br->ReadBytes(20);
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
		br->ReadBytes(12);
	}

	if(version >= 89)
	{
		required_reach_location = gcnew LocationSpan();
		v89_Required_Reach_Location_Count = br->ReadInt32();
		required_reach_location->map_id = br->ReadInt32();
	}
	else
	{
		required_reach_location = ReadLocationSpan(version, br, true);
	}
	required_wait_time = br->ReadInt32();

	// At this place the v79 positions must be guessed due to leak of informations...

	if(version >= 89)
	{
		br->ReadBytes(4);
		br->ReadInt32(); // unknown map id
		v89_Unknown_Location_3_Count = br->ReadInt32();
		br->ReadInt32();
		br->ReadBytes(5);
		br->ReadInt32(); // ID
		br->ReadInt32();
		br->ReadInt32();
		br->ReadInt32();
		br->ReadBytes(20);
		v79_Public_Count_3 = br->ReadInt32();
		br->ReadBytes(4);
		br->ReadBytes(4);
		v79_Public_Count_5 = br->ReadInt32();
		br->ReadBytes(4);
	}

	// Need to checked if contains something != 0
	UNKNOWN_016_b = br->ReadBytes(8);
	UNKNOWN_016_c = br->ReadBytes(24);
	parent_quest = br->ReadInt32();
	previous_quest = br->ReadInt32();
	next_quest = br->ReadInt32();
	sub_quest_first = br->ReadInt32();

	if(version >= 89)
	{
		br->ReadBytes(5);
	}

	if(version >= 89)
	{
		for(int m=0; m<v89_Trigger_Location_Count; m++)
		{
			// use the first location span for v56
			if(m == 0)
			{
				quest_trigger_location->east = br->ReadSingle();
				quest_trigger_location->bottom = br->ReadSingle();
				quest_trigger_location->south = br->ReadSingle();
				quest_trigger_location->west = br->ReadSingle();
				quest_trigger_location->top = br->ReadSingle();
				quest_trigger_location->north = br->ReadSingle();
			}
			else
			{
				br->ReadBytes(24);
			}
		}

		for(int m=0; m<v89_Unknown_Location_1_Count; m++)
		{
			br->ReadBytes(24);
		}

		for(int m=0; m<v89_Unknown_Location_2_Count; m++)
		{
			br->ReadBytes(24);
		}

		for(int m=0; m<v89_Required_Reach_Location_Count;m++)
		{
			// use the first location span for v56
			if(m == 0)
			{
				required_reach_location->east = br->ReadSingle();
				required_reach_location->bottom = br->ReadSingle();
				required_reach_location->south = br->ReadSingle();
				required_reach_location->west = br->ReadSingle();
				required_reach_location->top = br->ReadSingle();
				required_reach_location->north = br->ReadSingle();
			}
			else
			{
				br->ReadBytes(24);
			}
		}

		for(int m=0; m<v89_Unknown_Location_3_Count; m++)
		{
			br->ReadBytes(24);
		}
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

// ################# GROOVE AUDIT SCRIPTS #############################

	if(version >= 89)
	{
		for(int i=0; i<v79_Public_Count_1; i++)
		{
			br->ReadInt32(); // Script ID
			br->ReadInt32(); // ?
			br->ReadBytes(1); // 
		}

		for(int i=0; i<v79_Public_Count_2; i++)
		{
			br->ReadBytes(64); // Text
			br->ReadInt32(); // Count
			br->ReadSingle(); // Script ID
			br->ReadBytes(4); // Seperator
			br->ReadSingle(); // Some kind of link?
			br->ReadBytes(496); // Code
		}

		for(int i=0; i<v79_Public_Count_4; i++)
		{
			br->ReadInt32(); // Mob ID
			br->ReadBytes(4); // Unknown
			br->ReadInt32(); // Amount ?
			br->ReadBytes(4); // Unknown
		}

		for(int i=0; i<v79_Public_Count_3; i++)
		{
			br->ReadBytes(64); // Text
			br->ReadInt32(); // Count
			br->ReadSingle(); // Script ID
			br->ReadBytes(4); // Seperator
			br->ReadSingle(); // Some kind of link?
			br->ReadBytes(496); // Code
		}

		for(int i=0; i<v79_Public_Count_5; i++)
		{
			br->ReadBytes(128); // Text
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