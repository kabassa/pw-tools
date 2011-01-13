#pragma once

namespace PW
{
	namespace Data
	{
		namespace AiPolicy
		{
			public ref class Procedure
			{
				public: Procedure(void)
				{
				}

				protected: ~Procedure()
				{
				}

				public: int type;
				public: array<Object^>^ parameters;
				public: int target;
				public: int extra;

				public: void Load(BinaryReader^ br)
				{
					type = br->ReadInt32();

					if(type == 0)
					{
						parameters = gcnew array<Object^>{br->ReadInt32()}; // Attack
					}
					if(type == 1)
					{
						parameters = gcnew array<Object^>{br->ReadInt32(), br->ReadInt32()}; // Cast Skill
					}
					if(type == 2)
					{
						int count = br->ReadInt32();
						parameters = gcnew array<Object^>{count, br->ReadBytes(count)}; // Broadcast Message
					}
					if(type == 3)
					{
						parameters = gcnew array<Object^>{}; // Break
					}
					if(type == 4)
					{
						parameters = gcnew array<Object^>{br->ReadInt32()}; // Execute Trigger
					}
					if(type == 5)
					{
						parameters = gcnew array<Object^>{br->ReadInt32()}; // Disable Trigger
					}
					if(type == 6)
					{
						parameters = gcnew array<Object^>{br->ReadInt32()}; // Enable Trigger
					}
					if(type == 7)
					{
						parameters = gcnew array<Object^>{br->ReadInt32(), br->ReadInt32(), br->ReadInt32()}; // Create Timer
					}
					if(type == 8)
					{
						parameters = gcnew array<Object^>{br->ReadInt32()}; // Remove Timer
					}
					if(type == 9)
					{
						parameters = gcnew array<Object^>{}; // Run Away (AGGRO_FIRST)
					}
					if(type == 10)
					{
						parameters = gcnew array<Object^>{}; // Be Taunted (COMBO, int)
					}
					if(type == 11)
					{
						parameters = gcnew array<Object^>{}; // Fade Target (AGGRO_SECOND)
					}
					if(type == 12)
					{
						parameters = gcnew array<Object^>{}; // Fade Aggro ()
					}
					if(type == 13)
					{
						parameters = gcnew array<Object^>{}; // Break
					}
					if(type == 14)
					{
						parameters = gcnew array<Object^>{br->ReadInt32(), br->ReadInt32()}; // NPC Generator
					}
					// ---------- following procedure types are > 1.3.6 -----------------
					if(type == 15)
					{
						parameters = gcnew array<Object^>{br->ReadInt32(), br->ReadInt32(), br->ReadInt32()};
					}
					if(type == 16)
					{
						parameters = gcnew array<Object^>{br->ReadInt32(), br->ReadInt32()};
					}
					if(type == 17)
					{
						parameters = gcnew array<Object^>{br->ReadInt32(), br->ReadInt32(), br->ReadInt32(), br->ReadInt32(), br->ReadInt32(), br->ReadInt32()};
					}
					if(type > 17)
					{
						parameters = gcnew array<Object^>(0);
					}

					target = br->ReadInt32();
					if(target == 6)
					{
						extra = br->ReadInt32();
					}
				}

				public: void Save(BinaryWriter^ bw)
				{
						bw->Write(type);

						if(type == 0)
						{
							bw->Write((int)parameters[0]);
						}
						if(type == 1)
						{
							bw->Write((int)parameters[0]);
							bw->Write((int)parameters[1]);
						}
						if(type == 2)
						{
							int count = (int)parameters[0];
							bw->Write(count);
							bw->Write((array<unsigned char>^)parameters[1]);
						}
						if(type == 4)
						{
							bw->Write((int)parameters[0]);
						}
						if(type == 5)
						{
							bw->Write((int)parameters[0]);
						}
						if(type == 6)
						{
							bw->Write((int)parameters[0]);
						}
						if(type == 7)
						{
							bw->Write((int)parameters[0]);
							bw->Write((int)parameters[1]);
							bw->Write((int)parameters[2]);
						}
						if(type == 8)
						{
							bw->Write((int)parameters[0]);
						}
						if(type == 14)
						{
							bw->Write((int)parameters[0]);
							bw->Write((int)parameters[1]);
						}
						// ---------- following procedure types are > 1.3.6 Server -----------------
						if(type == 15)
						{
							bw->Write((int)parameters[0]);
							bw->Write((int)parameters[1]);
							bw->Write((int)parameters[2]);
						}
						if(type == 16)
						{
							bw->Write((int)parameters[0]);
							bw->Write((int)parameters[1]);
						}
						if(type == 17)
						{
							bw->Write((int)parameters[0]);
							bw->Write((int)parameters[1]);
							bw->Write((int)parameters[2]);
							bw->Write((int)parameters[3]);
							bw->Write((int)parameters[4]);
							bw->Write((int)parameters[5]);
						}

						bw->Write(target);
						if(target == 6)
						{
							bw->Write(extra);
						}
				}

				private: String^ GetExtraExpression()
				{
					if(target == 0)
					{
						return "AGGRO_FIRST";
					}
					if(target == 1)
					{
						return "AGGRO_SECOND";
					}
					if(target == 2)
					{
						return "AGGRO_SECOND_RAND";
					}
					if(target == 3)
					{
						return "MOST_HP";
					}
					if(target == 4)
					{
						return "MOST_MP";
					}
					if(target == 5)
					{
						return "LEAST_HP";
					}
					if(target == 6)
					{
						return "COMBO";
					}
					if(target == 7)
					{
						return "SELF";
					}
					return "?";
				}
				public: String^ GetExpression()
				{
					String^ expression = "";

					if(type == 0)
					{
						expression = "Attack(";
						expression += ((int)parameters[0]).ToString();
						expression += ")";
					}
					if(type == 1)
					{
						expression = "Cast_Skill(";
						expression += ((int)parameters[0]).ToString() + ", ";
						expression += ((int)parameters[1]).ToString();
						expression += ")";
					}
					if(type == 2)
					{
						expression = "Broadcast_Message(";
						expression += ((int)parameters[0]).ToString() + ", ";
						expression += "\"" + (Encoding::Unicode)->GetString((array<unsigned char>^)parameters[1])->Replace("\0", "") + "\"";
						expression += ")";
					}
					if(type == 3)
					{
						expression = "Reset_Aggro()";
					}
					if(type == 4)
					{
						expression = "Execute_ActionSet(";
						expression += ((int)parameters[0]).ToString();
						expression += ")";
					}
					if(type == 5)
					{
						expression = "Disable_ActionSet(";
						expression += ((int)parameters[0]).ToString();
						expression += ")";
					}
					if(type == 6)
					{
						expression = "Enable_ActionSet(";
						expression += ((int)parameters[0]).ToString();
						expression += ")";
					}
					if(type == 7)
					{
						expression = "Create_Timer(";
						expression += ((int)parameters[0]).ToString() + ", ";
						expression += ((int)parameters[1]).ToString() + ", ";
						expression += ((int)parameters[2]).ToString();
						expression += ")";
					}
					if(type == 8)
					{
						expression = "Remove_Timer(";
						expression += ((int)parameters[0]).ToString();
						expression += ")";
					}
					if(type == 9)
					{
						expression = "Run_Away()";
					}
					if(type == 10)
					{
						expression = "Be_Taunted()";
					}
					if(type == 11)
					{
						expression = "Fade_Target()";
					}
					if(type == 12)
					{
						expression = "Fade_Aggro()";
					}
					if(type == 13)
					{
						expression = "Break()";
					}
					if(type == 14)
					{
						expression = "NPC_Generator(";
						expression += ((int)parameters[0]).ToString() + ", ";
						expression += ((int)parameters[1]).ToString();
						expression += ")";
					}
					// ---------- following procedure types are > 1.3.6 Server -----------------
					if(type == 15)
					{
						expression = "Initialize_Public_Counter(";
						expression += ((int)parameters[0]).ToString() + ", ";
						expression += ((int)parameters[1]).ToString() + ", ";
						expression += ((int)parameters[2]).ToString();
						expression += ")";
					}
					if(type == 16)
					{
						expression = "Increment_Public_Counter(";
						expression += ((int)parameters[0]).ToString() + ", ";
						expression += ((int)parameters[1]).ToString();
						expression += ")";
					}
					if(type == 17)
					{
						expression = "Player_Aimed_NPC_Spawn(";
						expression += ((int)parameters[0]).ToString() + ", "; // NPC ID
						expression += ((int)parameters[1]).ToString() + ", ";
						expression += ((int)parameters[2]).ToString() + ", "; // LifeTime
						expression += ((int)parameters[3]).ToString() + ", ";
						expression += ((int)parameters[4]).ToString() + ", ";
						expression += ((int)parameters[5]).ToString();
						expression += ")";
					}
					expression += " EXT(" + GetExtraExpression();
					if(target == 6)
					{
						expression += ", " + extra.ToString();
					}
					expression += ")";
					return expression;
				}

			};

