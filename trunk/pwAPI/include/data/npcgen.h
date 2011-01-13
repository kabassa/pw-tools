#pragma once

namespace PW
{
	namespace Data
	{
		namespace NpcGen
		{
			public ref struct CreatureGroup
			{
				public: int ID;
				public: int Amount;
				public: int Respawn;
				public: int unknown_2;
				public: int unknown_3;
				public: int unknown_4;
				public: int unknown_5;
				public: int unknown_6;
				public: int unknown_7;
				public: int unknown_8;
				public: bool unknown_9;
				public: bool unknown_10;
				public: bool unknown_11;
				public: bool unknown_12;
				public: int PathID;
				public: int unknown_14;
				public: int unknown_15;
				public: int unknown_16;
			};

			public ref struct CreatureSet
			{
				public: int SpawnMode;
				public: float SpawnX;
				public: float SpawnAltitude;
				public: float SpawnZ;
				public: float DirectionX;
				public: float DirectionAltitude;
				public: float DirectionZ;
				public: float SpreadX;
				public: float SpreadAltitude;
				public: float SpreadZ;
				public: int Type;
				public: int unknown_8;
				public: bool unknown_9;
				public: bool unknown_10;
				public: bool InstantRespawn;
				public: int unknown_12;
				public: int TriggerID;
				public: int unknown_14;
				public: int unknown_15;
				public: array<CreatureGroup^>^ CreatureGroups;
			};

			public ref struct ResourceGroup
			{
				public: int unknown_1;
				public: int ID;
				public: int Respawn;
				public: int Amount;
				public: int unknown_2;
			};
			public ref struct ResourceSet
			{
				public: float SpawnX;
				public: float SpawnAltitude;
				public: float SpawnZ;
				public: float SpreadX;
				public: float SpreadZ;
				public: bool unknown_1;
				public: bool unknown_2;
				public: bool unknown_3;
				public: int unknown_4;
				public: unsigned char  unknown_5a;
				public: unsigned char unknown_5b;
				public: unsigned char unknown_5c;
				public: int TriggerID;
				public: unsigned char unknown_6;
				public: bool unknown_7;
				public: bool unknown_8;
				public: bool unknown_9;
				public: array<ResourceGroup^>^ ResourceGroups;
			};

			public ref struct Dynamic
			{
				public: int ID;
				public: float SpawnX;
				public: float SpawnAltitude;
				public: float SpawnZ;
				public: unsigned char unknown_5;
				public: unsigned char unknown_6;
				public: unsigned char unknown_7;
				public: int TriggerID;
				public: unsigned char unknown_8;
			};

			public ref struct Trigger
			{
				public: int TriggerID;
				public: int CreatureBuilderID;
				public: array<unsigned char>^ Name;
				public: bool unknown_3;
				public: int AutostartDelayTime;
				public: int AutostopDelayTime;
				public: bool AutostartDisable;
				public: bool AutostopDisable;
				public: int StartYear;
				public: int StartMonth;
				public: int StartWeekDay;
				public: int StartDay;
				public: int StartHour;
				public: int StartMinute;
				public: int EndYear;
				public: int EndMonth;
				public: int EndWeekDay;
				public: int EndDay;
				public: int EndHour;
				public: int EndMinute;
				public: int Duration;
			};

