#pragma once

#include "stck.h"

namespace PW
{
	namespace Models
	{
		public ref struct Joint
		{
			//int NameCharCount;
			array<unsigned char>^ Name; // char_count bytes GBK
			int unknown;
			int PreviousJointID;
			int ID;
			//int ConnectionCount;
			array<unsigned char>^ Parameters; // 32 float values (4*32 byte)
			array<int>^ ConnectionIDs;
		};

		public ref struct AnimatedJoint
		{
			//int NameCharCount;
			array<unsigned char>^ Name; // char_count bytes GBK
			int PreviousAnimatedJointID;
			int ID;
			int unknown;
			AnimatedJointKeyFrames^ JointKeyFrames; // only for bon Version < 6
		};

		public ref struct Hook
		{
			//int NameCharCount;
			array<unsigned char>^ Name; // char_count bytes GBK
			int unknown_1;
			int unknown_2;
			array<float>^ TransformationMatrix; // 4x4 floats
		};

		public ref class BON
		{
			public: BON()
			{
			}

			protected: ~BON()
			{
			}

			public: array<unsigned char>^ Signature; // 8 byte GBK
			public: int Version;
			private: int unknown_1;
			public: int Samples;
			private: int unknown_3;
			private: array<unsigned char>^ zeros; // 64 byte
			public: array<Joint^>^ Joints;
			private: array<int>^ unknowns;
			public: array<AnimatedJoint^>^ AnimatedJoints;
			public: array<Hook^>^ Hooks;

			// only for loading v5 and v6
			public: void Load(String^ File)
			{
				FileStream^ fs =File::OpenRead(File);
				BinaryReader^ br = gcnew BinaryReader(fs);

				Signature = br->ReadBytes(8);
				Version = br->ReadInt32();
				int JointCount = br->ReadInt32();
				int AnimatedJointCount = br->ReadInt32();
				int HookCount = br->ReadInt32();
				unknown_1 = br->ReadInt32();
				Samples = br->ReadInt32();
				unknown_3 = br->ReadInt32();
				zeros = br->ReadBytes(64);
				Joints = gcnew array<Joint^>(JointCount);
				for(int b=0; b<Joints->Length; b++)
				{
					Joints[b] = gcnew Joint();
					int NameCharCount = br->ReadInt32();
					Joints[b]->Name = br->ReadBytes(NameCharCount);
					Joints[b]->unknown = br->ReadInt32();
					Joints[b]->PreviousJointID = br->ReadInt32();
					Joints[b]->ID = br->ReadInt32();
					int ConnectionCount = br->ReadInt32();
					Joints[b]->Parameters = br->ReadBytes(128);
					Joints[b]->ConnectionIDs = gcnew array<int>(ConnectionCount);
					for(int i=0; i<Joints[b]->ConnectionIDs->Length; i++)
					{
						Joints[b]->ConnectionIDs[i] = br->ReadInt32();
					}
				}
				unknowns = gcnew array<int>(JointCount);
				for(int b=0; b<unknowns->Length; b++)
				{
					unknowns[b] = br->ReadInt32();
				}
				AnimatedJoints = gcnew array<AnimatedJoint^>(AnimatedJointCount);
				for(int a=0; a<AnimatedJoints->Length; a++)
				{
					AnimatedJoints[a] = gcnew AnimatedJoint();
					int NameCharCount = br->ReadInt32();
					AnimatedJoints[a]->Name = br->ReadBytes(NameCharCount);
					AnimatedJoints[a]->PreviousAnimatedJointID = br->ReadInt32();
					AnimatedJoints[a]->ID = br->ReadInt32();
					AnimatedJoints[a]->unknown = br->ReadInt32();
					if(Version < 6)
					{
						AnimatedJoints[a]->JointKeyFrames = gcnew AnimatedJointKeyFrames();
						AnimatedJoints[a]->JointKeyFrames->JointID = AnimatedJoints[a]->ID;
						int PositionKeyPointCount = br->ReadInt32();
						int Properties1KeyPointCount = br->ReadInt32();
						AnimatedJoints[a]->JointKeyFrames->unknown1 = br->ReadInt32();
						AnimatedJoints[a]->JointKeyFrames->PositionKeyPoints = gcnew array<Point3f^>(PositionKeyPointCount);
						for(int i=0; i<	AnimatedJoints[a]->JointKeyFrames->PositionKeyPoints->Length; i++)
						{
							AnimatedJoints[a]->JointKeyFrames->PositionKeyPoints[i] = gcnew Point3f();
							AnimatedJoints[a]->JointKeyFrames->PositionKeyPoints[i]->X = br->ReadSingle();
							AnimatedJoints[a]->JointKeyFrames->PositionKeyPoints[i]->Y = br->ReadSingle();
							AnimatedJoints[a]->JointKeyFrames->PositionKeyPoints[i]->Z = br->ReadSingle();
						}
						AnimatedJoints[a]->JointKeyFrames->PositionKeyPointControllers = gcnew array<KeyPointController^>(Properties1KeyPointCount);
						for(int i=0; i<	AnimatedJoints[a]->JointKeyFrames->PositionKeyPointControllers->Length; i++)
						{
							AnimatedJoints[a]->JointKeyFrames->PositionKeyPointControllers[i] = gcnew KeyPointController();
							AnimatedJoints[a]->JointKeyFrames->PositionKeyPointControllers[i]->StartTime = br->ReadInt32();
							AnimatedJoints[a]->JointKeyFrames->PositionKeyPointControllers[i]->EndTime = br->ReadInt32();
							AnimatedJoints[a]->JointKeyFrames->PositionKeyPointControllers[i]->StartKeyPointIndex = br->ReadInt32();
							AnimatedJoints[a]->JointKeyFrames->PositionKeyPointControllers[i]->EndKeyPointIndex = br->ReadInt32();
						}
						int OrientationKeyPointCount = br->ReadInt32();
						int Properties2KeyPointCount = br->ReadInt32();
						AnimatedJoints[a]->JointKeyFrames->unknown2 = br->ReadInt32();
						AnimatedJoints[a]->JointKeyFrames->OrientationKeyPoints = gcnew array<Point4f^>(OrientationKeyPointCount);
						for(int i=0; i<	AnimatedJoints[a]->JointKeyFrames->OrientationKeyPoints->Length; i++)
						{
							AnimatedJoints[a]->JointKeyFrames->OrientationKeyPoints[i] = gcnew Point4f();
							AnimatedJoints[a]->JointKeyFrames->OrientationKeyPoints[i]->X = br->ReadSingle();
							AnimatedJoints[a]->JointKeyFrames->OrientationKeyPoints[i]->Y = br->ReadSingle();
							AnimatedJoints[a]->JointKeyFrames->OrientationKeyPoints[i]->Z = br->ReadSingle();
							AnimatedJoints[a]->JointKeyFrames->OrientationKeyPoints[i]->W = br->ReadSingle();
						}
						AnimatedJoints[a]->JointKeyFrames->OrientationKeyPointControllers = gcnew array<KeyPointController^>(Properties2KeyPointCount);
						for(int i=0; i<	AnimatedJoints[a]->JointKeyFrames->OrientationKeyPointControllers->Length; i++)
						{
							AnimatedJoints[a]->JointKeyFrames->OrientationKeyPointControllers[i] = gcnew KeyPointController();;
							AnimatedJoints[a]->JointKeyFrames->OrientationKeyPointControllers[i]->StartTime = br->ReadInt32();
							AnimatedJoints[a]->JointKeyFrames->OrientationKeyPointControllers[i]->EndTime = br->ReadInt32();
							AnimatedJoints[a]->JointKeyFrames->OrientationKeyPointControllers[i]->StartKeyPointIndex = br->ReadInt32();
							AnimatedJoints[a]->JointKeyFrames->OrientationKeyPointControllers[i]->EndKeyPointIndex = br->ReadInt32();
						}
					}
				}
				Hooks = gcnew array<Hook^>(HookCount);
				for(int h=0; h<Hooks->Length; h++)
				{
					Hooks[h] = gcnew Hook();
					int NameCharCount = br->ReadInt32();
					Hooks[h]->Name = br->ReadBytes(NameCharCount);
					Hooks[h]->unknown_1 = br->ReadInt32();
					Hooks[h]->unknown_2 = br->ReadInt32();
					Hooks[h]->TransformationMatrix = gcnew array<float>(16);
					for(int m=0; m<Hooks[h]->TransformationMatrix->Length; m++)
					{
						Hooks[h]->TransformationMatrix[m] = br->ReadSingle();
					}
				}

				br->Close();
				fs->Close();
			}

			// only for saving v5 and v6
			void Save(String^ File)
			{
				FileStream^ fs = gcnew FileStream(File, FileMode::Create, FileAccess::Write);
				BinaryWriter^ bw = gcnew BinaryWriter(fs);

				bw->Write(Signature);
				bw->Write(Version);
				bw->Write(Joints->Length);
				bw->Write(AnimatedJoints->Length);
				bw->Write(Hooks->Length);
				bw->Write(unknown_1);
				bw->Write(Samples);
				bw->Write(unknown_3);
				bw->Write(zeros);
				for(int b=0; b<Joints->Length; b++)
				{
					bw->Write(Joints[b]->Name->Length);
					bw->Write(Joints[b]->Name);
					bw->Write(Joints[b]->unknown);
					bw->Write(Joints[b]->PreviousJointID);
					bw->Write(Joints[b]->ID);
					bw->Write(Joints[b]->ConnectionIDs->Length);
					bw->Write(Joints[b]->Parameters);
					for(int i=0; i<Joints[b]->ConnectionIDs->Length; i++)
					{
						bw->Write(Joints[b]->ConnectionIDs[i]);
					}
				}
				for(int b=0; b<unknowns->Length; b++)
				{
					bw->Write(unknowns[b]);
				}
				for(int a=0; a<AnimatedJoints->Length; a++)
				{
					bw->Write(AnimatedJoints[a]->Name->Length);
					bw->Write(AnimatedJoints[a]->Name);
					bw->Write(AnimatedJoints[a]->PreviousAnimatedJointID);
					bw->Write(AnimatedJoints[a]->ID);
					bw->Write(AnimatedJoints[a]->unknown);
					if(Version < 6)
					{
						bw->Write(AnimatedJoints[a]->JointKeyFrames->PositionKeyPoints->Length);
						bw->Write(AnimatedJoints[a]->JointKeyFrames->PositionKeyPointControllers->Length);
						bw->Write(AnimatedJoints[a]->JointKeyFrames->unknown1);
						for(int i=0; i<	AnimatedJoints[a]->JointKeyFrames->PositionKeyPoints->Length; i++)
						{
							bw->Write(AnimatedJoints[a]->JointKeyFrames->PositionKeyPoints[i]->X);
							bw->Write(AnimatedJoints[a]->JointKeyFrames->PositionKeyPoints[i]->Y);
							bw->Write(AnimatedJoints[a]->JointKeyFrames->PositionKeyPoints[i]->Z);
						}
						for(int i=0; i<	AnimatedJoints[a]->JointKeyFrames->PositionKeyPointControllers->Length; i++)
						{
							bw->Write(AnimatedJoints[a]->JointKeyFrames->PositionKeyPointControllers[i]->StartTime);
							bw->Write(AnimatedJoints[a]->JointKeyFrames->PositionKeyPointControllers[i]->EndTime);
							bw->Write(AnimatedJoints[a]->JointKeyFrames->PositionKeyPointControllers[i]->StartKeyPointIndex);
							bw->Write(AnimatedJoints[a]->JointKeyFrames->PositionKeyPointControllers[i]->EndKeyPointIndex);
						}
						bw->Write(AnimatedJoints[a]->JointKeyFrames->OrientationKeyPoints->Length);
						bw->Write(AnimatedJoints[a]->JointKeyFrames->OrientationKeyPointControllers->Length);
						bw->Write(AnimatedJoints[a]->JointKeyFrames->unknown2);
						for(int i=0; i<	AnimatedJoints[a]->JointKeyFrames->OrientationKeyPoints->Length; i++)
						{
							bw->Write(AnimatedJoints[a]->JointKeyFrames->OrientationKeyPoints[i]->X);
							bw->Write(AnimatedJoints[a]->JointKeyFrames->OrientationKeyPoints[i]->Y);
							bw->Write(AnimatedJoints[a]->JointKeyFrames->OrientationKeyPoints[i]->Z);
							bw->Write(AnimatedJoints[a]->JointKeyFrames->OrientationKeyPoints[i]->W);
						}
						for(int i=0; i<	AnimatedJoints[a]->JointKeyFrames->OrientationKeyPointControllers->Length; i++)
						{
							bw->Write(AnimatedJoints[a]->JointKeyFrames->OrientationKeyPointControllers[i]->StartTime);
							bw->Write(AnimatedJoints[a]->JointKeyFrames->OrientationKeyPointControllers[i]->EndTime);
							bw->Write(AnimatedJoints[a]->JointKeyFrames->OrientationKeyPointControllers[i]->StartKeyPointIndex);
							bw->Write(AnimatedJoints[a]->JointKeyFrames->OrientationKeyPointControllers[i]->EndKeyPointIndex);
						}
					}
				}
				for(int h=0; h<Hooks->Length; h++)
				{
					bw->Write(Hooks[h]->Name->Length);
					bw->Write(Hooks[h]->Name);
					bw->Write(Hooks[h]->unknown_1);
					bw->Write(Hooks[h]->unknown_2);
					for(int m=0; m<Hooks[h]->TransformationMatrix->Length; m++)
					{
						bw->Write(Hooks[h]->TransformationMatrix[m]);
					}
				}

				bw->Close();
				fs->Close();
			}

		};
	}
}