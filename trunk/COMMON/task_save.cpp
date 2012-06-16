#pragma once

#include "task.h"

void WriteDate(int version, BinaryWriter^ bw, Date^ date)
{
	bw->Write(date->year);
	bw->Write(date->month);
	bw->Write(date->day);
	bw->Write(date->hour);
	bw->Write(date->minute);
	bw->Write(date->weekday);
}

void WriteDateSpan(int version, BinaryWriter^ bw, DateSpan^ date_span)
{
	WriteDate(version, bw, date_span->from);
	WriteDate(version, bw, date_span->to);
}

void WriteItem(int version, BinaryWriter^ bw, Item^ item)
{
	bw->Write(item->id);
	bw->Write(item->unknown);
	bw->Write(item->amount);
	bw->Write(item->probability);

	if(version >= 89)
	{
		bw->Write(item->expiration);
	}
}

void WriteItemGroup(int version, BinaryWriter^ bw, ItemGroup^ item_group)
{
	bw->Write(item_group->unknown);
	bw->Write(item_group->items_count);
	for(int n=0; n<item_group->items->Length; n++)
	{
		WriteItem(version, bw, item_group->items[n]);
	}
}

void WriteTeamMembers(int version, BinaryWriter^ bw, TeamMembers^ team_member_group)
{
	bw->Write(team_member_group->level_min);
	bw->Write(team_member_group->level_max);
	bw->Write(team_member_group->unknown_1);
	bw->Write(team_member_group->unknown_2);
	bw->Write(team_member_group->unknown_3);
	bw->Write(team_member_group->amount_min);
	bw->Write(team_member_group->amount_max);
	bw->Write(team_member_group->quest);
	if(version >= 100)
	{
		bw->Write(team_member_group->order);
	}
}

void WriteChase(int version, BinaryWriter^ bw, Chase^ chase)
{
	bw->Write(chase->id_monster);
	bw->Write(chase->amount_monster);
	bw->Write(chase->id_drop);
	bw->Write(chase->amount_drop);
	bw->Write(chase->unknown_1);
	bw->Write(chase->probability);
	bw->Write(chase->unknown_2);

	if(version >= 92)
	{
		bw->Write(chase->unknown_3);
	}
}

void WriteLocation(int version, BinaryWriter^ bw, Location^ location)
{
	bw->Write(location->map_id);
	bw->Write(location->x);
	bw->Write(location->altitude);
	bw->Write(location->z);
}

void WriteSpan(int version, BinaryWriter^ bw, Span^ location_span)
{
	bw->Write(location_span->east);
	bw->Write(location_span->bottom);
	bw->Write(location_span->south);
	bw->Write(location_span->west);
	bw->Write(location_span->top);
	bw->Write(location_span->north);
}

