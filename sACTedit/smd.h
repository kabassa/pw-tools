#pragma once

namespace PW
{
	namespace Models
	{
		public ref struct AnimatedJointAct abstract
		{
			array<unsigned char>^ ActName; // GBK encoded
		};

		public ref struct AnimatedJointAct5SubBlock
		{
			int JointID;
			float StartSample;
			float EndSample;
			int unknown1;
			float unknown2;
		};

		public ref struct AnimatedJointAct5 : AnimatedJointAct
		{
			int seperator;
			int unknown;
			array<AnimatedJointAct5SubBlock^>^ AnimatedJointActSubBlocks;
		};

		public ref struct AnimatedJointAct6 : AnimatedJointAct
		{
			float StartSample;
			float EndSample;
		};

		public ref struct AnimatedJointAct8 : AnimatedJointAct
		{
			float StartSample;
			float EndSample;
			array<unsigned char>^ StckFile;
		};

		public ref class SMD
		{
			public: SMD()
			{
				enc = Encoding::GetEncoding("GBK");
			}

			protected: ~SMD()
			{
			}

			private: Encoding^ enc;
			public: array<unsigned char>^ Signature; // 8 byte
			public: int Version;
			public: int unknown;
			public: array<unsigned char>^ zeros; // 68 byte
			public: array<unsigned char>^ BonFile; // GBK encoded
			public: array<unsigned char>^ SkiFile; // GBK encoded
			public: array<unsigned char>^ PhyFile; // GBK encoded
			public: array<unsigned char>^ TckPath; // GBK encoded
			private: array<AnimatedJointAct^>^ AnimatedJointActs;

			// only for loading v5, v6 and v8
			public: void Load(String^ File)
			{
				FileStream^ fs =File::OpenRead(File);
				BinaryReader^ br = gcnew BinaryReader(fs);

				Signature = br->ReadBytes(8);
				Version = br->ReadInt32();
				unknown = br->ReadInt32();
				int BlockCount = br->ReadInt32();
				zeros = br->ReadBytes(68);
				int BonPathCharCount = br->ReadInt32();
				BonFile = br->ReadBytes(BonPathCharCount);
				int SkiPathCharCount = br->ReadInt32();
				SkiFile = br->ReadBytes(SkiPathCharCount);
				if(unknown > 0)
				{
					int PhyPathCharCount = br->ReadInt32();
					PhyFile = br->ReadBytes(PhyPathCharCount);
				}
				if(Version > 6)
				{
					int TckPathCharCount = br->ReadInt32();
					TckPath = br->ReadBytes(TckPathCharCount);
				}
				AnimatedJointActs = gcnew array<AnimatedJointAct^>(BlockCount);
				for(int i=0; i<AnimatedJointActs->Length; i++)
				{
					if(Version == 5)
					{
						AnimatedJointActs[i] = gcnew AnimatedJointAct5();
						int ActNameCharCount = br->ReadInt32();
						((AnimatedJointAct5^)AnimatedJointActs[i])->ActName = br->ReadBytes(ActNameCharCount);
						((AnimatedJointAct5^)AnimatedJointActs[i])->seperator = br->ReadInt32();
						int AnimatedJointActSubBlockCount = br->ReadInt32();
						((AnimatedJointAct5^)AnimatedJointActs[i])->unknown = br->ReadInt32();
						((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks = gcnew array<AnimatedJointAct5SubBlock^>(AnimatedJointActSubBlockCount);
						for(int n=0; n<((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks->Length; n++)
						{
							((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks[n] = gcnew AnimatedJointAct5SubBlock();
							((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks[n]->JointID = br->ReadInt32();
							((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks[n]->StartSample = br->ReadSingle();
							((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks[n]->EndSample = br->ReadSingle();
							((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks[n]->unknown1 = br->ReadInt32();
							((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks[n]->unknown2 = br->ReadSingle();
						}
					}
					if(Version == 6)
					{
						AnimatedJointActs[i] = gcnew AnimatedJointAct6();
						int ActNameCharCount = br->ReadInt32();
						((AnimatedJointAct6^)AnimatedJointActs[i])->ActName = br->ReadBytes(ActNameCharCount);
						((AnimatedJointAct6^)AnimatedJointActs[i])->StartSample = br->ReadSingle();
						((AnimatedJointAct6^)AnimatedJointActs[i])->EndSample = br->ReadSingle();
					}
					if(Version == 8)
					{
						AnimatedJointActs[i] = gcnew AnimatedJointAct8();
						int ActNameCharCount = br->ReadInt32();
						((AnimatedJointAct8^)AnimatedJointActs[i])->ActName = br->ReadBytes(ActNameCharCount);
						((AnimatedJointAct8^)AnimatedJointActs[i])->StartSample = br->ReadSingle();
						((AnimatedJointAct8^)AnimatedJointActs[i])->EndSample = br->ReadSingle();
						int StckFileCharCount = br->ReadInt32();
						((AnimatedJointAct8^)AnimatedJointActs[i])->StckFile = br->ReadBytes(StckFileCharCount);
					}
				}

				br->Close();
				fs->Close();
			}

			// only for saving v5, v6 and v8
			public: void Save(String^ File)
			{
				FileStream^ fs = gcnew FileStream(File, FileMode::Create, FileAccess::Write);
				BinaryWriter^ bw = gcnew BinaryWriter(fs);

				bw->Write(Signature);
				bw->Write(Version);
				bw->Write(unknown);
				bw->Write(AnimatedJointActs->Length);
				bw->Write(zeros);
				bw->Write(BonFile->Length);
				bw->Write(BonFile);
				bw->Write(SkiFile->Length);
				bw->Write(SkiFile);
				if(unknown > 0)
				{
					bw->Write(PhyFile->Length);
					bw->Write(PhyFile);
				}
				if(Version > 6)
				{
					bw->Write(TckPath->Length);
					bw->Write(TckPath);
				}
				for(int i=0; i<AnimatedJointActs->Length; i++)
				{
					if(Version == 5)
					{
						bw->Write(((AnimatedJointAct5^)AnimatedJointActs[i])->ActName->Length);
						bw->Write(((AnimatedJointAct5^)AnimatedJointActs[i])->ActName);
						bw->Write(((AnimatedJointAct5^)AnimatedJointActs[i])->seperator);
						bw->Write(((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks->Length);
						bw->Write(((AnimatedJointAct5^)AnimatedJointActs[i])->unknown);
						for(int n=0; n<((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks->Length; n++)
						{
							bw->Write(((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks[n]->JointID);
							bw->Write(((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks[n]->StartSample);
							bw->Write(((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks[n]->EndSample);
							bw->Write(((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks[n]->unknown1);
							bw->Write(((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks[n]->unknown2);
						}
					}
					if(Version == 6)
					{
						bw->Write(((AnimatedJointAct6^)AnimatedJointActs[i])->ActName->Length);
						bw->Write(((AnimatedJointAct6^)AnimatedJointActs[i])->ActName);
						bw->Write(((AnimatedJointAct6^)AnimatedJointActs[i])->StartSample);
						bw->Write(((AnimatedJointAct6^)AnimatedJointActs[i])->EndSample);
					}
					if(Version == 8)
					{
						bw->Write(((AnimatedJointAct8^)AnimatedJointActs[i])->ActName->Length);
						bw->Write(((AnimatedJointAct8^)AnimatedJointActs[i])->ActName);
						bw->Write(((AnimatedJointAct8^)AnimatedJointActs[i])->StartSample);
						bw->Write(((AnimatedJointAct8^)AnimatedJointActs[i])->EndSample);
						bw->Write(((AnimatedJointAct8^)AnimatedJointActs[i])->StckFile->Length);
						bw->Write(((AnimatedJointAct8^)AnimatedJointActs[i])->StckFile);
					}
				}

				bw->Close();
				fs->Close();
			}

			public: int GetAnimatedJointActCount()
			{
				return AnimatedJointActs->Length;
			}
			public: String^ GetActName(int ActIndex)
			{
				return enc->GetString(AnimatedJointActs[ActIndex]->ActName);
			}
			public: String^ GetStckFile(int ActIndex)
			{
				if(Version == 8)
				{
					return (enc->GetString(TckPath) + "\\" + enc->GetString(((AnimatedJointAct8^)AnimatedJointActs[ActIndex])->StckFile));
				}
				return "";
			}
			public: float GetStartSample(int ActIndex)
			{
				if(Version == 5)
				{
					float startSample = float::MaxValue;
					for(int n=0; n<((AnimatedJointAct5^)AnimatedJointActs[ActIndex])->AnimatedJointActSubBlocks->Length; n++)
					{
						if(startSample > ((AnimatedJointAct5^)AnimatedJointActs[ActIndex])->AnimatedJointActSubBlocks[n]->StartSample)
						{
							startSample = ((AnimatedJointAct5^)AnimatedJointActs[ActIndex])->AnimatedJointActSubBlocks[n]->StartSample;
						}
					}
					return startSample;
				}
				if(Version == 6)
				{
					return ((AnimatedJointAct6^)AnimatedJointActs[ActIndex])->StartSample;
				}
				if(Version == 8)
				{
					return ((AnimatedJointAct8^)AnimatedJointActs[ActIndex])->StartSample;
				}
				return -1;
			}
			public: float GetEndSample(int ActIndex)
			{
				if(Version == 5)
				{
					float endSample = float::MinValue;
					for(int n=0; n<((AnimatedJointAct5^)AnimatedJointActs[ActIndex])->AnimatedJointActSubBlocks->Length; n++)
					{
						if(endSample < ((AnimatedJointAct5^)AnimatedJointActs[ActIndex])->AnimatedJointActSubBlocks[n]->EndSample)
						{
							endSample = ((AnimatedJointAct5^)AnimatedJointActs[ActIndex])->AnimatedJointActSubBlocks[n]->EndSample;
						}
					}
					return endSample;
				}
				if(Version == 6)
				{
					return ((AnimatedJointAct6^)AnimatedJointActs[ActIndex])->EndSample;
				}
				if(Version == 8)
				{
					return ((AnimatedJointAct8^)AnimatedJointActs[ActIndex])->EndSample;
				}
				return -1;
			}
			public: void SetSample(int ActIndex, float StartSample, float EndSample)
			{
				if(Version == 5)
				{
					float NewStartSample;
					float NewEndSample;

					for(int i=ActIndex; i<AnimatedJointActs->Length; i++)
					{
						if(i == ActIndex)
						{
							NewStartSample = GetStartSample(i);
							NewEndSample = NewStartSample + (EndSample - StartSample);
						}
						else
						{
							float diff = GetEndSample(i) - GetStartSample(i);
							NewStartSample = GetEndSample(i-1)+1; 
							NewEndSample = NewStartSample + diff;
						}

						for(int n=0; n<((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks->Length; n++)
						{
							((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks[n]->StartSample = NewStartSample;
							((AnimatedJointAct5^)AnimatedJointActs[i])->AnimatedJointActSubBlocks[n]->EndSample = NewEndSample;
						}
					}
				}
				if(Version == 6)
				{
					for(int i=ActIndex; i<AnimatedJointActs->Length; i++)
					{
						if(i == ActIndex)
						{
							((AnimatedJointAct6^)AnimatedJointActs[i])->EndSample = GetStartSample(i) + (EndSample - StartSample);
						}
						else
						{
							float diff = GetEndSample(i) - GetStartSample(i);
							((AnimatedJointAct6^)AnimatedJointActs[i])->StartSample = GetEndSample(i-1)+1; 
							((AnimatedJointAct6^)AnimatedJointActs[i])->EndSample = GetStartSample(i) + diff;
						}
					}
				}
				if(Version == 8)
				{
					((AnimatedJointAct8^)AnimatedJointActs[ActIndex])->StartSample = StartSample;
					((AnimatedJointAct8^)AnimatedJointActs[ActIndex])->EndSample = EndSample;
				}
			}
		};
	}
}