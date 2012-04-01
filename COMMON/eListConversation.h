#pragma once

using namespace System::IO;

public ref struct eChoice
{
	public: int Control;
	public: array<unsigned char>^ ChoiceText;
	public: String^ GetText()
	{
		Encoding^ enc = Encoding::GetEncoding("Unicode");
		return enc->GetString(ChoiceText);
	}
	public: void SetText(String^ Value)
	{
		Encoding^ enc = Encoding::GetEncoding("Unicode");
		array<unsigned char>^ target = gcnew array<unsigned char>(132);
		array<unsigned char>^ source = enc->GetBytes(Value);
		if(target->Length > source->Length)
		{
			Array::Copy(source, target, source->Length);
		}
		else
		{
			Array::Copy(source, target, target->Length);
		}
		ChoiceText = target;
	}
};

public ref struct eQuestion
{
	public: int QuestionID;
	public: int Control;
	public: int QuestionTextLength;
	public: array<unsigned char>^ QuestionText;
	public: String^ GetText()
	{
		Encoding^ enc = Encoding::GetEncoding("Unicode");
		return enc->GetString(QuestionText);
	}
	public: void SetText(String^ Value)
	{
		Encoding^ enc = Encoding::GetEncoding("Unicode");
		QuestionText = enc->GetBytes(Value + wchar_t(0));
		QuestionTextLength = QuestionText->Length/2;
	}
	public: int ChoiceQount;
	public: array<eChoice^>^ Choices;
};

public ref struct eDialog
{
	public: int DialogID;
	public: array<unsigned char>^ DialogName;
	public: String^ GetText()
	{
		Encoding^ enc = Encoding::GetEncoding("Unicode");
		return enc->GetString(DialogName);
	}
	public: void SetText(String^ Value)
	{
		Encoding^ enc = Encoding::GetEncoding("Unicode");
		array<unsigned char>^ target = gcnew array<unsigned char>(128);
		array<unsigned char>^ source = enc->GetBytes(Value);
		if(target->Length > source->Length)
		{
			Array::Copy(source, target, source->Length);
		}
		else
		{
			Array::Copy(source, target, target->Length);
		}
		DialogName = target;
	}
	public: int QuestionCount;
	public: array<eQuestion^>^ Questions;
};

public ref class eListConversation
{
	public: eListConversation(array<unsigned char>^ Bytes)
	{
		MemoryStream^ ms = gcnew MemoryStream(Bytes);
		BinaryReader^ br = gcnew BinaryReader(ms);
		DialogCount = br->ReadInt32();
		Dialogs = gcnew array<eDialog^>(DialogCount);
		for(int d=0; d<DialogCount; d++)
		{
			Dialogs[d] = gcnew eDialog();
			Dialogs[d]->DialogID = br->ReadInt32();
			Dialogs[d]->DialogName = br->ReadBytes(128);
			Dialogs[d]->QuestionCount = br->ReadInt32();
			Dialogs[d]->Questions = gcnew array<eQuestion^>(Dialogs[d]->QuestionCount);
			for(int q=0; q<Dialogs[d]->QuestionCount; q++)
			{
				Dialogs[d]->Questions[q] = gcnew eQuestion();
				Dialogs[d]->Questions[q]->QuestionID = br->ReadInt32();
				Dialogs[d]->Questions[q]->Control = br->ReadInt32();
				Dialogs[d]->Questions[q]->QuestionTextLength = br->ReadInt32();
				Dialogs[d]->Questions[q]->QuestionText = br->ReadBytes(2*Dialogs[d]->Questions[q]->QuestionTextLength);
				Dialogs[d]->Questions[q]->ChoiceQount = br->ReadInt32();
				Dialogs[d]->Questions[q]->Choices = gcnew array<eChoice^>(Dialogs[d]->Questions[q]->ChoiceQount);
				for(int c=0; c<Dialogs[d]->Questions[q]->ChoiceQount; c++)
				{
					Dialogs[d]->Questions[q]->Choices[c] = gcnew eChoice();
					Dialogs[d]->Questions[q]->Choices[c]->Control = br->ReadInt32();
					Dialogs[d]->Questions[q]->Choices[c]->ChoiceText = br->ReadBytes(132);
				}
			}
		}
		br->Close();
		ms->Close();
	}
	protected: ~eListConversation()
	{
		DialogCount = 0;
		//delete Count;
		delete Dialogs;
	}

	public: int DialogCount;
	public: array<eDialog^>^ Dialogs;
	public: array<unsigned char>^ GetBytes()
	{
		MemoryStream^ ms = gcnew MemoryStream(DialogCount);
		BinaryWriter^ bw = gcnew BinaryWriter(ms);

		bw->Write(DialogCount);
		for(int d=0; d<DialogCount; d++)
		{
			bw->Write(Dialogs[d]->DialogID);
			bw->Write(Dialogs[d]->DialogName);
			bw->Write(Dialogs[d]->QuestionCount);
			for(int q=0; q<Dialogs[d]->QuestionCount; q++)
			{
				bw->Write(Dialogs[d]->Questions[q]->QuestionID);
				bw->Write(Dialogs[d]->Questions[q]->Control);
				bw->Write(Dialogs[d]->Questions[q]->QuestionTextLength);
				bw->Write(Dialogs[d]->Questions[q]->QuestionText);
				bw->Write(Dialogs[d]->Questions[q]->ChoiceQount);
				for(int c=0; c<Dialogs[d]->Questions[q]->ChoiceQount; c++)
				{
					bw->Write(Dialogs[d]->Questions[q]->Choices[c]->Control);
					bw->Write(Dialogs[d]->Questions[q]->Choices[c]->ChoiceText);
				}
			}
		}

		array<unsigned char>^ result = ms->ToArray();
		bw->Close();
		ms->Close();
		return result;
	}
};