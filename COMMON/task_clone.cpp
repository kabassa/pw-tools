#pragma once

#include "task.h"

Task^ Task::Clone()
{
	Task^ result = gcnew Task();
	result->id = this->id;
	result->Name = this->Name; // clone this array, no pointers !!!
	result->author_mode = this->author_mode;
	result->UNKNOWN_001a = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_001a));
	result->type = this->type;
	result->time_limit = this->time_limit;
	result->UNKNOWN_002 = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_002));
	result->date_spans_count = this->date_spans_count;
	result->UNKNOWN_EVENT = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_EVENT));
	result->UNKNOWN_ZEROS = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_ZEROS));
	result->date_unknown = HexString_to_ByteArray(ByteArray_to_HexString(this->date_unknown));
	result->UNKNOWN_FLAGS_1 = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_FLAGS_1));
	result->UNKNOWN_FLAGS_2 = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_FLAGS_2));
	result->can_give_up = this->can_give_up;
	result->repeatable = this->repeatable;
	result->repeatable_after_failure = this->repeatable_after_failure;
	result->UNKNOWN_004 = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_004));
	/*
	result->quest_trigger_location = gcnew LocationSpan();
	result->quest_trigger_location->map_id = this->quest_trigger_location->map_id;
	result->quest_trigger_location->north = this->quest_trigger_location->north;
	result->quest_trigger_location->south = this->quest_trigger_location->south;
	result->quest_trigger_location->west = this->quest_trigger_location->west;
	result->quest_trigger_location->east = this->quest_trigger_location->east;
	result->quest_trigger_location->top = this->quest_trigger_location->top;
	result->quest_trigger_location->bottom = this->quest_trigger_location->bottom;
	*/
	result->UNKNOWN_005a_1 = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_005a_1));
	result->instant_teleport_location = gcnew Location();
	result->instant_teleport_location->map_id = this->instant_teleport_location->map_id;
	result->instant_teleport_location->x = this->instant_teleport_location->x;
	result->instant_teleport_location->altitude = this->instant_teleport_location->altitude;
	result->instant_teleport_location->z = this->instant_teleport_location->z;
	result->ai_trigger = this->ai_trigger;
	result->UNKNOWN_005a_3 = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_005a_3));
	result->UNKNOWN_005b = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_005b));
	result->UNKNOWN_LEVEL = this->UNKNOWN_LEVEL;
	result->UNKNOWN_005c = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_005c));
	result->quest_npc = this->quest_npc;
	result->reward_npc = this->reward_npc;
	result->UNKNOWN_006 = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_006));
	result->level_min = this->level_min;
	result->level_max = this->level_max;
	result->UNKNOWN_007 = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_007));
	result->required_items_count = this->required_items_count;
	result->required_items_unknown = HexString_to_ByteArray(ByteArray_to_HexString(this->required_items_unknown));
	result->UNKNOWN_008_ = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_008_));
	result->given_items_count = this->given_items_count;
	result->GIVEN_UNKNOWN_INTEGERS = HexString_to_ByteArray(ByteArray_to_HexString(this->GIVEN_UNKNOWN_INTEGERS));
	result->given_items_unknown = HexString_to_ByteArray(ByteArray_to_HexString(this->given_items_unknown));
	result->instant_pay_coins = this->instant_pay_coins;
	result->UNKNOWN_009b = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_009b));
	result->required_reputation = this->required_reputation;
	result->UNKNOWN_010 = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_010));
	result->required_quests_done_count = this->required_quests_done_count;
	result->required_quests_done = gcnew array<int>(this->required_quests_done->Length);
	for(int i=0; i<this->required_quests_done->Length; i++)
	{
		result->required_quests_done[i] = this->required_quests_done[i];
	}
	result->UNKNOWN_011_1a = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_011_1a));
	result->UNKNOWN_011_1b = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_011_1b));
	result->required_gender = this->required_gender;
	result->UNKNOWN_011_2 = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_011_2));
	result->required_occupations_count = this->required_occupations_count;
	result->required_occupations = gcnew array<int>(this->required_occupations->Length);
	for(int i=0; i<this->required_occupations->Length; i++)
	{
		result->required_occupations[i] = this->required_occupations[i];
	}
	result->UNKNOWN_011_a2 = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_011_a2));
	result->UNKNOWN_011_b = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_011_b));
	result->required_quests_undone_count = this->required_quests_undone_count;
	result->required_quests_undone = gcnew array<int>(this->required_quests_undone->Length);
	for(int i=0; i<this->required_quests_undone->Length; i++)
	{
		result->required_quests_undone[i] = this->required_quests_undone[i];
	}
	result->required_blacksmith_level = this->required_blacksmith_level;
	result->required_tailor_level = this->required_tailor_level;
	result->required_craftsman_level = this->required_craftsman_level;
	result->required_apothecary_level = this->required_apothecary_level;
	result->TEAM_MEMBER_REQUIREMENT = HexString_to_ByteArray(ByteArray_to_HexString(this->TEAM_MEMBER_REQUIREMENT));
	result->required_team_member_groups_count = this->required_team_member_groups_count;
	result->required_team_member_groups_unknown = this->required_team_member_groups_unknown;
	result->UNKNOWN_012_a = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_012_a));
	result->UNKNOWN_012_b = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_012_b));
	result->required_chases_count = this->required_chases_count;
	result->required_chases_unknown = HexString_to_ByteArray(ByteArray_to_HexString(this->required_chases_unknown));
	result->required_get_items_count = this->required_get_items_count;
	result->required_get_items_unknown = HexString_to_ByteArray(ByteArray_to_HexString(this->required_get_items_unknown));
	result->required_coins = this->required_coins;
	result->UNKNOWN_015 = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_015));
	/*
	result->required_reach_location = gcnew LocationSpan();
	result->required_reach_location->map_id = this->required_reach_location->map_id;
	result->required_reach_location->north = this->required_reach_location->north;
	result->required_reach_location->south = this->required_reach_location->south;
	result->required_reach_location->west = this->required_reach_location->west;
	result->required_reach_location->east = this->required_reach_location->east;
	result->required_reach_location->top = this->required_reach_location->top;
	result->required_reach_location->bottom = this->required_reach_location->bottom;
	*/
	result->required_wait_time = this->required_wait_time;
	result->UNKNOWN_016_b = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_016_b));
	result->UNKNOWN_016_c = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_016_c));
	result->parent_quest = this->parent_quest;
	result->previous_quest = this->previous_quest;
	result->next_quest = this->next_quest;
	result->sub_quest_first = this->sub_quest_first;
	result->AuthorText = this->AuthorText;