			public ref class Condition
			{
				public: Condition(void)
				{
				}

				protected: ~Condition()
				{
				}

				public: int operator_id;
				public: int argument_bytes;
				public: array<unsigned char>^ value;
				public: int condition_type;
				public: Condition^ condition_left;
				public: int subnode_2;
				public: Condition^ condition_right;
				public: int subnode_3;

				public: void Load(BinaryReader^ br)
				{
					operator_id = br->ReadInt32();
					argument_bytes = br->ReadInt32();
					//if(argument_bytes == 4)
					//{
						value = br->ReadBytes(argument_bytes);
					//}
					condition_type = br->ReadInt32(); // 1 || 2 || 3
					if(condition_type == 1)
					{
						condition_left = gcnew Condition();
						condition_left->Load(br);
						subnode_2 = br->ReadInt32(); // always 2
						//if(subnode_2 == 2)
						//{
							condition_right = gcnew Condition();
							condition_right->Load(br);
							subnode_3 = br->ReadInt32(); // always 4
						//}
					}

					if(condition_type == 2)
					{
						condition_right = gcnew Condition();
						condition_right->Load(br);
						subnode_2 = br->ReadInt32(); // always 4
					}
				}

				public: void Save(BinaryWriter^ bw)
				{
					bw->Write(operator_id);
					bw->Write(argument_bytes);
					if(argument_bytes == 4)
					{
						bw->Write(value);
					}

					bw->Write(condition_type);

					if(condition_type == 1)
					{
						condition_left->Save(bw);
						bw->Write(subnode_2);
						if(subnode_2 == 2)
						{
							condition_right->Save(bw);
							bw->Write(subnode_3);
						}
					}

					if(condition_type == 2)
					{
						condition_right->Save(bw);
						bw->Write(subnode_2);
					}
				}

				// Rebuild the condition tree
				// If conditions are based on property ID's > 8, then this condition will be set to NULL
				public: Condition^ GetFixedCondition()
				{
					if(operator_id > 8)
					{
						// try to replace operator id with a valid condition_(chain)

						// remove condition
						return nullptr;
					}
					else
					{
						if(condition_type == 1)
						{
							condition_left = condition_left->GetFixedCondition();
							condition_right = condition_right->GetFixedCondition();

							if(condition_left && condition_right)
							{
								// everything is OK
								return this;
							}
							if(!condition_left && condition_right)
							{
								// left condition is broken, no need to operate between both conditions
								// right condition replaces the current operator condition i.e. AND
								return condition_right;
							}
							if(condition_left && !condition_right)
							{
								// right condition is broken, no need to operate between both conditions
								// left condition replaces the current operator condition i.e. AND
								return condition_left;
							}
							if(!condition_left && !condition_right)
							{
								// both conditions for this operator condition are broken
								// completely drop this condition
								return nullptr;
							}
						}
						if(condition_type == 2)
						{
							condition_right = condition_right->GetFixedCondition();

							if(condition_right)
							{
								return this;
							}
							else
							{
								return nullptr;
							}
						}
						//if(condition_type > 2)
						return this;
					}
				}
				private: String^ GetOperatorName()
				{
					if(operator_id == 0)
					{
						return "Is_Timer_Ticking";
					}
					if(operator_id == 1)
					{
						return "Is_HP_Less";
					}
					if(operator_id == 2)
					{
						return "Is_Combat_Started";
					}
					if(operator_id == 3)
					{
						return "Randomize";
					}
					if(operator_id == 4)
					{
						return "Is_Target_Killed";
					}
					if(operator_id == 5)
					{
						return "!"; // NOT
					}
					if(operator_id == 6)
					{
						return "||"; // OR
					}
					if(operator_id == 7)
					{
						return "&&"; // AND
					}
					if(operator_id == 8)
					{
						return "Is_Dead";
					}
					// ---------- following condition types are > 1.3.6 -----------------
					if(operator_id == 9)
					{
						return "+"; // SUM
					}
					if(operator_id == 10)
					{
						return "-"; // MINUS ?
					}
					if(operator_id == 11)
					{
						return "=="; // EQUALS ?
					}
					if(operator_id == 12)
					{
						return ">"; // GREATER THEN
					}
					if(operator_id == 13)
					{
						return ">="; // GREATER EQUALS
					}
					if(operator_id == 14)
					{
						return "<"; // LESS THEN
					}
					if(operator_id == 15)
					{
						return "<="; // LESS EQUALS ?
					}
					if(operator_id == 16)
					{
						return "Public_Counter"; // A property/counter that holds a public/shared value
					}
					if(operator_id == 17)
					{
						return "Value"; // defines a value for operator comparsion i.e. value of score, minutes, level, ...
					}
					return "?";
				}
				private: String^ GetOperatorValue()
				{
					if(operator_id == 0)
					{
						return BitConverter::ToInt32(value, 0).ToString();
					}
					if(operator_id == 1)
					{
						return BitConverter::ToSingle(value, 0).ToString("F2");
					}
					if(operator_id == 2)
					{
						return "";
					}
					if(operator_id == 3)
					{
						return BitConverter::ToSingle(value, 0).ToString("F2");
					}
					if(operator_id == 4)
					{
						return "";
					}
					if(operator_id == 5)
					{
						return "NOT";
					}
					if(operator_id == 6)
					{
						return "";
					}
					if(operator_id == 7)
					{
						return "";
					}
					if(operator_id == 8)
					{
						return "";
					}
					// ---------- following condition types are > 1.3.6 -----------------
					if(operator_id == 9)
					{
						return "";
					}
					if(operator_id == 10)
					{
						return "";
					}
					if(operator_id == 11)
					{
						return "";
					}
					if(operator_id == 12)
					{
						return "";
					}
					if(operator_id == 13)
					{
						return "";
					}
					if(operator_id == 14)
					{
						return "";
					}
					if(operator_id == 15)
					{
						return "";
					}
					if(operator_id == 16)
					{
						return BitConverter::ToInt32(value, 0).ToString();
					}
					if(operator_id == 17)
					{
						return BitConverter::ToInt32(value, 0).ToString();
					}
					return "?";
				}
				public: String^ GetExpression()
				{
					String^ expression = "";

					if(condition_type == 1)
					{
						expression += "(";
						expression += condition_left->GetExpression();
						expression += " " + GetOperatorName() + " ";
						expression += condition_right->GetExpression();
						expression += ")";
					}
					if(condition_type == 2)
					{
						expression += GetOperatorName();
						expression += "(";
						expression += condition_right->GetExpression();
						expression += ")";
					}
					if(condition_type > 2)
					{
						expression += GetOperatorName();
						expression += "(";
						if(argument_bytes > 0)
						{
							expression += GetOperatorValue();
						}
						expression += ")";
					}

					return expression;
				}
			};

