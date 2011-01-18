#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;

String^ decrypt(int key, array<unsigned char>^ text);
array<unsigned char>^ encrypt(int key, String^ text, int length, bool appendZero);
String^ ByteArray_to_HexString(array<unsigned char>^ value);
array<unsigned char>^ HexString_to_ByteArray(String^ value);
public ref struct Item
{
	int id;
	bool unknown;
	int amount;
	float probability;
};

public ref struct ItemGroup
{
	bool unknown;
	int items_count;
	array<Item^>^ items;
};

public ref struct Chase
{
	int id_monster;
	int amount_monster;
	int id_drop;
	int amount_drop;
	unsigned char unknown_1;
	float probability;
	unsigned char unknown_2;
};

public ref struct Date
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int weekday;
};

public ref struct DateSpan
{
	Date^ from;
	Date^ to;
};

public ref struct Location
{
	int map_id;
	float x;
	float altitude;
	float z;
};

public ref struct LocationSpan
{
	int map_id;
	float east;
	float bottom;
	float south;
	float west;
	float top;
	float north;
};
public ref struct TeamMembers
{
	int level_min;
	int level_max;
	int unknown_1;
	int unknown_2;
	int unknown_3;
	int amount_min;
	int amount_max;
	int quest;
};

public ref struct Reward
{
	int coins;
	int experience;
	int new_quest;
	int spirit;
	int reputation;
	int cultivation;
	int UNKNOWN_1; // 4 Byte
	int storage_slots;
	int inventory_slots;
	int petbag_slots;
	int vigor;
	Location^ teleport;
	int aiTrigger;
	array<unsigned char>^ UNKNOWN_2; // 8 Byte
	int item_groups_count;
	array<unsigned char>^ SEPERATOR; // 4 Byte
	array<ItemGroup^>^ item_groups;
};
public ref struct Answer
{
	int crypt_key;
	int question_link;
	array<unsigned char>^ answer_text;
	// 128 Byte Unicode
	property String^ AnswerText
	{
		String^ get()
		{
			return decrypt(crypt_key, answer_text);
		}
		void set(String^ value)
		{
			answer_text = encrypt(crypt_key, value, 128, false);
		}
	}
	int task_link;
};

public ref struct Question
{
	int crypt_key;
	int question_id;
	int previous_question;
	int question_character_count;
	array<unsigned char>^ question_text;
	// 2*question_character_count Byte Unicode
	property String^ QuestionText
	{
		String^ get()
		{
			return decrypt(crypt_key, question_text);
		}
		void set(String^ value)
		{
			value = value->TrimEnd(gcnew array<wchar_t>{'\0'});
			question_text = encrypt(crypt_key, value, 2*value->Length + 2, true);
			question_character_count = question_text->Length/2;
		}
	}
	int answer_count;
	array<Answer^>^ answers;
};

public ref struct Dialog
{
	int crypt_key;
	int unknown;
	array<unsigned char>^ dialog_text;
	// 128 Byte Unicode
	property String^ DialogText
	{
		String^ get()
		{
			return decrypt(crypt_key, dialog_text);
		}
		void set(String^ value)
		{
			dialog_text = encrypt(crypt_key, value, 128, false);
		}
	}
	int question_count;
	array<Question^>^ questions;
};

public ref struct Conversation
{
	int crypt_key;
	int prompt_character_count;
	array<unsigned char>^ prompt_text;
	// 2*prompt_character_count Byte Unicode
	property String^ PromptText
	{
		String^ get()
		{
			return decrypt(crypt_key, prompt_text);
		}
		void set(String^ value)
		{
			value = value->TrimEnd(gcnew array<wchar_t>{'\0'});
			prompt_text = encrypt(crypt_key, value, 2*value->Length + 2, true);
			prompt_character_count = prompt_text->Length/2;
		}
	}
	array<unsigned char>^ seperator;
	int general_character_count;
	array<unsigned char>^ general_text;
	// 2*general_character_count Byte Unicode
	property String^ GeneralText
	{
		String^ get()
		{
			return decrypt(crypt_key, general_text);
		}
		void set(String^ value)
		{
			value = value->TrimEnd(gcnew array<wchar_t>{'\0'});
			general_text = encrypt(crypt_key, value, 2*value->Length+2, true);
			general_character_count = general_text->Length/2;
		}
	}
	array<Dialog^>^ dialogs;
};

