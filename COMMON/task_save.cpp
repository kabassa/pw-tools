#pragma once

#include "task.h"

void Task::Save(int version, BinaryWriter^ bw)
{

// ################# GENERAL #############################

	bw->Write(id);
	bw->Write(name);
	bw->Write(author_mode);
	bw->Write(UNKNOWN_001a);
	bw->Write(type);
	bw->Write(time_limit);
	bw->Write(UNKNOWN_002);
	bw->Write(date_spans_count);
	bw->Write(UNKNOWN_EVENT);
	bw->Write(UNKNOWN_ZEROS);
	bw->Write(date_unknown);
	bw->Write(UNKNOWN_FLAGS_1);
	bw->Write(UNKNOWN_FLAGS_2);
	bw->Write(can_give_up);
	bw->Write(repeatable);
	bw->Write(repeatable_after_failure);
	bw->Write(UNKNOWN_004);
	bw->Write(quest_trigger_location->map_id);
	bw->Write(quest_trigger_location->east);
	bw->Write(quest_trigger_location->bottom);
	bw->Write(quest_trigger_location->south);
	bw->Write(quest_trigger_location->west);
	bw->Write(quest_trigger_location->top);
	bw->Write(quest_trigger_location->north);
	bw->Write(UNKNOWN_005a_1);
	bw->Write(instant_teleport_location->map_id);
	bw->Write(instant_teleport_location->x);
	bw->Write(instant_teleport_location->altitude);
	bw->Write(instant_teleport_location->z);
	bw->Write(ai_trigger);
	bw->Write(UNKNOWN_005a_3);
	bw->Write(UNKNOWN_005b);
	bw->Write(UNKNOWN_LEVEL);
	bw->Write(UNKNOWN_005c);
	bw->Write(quest_npc);
	bw->Write(reward_npc);
	bw->Write(UNKNOWN_006);
	bw->Write(level_min);
	bw->Write(level_max);
	bw->Write(UNKNOWN_007);
	bw->Write(required_items_count);
	bw->Write(required_items_unknown);
	bw->Write(UNKNOWN_008_);
	bw->Write(given_items_count);
	bw->Write(GIVEN_UNKNOWN_INTEGERS);
	bw->Write(given_items_unknown);
	bw->Write(instant_pay_coins);
	bw->Write(UNKNOWN_009b);
	bw->Write(required_reputation);
	bw->Write(UNKNOWN_010);
	bw->Write(required_quests_done_count);
	for(int i=0; i<required_quests_done->Length; i++)
	{
		bw->Write(required_quests_done[i]);
	}
	bw->Write(UNKNOWN_011_1a);
	bw->Write(UNKNOWN_011_1b);
	bw->Write(required_gender);
	bw->Write(UNKNOWN_011_2);
	bw->Write(required_occupations_count);
	for(int i=0; i<required_occupations->Length; i++)
	{
		bw->Write(required_occupations[i]);
	}
	bw->Write(UNKNOWN_011_a2);
	bw->Write(UNKNOWN_011_b);
	bw->Write(required_quests_undone_count);
	for(int i=0; i<required_quests_undone->Length; i++)
	{
		bw->Write(required_quests_undone[i]);
	}
	bw->Write(required_blacksmith_level);
	bw->Write(required_tailor_level);
	bw->Write(required_craftsman_level);
	bw->Write(required_apothecary_level);
	bw->Write(TEAM_MEMBER_REQUIREMENT);
	bw->Write(required_team_member_groups_count);
	bw->Write(required_team_member_groups_unknown);
	bw->Write(UNKNOWN_012_a);
	bw->Write(UNKNOWN_012_b);
	bw->Write(required_chases_count);
	bw->Write(required_chases_unknown);
	bw->Write(required_get_items_count);
	bw->Write(required_get_items_unknown);
	bw->Write(required_coins);
	bw->Write(UNKNOWN_015);
	bw->Write(required_reach_location->east);
	bw->Write(required_reach_location->bottom);
	bw->Write(required_reach_location->south);
	bw->Write(required_reach_location->west);
	bw->Write(required_reach_location->top);
	bw->Write(required_reach_location->north);
	bw->Write(required_reach_location->map_id);
	bw->Write(required_wait_time);
	bw->Write(UNKNOWN_016_b);
	bw->Write(UNKNOWN_016_c);
	bw->Write(parent_quest);
	bw->Write(previous_quest);
	bw->Write(next_quest);
	bw->Write(sub_quest_first);
	if(author_mode)
	{
		bw->Write(author_text);
	}

// ################# DATES #############################

	for(int i=0; i<date_spans->Length; i++)
	{
		bw->Write(date_spans[i]->from->year);
		bw->Write(date_spans[i]->from->month);
		bw->Write(date_spans[i]->from->day);
		bw->Write(date_spans[i]->from->hour);
		bw->Write(date_spans[i]->from->minute);
		bw->Write(date_spans[i]->from->weekday);

		bw->Write(date_spans[i]->to->year);
		bw->Write(date_spans[i]->to->month);
		bw->Write(date_spans[i]->to->day);
		bw->Write(date_spans[i]->to->hour);
		bw->Write(date_spans[i]->to->minute);
		bw->Write(date_spans[i]->to->weekday);
	}

// ################# REQUIRED ITEMS #############################

	for(int i=0; i<required_items->Length; i++)
	{
		bw->Write(required_items[i]->id);
		bw->Write(required_items[i]->unknown);
		bw->Write(required_items[i]->amount);
		bw->Write(required_items[i]->probability);
	}

// ################# GIVEN ITEMS #############################

	for(int i=0; i<given_items->Length; i++)
	{
		bw->Write(given_items[i]->id);
		bw->Write(given_items[i]->unknown);
		bw->Write(given_items[i]->amount);
		bw->Write(given_items[i]->probability);
	}

// ################# TEAM MEMBERS #############################

	for(int i=0; i<required_team_member_groups->Length; i++)
	{
		bw->Write(required_team_member_groups[i]->level_min);
		bw->Write(required_team_member_groups[i]->level_max);
		bw->Write(required_team_member_groups[i]->unknown_1);
		bw->Write(required_team_member_groups[i]->unknown_2);
		bw->Write(required_team_member_groups[i]->unknown_3);
		bw->Write(required_team_member_groups[i]->amount_min);
		bw->Write(required_team_member_groups[i]->amount_max);
		bw->Write(required_team_member_groups[i]->quest);
	}

// ################# CHASE #############################

	for(int i=0; i<required_chases->Length; i++)
	{
		bw->Write(required_chases[i]->id_monster);
		bw->Write(required_chases[i]->amount_monster);
		bw->Write(required_chases[i]->id_drop);
		bw->Write(required_chases[i]->amount_drop);
		bw->Write(required_chases[i]->unknown_1);
		bw->Write(required_chases[i]->probability);
		bw->Write(required_chases[i]->unknown_2);
	}

// ################# GET ITEMS #############################

	for(int i=0; i<required_get_items->Length; i++)
	{
		bw->Write(required_get_items[i]->id);
		bw->Write(required_get_items[i]->unknown);
		bw->Write(required_get_items[i]->amount);
		bw->Write(required_get_items[i]->probability);
	}

// ################# SUCCESS REWARDS #############################

	bw->Write(reward_success->coins);
	bw->Write(reward_success->experience);
	bw->Write(reward_success->new_quest);
	bw->Write(reward_success->spirit);
	bw->Write(reward_success->reputation);
	bw->Write(reward_success->cultivation);
	bw->Write(reward_success->UNKNOWN_1);
	bw->Write(reward_success->storage_slots);
	bw->Write(reward_success->inventory_slots);
	bw->Write(reward_success->petbag_slots);
	bw->Write(reward_success->vigor);
	bw->Write(reward_success->teleport->map_id);
	bw->Write(reward_success->teleport->x);
	bw->Write(reward_success->teleport->altitude);
	bw->Write(reward_success->teleport->z);
	bw->Write(reward_success->aiTrigger);

if(version == 55)
{
	// Write first 3 Bytes of 8
	bw->Write(reward_success->UNKNOWN_2[0]);
	bw->Write(reward_success->UNKNOWN_2[1]);
	bw->Write(reward_success->UNKNOWN_2[2]);
}
else
{
	bw->Write(reward_success->UNKNOWN_2);
}

	bw->Write(reward_success->item_groups_count);
	bw->Write(reward_success->SEPERATOR);

	for(int i=0; i<reward_success->item_groups->Length; i++)
	{
		bw->Write(reward_success->item_groups[i]->unknown);
		bw->Write(reward_success->item_groups[i]->items_count);
		for(int n=0; n<reward_success->item_groups[i]->items->Length; n++)
		{
			bw->Write(reward_success->item_groups[i]->items[n]->id);
			bw->Write(reward_success->item_groups[i]->items[n]->unknown);
			bw->Write(reward_success->item_groups[i]->items[n]->amount);
			bw->Write(reward_success->item_groups[i]->items[n]->probability);
		}
	}

// ################# FAILED REWARDS #############################

	bw->Write(reward_failed->coins);
	bw->Write(reward_failed->experience);
	bw->Write(reward_failed->new_quest);
	bw->Write(reward_failed->spirit);
	bw->Write(reward_failed->reputation);
	bw->Write(reward_failed->cultivation);
	bw->Write(reward_failed->UNKNOWN_1);
	bw->Write(reward_failed->storage_slots);
	bw->Write(reward_failed->inventory_slots);
	bw->Write(reward_failed->petbag_slots);
	bw->Write(reward_failed->vigor);
	bw->Write(reward_failed->teleport->map_id);
	bw->Write(reward_failed->teleport->x);
	bw->Write(reward_failed->teleport->altitude);
	bw->Write(reward_failed->teleport->z);
	bw->Write(reward_failed->aiTrigger);

if(version == 55)
{
	// Write first 3 Bytes of 8
	bw->Write(reward_failed->UNKNOWN_2[0]);
	bw->Write(reward_failed->UNKNOWN_2[1]);
	bw->Write(reward_failed->UNKNOWN_2[2]);
}
else
{
	bw->Write(reward_failed->UNKNOWN_2);
}

	bw->Write(reward_failed->item_groups_count);
	bw->Write(reward_failed->SEPERATOR);

	for(int i=0; i<reward_failed->item_groups->Length; i++)
	{
		bw->Write(reward_failed->item_groups[i]->unknown);
		bw->Write(reward_failed->item_groups[i]->items_count);
		for(int n=0; n<reward_failed->item_groups[i]->items->Length; n++)
		{
			bw->Write(reward_failed->item_groups[i]->items[n]->id);
			bw->Write(reward_failed->item_groups[i]->items[n]->unknown);
			bw->Write(reward_failed->item_groups[i]->items[n]->amount);
			bw->Write(reward_failed->item_groups[i]->items[n]->probability);
		}
	}

// ################# TIMED REWARDS #############################

		bw->Write(rewards_timed_count);
		for(int i=0; i<rewards_timed_factors->Length; i++)
		{
			bw->Write(rewards_timed_factors[i]);
		}

		for(int i=0; i<rewards_timed->Length; i++)
		{
			bw->Write(rewards_timed[i]->coins);
			bw->Write(rewards_timed[i]->experience);
			bw->Write(rewards_timed[i]->new_quest);
			bw->Write(rewards_timed[i]->spirit);
			bw->Write(rewards_timed[i]->reputation);
			bw->Write(rewards_timed[i]->cultivation);
			bw->Write(rewards_timed[i]->UNKNOWN_1);
			bw->Write(rewards_timed[i]->storage_slots);
			bw->Write(rewards_timed[i]->inventory_slots);
			bw->Write(rewards_timed[i]->petbag_slots);
			bw->Write(rewards_timed[i]->vigor);
			bw->Write(rewards_timed[i]->teleport->map_id);
			bw->Write(rewards_timed[i]->teleport->x);
			bw->Write(rewards_timed[i]->teleport->altitude);
			bw->Write(rewards_timed[i]->teleport->z);
			bw->Write(rewards_timed[i]->aiTrigger);

if(version == 55)
{
	// Write first 3 Bytes of 8
	bw->Write(rewards_timed[i]->UNKNOWN_2[0]);
	bw->Write(rewards_timed[i]->UNKNOWN_2[1]);
	bw->Write(rewards_timed[i]->UNKNOWN_2[2]);
}
else
{
	bw->Write(rewards_timed[i]->UNKNOWN_2);
}

			bw->Write(rewards_timed[i]->item_groups_count);
			bw->Write(rewards_timed[i]->SEPERATOR);

			for(int m=0; m<rewards_timed[i]->item_groups->Length; m++)
			{
				bw->Write(rewards_timed[i]->item_groups[m]->unknown);
				bw->Write(rewards_timed[i]->item_groups[m]->items_count);
				for(int n=0; n<rewards_timed[i]->item_groups[m]->items->Length; n++)
				{
					bw->Write(rewards_timed[i]->item_groups[m]->items[n]->id);
					bw->Write(rewards_timed[i]->item_groups[m]->items[n]->unknown);
					bw->Write(rewards_timed[i]->item_groups[m]->items[n]->amount);
					bw->Write(rewards_timed[i]->item_groups[m]->items[n]->probability);
				}
			}
		}

// ################# UNKNOWN REWARDS #############################

	bw->Write(UNKNOWN_025);

// ################# CONVERSATION #############################

	bw->Write(conversation->prompt_character_count);
	bw->Write(conversation->prompt_text);
	bw->Write(conversation->seperator);
	bw->Write(conversation->general_character_count);
	bw->Write(conversation->general_text);
	for(int d=0; d<conversation->dialogs->Length; d++)
	{
		bw->Write(conversation->dialogs[d]->unknown);
		bw->Write(conversation->dialogs[d]->dialog_text);
		bw->Write(conversation->dialogs[d]->question_count);
		for(int q=0; q<conversation->dialogs[d]->questions->Length; q++)
		{
			bw->Write(conversation->dialogs[d]->questions[q]->question_id);
			bw->Write(conversation->dialogs[d]->questions[q]->previous_question);
			bw->Write(conversation->dialogs[d]->questions[q]->question_character_count);
			bw->Write(conversation->dialogs[d]->questions[q]->question_text);
			bw->Write(conversation->dialogs[d]->questions[q]->answer_count);
			for(int a=0; a<conversation->dialogs[d]->questions[q]->answer_count; a++)
			{
				bw->Write(conversation->dialogs[d]->questions[q]->answers[a]->question_link);
				bw->Write(conversation->dialogs[d]->questions[q]->answers[a]->answer_text);
				bw->Write(conversation->dialogs[d]->questions[q]->answers[a]->task_link);
			}
		}
	}

// ################# SUB TASKS #############################

	bw->Write(sub_quest_count);

	for(int i=0; i<sub_quest_count; i++)
	{
		sub_quests[i]->Save(version, bw);
	}
}