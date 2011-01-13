#pragma once

namespace PW
{
	namespace Data
	{
		namespace Task
		{
			#pragma region Helper Functions
			//{
				String^ Decrypt(int key, array<unsigned char>^ text)
				{
					String^ result = "";
					array<unsigned char>^ dbyte = gcnew array<unsigned char>(2);
					for(int i=0; i<text->Length; i+=2)
					{
						dbyte = BitConverter::GetBytes((short)key);
						// XOR decoding to receive Unicode character code
						dbyte[0] ^= text[i];
						dbyte[1] ^= text[i+1];
						result += BitConverter::ToChar(dbyte, 0);
					}
					return result->TrimEnd(gcnew array<wchar_t>{'\0'});
				}

				array<unsigned char>^ Encrypt(int key, String^ text, int length, bool appendZero)
				{
					array<unsigned char>^ result;

					if(appendZero)
					{
						result = gcnew array<unsigned char>(length+2);
					}
					else
					{
						result = gcnew array<unsigned char>(length);
					}

					array<unsigned char>^ dbyte = gcnew array<unsigned char>(2);

					for(int i=0; i<result->Length; i+=2)
					{
						dbyte = BitConverter::GetBytes((short)key);
						result[i] = dbyte[0];
						result[i+1] = dbyte[1];

						if(i/2 < text->Length)
						{
							dbyte = BitConverter::GetBytes(text[i/2]);
							result[i] ^= dbyte[0];
							result[i+1] ^= dbyte[1];
						}				
					}
					/*
					if(appendZero)
					{
						dbyte = BitConverter::GetBytes((short)key);
						result[result->Length-2] = dbyte[0];//^(unsigned char)0;
						result[result->Length-1] = dbyte[1];//^(unsigned char)0;
					}
					*/
					return result;
				}

				String^ ByteArray_to_HexString(array<unsigned char>^ value)
				{
					return BitConverter::ToString(value);
				}