// ################# DATES #############################

	result->date_spans = gcnew array<DateSpan^>(this->date_spans_count);
	for(int i=0; i<this->date_spans_count; i++)
	{
		result->date_spans[i] = gcnew DateSpan();
		result->date_spans[i]->from = gcnew Date();
		result->date_spans[i]->from->year = this->date_spans[i]->from->year;
		result->date_spans[i]->from->month = this->date_spans[i]->from->month;
		result->date_spans[i]->from->day = this->date_spans[i]->from->day;
		result->date_spans[i]->from->hour = this->date_spans[i]->from->hour;
		result->date_spans[i]->from->minute = this->date_spans[i]->from->minute;
		result->date_spans[i]->from->weekday = this->date_spans[i]->from->weekday;
		result->date_spans[i]->to = gcnew Date();
		result->date_spans[i]->to->year = this->date_spans[i]->to->year;
		result->date_spans[i]->to->month = this->date_spans[i]->to->month;
		result->date_spans[i]->to->day = this->date_spans[i]->to->day;
		result->date_spans[i]->to->hour = this->date_spans[i]->to->hour;
		result->date_spans[i]->to->minute = this->date_spans[i]->to->minute;
		result->date_spans[i]->to->weekday = this->date_spans[i]->to->weekday;
	}

// ################# REQUIRED ITEMS #############################

	result->required_items = gcnew array<Item^>(this->required_items_count);
	for(int i=0; i<this->required_items_count; i++)
	{
		result->required_items[i] = gcnew Item();
		result->required_items[i]->id = this->required_items[i]->id;
		result->required_items[i]->amount = this->required_items[i]->amount;
		result->required_items[i]->unknown = this->required_items[i]->unknown;
		result->required_items[i]->probability = this->required_items[i]->probability;
	}