public ref class Task
{
	public: Task(void)
	{
	}
	public: Task(int version, BinaryReader^ BinaryStream, int BaseStreamPosition, TreeNodeCollection^ Nodes)
	{
		Load(version, BinaryStream, BaseStreamPosition, Nodes);
	}	

	protected: ~Task()
	{
	}

	public: int id;
	public: array<unsigned char>^ name;
	// 60 Byte Unicode
	public: property String^ Name
	{
		String^ get()
		{
			return decrypt(id, name);
		}
		void set(String^ value)
		{
			name = encrypt(id, value, 60, false);
		}
	}
	public: bool author_mode;
	public: array<unsigned char>^ UNKNOWN_001a; // 4 Byte
	public: int type;
	public: int time_limit;
	public: array<unsigned char>^ UNKNOWN_002; // 1 Byte
	public: int date_spans_count;
	public: array<unsigned char>^ UNKNOWN_EVENT; // 4 Bytes
	public: array<unsigned char>^ UNKNOWN_ZEROS; // 8 Bytes -> All Zeros
	public: array<unsigned char>^ date_unknown; // 8 Bytes
	public: array<unsigned char>^ UNKNOWN_FLAGS_1; // 6 Bytes
	public: array<unsigned char>^ UNKNOWN_FLAGS_2; // 3 Bytes
	public: bool can_give_up;
	public: bool repeatable;
	public: bool repeatable_after_failure;
	public: array<unsigned char>^ UNKNOWN_004; // 8 Byte
	public: LocationSpan^ quest_trigger_location;
	public: array<unsigned char>^ UNKNOWN_005a_1; // 1 Byte
	public: Location^ instant_teleport_location;
	public: int ai_trigger;
	public: array<unsigned char>^ UNKNOWN_005a_3; // 3 Byte
	public: array<unsigned char>^ UNKNOWN_005b; // 1 Byte
	public: int UNKNOWN_LEVEL;
	public: array<unsigned char>^ UNKNOWN_005c; // 2 Byte
	public: int quest_npc;
	public: int reward_npc;
	public: array<unsigned char>^ UNKNOWN_006; // 4 Byte
	public: int level_min;
	public: int level_max;
	public: array<unsigned char>^ UNKNOWN_007; // 1 Byte
	public: int required_items_count;
	public: array<unsigned char>^ required_items_unknown;
	public: array<unsigned char>^ UNKNOWN_008_; // 1 Byte
	public: int given_items_count;
	public: array<unsigned char>^ GIVEN_UNKNOWN_INTEGERS; // 8 Byte
	public: array<unsigned char>^ given_items_unknown; // 4 Byte
	public: int instant_pay_coins;
	public: array<unsigned char>^ UNKNOWN_009b; // 1 Byte
	public: int required_reputation;
	public: array<unsigned char>^ UNKNOWN_010; // 5 Byte
	public: int required_quests_done_count;
	public: array<int>^ required_quests_done;

	public: array<unsigned char>^ UNKNOWN_011_1; // 11 Byte
	public: int required_gender;
	public: array<unsigned char>^ UNKNOWN_011_2; // 1 Byte
	public: int required_occupations_count;
	public: array<int>^ required_occupations;
	public: array<unsigned char>^ UNKNOWN_011_a2; // 5 Byte
	public: array<unsigned char>^ UNKNOWN_011_b; // 7 Byte -> All Zeros
	public: int required_quests_undone_count;
	public: array<int>^ required_quests_undone;
	// Married, Occupation, Reputation?, ...

	public: int required_blacksmith_level;
	public: int required_tailor_level;
	public: int required_craftsman_level;
	public: int required_apothecary_level;
	public: array<unsigned char>^ TEAM_MEMBER_REQUIREMENT; // 32 Byte
	public: int required_team_member_groups_count;
	public: array<unsigned char>^ required_team_member_groups_unknown; // 4 Byte
	public: array<unsigned char>^ UNKNOWN_012_a; // 1 Byte
	public: array<unsigned char>^ UNKNOWN_012_b; // 8 Byte
	public: int required_chases_count;
	public: array<unsigned char>^ required_chases_unknown; // 4 Byte
	public: int required_get_items_count;
	public: array<unsigned char>^ required_get_items_unknown; // 4 Byte
	public: int required_coins;
	public: array<unsigned char>^ UNKNOWN_015; // 16 Byte
	public: LocationSpan^ required_reach_location;
	public: int required_wait_time;
	public: array<unsigned char>^ UNKNOWN_016_b; // 8 Byte
	public: array<unsigned char>^ UNKNOWN_016_c; // 24 Byte
	public: int parent_quest;
	public: int previous_quest;
	public: int next_quest;
	public: int sub_quest_first;
	public: array<unsigned char>^ author_text;
	// 60 Byte Unicode
	public: property String^ AuthorText
	{
		String^ get()
		{
			return decrypt(id, author_text);
		}
		void set(String^ value)
		{
			author_text = encrypt(id, value, 60, false);
		}
	}
	public: array<DateSpan^>^ date_spans;
	public: array<Item^>^ required_items;
	public: array<Item^>^ given_items;
	public: array<TeamMembers^>^ required_team_member_groups;
	public: array<Chase^>^ required_chases;
	public: array<Item^>^ required_get_items;
	public: Reward^ reward_success;
	public: Reward^ reward_failed;
	public: int rewards_timed_count;
	public: array<float>^ rewards_timed_factors;
	public: array<Reward^>^ rewards_timed;

// Another Rewards section?
	public: array<unsigned char>^ UNKNOWN_025; // 80 Byte //public: Reward^ REWARD_UNKNOWN;
	
	Conversation^ conversation;
	int sub_quest_count;
	array<Task^>^ sub_quests;

	private: void Load(int version, BinaryReader^ br, int stream_position, TreeNodeCollection^ nodes);
	public: void Save(int version, BinaryWriter^ bw);
	public: Task^ Clone();
};