				array<unsigned char>^ HexString_to_ByteArray(String^ value)
				{
					// Convert from Hex to byte[]
					array<String^>^ hex = value->Split(gcnew array<wchar_t>{'-'});
					array<unsigned char>^ bytes = gcnew array<unsigned char>(hex->Length);
					for(int i=0; i<hex->Length; i++)
					{
						bytes[i] = Convert::ToByte(hex[i], 16);
					}
					return bytes;
				}
			//}
			#pragma endregion

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
						return Decrypt(crypt_key, answer_text);
					}
					void set(String^ value)
					{
						answer_text = Encrypt(crypt_key, value, 128, false);
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
						return Decrypt(crypt_key, question_text);
					}
					void set(String^ value)
					{
						value = value->TrimEnd(gcnew array<wchar_t>{'\0'});
						question_text = Encrypt(crypt_key, value, 2*value->Length + 2, true);
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
						return Decrypt(crypt_key, dialog_text);
					}
					void set(String^ value)
					{
						dialog_text = Encrypt(crypt_key, value, 128, false);
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
						return Decrypt(crypt_key, prompt_text);
					}
					void set(String^ value)
					{
						value = value->TrimEnd(gcnew array<wchar_t>{'\0'});
						prompt_text = Encrypt(crypt_key, value, 2*value->Length + 2, true);
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
						return Decrypt(crypt_key, general_text);
					}
					void set(String^ value)
					{
						value = value->TrimEnd(gcnew array<wchar_t>{'\0'});
						general_text = Encrypt(crypt_key, value, 2*value->Length+2, true);
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
						return Decrypt(id, name);
					}
					void set(String^ value)
					{
						name = Encrypt(id, value, 60, false);
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
				public: array<unsigned char>^ UNKNOWN_FLAGS; // 9 Bytes
				public: bool can_give_up;
				public: bool repeatable;
				public: bool repeatable_after_failure;
				public: array<unsigned char>^ UNKNOWN_004; // 12 Byte
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
				public: array<unsigned char>^ TEAM_MEMBER_REQUIREMENTS; // 48 Byte
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
						return Decrypt(id, author_text);
					}
					void set(String^ value)
					{
						author_text = Encrypt(id, value, 60, false);
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

			#pragma region Load Functions
			//{
				private: Date^ ReadDate(int version, BinaryReader^ br)
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

				private: DateSpan^ ReadDateSpan(int version, BinaryReader^ br)
				{
					DateSpan^ date_span = gcnew DateSpan();

					date_span->from = ReadDate(version, br);
					date_span->to = ReadDate(version, br);

					return date_span;
				}

				private: Item^ ReadItem(int version, BinaryReader^ br)
				{
					Item^ item = gcnew Item();

					item->id = br->ReadInt32();
					item->unknown = br->ReadBoolean();
					item->amount = br->ReadInt32();
					item->probability = br->ReadSingle();

					if(version >= 79)
					{
						br->ReadBytes(4);
					}

					return item;
				}

				private: ItemGroup^ ReadItemGroup(int version, BinaryReader^ br)
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

				private: TeamMembers^ ReadTeamMembers(int version, BinaryReader^ br)
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

				private: Chase^ ReadChase(int version, BinaryReader^ br)
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

				private: Location^ ReadLocation(int version, BinaryReader^ br)
				{
					Location^ location = gcnew Location();

					location->map_id = br->ReadInt32();
					location->x = br->ReadSingle();
					location->altitude = br->ReadSingle();
					location->z = br->ReadSingle();

					return location;
				}
				private: LocationSpan^ ReadLocationSpan(int version, BinaryReader^ br, bool reverse)
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

				private: Reward^ ReadReward(int version, BinaryReader^ br)
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

					if(version >= 79)
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
					if(version >= 79)
					{
						v79_Count_1 = br->ReadInt32(); // public reward chases count
						br->ReadBytes(19);
						br->ReadInt32(); // New Quest ???
						br->ReadBytes(4);
						br->ReadInt32(); // Level ???
						br->ReadInt32(); // random contribution min
						br->ReadInt32(); // random contribution max
						br->ReadInt32(); // required reward contribution
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

					if(version >= 79)
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

				public: void Load(int version, BinaryReader^ br, int stream_position, TreeNodeCollection^ nodes)
				{
					br->BaseStream->Position = stream_position;

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

					if(version >= 79)
					{
						br->ReadBytes(2);
						ReadDate(version, br);
						br->ReadBytes(1);	
					}

					UNKNOWN_002 = br->ReadBytes(1);
					date_spans_count = br->ReadInt32();
					UNKNOWN_EVENT = br->ReadBytes(4);
					UNKNOWN_ZEROS = br->ReadBytes(8);

					if(version >= 79)
					{
						br->ReadBytes(12);
					}

					date_unknown = br->ReadBytes(8);
					UNKNOWN_FLAGS = br->ReadBytes(9);
					can_give_up = br->ReadBoolean();
					repeatable = br->ReadBoolean();
					repeatable_after_failure = br->ReadBoolean();
					UNKNOWN_004 = br->ReadBytes(8);
					quest_trigger_location = ReadLocationSpan(version, br, false);

					if(version >= 79)
					{
						br->ReadBytes(58);
					}

					UNKNOWN_005a_1 = br->ReadBytes(1);
					instant_teleport_location = ReadLocation(version, br);
					ai_trigger = br->ReadInt32();
					UNKNOWN_005a_3 = br->ReadBytes(3);
					UNKNOWN_005b = br->ReadBytes(1);
					UNKNOWN_LEVEL = br->ReadInt32();
					UNKNOWN_005c = br->ReadBytes(2);
					quest_npc = br->ReadInt32();
					reward_npc = br->ReadInt32();
					UNKNOWN_006 = br->ReadBytes(4);

					if(version >= 79)
					{
						v79_Public_Count_1 = br->ReadInt32();
						br->ReadBytes(12);
						br->ReadInt32();
						br->ReadBytes(10);
						v79_Public_Count_2 = br->ReadInt32();
						br->ReadBytes(8);
						br->ReadBytes(1);
						br->ReadBytes(1);
						v79_Public_Count_4 = br->ReadInt32();
						br->ReadBytes(9);
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
					UNKNOWN_011_a2 = br->ReadBytes(5);

					if(version >= 79)
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

					if(version >= 79)
					{
						br->ReadBytes(2);
					}

					required_team_member_groups_count = br->ReadInt32();
					required_team_member_groups_unknown = br->ReadBytes(4);
					UNKNOWN_012_a = br->ReadBytes(1);

					if(version >= 79)
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
					required_reach_location = ReadLocationSpan(version, br, true);
					required_wait_time = br->ReadInt32();

					// At this place the v79 positions must be guessed due to leak of informations...

					if(version >= 79)
					{
						br->ReadBytes(28);
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

					if(version >= 79)
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
						sub_quests[i] = gcnew Task();
						sub_quests[i]->Load(version, br, (int)br->BaseStream->Position, nodes[nodes->Count-1]->Nodes);
					}
				}
			//}
			#pragma endregion

			#pragma region Save
			//{
				void Save(int version, BinaryWriter^ bw)
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
					bw->Write(UNKNOWN_FLAGS);
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
					bw->Write(UNKNOWN_011_1);
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
					bw->Write(TEAM_MEMBER_REQUIREMENTS);
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
			//}
			#pragma endregion

			#pragma region Clone
			//{
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
					result->UNKNOWN_FLAGS = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_FLAGS));
					result->can_give_up = this->can_give_up;
					result->repeatable = this->repeatable;
					result->repeatable_after_failure = this->repeatable_after_failure;
					result->UNKNOWN_004 = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_004));
					result->quest_trigger_location = gcnew LocationSpan();
					result->quest_trigger_location->map_id = this->quest_trigger_location->map_id;
					result->quest_trigger_location->north = this->quest_trigger_location->north;
					result->quest_trigger_location->south = this->quest_trigger_location->south;
					result->quest_trigger_location->west = this->quest_trigger_location->west;
					result->quest_trigger_location->east = this->quest_trigger_location->east;
					result->quest_trigger_location->top = this->quest_trigger_location->top;
					result->quest_trigger_location->bottom = this->quest_trigger_location->bottom;
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
					result->UNKNOWN_011_1 = HexString_to_ByteArray(ByteArray_to_HexString(this->UNKNOWN_011_1));
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
					result->TEAM_MEMBER_REQUIREMENTS = HexString_to_ByteArray(ByteArray_to_HexString(this->TEAM_MEMBER_REQUIREMENTS));
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
					result->required_reach_location = gcnew LocationSpan();
					result->required_reach_location->map_id = this->required_reach_location->map_id;
					result->required_reach_location->north = this->required_reach_location->north;
					result->required_reach_location->south = this->required_reach_location->south;
					result->required_reach_location->west = this->required_reach_location->west;
					result->required_reach_location->east = this->required_reach_location->east;
					result->required_reach_location->top = this->required_reach_location->top;
					result->required_reach_location->bottom = this->required_reach_location->bottom;
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
					result->reward_success->UNKNOWN_2 = HexString_to_ByteArray(ByteArray_to_HexString(this->reward_success->UNKNOWN_2));
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
					result->reward_failed->UNKNOWN_2 = HexString_to_ByteArray(ByteArray_to_HexString(this->reward_failed->UNKNOWN_2));
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
						result->rewards_timed[r]->UNKNOWN_2 = HexString_to_ByteArray(ByteArray_to_HexString(this->rewards_timed[r]->UNKNOWN_2));
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
			//}
			#pragma endregion

			};
		}
	}
}