			public ref class NpcGen
			{
				public: NpcGen()
				{
				}

				protected: ~NpcGen()
				{
				}

				public: int Version;
				public: array<CreatureSet^>^ CreatureSets;
				public: array<ResourceSet^>^ ResourceSets;
				public: array<Dynamic^>^ Dynamics;
				public: array<Trigger^>^ Triggers;

				public: void Load(String^ File)
				{
					FileStream^ fr = File::OpenRead(File);
					BinaryReader^ br = gcnew BinaryReader(fr);

					Version = br->ReadInt32();
					int CreatureSets_count = br->ReadInt32();
					int ResourceSets_count = br->ReadInt32();
					int Dynamics_count = 0;
					int Triggers_count = 0;
					if(Version == 10)
					{
						Dynamics_count = br->ReadInt32();
						Triggers_count = br->ReadInt32();
					}

					CreatureSets = gcnew array<CreatureSet^>(CreatureSets_count);
					for(int i=0; i<CreatureSets->Length; i++)
					{
						Application::DoEvents();

						CreatureSets[i] = gcnew CreatureSet();
						CreatureSets[i]->SpawnMode = br->ReadInt32();
						int CreatureGroups_count = br->ReadInt32();
						CreatureSets[i]->SpawnX = br->ReadSingle();
						CreatureSets[i]->SpawnAltitude = br->ReadSingle();
						CreatureSets[i]->SpawnZ = br->ReadSingle();
						CreatureSets[i]->DirectionX = br->ReadSingle();
						CreatureSets[i]->DirectionAltitude = br->ReadSingle();
						CreatureSets[i]->DirectionZ = br->ReadSingle();
						CreatureSets[i]->SpreadX = br->ReadSingle();
						CreatureSets[i]->SpreadAltitude = br->ReadSingle();
						CreatureSets[i]->SpreadZ = br->ReadSingle();
						CreatureSets[i]->Type = br->ReadInt32();
						CreatureSets[i]->unknown_8 = br->ReadInt32();
						CreatureSets[i]->unknown_9 = br->ReadBoolean();
						CreatureSets[i]->unknown_10 = br->ReadBoolean();
						CreatureSets[i]->InstantRespawn = br->ReadBoolean();
						CreatureSets[i]->unknown_12 = br->ReadInt32();
						if(Version == 10)
						{
							CreatureSets[i]->TriggerID = br->ReadInt32();
							CreatureSets[i]->unknown_14 = br->ReadInt32();
							CreatureSets[i]->unknown_15 = br->ReadInt32();
						}
						else
						{
							CreatureSets[i]->TriggerID = 0;
							CreatureSets[i]->unknown_14 = 0;
							CreatureSets[i]->unknown_15 = 0;
						}
						CreatureSets[i]->CreatureGroups = gcnew array<CreatureGroup^>(CreatureGroups_count);
						for(int n=0; n<CreatureSets[i]->CreatureGroups->Length; n++)
						{
							CreatureSets[i]->CreatureGroups[n] = gcnew CreatureGroup();
							CreatureSets[i]->CreatureGroups[n]->ID = br->ReadInt32();
							CreatureSets[i]->CreatureGroups[n]->Amount = br->ReadInt32();
							CreatureSets[i]->CreatureGroups[n]->Respawn = br->ReadInt32();
							CreatureSets[i]->CreatureGroups[n]->unknown_2 = br->ReadInt32();
							CreatureSets[i]->CreatureGroups[n]->unknown_3 = br->ReadInt32();
							CreatureSets[i]->CreatureGroups[n]->unknown_4 = br->ReadInt32();
							CreatureSets[i]->CreatureGroups[n]->unknown_5 = br->ReadInt32();
							CreatureSets[i]->CreatureGroups[n]->unknown_6 = br->ReadInt32();
							CreatureSets[i]->CreatureGroups[n]->unknown_7 = br->ReadInt32();
							CreatureSets[i]->CreatureGroups[n]->unknown_8 = br->ReadInt32();
							CreatureSets[i]->CreatureGroups[n]->unknown_9 = br->ReadBoolean();
							CreatureSets[i]->CreatureGroups[n]->unknown_10 = br->ReadBoolean();
							CreatureSets[i]->CreatureGroups[n]->unknown_11 = br->ReadBoolean();
							CreatureSets[i]->CreatureGroups[n]->unknown_12 = br->ReadBoolean();
							CreatureSets[i]->CreatureGroups[n]->PathID = br->ReadInt32();
							CreatureSets[i]->CreatureGroups[n]->unknown_14 = br->ReadInt32();
							CreatureSets[i]->CreatureGroups[n]->unknown_15 = br->ReadInt32();
							CreatureSets[i]->CreatureGroups[n]->unknown_16 = br->ReadInt32();
						}
					}

					ResourceSets = gcnew array<ResourceSet^>(ResourceSets_count);
					for(int i=0; i<ResourceSets->Length; i++)
					{
						Application::DoEvents();

						ResourceSets[i] = gcnew ResourceSet();
						ResourceSets[i]->SpawnX = br->ReadSingle();
						ResourceSets[i]->SpawnAltitude = br->ReadSingle();
						ResourceSets[i]->SpawnZ = br->ReadSingle();
						ResourceSets[i]->SpreadX = br->ReadSingle();
						ResourceSets[i]->SpreadZ = br->ReadSingle();
						int ResourceGroups_count = br->ReadInt32();
						ResourceSets[i]->unknown_1 = br->ReadBoolean();
						ResourceSets[i]->unknown_2 = br->ReadBoolean();
						ResourceSets[i]->unknown_3 = br->ReadBoolean();
						ResourceSets[i]->unknown_4 = br->ReadInt32();
						if(Version == 10)
						{
							ResourceSets[i]->unknown_5a = br->ReadByte();
							ResourceSets[i]->unknown_5b = br->ReadByte();
							ResourceSets[i]->unknown_5c = br->ReadByte();
							ResourceSets[i]->TriggerID = br->ReadInt32();
							ResourceSets[i]->unknown_6 = br->ReadByte();
							ResourceSets[i]->unknown_7 = br->ReadBoolean();
							ResourceSets[i]->unknown_8 = br->ReadBoolean();
							ResourceSets[i]->unknown_9 = br->ReadBoolean();
						}
						else
						{
							ResourceSets[i]->unknown_5a = 192;
							ResourceSets[i]->unknown_5b = 63;
							ResourceSets[i]->unknown_5c = 0;
							ResourceSets[i]->TriggerID = 0;
							ResourceSets[i]->unknown_6 = 0;
							ResourceSets[i]->unknown_7 = false;
							ResourceSets[i]->unknown_8 = false;
							ResourceSets[i]->unknown_9 = false;
						}
						ResourceSets[i]->ResourceGroups = gcnew array<ResourceGroup^>(ResourceGroups_count);
						for(int n=0; n<ResourceSets[i]->ResourceGroups->Length; n++)
						{
							ResourceSets[i]->ResourceGroups[n] = gcnew ResourceGroup();
							ResourceSets[i]->ResourceGroups[n]->unknown_1 = br->ReadInt32();
							ResourceSets[i]->ResourceGroups[n]->ID = br->ReadInt32();
							ResourceSets[i]->ResourceGroups[n]->Respawn = br->ReadInt32();
							ResourceSets[i]->ResourceGroups[n]->Amount = br->ReadInt32();
							ResourceSets[i]->ResourceGroups[n]->unknown_2 = br->ReadInt32();
						}
					}

					Dynamics = gcnew array<Dynamic^>(Dynamics_count);
					for(int i=0; i<Dynamics->Length; i++)
					{
						Application::DoEvents();

						Dynamics[i] = gcnew Dynamic();
						Dynamics[i]->ID = br->ReadInt32();
						Dynamics[i]->SpawnX = br->ReadSingle();
						Dynamics[i]->SpawnAltitude = br->ReadSingle();
						Dynamics[i]->SpawnZ = br->ReadSingle();
						Dynamics[i]->unknown_5 = br->ReadByte();
						Dynamics[i]->unknown_6 = br->ReadByte();
						Dynamics[i]->unknown_7 = br->ReadByte();
						Dynamics[i]->TriggerID = br->ReadInt32();
						Dynamics[i]->unknown_8 = br->ReadByte();
					}

					Triggers = gcnew array<Trigger^>(Triggers_count);
					for(int i=0; i<Triggers->Length; i++)
					{
						Application::DoEvents();

						Triggers[i] = gcnew Trigger();
						Triggers[i]->TriggerID = br->ReadInt32();
						Triggers[i]->CreatureBuilderID = br->ReadInt32();
						Triggers[i]->Name = br->ReadBytes(128);
						Triggers[i]->unknown_3 = br->ReadBoolean();
						Triggers[i]->AutostartDelayTime = br->ReadInt32();
						Triggers[i]->AutostopDelayTime = br->ReadInt32();
						Triggers[i]->AutostartDisable = br->ReadBoolean();
						Triggers[i]->AutostopDisable = br->ReadBoolean();
						Triggers[i]->StartYear = br->ReadInt32();
						Triggers[i]->StartMonth = br->ReadInt32();
						Triggers[i]->StartWeekDay = br->ReadInt32();
						Triggers[i]->StartDay = br->ReadInt32();
						Triggers[i]->StartHour = br->ReadInt32();
						Triggers[i]->StartMinute = br->ReadInt32();
						Triggers[i]->EndYear = br->ReadInt32();
						Triggers[i]->EndMonth = br->ReadInt32();
						Triggers[i]->EndWeekDay = br->ReadInt32();
						Triggers[i]->EndDay = br->ReadInt32();
						Triggers[i]->EndHour = br->ReadInt32();
						Triggers[i]->EndMinute = br->ReadInt32();
						Triggers[i]->Duration = br->ReadInt32();
					}

					br->Close();
					fr->Close();
				}

				// save as version v10
				public: void Save(String^ File)
				{
					FileStream^ fs = gcnew FileStream(File, FileMode::Create, FileAccess::Write);
					BinaryWriter^ bw = gcnew BinaryWriter(fs);

					bw->Write((int)10);
					bw->Write(CreatureSets->Length);
					bw->Write(ResourceSets->Length);
					bw->Write(Dynamics->Length);
					bw->Write(Triggers->Length);

					for(int i=0; i<CreatureSets->Length; i++)
					{
						bw->Write(CreatureSets[i]->SpawnMode);
						bw->Write(CreatureSets[i]->CreatureGroups->Length);
						bw->Write(CreatureSets[i]->SpawnX);
						bw->Write(CreatureSets[i]->SpawnAltitude);
						bw->Write(CreatureSets[i]->SpawnZ);
						bw->Write(CreatureSets[i]->DirectionX);
						bw->Write(CreatureSets[i]->DirectionAltitude);
						bw->Write(CreatureSets[i]->DirectionZ);
						bw->Write(CreatureSets[i]->SpreadX);
						bw->Write(CreatureSets[i]->SpreadAltitude);
						bw->Write(CreatureSets[i]->SpreadZ);
						bw->Write(CreatureSets[i]->Type);
						bw->Write(CreatureSets[i]->unknown_8);
						bw->Write(CreatureSets[i]->unknown_9);
						bw->Write(CreatureSets[i]->unknown_10);
						bw->Write(CreatureSets[i]->InstantRespawn);
						bw->Write(CreatureSets[i]->unknown_12);
						bw->Write(CreatureSets[i]->TriggerID);
						bw->Write(CreatureSets[i]->unknown_14);
						bw->Write(CreatureSets[i]->unknown_15);
						for(int n=0; n<CreatureSets[i]->CreatureGroups->Length; n++)
						{
							bw->Write(CreatureSets[i]->CreatureGroups[n]->ID);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->Amount);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->Respawn);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->unknown_2);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->unknown_3);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->unknown_4);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->unknown_5);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->unknown_6);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->unknown_7);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->unknown_8);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->unknown_9);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->unknown_10);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->unknown_11);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->unknown_12);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->PathID);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->unknown_14);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->unknown_15);
							bw->Write(CreatureSets[i]->CreatureGroups[n]->unknown_16);
						}
					}

					for(int i=0; i<ResourceSets->Length; i++)
					{
						bw->Write(ResourceSets[i]->SpawnX);
						bw->Write(ResourceSets[i]->SpawnAltitude);
						bw->Write(ResourceSets[i]->SpawnZ);
						bw->Write(ResourceSets[i]->SpreadX);
						bw->Write(ResourceSets[i]->SpreadZ);
						bw->Write(ResourceSets[i]->ResourceGroups->Length);
						bw->Write(ResourceSets[i]->unknown_1);
						bw->Write(ResourceSets[i]->unknown_2);
						bw->Write(ResourceSets[i]->unknown_3);
						bw->Write(ResourceSets[i]->unknown_4);
						bw->Write(ResourceSets[i]->unknown_5a);
						bw->Write(ResourceSets[i]->unknown_5b);
						bw->Write(ResourceSets[i]->unknown_5c);
						bw->Write(ResourceSets[i]->TriggerID);
						bw->Write(ResourceSets[i]->unknown_6);
						bw->Write(ResourceSets[i]->unknown_7);
						bw->Write(ResourceSets[i]->unknown_8);
						bw->Write(ResourceSets[i]->unknown_9);
						for(int n=0; n<ResourceSets[i]->ResourceGroups->Length; n++)
						{
							bw->Write(ResourceSets[i]->ResourceGroups[n]->unknown_1);
							bw->Write(ResourceSets[i]->ResourceGroups[n]->ID);
							bw->Write(ResourceSets[i]->ResourceGroups[n]->Respawn);
							bw->Write(ResourceSets[i]->ResourceGroups[n]->Amount);
							bw->Write(ResourceSets[i]->ResourceGroups[n]->unknown_2);
						}
					}

					for(int i=0; i<Dynamics->Length; i++)
					{
						bw->Write(Dynamics[i]->ID);
						bw->Write(Dynamics[i]->SpawnX);
						bw->Write(Dynamics[i]->SpawnAltitude);
						bw->Write(Dynamics[i]->SpawnZ);
						bw->Write(Dynamics[i]->unknown_5);
						bw->Write(Dynamics[i]->unknown_6);
						bw->Write(Dynamics[i]->unknown_7);
						bw->Write(Dynamics[i]->TriggerID);
						bw->Write(Dynamics[i]->unknown_8);
					}

					for(int i=0; i<Triggers->Length; i++)
					{
						bw->Write(Triggers[i]->TriggerID);
						bw->Write(Triggers[i]->CreatureBuilderID);
						bw->Write(Triggers[i]->Name);
						bw->Write(Triggers[i]->unknown_3);
						bw->Write(Triggers[i]->AutostartDelayTime);
						bw->Write(Triggers[i]->AutostopDelayTime);
						bw->Write(Triggers[i]->AutostartDisable);
						bw->Write(Triggers[i]->AutostopDisable);
						bw->Write(Triggers[i]->StartYear);
						bw->Write(Triggers[i]->StartMonth);
						bw->Write(Triggers[i]->StartWeekDay);
						bw->Write(Triggers[i]->StartDay);
						bw->Write(Triggers[i]->StartHour);
						bw->Write(Triggers[i]->StartMinute);
						bw->Write(Triggers[i]->EndYear);
						bw->Write(Triggers[i]->EndMonth);
						bw->Write(Triggers[i]->EndWeekDay);
						bw->Write(Triggers[i]->EndDay);
						bw->Write(Triggers[i]->EndHour);
						bw->Write(Triggers[i]->EndMinute);
						bw->Write(Triggers[i]->Duration);
					}

					bw->Close();
					fs->Close();
				}
			};
		}
	}
}