// ################# GIVEN ITEMS #############################

	result->given_items = gcnew array<Item^>(this->given_items_count);
	for(int i=0; i<this->given_items_count; i++)
	{
		result->given_items[i] = gcnew Item();
		result->given_items[i]->id = this->given_items[i]->id;
		result->given_items[i]->amount = this->given_items[i]->amount;
		result->given_items[i]->unknown = this->given_items[i]->unknown;
		result->given_items[i]->probability = this->given_items[i]->probability;
	}

// ################# TEAM MEMBERS #############################

	result->required_team_member_groups = gcnew array<TeamMembers^>(this->required_team_member_groups_count);
	for(int i=0; i<this->required_team_member_groups_count; i++)
	{
		result->required_team_member_groups[i] = gcnew TeamMembers();
		result->required_team_member_groups[i]->amount_min = this->required_team_member_groups[i]->amount_min;
		result->required_team_member_groups[i]->amount_max = this->required_team_member_groups[i]->amount_max;
		result->required_team_member_groups[i]->level_min = this->required_team_member_groups[i]->level_min;
		result->required_team_member_groups[i]->level_max = this->required_team_member_groups[i]->level_max;
		result->required_team_member_groups[i]->quest = this->required_team_member_groups[i]->quest;
		result->required_team_member_groups[i]->unknown_1 = this->required_team_member_groups[i]->unknown_1;
		result->required_team_member_groups[i]->unknown_2 = this->required_team_member_groups[i]->unknown_2;
		result->required_team_member_groups[i]->unknown_3 = this->required_team_member_groups[i]->unknown_3;
	}

// ################# CHASE #############################

	result->required_chases = gcnew array<Chase^>(this->required_chases_count);
	for(int i=0; i<this->required_chases_count; i++)
	{
		result->required_chases[i] = gcnew Chase();
		result->required_chases[i]->id_monster = this->required_chases[i]->id_monster;
		result->required_chases[i]->amount_monster = this->required_chases[i]->amount_monster;
		result->required_chases[i]->unknown_1 = this->required_chases[i]->unknown_1;
		result->required_chases[i]->id_drop = this->required_chases[i]->id_drop;
		result->required_chases[i]->amount_drop = this->required_chases[i]->amount_drop;
		result->required_chases[i]->unknown_2 = this->required_chases[i]->unknown_2;
		result->required_chases[i]->probability = this->required_chases[i]->probability;
	}

// ################# GET ITEMS #############################

	result->required_get_items = gcnew array<Item^>(this->required_get_items_count);
	for(int i=0; i<this->required_get_items_count; i++)
	{
		result->required_get_items[i] = gcnew Item();
		result->required_get_items[i]->id = this->required_get_items[i]->id;
		result->required_get_items[i]->amount = this->required_get_items[i]->amount;
		result->required_get_items[i]->unknown = this->required_get_items[i]->unknown;
		result->required_get_items[i]->probability = this->required_get_items[i]->probability;
	}