void WriteReward(int version, BinaryWriter^ bw, Reward^ reward)
{
	bw->Write(reward->coins);
	bw->Write(reward->experience);
	bw->Write(reward->new_quest);
	bw->Write(reward->spirit);
	bw->Write(reward->reputation);
	bw->Write(reward->cultivation);
	bw->Write(reward->new_waypoint);
	bw->Write(reward->storage_slots);

	if(version >= 89)
	{
		bw->Write(reward->cupboard_slots);
		bw->Write(reward->wardrobe_slots);
		bw->Write(reward->account_stash_slots);
	}

	bw->Write(reward->inventory_slots);
	bw->Write(reward->petbag_slots);
	bw->Write(reward->vigor);
	WriteLocation(version, bw, reward->teleport);
	bw->Write(reward->ai_trigger);
	bw->Write(reward->UNKNOWN_2a);

	if(version > 55)
	{
		bw->Write(reward->UNKNOWN_2b);
	}

	bw->Write(reward->item_groups_count);
	bw->Write(reward->SEPERATOR);

	if(version >= 89)
	{
		bw->Write(reward->pq->chase_count);
		bw->Write(reward->pq->unknown_0);
		bw->Write(reward->pq->event_gold);
		bw->Write(reward->pq->unknown_1);
		bw->Write(reward->pq->unknown_quest);
		bw->Write(reward->pq->unknown_2);
		bw->Write(reward->pq->unknown_level);
		bw->Write(reward->pq->contribution_random_min);
		bw->Write(reward->pq->contribution_random_max);
		bw->Write(reward->pq->contribution_required);
		bw->Write(reward->pq->unknown_3);
		bw->Write(reward->pq->item_count);
		bw->Write(reward->pq->unknown_4);
		bw->Write(reward->pq->special_count);
		bw->Write(reward->pq->unknown_5);
		bw->Write(reward->pq->script_count);
		bw->Write(reward->pq->unknown_6);
		bw->Write(reward->pq->message_count);
		bw->Write(reward->pq->unknown_7);
	}

	if(version >= 100)
	{
		bw->Write(reward->influence);
		bw->Write(reward->prestige);
		bw->Write(reward->UNKNOWN_5);
		bw->Write(reward->UNKNOWN_6);
	}

	for(int i=0; i<reward->item_groups->Length; i++)
	{
		 WriteItemGroup(version, bw, reward->item_groups[i]);
	}

	if(version >= 89)
	{
		if(reward->pq->chase_count>0)
		{
			bw->Write(reward->pq->chase_unknown_1);
			bw->Write(reward->pq->chase_unknown_2);
			bw->Write(reward->pq->chase_unknown_3);
			for(int i=0; i<reward->pq->chase_count; i++)
			{
				bw->Write(reward->pq->chases[i]->id_monster);
				bw->Write(reward->pq->chases[i]->amount_monster);
				bw->Write(reward->pq->chases[i]->probability);
				bw->Write(reward->pq->chases[i]->amount_unknown);
			}
		}

		if(reward->pq->item_count>0)
		{
			bw->Write(reward->pq->item_unknown_1);
			for(int i=0; i<reward->pq->item_count; i++)
			{
				bw->Write(reward->pq->items[i]->ranking_from);
				bw->Write(reward->pq->items[i]->ranking_to);
				bw->Write(reward->pq->items[i]->unknown_3);
				bw->Write(reward->pq->items[i]->id);
				bw->Write(reward->pq->items[i]->amount);
				bw->Write(reward->pq->items[i]->probability);
			}
		}

		if(reward->pq->special_count>0)
		{
			for(int i=0; i<reward->pq->special_count; i++)
			{
				bw->Write(reward->pq->specials[i]->id_pq);
				bw->Write(reward->pq->specials[i]->unknown_2);
				bw->Write(reward->pq->specials[i]->unknown_3);
			}
		}

		if(reward->pq->script_count>0)
		{
			for(int i=0; i<reward->pq->script_count; i++)
			{
				bw->Write(reward->pq->scripts[i]);
			}
		}

		if(reward->pq->message_count>0)
		{
			for(int i=0; i<reward->pq->message_count; i++)
			{
				bw->Write(reward->pq->messages[i]);
			}
		}
	}
}

