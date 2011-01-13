#pragma once

using namespace System::IO;
using namespace System::Text;

#include "ecm.h"
#include "smd.h"
#include "ski.h"
#include "bon.h"
#include "stck.h"

public ref class Act
{
	public: Act(void)
	{
	}

	protected: ~Act()
	{
	}

	public: float StartSample;
	public: float EndSample;
	array<AnimatedJoint^>^ AnimatedJoints;

	public: void Load(String^ File)
	{
		FileStream^ fs =File::OpenRead(File);
		BinaryReader^ br = gcnew BinaryReader(fs);

		StartSample = br->ReadSingle();
		EndSample = br->ReadSingle();
		int AnimatedJointCount = br->ReadInt32();
		AnimatedJoints = gcnew array<AnimatedJoint^>(AnimatedJointCount);
		for(int a=0; a<AnimatedJoints->Length; a++)
		{
			AnimatedJoints[a] = gcnew AnimatedJoint();
			int NameCharCount = br->ReadInt32();
			AnimatedJoints[a]->Name = br->ReadBytes(NameCharCount);
			AnimatedJoints[a]->PreviousAnimatedJointID = br->ReadInt32();
			AnimatedJoints[a]->ID = br->ReadInt32();
			AnimatedJoints[a]->unknown = br->ReadInt32();
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

		br->Close();
		fs->Close();
	}

	public: void Save(String^ File)
	{
		FileStream^ fs = gcnew FileStream(File, FileMode::Create, FileAccess::Write);
		BinaryWriter^ bw = gcnew BinaryWriter(fs);

		bw->Write(StartSample);
		bw->Write(EndSample);
		bw->Write(AnimatedJoints->Length);
		for(int a=0; a<AnimatedJoints->Length; a++)
		{
			bw->Write(AnimatedJoints[a]->Name->Length);
			bw->Write(AnimatedJoints[a]->Name);
			bw->Write(AnimatedJoints[a]->PreviousAnimatedJointID);
			bw->Write(AnimatedJoints[a]->ID);
			bw->Write(AnimatedJoints[a]->unknown);
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

		bw->Close();
		fs->Close();
	}
};

public ref class MODEL
{
	public: MODEL(void)
	{
		enc = Encoding::GetEncoding("GBK");
	}

	protected: ~MODEL()
	{
	}

	public: ECM^ ECModel;
	public: SMD^ ModelDescription;
	public: SKI^ Skin;
	public: BON^ Skeleton;
	private: array<STCK^>^ Acts;
	private: Encoding^ enc;

	public: void Load(String^ ecmFile)
	{
		ECModel = gcnew ECM();
		ECModel->Load(ecmFile);

		String^ smdFile = ecmFile->Substring(0, ecmFile->IndexOf("\\models\\")+1) + ECModel->header->SkinModelPath;
		if(File::Exists(smdFile))
		{
			String^ basePath = smdFile->Substring(0, smdFile->LastIndexOf("\\")+1);

			ModelDescription = gcnew SMD();
			ModelDescription->Load(smdFile);

			Skin = gcnew SKI();
			Skin->Load(basePath + enc->GetString(ModelDescription->SkiFile));

			Skeleton = gcnew BON();
			Skeleton->Load(basePath + enc->GetString(ModelDescription->BonFile));

			if(ModelDescription->Version > 6)
			{
				Acts = gcnew array<STCK^>(ModelDescription->GetAnimatedJointActCount());
				for(int i=0; i<Acts->Length; i++)
				{
					Acts[i] = gcnew STCK();
					Acts[i]->Load(basePath + ModelDescription->GetStckFile(i));
				}
			}
		}
	}

	public: void Save(String^ ecmFile)
	{
		ECModel->Save(ecmFile);

		String^ smdFile = ecmFile->Substring(0, ecmFile->IndexOf("\\models\\")+1) + ECModel->header->SkinModelPath;
		String^ basePath = smdFile->Substring(0, smdFile->LastIndexOf("\\")+1);

		ModelDescription->Save(smdFile);

		Skin->Save(basePath + enc->GetString(ModelDescription->SkiFile));

		Skeleton->Save(basePath + enc->GetString(ModelDescription->BonFile));

		if(ModelDescription->Version > 6)
		{
			for(int i=0; i<Acts->Length; i++)
			{
				Acts[i]->Save(basePath + ModelDescription->GetStckFile(i));
			}
		}
	}

	public: String^ GetAnimatedJointName(int AnimatedJointIndex)
	{
		return enc->GetString(Skeleton->AnimatedJoints[AnimatedJointIndex]->Name);
	}
	Point3f^ GetJointPosition(int ActIndex, int AnimatedJointIndex, int Sample)
	{
		if(ModelDescription->Version > 6 && Skeleton->Version > 5)
		{
			int keyPointIndex = Convert::ToInt32(ModelDescription->GetEndSample(ActIndex) - ModelDescription->GetStartSample(ActIndex) + 1);
			keyPointIndex = Sample * Acts[ActIndex]->JointKeyFrames[AnimatedJointIndex]->PositionKeyPoints->Length / keyPointIndex;
			//return GetAct(ActIndex)->AnimatedJoints[AnimatedJointIndex]->JointKeyFrames->PositionKeyPoints[keyPointIndex];
		}
		else
		{
			// BON < v6 not supported;
		}
		return gcnew Point3f();
	}

	Point4f^ GetJointOrientation(int ActIndex, int AnimatedJointIndex, int Sample)
	{
		if(ModelDescription->Version > 6 && Skeleton->Version > 5)
		{
			int keyPointIndex = Convert::ToInt32(ModelDescription->GetEndSample(ActIndex) - ModelDescription->GetStartSample(ActIndex) + 1);
			keyPointIndex = Sample * Acts[ActIndex]->JointKeyFrames[AnimatedJointIndex]->OrientationKeyPoints->Length / keyPointIndex;
			//return GetAct(ActIndex)->AnimatedJoints[AnimatedJointIndex]->JointKeyFrames->OrientationKeyPoints[keyPointIndex];
		}
		else
		{
			// BON < v6 not supported;
		}
		return gcnew Point4f();
	}

	public: int GetCombineActCount()
	{
		return ECModel->combineActs->Length;
	}
	public: String^ GetCombineActName(int ActIndex)
	{
		if(ActIndex < ECModel->combineActs->Length)
		{
			return ((String^)ECModel->combineActs[ActIndex]->Parameters[0])->Split(gcnew array<wchar_t>{' '})[1];
		}
		return "";
	}
	public: int GetActCount()
	{
		return ModelDescription->GetAnimatedJointActCount();
	}
	public: String^ GetActStckFile(int ActIndex)
	{
		return ModelDescription->GetStckFile(ActIndex);
	}
	public: String^ GetActName(int ActIndex)
	{
		if(ActIndex < ModelDescription->GetAnimatedJointActCount())
		{
			return ModelDescription->GetActName(ActIndex);
		}
		return "";
	}
	public: void ImportAct(int ActIndex, String^ File)
	{
		if(ActIndex < ModelDescription->GetAnimatedJointActCount())
		{
			if(Skeleton->Version > 5)
			{
				Act^ animation = gcnew Act();
				animation->Load(File);

				ModelDescription->SetSample(ActIndex, animation->StartSample, animation->EndSample);
				Skeleton->AnimatedJoints = animation->AnimatedJoints;
				if(ModelDescription->Version > 6)
				{
					for(int i=0; i<animation->AnimatedJoints->Length; i++)
					{
						Acts[ActIndex]->JointKeyFrames[i] = animation->AnimatedJoints[i]->JointKeyFrames;
					}
				}
			}
			else
			{
				MessageBox::Show("BON < v6 not supported");
			}
		}
	}

	public: void ExportAct(int ActIndex, String^ File)
	{
		if(ActIndex < ModelDescription->GetAnimatedJointActCount())
		{
			if(Skeleton->Version > 5)
			{
				Act^ result = gcnew Act();
				result->StartSample = ModelDescription->GetStartSample(ActIndex);
				result->EndSample = ModelDescription->GetEndSample(ActIndex);
				result->AnimatedJoints = Skeleton->AnimatedJoints;
				if(ModelDescription->Version > 6 && Skeleton->Version > 5)
				{
					for(int i=0; i<result->AnimatedJoints->Length; i++)
					{
						result->AnimatedJoints[i]->JointKeyFrames = Acts[ActIndex]->JointKeyFrames[i];
					}
				}
				result->Save(File);
			}
			else
			{
				MessageBox::Show("BON < v6 not supported");
			}
		}
	}
};