// ################# SUCCESS REWARDS #############################

	result->reward_success = gcnew Reward();
	result->reward_success->coins = this->reward_success->coins;
	result->reward_success->experience = this->reward_success->experience;
	result->reward_success->spirit = this->reward_success->spirit;
	result->reward_success->reputation = this->reward_success->reputation;
	result->reward_success->new_quest = this->reward_success->new_quest;
	result->reward_success->cultivation = this->reward_success->cultivation;
	result->reward_success->UNKNOWN_1 = this->reward_success->UNKNOWN_1;
	result->reward_success->storage_slots = this->reward_success->storage_slots;
	result->reward_success->inventory_slots = this->reward_success->inventory_slots;
	result->reward_success->petbag_slots = this->reward_success->petbag_slots;
	result->reward_success->vigor = this->reward_success->vigor;
	result->reward_success->teleport = gcnew Location();
	result->reward_success->teleport->map_id = this->reward_success->teleport->map_id;
	result->reward_success->teleport->x = this->reward_success->teleport->x;
	result->reward_success->teleport->altitude = this->reward_success->teleport->altitude;
	result->reward_success->teleport->z = this->reward_success->teleport->z;
	result->reward_success->aiTrigger = this->reward_success->aiTrigger;
	result->reward_success->UNKNOWN_2a = HexString_to_ByteArray(ByteArray_to_HexString(this->reward_success->UNKNOWN_2a));
	result->reward_success->UNKNOWN_2b = HexString_to_ByteArray(ByteArray_to_HexString(this->reward_success->UNKNOWN_2b));
	result->reward_success->item_groups_count = this->reward_success->item_groups_count;
	result->reward_success->SEPERATOR = HexString_to_ByteArray(ByteArray_to_HexString(this->reward_success->SEPERATOR));
	result->reward_success->item_groups = gcnew array<ItemGroup^>(this->reward_success->item_groups_count);
	for(int g=0; g<this->reward_success->item_groups_count; g++)
	{
		result->reward_success->item_groups[g] = gcnew ItemGroup();
		result->reward_success->item_groups[g]->unknown = this->reward_success->item_groups[g]->unknown;
		result->reward_success->item_groups[g]->items_count = this->reward_success->item_groups[g]->items_count;
		result->reward_success->item_groups[g]->items = gcnew array<Item^>(this->reward_success->item_groups[g]->items_count);
		for(int i=0; i<this->reward_success->item_groups[g]->items_count; i++)
		{
			result->reward_success->item_groups[g]->items[i] = gcnew Item();
			result->reward_success->item_groups[g]->items[i]->id = this->reward_success->item_groups[g]->items[i]->id;
			result->reward_success->item_groups[g]->items[i]->amount = this->reward_success->item_groups[g]->items[i]->amount;
			result->reward_success->item_groups[g]->items[i]->unknown = this->reward_success->item_groups[g]->items[i]->unknown;
			result->reward_success->item_groups[g]->items[i]->probability = this->reward_success->item_groups[g]->items[i]->probability;
		}
	}

// ################# FAILED REWARDS #############################

	result->reward_failed = gcnew Reward();
	result->reward_failed->coins = this->reward_failed->coins;
	result->reward_failed->experience = this->reward_failed->experience;
	result->reward_failed->spirit = this->reward_failed->spirit;
	result->reward_failed->reputation = this->reward_failed->reputation;
	result->reward_failed->new_quest = this->reward_failed->new_quest;
	result->reward_failed->cultivation = this->reward_failed->cultivation;
	result->reward_failed->UNKNOWN_1 = this->reward_failed->UNKNOWN_1;
	result->reward_failed->storage_slots = this->reward_failed->storage_slots;
	result->reward_failed->inventory_slots = this->reward_failed->inventory_slots;
	result->reward_failed->petbag_slots = this->reward_failed->petbag_slots;
	result->reward_failed->vigor = this->reward_failed->vigor;
	result->reward_failed->teleport = gcnew Location();
	result->reward_failed->teleport->map_id = this->reward_failed->teleport->map_id;
	result->reward_failed->teleport->x = this->reward_failed->teleport->x;
	result->reward_failed->teleport->altitude = this->reward_failed->teleport->altitude;
	result->reward_failed->teleport->z = this->reward_failed->teleport->z;
	result->reward_failed->aiTrigger = this->reward_failed->aiTrigger;
	result->reward_failed->UNKNOWN_2a = HexString_to_ByteArray(ByteArray_to_HexString(this->reward_failed->UNKNOWN_2a));
	result->reward_failed->UNKNOWN_2b = HexString_to_ByteArray(ByteArray_to_HexString(this->reward_failed->UNKNOWN_2b));
	result->reward_failed->item_groups_count = this->reward_failed->item_groups_count;
	result->reward_failed->SEPERATOR = HexString_to_ByteArray(ByteArray_to_HexString(this->reward_failed->SEPERATOR));
	result->reward_failed->item_groups = gcnew array<ItemGroup^>(this->reward_failed->item_groups_count);
	for(int g=0; g<this->reward_failed->item_groups_count; g++)
	{
		result->reward_failed->item_groups[g] = gcnew ItemGroup();
		result->reward_failed->item_groups[g]->unknown = this->reward_failed->item_groups[g]->unknown;
		result->reward_failed->item_groups[g]->items_count = this->reward_failed->item_groups[g]->items_count;
		result->reward_failed->item_groups[g]->items = gcnew array<Item^>(this->reward_failed->item_groups[g]->items_count);
		for(int i=0; i<this->reward_failed->item_groups[g]->items_count; i++)
		{
			result->reward_failed->item_groups[g]->items[i] = gcnew Item();
			result->reward_failed->item_groups[g]->items[i]->id = this->reward_failed->item_groups[g]->items[i]->id;
			result->reward_failed->item_groups[g]->items[i]->amount = this->reward_failed->item_groups[g]->items[i]->amount;
			result->reward_failed->item_groups[g]->items[i]->unknown = this->reward_failed->item_groups[g]->items[i]->unknown;
			result->reward_failed->item_groups[g]->items[i]->probability = this->reward_failed->item_groups[g]->items[i]->probability;
		}
	}