void Task::Save(int version, BinaryWriter^ bw)
{

// ################# GENERAL #############################

	bw->Write(id);
	bw->Write(name);
	bw->Write(author_mode);
	bw->Write(UNKNOWN_01);
	bw->Write(type);
	bw->Write(time_limit);

	if(version >= 89)
	{
		bw->Write(UNKNOWN_02);
		bw->Write(has_date_fail);
		WriteDate(version, bw, date_fail);
		bw->Write(UNKNOWN_03);	
	}

	bw->Write(has_date_spans);
	bw->Write(date_spans_count);
	bw->Write(UNKNOWN_04);
	bw->Write(UNKNOWN_05);

	if(version >= 89)
	{
		bw->Write(UNKNOWN_06);
	}

	bw->Write(UNKNOWN_07);
	bw->Write(UNKNOWN_08);

	if(version >= 89)
	{
		bw->Write(UNKNOWN_09);
	}

	bw->Write(activate_first_subquest);
	bw->Write(activate_random_subquest);
	bw->Write(activate_next_subquest);
	bw->Write(on_give_up_parent_fails);
	bw->Write(on_success_parent_success);
	bw->Write(can_give_up);
	bw->Write(repeatable);
	bw->Write(repeatable_after_failure);
	bw->Write(fail_on_death);
	bw->Write(on_fail_parent_fail);
	bw->Write(UNKNOWN_10);
	bw->Write(player_limit);

	// trigger location old and new format
	if(version >= 89)
	{
		bw->Write(trigger_locations->has_location);
		bw->Write(trigger_locations->map_id);
		bw->Write(trigger_locations->count);
		bw->Write(trigger_locations->unknown_1);
	}
	else
	{
		bw->Write(trigger_locations->has_location);
		bw->Write(trigger_locations->map_id);
		WriteSpan(version, bw, trigger_locations->spans[0]); // write only location [0]
	}

	// unknown location only version 89+
	if(version >= 89)
	{
		bw->Write(fail_locations->has_location);
		bw->Write(fail_locations->map_id);
		bw->Write(fail_locations->count);
		bw->Write(fail_locations->unknown_1);
	}

	// valid location only version 89+
	if(version >= 89)
	{
		bw->Write(valid_locations->has_location);
		bw->Write(valid_locations->map_id);
		bw->Write(valid_locations->count);
		bw->Write(valid_locations->unknown_1);
	}

	if(version >= 100)
	{
		bw->Write(UNKNOWN_17);
	}

	bw->Write(has_instant_teleport);
	WriteLocation(version, bw, instant_teleport_location);
	bw->Write(ai_trigger);
	bw->Write(UNKNOWN_18);
	bw->Write(UNKNOWN_19);
	bw->Write(UNKNOWN_20);

	if(version >= 89)
	{
		bw->Write(UNKNOWN_21);
		bw->Write(UNKNOWN_22);
	}

	bw->Write(UNKNOWN_23);
	bw->Write(UNKNOWN_LEVEL);
	bw->Write(mark_available_icon);
	bw->Write(mark_available_point);
	bw->Write(quest_npc);
	bw->Write(reward_npc);
	bw->Write(craft_skill);
	bw->Write(UNKNOWN_24);
	bw->Write(UNKNOWN_25);
	bw->Write(UNKNOWN_26);

	if(version >= 89)
	{
		bw->Write(pq->script_info_count);
		bw->Write(pq->unknown_1);
		bw->Write(pq->unknown_2);
		bw->Write(pq->unknown_3);
		bw->Write(pq->script_count);
		bw->Write(pq->unknown_4);
		bw->Write(pq->unknown_5);
		bw->Write(pq->unknown_6);
		bw->Write(pq->chase_count);
		bw->Write(pq->unknown_7);
		bw->Write(pq->required_quests_completed);
		bw->Write(pq->unknown_8);

		if(version >= 92)
		{
			bw->Write(pq->unknown_9);
		}

		bw->Write(pq->unknown_10);
	}

	if(version >= 100)
	{
		bw->Write(UNKNOWN_26_01);
	}

	bw->Write(level_min);
	bw->Write(level_max);
	bw->Write(UNKNOWN_27);
	bw->Write(required_items_count);
	bw->Write(required_items_unknown);
	bw->Write(UNKNOWN_28);
	if(version >= 100)
	{
		bw->Write(UNKNOWN_28_01);
	}
	bw->Write(given_items_count);
	bw->Write(UNKNOWN_29);
	bw->Write(UNKNOWN_30);
	bw->Write(given_items_unknown);
	bw->Write(instant_pay_coins);
	bw->Write(UNKNOWN_31);
	bw->Write(required_reputation);
	bw->Write(UNKNOWN_32);
	bw->Write(UNKNOWN_33);
	bw->Write(required_quests_done_count);
	for(int i=0; i<required_quests_done->Length; i++)
	{
		bw->Write(required_quests_done[i]);
	}

	if(version >= 90)
	{
		bw->Write(UNKNOWN_34);
	}

	bw->Write(UNKNOWN_35);

	if(version >= 90)
	{
		bw->Write(UNKNOWN_36);
	}

	bw->Write(UNKNOWN_37);

	if(version >= 93)
	{
		bw->Write(UNKNOWN_38);
	}

	bw->Write(UNKNOWN_39);
	bw->Write(required_gender);
	bw->Write(UNKNOWN_40);

	if(version < 89)
	{
// ToDo: remove entries with new classes (mystic & seeker)
// i.e. copy valid occupations to temp array
		// remove occupations [8] & [9]
		for(int i=8; i<required_occupations->Length; i++)
		{
			if(required_occupations[i] > 0)
			{
				required_occupations_count--;
			}
		}
	}

	bw->Write(required_occupations_count);
	if(version < 89)
	{
		for(int i=0; i<8; i++)
		{
			bw->Write(required_occupations[i]);
		}
	}
	else
	{
		for(int i=0; i<10; i++)
		{
			bw->Write(required_occupations[i]);
		}
	}

	bw->Write(UNKNOWN_41);
	bw->Write(required_be_married);
	bw->Write(UNKNOWN_42);
	bw->Write(required_be_gm);
	bw->Write(UNKNOWN_43);

	if(version >= 89)
	{
		bw->Write(UNKNOWN_44);
		WriteDate(version, bw, date_unknown);
		bw->Write(UNKNOWN_45);
		bw->Write(UNKNOWN_46);
	}

	bw->Write(UNKNOWN_47);
	bw->Write(required_quests_undone_count);
	for(int i=0; i<required_quests_undone->Length; i++)
	{
		bw->Write(required_quests_undone[i]);
	}
	bw->Write(required_blacksmith_level);
	bw->Write(required_tailor_level);
	bw->Write(required_craftsman_level);
	bw->Write(required_apothecary_level);
	bw->Write(UNKNOWN_48);

	if(version >= 89)
	{
		bw->Write(UNKNOWN_49);
	}

	bw->Write(required_team_member_groups_count);
	bw->Write(UNKNOWN_50);
	bw->Write(UNKNOWN_51);

	if(version >= 89)
	{
		bw->Write(UNKNOWN_52);
		bw->Write(resource_pq_audit_id);
		bw->Write(UNKNOWN_53);
		bw->Write(UNKNOWN_54);
		bw->Write(required_pq_contribution);
		bw->Write(UNKNOWN_55);
	}

	if(version >= 100)
	{
		bw->Write(UNKNOWN_55_02_01);
		bw->Write(required_force);
		bw->Write(UNKNOWN_55_02_02);
		bw->Write(required_prestige);
		bw->Write(UNKNOWN_55_03);
		bw->Write(required_influence_fee);
		bw->Write(UNKNOWN_55_04);
		bw->Write(UNKNOWN_55_05);
		bw->Write(UNKNOWN_55_06);
	}

	bw->Write(required_success_type);
	bw->Write(required_npc_type);
	bw->Write(required_chases_count);
	bw->Write(required_chases_unknown);
	bw->Write(required_get_items_count);
	bw->Write(required_get_items_unknown);
	bw->Write(required_coins);
	bw->Write(UNKNOWN_56);

	if(version >= 89)
	{
		bw->Write(UNKNOWN_57);
	}

	if(version >= 89)
	{
		// bw->Write(reach_locations->has_location);
		bw->Write(reach_locations->count);
		bw->Write(reach_locations->map_id);
		// bw->Write(reach_locations->unknown_1);
	}
	else
	{
		WriteSpan(version, bw, reach_locations->spans[0]);
		bw->Write(reach_locations->map_id);
	}

	bw->Write(required_wait_time);

	if(version >= 100)
	{
		bw->Write(UNKNOWN_57_01);
	}

	if(version >= 89)
	{
		bw->Write(pq->unknown_11);
		bw->Write(pq->location->map_id);
		bw->Write(pq->location->count);
		bw->Write(pq->unknown_12);
		bw->Write(pq->unknown_13);
		bw->Write(pq->id_script);
		bw->Write(pq->unknown_14);
		bw->Write(pq->unknown_15);
		bw->Write(pq->unknown_16);
		bw->Write(pq->unknown_17);
		bw->Write(pq->special_script_count);
		bw->Write(pq->unknown_18);
		bw->Write(pq->unknown_19);
		bw->Write(pq->message_count );
		bw->Write(pq->unknown_20);
	}

	bw->Write(UNKNOWN_58);
	bw->Write(UNKNOWN_59);
	bw->Write(parent_quest);
	bw->Write(previous_quest);
	bw->Write(next_quest);
	bw->Write(sub_quest_first);

	if(version >= 89)
	{
		bw->Write(UNKNOWN_60);
		bw->Write(receive_quest_probability);
	}

	if(version >= 100)
	{
		bw->Write(UNKNOWN_60_01);
	}

	if(author_mode)
	{
		bw->Write(author_text);
	}

// ################# DATES #############################

	for(int i=0; i<date_spans->Length; i++)
	{
		WriteDateSpan(version, bw, date_spans[i]);
	}

// ################# PQ AUDIT #############################

	if(version >= 89)
	{
		for(int i=0; i<pq->script_info_count; i++)
		{
			bw->Write(pq->script_infos[i]->id);
			bw->Write(pq->script_infos[i]->unknown_1);
			bw->Write(pq->script_infos[i]->unknown_2);
		}

		for(int i=0; i<pq->script_count; i++)
		{
			bw->Write(pq->scripts[i]->name);
			bw->Write(pq->scripts[i]->count);
			bw->Write(pq->scripts[i]->id);
			bw->Write(pq->scripts[i]->seperator);
			bw->Write(pq->scripts[i]->reference_id);
			bw->Write(pq->scripts[i]->code);
		}

		// exact arrangement of pq->chase cannot be determined
		// it would be guessed this data follows directly after pq->scripts
		for(int i=0; i<pq->chase_count; i++)
		{
			bw->Write(pq->chases[i]->id_monster);
			bw->Write(pq->chases[i]->amount_1);
			bw->Write(pq->chases[i]->contribution);
			bw->Write(pq->chases[i]->amount_3);
		}
	}

// ################# LOCATIONS #############################
// before: 
// after: 
// unknown: 
	if(version >= 89)
	{
		for(int m=0; m<trigger_locations->count; m++)
		{
			WriteSpan(version, bw, trigger_locations->spans[m]);
		}

		for(int m=0; m<fail_locations->count; m++)
		{
			WriteSpan(version, bw, fail_locations->spans[m]);
		}

		for(int m=0; m<valid_locations->count; m++)
		{
			WriteSpan(version, bw, valid_locations->spans[m]);
		}
	}

// ################# REQUIRED ITEMS #############################
// before: given_items
// after: valid_locaions
	for(int i=0; i<required_items->Length; i++)
	{
		WriteItem(version, bw, required_items[i]);
	}

// ################# GIVEN ITEMS #############################
// before: team_members
// after: required_items
	for(int i=0; i<given_items->Length; i++)
	{
		WriteItem(version, bw, given_items[i]);
	}

// ################# TEAM MEMBERS #############################
// after: given_items
// before: chase
	for(int i=0; i<required_team_member_groups->Length; i++)
	{
		WriteTeamMembers(version, bw, required_team_member_groups[i]);
	}

// ################# CHASE #############################
// after: team_members
// before: pq->special_scripts
	for(int i=0; i<required_chases->Length; i++)
	{
		WriteChase(version, bw, required_chases[i]);
	}

// ################# GET ITEMS #############################
// after: team_members
// before: pq->special_scripts
	for(int i=0; i<required_get_items->Length; i++)
	{
		WriteItem(version, bw, required_get_items[i]);
	}

// ################# LOCATIONS #############################
// after: team_members
// before: reward_success
	if(version >= 89)
	{
		for(int m=0; m<reach_locations->count;m++)
		{
			WriteSpan(version, bw, reach_locations->spans[m]);
		}

		// exact arrangement of pq->leave_area cannot be determined
		// it would be guessed this data follows directly after reach_locations
		for(int m=0; m<pq->location->count; m++)
		{
			WriteSpan(version, bw, pq->location->spans[m]);
		}
	}

// ################# PQ AUDIT #############################
// after: chases, get_items
// before: reward_success
	if(version >= 89)
	{
		for(int i=0; i<pq->special_script_count; i++)
		{
			bw->Write(pq->special_scripts[i]->name);
			bw->Write(pq->special_scripts[i]->count);
			bw->Write(pq->special_scripts[i]->id);
			bw->Write(pq->special_scripts[i]->seperator);
			bw->Write(pq->special_scripts[i]->reference_id);
			bw->Write(pq->special_scripts[i]->code);
		}

		for(int i=0; i<pq->message_count; i++)
		{
			bw->Write(pq->messages[i]);
		}
	}

// ################# SUCCESS REWARDS #############################

	WriteReward(version, bw, reward_success);

// ################# FAILED REWARDS #############################

	WriteReward(version, bw, reward_failed);

// ################# TIMED REWARDS #############################

		bw->Write(rewards_timed_count);
		for(int i=0; i<rewards_timed_factors->Length; i++)
		{
			bw->Write(rewards_timed_factors[i]);
		}

		for(int i=0; i<rewards_timed->Length; i++)
		{
			WriteReward(version, bw, rewards_timed[i]);
		}

// ################# UNKNOWN REWARDS #############################

	bw->Write(UNKNOWN_61);

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