			public ref class ActionSet
			{
				public: int version;
				public: int id;
				public: array<unsigned char>^ flags; // 3 Bytes
				public: array<unsigned char>^ name; // 128 Bytes
				public: property String^ Name
				{
					String^ get()
					{
						Encoding^ enc = Encoding::GetEncoding("GBK");
						return enc->GetString(name);//->Replace("\0", "");
					}
					void set(String^ value)
					{
						Encoding^ enc = Encoding::GetEncoding("GBK");
						array<unsigned char>^ target = gcnew array<unsigned char>(128);
						array<unsigned char>^ source = enc->GetBytes(value);
						if(target->Length > source->Length)
						{
							Array::Copy(source, target, source->Length);
						}
						else
						{
							Array::Copy(source, target, target->Length);
						}
						name = target;
					}
				}
				Condition^ conditions;
				array<Procedure^>^ procedures;

				// Rebuild procedure list by
				// removing all procedure types >= 15,
				// removing procedures that calls monster skills with id >= 887
				// replace player_based_npc_spawn with creature_builder (use a GUID for unique creature_builder ID's)
				// return the new GUID for the creature builder fix
				public: array<Procedure^>^ GetFixedProcedures(Collections::SortedList^ SkillReplaceList, int *GUID)
				{
					int count = 0;
					for(int i=0; i<procedures->Length; i++)
					{
						// count supported procedures
						if(procedures[i]->type != 15 && procedures[i]->type != 16)
						{
							count++;
						}
					}

					array<Procedure^>^ result = gcnew array<Procedure^>(count);
					count = 0;

					for(int i=0; i<procedures->Length; i++)
					{
						// only keep supported procedures 
						if(procedures[i]->type != 15 && procedures[i]->type != 16)
						{
							result[count] = gcnew Procedure();
							result[count]->type = procedures[i]->type;
							result[count]->parameters = procedures[i]->parameters;
							// replace skill if possible
							if(procedures[i]->type == 1 && SkillReplaceList->ContainsKey((int)procedures[i]->parameters[0]))
							{
								result[count]->parameters[0] = (int)SkillReplaceList[(int)procedures[i]->parameters[0]];
							}

							if(procedures[i]->type == 2 && ((array<unsigned char>^)result[count]->parameters[1])[0] == '$')
							{
								// remove whitespace after macro
								if(((array<unsigned char>^)result[count]->parameters[1])[4] == ' ')
								{
									array<unsigned char>^ _old = ((array<unsigned char>^)result[count]->parameters[1]);
									array<unsigned char>^ _new = gcnew array<unsigned char>(_old->Length-2);

									int n=0;
									for(int i=0; i<_new->Length; i++)
									{
										if(n == 4)
										{
											n = 6;
										}
										_new[i] = _old[n];
										n++;
									}

									result[count]->parameters[1] = _new;
									result[count]->parameters[0] = _new->Length;
								}

								// replace $S macro (no-name, color?) with $B macro (no-name, gold)
								if(((array<unsigned char>^)result[count]->parameters[1])[2] == 'S')
								{
									((array<unsigned char>^)result[count]->parameters[1])[2] = 'B';
								}

								// replace $I macro (no-name, red?) with $B macro (no-name, gold)
								if(((array<unsigned char>^)result[count]->parameters[1])[2] == 'I')
								{
									((array<unsigned char>^)result[count]->parameters[1])[2] = 'B';
								}
							}
							result[count]->target = procedures[i]->target;
							result[count]->extra = procedures[i]->extra;

							// replace player_aimed_npc_spawn with a simple npc_generator
							if(procedures[i]->type == 17)
							{
								result[count]->type = 14;
								// using guid as unifier to prevent multiple npc_generator() with same id's in the same action set
								int creature_builder_id = ((*GUID)*1000000 + (int)procedures[i]->parameters[0]);
								(*GUID)++;
								int start = 0; // 0: start, 1: stop
								result[count]->parameters = gcnew array<Object^>{creature_builder_id, start};
								result[count]->target = 0;
								result[count]->extra = 0;
							}

							count++;
						}
					}

					// if result is length 0 we have to add a dummy procedure, or action set will crash map
					if(result->Length < 1)
					{
						result = gcnew array<Procedure^>(1);
						result[0] = gcnew Procedure();
						result[0]->type = 2;
						result[0]->parameters = gcnew array<Object^>{6, Encoding::Unicode->GetBytes("...")};
						result[0]->target = 0;
						result[0]->extra = 0;
					}

					return result;
				}
			};