// ################# TIMED REWARDS #############################

	result->rewards_timed_count = this->rewards_timed_count;
	result->rewards_timed_factors = gcnew array<float>(this->rewards_timed_factors->Length);
	for(int i=0; i<this->rewards_timed_factors->Length; i++)
	{
		result->rewards_timed_factors[i] = this->rewards_timed_factors[i];
	}

	result->rewards_timed = gcnew array<Reward^>(this->rewards_timed_count);
	for(int r=0; r<this->rewards_timed_count; r++)
	{
		result->rewards_timed[r] = gcnew Reward();
		result->rewards_timed[r]->coins = this->rewards_timed[r]->coins;
		result->rewards_timed[r]->experience = this->rewards_timed[r]->experience;
		result->rewards_timed[r]->spirit = this->rewards_timed[r]->spirit;
		result->rewards_timed[r]->reputation = this->rewards_timed[r]->reputation;
		result->rewards_timed[r]->new_quest = this->rewards_timed[r]->new_quest;
		result->rewards_timed[r]->cultivation = this->rewards_timed[r]->cultivation;
		result->rewards_timed[r]->UNKNOWN_1 = this->rewards_timed[r]->UNKNOWN_1;
		result->rewards_timed[r]->storage_slots = this->rewards_timed[r]->storage_slots;
		result->rewards_timed[r]->inventory_slots = this->rewards_timed[r]->inventory_slots;
		result->rewards_timed[r]->petbag_slots = this->rewards_timed[r]->petbag_slots;
		result->rewards_timed[r]->vigor = this->rewards_timed[r]->vigor;
		result->rewards_timed[r]->teleport = gcnew Location();
		result->rewards_timed[r]->teleport->map_id = this->rewards_timed[r]->teleport->map_id;
		result->rewards_timed[r]->teleport->x = this->rewards_timed[r]->teleport->x;
		result->rewards_timed[r]->teleport->altitude = this->rewards_timed[r]->teleport->altitude;
		result->rewards_timed[r]->teleport->z = this->rewards_timed[r]->teleport->z;
		result->rewards_timed[r]->aiTrigger = this->rewards_timed[r]->aiTrigger;
		result->rewards_timed[r]->UNKNOWN_2a = HexString_to_ByteArray(ByteArray_to_HexString(this->rewards_timed[r]->UNKNOWN_2a));
		result->rewards_timed[r]->UNKNOWN_2b = HexString_to_ByteArray(ByteArray_to_HexString(this->rewards_timed[r]->UNKNOWN_2b));
		result->rewards_timed[r]->item_groups_count = this->rewards_timed[r]->item_groups_count;
		result->rewards_timed[r]->SEPERATOR = HexString_to_ByteArray(ByteArray_to_HexString(this->rewards_timed[r]->SEPERATOR));
		result->rewards_timed[r]->item_groups = gcnew array<ItemGroup^>(this->rewards_timed[r]->item_groups_count);
		for(int g=0; g<this->rewards_timed[r]->item_groups_count; g++)
		{
			result->rewards_timed[r]->item_groups[g] = gcnew ItemGroup();
			result->rewards_timed[r]->item_groups[g]->unknown = this->rewards_timed[r]->item_groups[g]->unknown;
			result->rewards_timed[r]->item_groups[g]->items_count = this->rewards_timed[r]->item_groups[g]->items_count;
			result->rewards_timed[r]->item_groups[g]->items = gcnew array<Item^>(this->rewards_timed[r]->item_groups[g]->items_count);
			for(int i=0; i<this->rewards_timed[r]->item_groups[g]->items_count; i++)
			{
				result->rewards_timed[r]->item_groups[g]->items[i] = gcnew Item();
				result->rewards_timed[r]->item_groups[g]->items[i]->id = this->rewards_timed[r]->item_groups[g]->items[i]->id;
				result->rewards_timed[r]->item_groups[g]->items[i]->amount = this->rewards_timed[r]->item_groups[g]->items[i]->amount;
				result->rewards_timed[r]->item_groups[g]->items[i]->unknown = this->rewards_timed[r]->item_groups[g]->items[i]->unknown;
				result->rewards_timed[r]->item_groups[g]->items[i]->probability = this->rewards_timed[r]->item_groups[g]->items[i]->probability;
			}
		}
	}

