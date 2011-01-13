#pragma once

namespace PW
{
	namespace Models
	{
		public ref struct Point3f
		{
			float X;
			float Y;
			float Z;
		};

		public ref struct Point4f
		{
			float X;
			float Y;
			float Z;
			float W;
		};

		public ref struct KeyPointController
		{
			int StartTime;
			int EndTime;
			int StartKeyPointIndex;
			int EndKeyPointIndex;
		};

		public ref struct AnimatedJointKeyFrames
		{
			public: int JointID;
			public: int unknown1;
			public: array<Point3f^>^ PositionKeyPoints; // vectors
			public: array<KeyPointController^>^ PositionKeyPointControllers;
			public: int unknown2;
			public: array<Point4f^>^ OrientationKeyPoints; // quaternions
			public: array<KeyPointController^>^ OrientationKeyPointControllers;
		};

		public ref class STCK
		{
			public: STCK()
			{
			}

			protected: ~STCK()
			{
			}

			public: array<unsigned char>^ Signature; // 8 byte GBK
			public: int Version;
			public: int unknown1;
			public: int unknown2;
			public: int unknown3;
			public: array<AnimatedJointKeyFrames^>^ JointKeyFrames;

			// only for loading v1
			public: void Load(String^ File)
			{
				FileStream^ fs = File::OpenRead(File);
				BinaryReader^ br = gcnew BinaryReader(fs);

				Signature = br->ReadBytes(8);
				Version = br->ReadInt32();
				int AnimatedJointCount = br->ReadInt32();
				unknown1 = br->ReadInt32();
				unknown2 = br->ReadInt32();
				unknown3 = br->ReadInt32();

				JointKeyFrames = gcnew array<AnimatedJointKeyFrames^>(AnimatedJointCount);
				for(int b=0; b<JointKeyFrames->Length; b++)
				{
					JointKeyFrames[b] = gcnew AnimatedJointKeyFrames();
					JointKeyFrames[b]->JointID = br->ReadInt32();
					int PositionKeyPointCount = br->ReadInt32();
					int Properties1KeyPointCount = br->ReadInt32();
					JointKeyFrames[b]->unknown1 = br->ReadInt32();
					JointKeyFrames[b]->PositionKeyPoints = gcnew array<Point3f^>(PositionKeyPointCount);
					for(int i=0; i<JointKeyFrames[b]->PositionKeyPoints->Length; i++)
					{
						JointKeyFrames[b]->PositionKeyPoints[i] = gcnew Point3f();
						JointKeyFrames[b]->PositionKeyPoints[i]->X = br->ReadSingle();
						JointKeyFrames[b]->PositionKeyPoints[i]->Y = br->ReadSingle();
						JointKeyFrames[b]->PositionKeyPoints[i]->Z = br->ReadSingle();
					}
					JointKeyFrames[b]->PositionKeyPointControllers = gcnew array<KeyPointController^>(Properties1KeyPointCount);
					for(int i=0; i<JointKeyFrames[b]->PositionKeyPointControllers->Length; i++)
					{
						JointKeyFrames[b]->PositionKeyPointControllers[i] = gcnew KeyPointController();
						JointKeyFrames[b]->PositionKeyPointControllers[i]->StartTime = br->ReadInt32();
						JointKeyFrames[b]->PositionKeyPointControllers[i]->EndTime = br->ReadInt32();
						JointKeyFrames[b]->PositionKeyPointControllers[i]->StartKeyPointIndex = br->ReadInt32();
						JointKeyFrames[b]->PositionKeyPointControllers[i]->EndKeyPointIndex = br->ReadInt32();
					}
					int OrientationKeyPointCount = br->ReadInt32();
					int Properties2KeyPointCount = br->ReadInt32();
					JointKeyFrames[b]->unknown2 = br->ReadInt32();
					JointKeyFrames[b]->OrientationKeyPoints = gcnew array<Point4f^>(OrientationKeyPointCount);
					for(int i=0; i<JointKeyFrames[b]->OrientationKeyPoints->Length; i++)
					{
						JointKeyFrames[b]->OrientationKeyPoints[i] = gcnew Point4f();
						JointKeyFrames[b]->OrientationKeyPoints[i]->X = br->ReadSingle();
						JointKeyFrames[b]->OrientationKeyPoints[i]->Y = br->ReadSingle();
						JointKeyFrames[b]->OrientationKeyPoints[i]->Z = br->ReadSingle();
						JointKeyFrames[b]->OrientationKeyPoints[i]->W = br->ReadSingle();
					}
					JointKeyFrames[b]->OrientationKeyPointControllers = gcnew array<KeyPointController^>(Properties2KeyPointCount);
					for(int i=0; i<JointKeyFrames[b]->OrientationKeyPointControllers->Length; i++)
					{
						JointKeyFrames[b]->OrientationKeyPointControllers[i] = gcnew KeyPointController();
						JointKeyFrames[b]->OrientationKeyPointControllers[i]->StartTime = br->ReadInt32();
						JointKeyFrames[b]->OrientationKeyPointControllers[i]->EndTime = br->ReadInt32();
						JointKeyFrames[b]->OrientationKeyPointControllers[i]->StartKeyPointIndex = br->ReadInt32();
						JointKeyFrames[b]->OrientationKeyPointControllers[i]->EndKeyPointIndex = br->ReadInt32();
					}
				}

				br->Close();
				fs->Close();
			}

			// only for saving v1
			public: void Save(String^ File)
			{
				FileStream^ fs = gcnew FileStream(File, FileMode::Create, FileAccess::Write);
				BinaryWriter^ bw = gcnew BinaryWriter(fs);

				bw->Write(Signature);
				bw->Write(Version);
				bw->Write(JointKeyFrames->Length);
				bw->Write(unknown1);
				bw->Write(unknown2);
				bw->Write(unknown3);

				for(int b=0; b<JointKeyFrames->Length; b++)
				{
					bw->Write(JointKeyFrames[b]->JointID);
					bw->Write(JointKeyFrames[b]->PositionKeyPoints->Length);
					bw->Write(JointKeyFrames[b]->PositionKeyPointControllers->Length);
					bw->Write(JointKeyFrames[b]->unknown1);
					for(int i=0; i<JointKeyFrames[b]->PositionKeyPoints->Length; i++)
					{
						bw->Write(JointKeyFrames[b]->PositionKeyPoints[i]->X);
						bw->Write(JointKeyFrames[b]->PositionKeyPoints[i]->Y);
						bw->Write(JointKeyFrames[b]->PositionKeyPoints[i]->Z);
					}
					for(int i=0; i<JointKeyFrames[b]->PositionKeyPointControllers->Length; i++)
					{
						bw->Write(JointKeyFrames[b]->PositionKeyPointControllers[i]->StartTime);
						bw->Write(JointKeyFrames[b]->PositionKeyPointControllers[i]->EndTime);
						bw->Write(JointKeyFrames[b]->PositionKeyPointControllers[i]->StartKeyPointIndex);
						bw->Write(JointKeyFrames[b]->PositionKeyPointControllers[i]->EndKeyPointIndex);
					}
					bw->Write(JointKeyFrames[b]->OrientationKeyPoints->Length);
					bw->Write(JointKeyFrames[b]->OrientationKeyPointControllers->Length);
					bw->Write(JointKeyFrames[b]->unknown2);
					for(int i=0; i<JointKeyFrames[b]->OrientationKeyPoints->Length; i++)
					{
						bw->Write(JointKeyFrames[b]->OrientationKeyPoints[i]->X);
						bw->Write(JointKeyFrames[b]->OrientationKeyPoints[i]->Y);
						bw->Write(JointKeyFrames[b]->OrientationKeyPoints[i]->Z);
						bw->Write(JointKeyFrames[b]->OrientationKeyPoints[i]->W);
					}
					for(int i=0; i<JointKeyFrames[b]->OrientationKeyPointControllers->Length; i++)
					{
						bw->Write(JointKeyFrames[b]->OrientationKeyPointControllers[i]->StartTime);
						bw->Write(JointKeyFrames[b]->OrientationKeyPointControllers[i]->EndTime);
						bw->Write(JointKeyFrames[b]->OrientationKeyPointControllers[i]->StartKeyPointIndex);
						bw->Write(JointKeyFrames[b]->OrientationKeyPointControllers[i]->EndKeyPointIndex);
					}
				}

				bw->Close();
				fs->Close();
			}
		};
	}
}