			public ref struct ActionController
			{
				public: int signature;
				public: int id;
				public: int action_sets_count;
				public: array<ActionSet^>^ action_sets;
			};

			public ref class AiPolicy
			{
				public: AiPolicy(void)
				{
				}

				protected: ~AiPolicy()
				{
				}

				public: int signature;
				public: array<ActionController^>^ action_controllers;

				public: void Load(String^ File)
				{
					FileStream^ fr = File::OpenRead(File);
					BinaryReader^ br = gcnew BinaryReader(fr);

					signature = br->ReadInt32();
					int action_controllers_count = br->ReadInt32();
					action_controllers = gcnew array<ActionController^>(action_controllers_count);
					for(int ac=0; ac<action_controllers->Length; ac++)
					{
						action_controllers[ac] = gcnew ActionController();
						action_controllers[ac]->signature = br->ReadInt32();
						action_controllers[ac]->id = br->ReadInt32();
						action_controllers[ac]->action_sets_count = br->ReadInt32();
						action_controllers[ac]->action_sets = gcnew array<ActionSet^>(action_controllers[ac]->action_sets_count);
						for(int as=0; as<action_controllers[ac]->action_sets->Length; as++)
						{
							action_controllers[ac]->action_sets[as] = gcnew ActionSet();
							action_controllers[ac]->action_sets[as]->version = br->ReadInt32();
							action_controllers[ac]->action_sets[as]->id = br->ReadInt32();
							action_controllers[ac]->action_sets[as]->flags = br->ReadBytes(3);
							action_controllers[ac]->action_sets[as]->name = br->ReadBytes(128);
							action_controllers[ac]->action_sets[as]->conditions = gcnew Condition();
							action_controllers[ac]->action_sets[as]->conditions->Load(br);
							int procedures_count = br->ReadInt32();
							action_controllers[ac]->action_sets[as]->procedures = gcnew array<Procedure^>(procedures_count);
							for(int p=0; p<action_controllers[ac]->action_sets[as]->procedures->Length; p++)
							{
								action_controllers[ac]->action_sets[as]->procedures[p] = gcnew Procedure();
								action_controllers[ac]->action_sets[as]->procedures[p]->Load(br);
							}
						}
					}

					br->Close();
					fr->Close();
				}

				public: void Save(String^ File)
				{
					FileStream^ fw = gcnew FileStream(File, FileMode::Create, FileAccess::Write);
					BinaryWriter^ bw = gcnew BinaryWriter(fw);

					bw->Write(signature);
					bw->Write(action_controllers->Length);
					for(int ac=0; ac<action_controllers->Length; ac++)
					{
						bw->Write(action_controllers[ac]->signature);
						bw->Write(action_controllers[ac]->id);
						bw->Write(action_controllers[ac]->action_sets_count);
						for(int as=0; as<action_controllers[ac]->action_sets->Length; as++)
						{
							bw->Write(action_controllers[ac]->action_sets[as]->version);
							bw->Write(action_controllers[ac]->action_sets[as]->id);
							bw->Write(action_controllers[ac]->action_sets[as]->flags);
							bw->Write(action_controllers[ac]->action_sets[as]->name);
							// Write conditions
							action_controllers[ac]->action_sets[as]->conditions->Save(bw);
							
							bw->Write(action_controllers[ac]->action_sets[as]->procedures->Length);
							for(int p=0; p<action_controllers[ac]->action_sets[as]->procedures->Length; p++)
							{
								action_controllers[ac]->action_sets[as]->procedures[p]->Save(bw);
							}
						}
					}

					bw->Close();
					fw->Close();
				}

				/*
					try to convert any AI structure to a 1.3.6 compatible server version
					+ replace signature and versions for file, collections and sets
					+ remove unsupported conditions (condition->property > 8) and rebuild condition tree
					+ remove unsupported procedures (procedure->id > 14)
					+ remove procedures that are using monster skills with id > 887
				*/
				public: AiPolicy^ GetFixedAiPolicy(Collections::SortedList^ SkillReplaceList)
				{
					// a counter for creating unique creature builder id's
					// when replacing player_aimed_npc_spawn() procedure with npc_generate() procedure
					int GUID = 1;

					AiPolicy^ result = gcnew AiPolicy();
					result->signature = (int)0; // signature = 0 for <= 1.3.6
					result->action_controllers = gcnew array<ActionController^>(action_controllers->Length);

					for(int ac=0; ac<result->action_controllers->Length; ac++)
					{
						result->action_controllers[ac] = gcnew ActionController();
						result->action_controllers[ac]->signature = (int)0; // signature = 0 for <= 1.3.6
						result->action_controllers[ac]->id = action_controllers[ac]->id;
						result->action_controllers[ac]->action_sets_count = action_controllers[ac]->action_sets_count;
						result->action_controllers[ac]->action_sets = gcnew array<ActionSet^>(result->action_controllers[ac]->action_sets_count);

						for(int as=0; as<result->action_controllers[ac]->action_sets->Length; as++)
						{
							result->action_controllers[ac]->action_sets[as] = gcnew ActionSet();
							result->action_controllers[ac]->action_sets[as]->version = (int)1; // signature = 1 for <= 1.3.6
							result->action_controllers[ac]->action_sets[as]->id = action_controllers[ac]->action_sets[as]->id;
							result->action_controllers[ac]->action_sets[as]->flags = action_controllers[ac]->action_sets[as]->flags; // 3 Bytes
							result->action_controllers[ac]->action_sets[as]->name = action_controllers[ac]->action_sets[as]->name; // 128 Bytes
							// convert conditions
							result->action_controllers[ac]->action_sets[as]->conditions = action_controllers[ac]->action_sets[as]->conditions->GetFixedCondition();
							// convert procedures
							result->action_controllers[ac]->action_sets[as]->procedures = action_controllers[ac]->action_sets[as]->GetFixedProcedures(SkillReplaceList, &GUID);

							// check for nullptr conditions after conversion
							// because it could happen that condition only consists
							// of properties > 1.3.6, this will cause in complete useless of condition tree 1.3.6
							if(!result->action_controllers[ac]->action_sets[as]->conditions)
							{
								// Removing an actionset can leads to dead links, if a link from a procedure is pointing to this actionset id
								// instead of removing this actionset, we create a default condition that is common false,
								// but will be executed when linked by an execute_actionset() procedure
								// for this behaviour we are using randomize(1.00)
								result->action_controllers[ac]->action_sets[as]->conditions = gcnew Condition();
								result->action_controllers[ac]->action_sets[as]->conditions->operator_id = 3;
								result->action_controllers[ac]->action_sets[as]->conditions->argument_bytes = 4;
								result->action_controllers[ac]->action_sets[as]->conditions->value = gcnew array<unsigned char>{0, 0, 128, 63};
								result->action_controllers[ac]->action_sets[as]->conditions->subnode_2 = 0;
								result->action_controllers[ac]->action_sets[as]->conditions->subnode_3 = 0;
								result->action_controllers[ac]->action_sets[as]->conditions->condition_type = 3;
							}
						}
					}

					return result;
				}
			};
		}
	}
}