// ################# UNKNOWN REWARDS ??? #############################

	result->UNKNOWN_025 = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_025));

// ################# CONVERSATION #############################

	result->conversation = gcnew Conversation();
	result->conversation->crypt_key = this->conversation->crypt_key;
	result->conversation->PromptText = this->conversation->PromptText;
	result->conversation->seperator = HexString_to_ByteArray(ByteArray_to_HexString(this->conversation->seperator));
	result->conversation->GeneralText = this->conversation->GeneralText;
	result->conversation->dialogs = gcnew array<Dialog^>(this->conversation->dialogs->Length);
	for(int d=0; d<this->conversation->dialogs->Length; d++)
	{
		result->conversation->dialogs[d] = gcnew Dialog();
		result->conversation->dialogs[d]->crypt_key = this->conversation->dialogs[d]->crypt_key;
		result->conversation->dialogs[d]->DialogText = this->conversation->dialogs[d]->DialogText;
		result->conversation->dialogs[d]->unknown = this->conversation->dialogs[d]->unknown;
		result->conversation->dialogs[d]->question_count = this->conversation->dialogs[d]->question_count;
		result->conversation->dialogs[d]->questions = gcnew array<Question^>(this->conversation->dialogs[d]->question_count);
		for(int q=0; q<this->conversation->dialogs[d]->question_count; q++)
		{
			result->conversation->dialogs[d]->questions[q] = gcnew Question();
			result->conversation->dialogs[d]->questions[q]->crypt_key = this->conversation->dialogs[d]->questions[q]->crypt_key;
			result->conversation->dialogs[d]->questions[q]->QuestionText = this->conversation->dialogs[d]->questions[q]->QuestionText;
			result->conversation->dialogs[d]->questions[q]->question_id = this->conversation->dialogs[d]->questions[q]->question_id;
			result->conversation->dialogs[d]->questions[q]->previous_question = this->conversation->dialogs[d]->questions[q]->previous_question;
			result->conversation->dialogs[d]->questions[q]->answer_count = this->conversation->dialogs[d]->questions[q]->answer_count;
			result->conversation->dialogs[d]->questions[q]->answers = gcnew array<Answer^>(this->conversation->dialogs[d]->questions[q]->answer_count);
			for(int a=0; a<this->conversation->dialogs[d]->questions[q]->answer_count; a++)
			{
				result->conversation->dialogs[d]->questions[q]->answers[a] = gcnew Answer();
				result->conversation->dialogs[d]->questions[q]->answers[a]->crypt_key = this->conversation->dialogs[d]->questions[q]->answers[a]->crypt_key;
				result->conversation->dialogs[d]->questions[q]->answers[a]->AnswerText = this->conversation->dialogs[d]->questions[q]->answers[a]->AnswerText;
				result->conversation->dialogs[d]->questions[q]->answers[a]->question_link = this->conversation->dialogs[d]->questions[q]->answers[a]->question_link;
				result->conversation->dialogs[d]->questions[q]->answers[a]->task_link = this->conversation->dialogs[d]->questions[q]->answers[a]->task_link;
			}
		}
	}

// ################# SUB TASKS #############################

	result->sub_quest_count = this->sub_quest_count;

	result->sub_quests = gcnew array<Task^>(this->sub_quest_count);
	for(int i=0; i<this->sub_quest_count; i++)
	{
		result->sub_quests[i] = this->sub_quests[i]->Clone();
	}


	return result;
}