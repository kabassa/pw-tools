#pragma once

using namespace System;
using namespace System::IO;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Text;

public ref class SGC
{
	public: SGC(void)
	{
	}

	protected: ~SGC()
	{
	}

	ArrayList^ Parameters;

	public: void Load(String^ file)
	{
		array<String^>^ linebreak = gcnew array<String^>{"\r\n"};
		StreamReader^ sr = gcnew StreamReader(file, Encoding::GetEncoding("GBK"));

		array<String^>^ blocks = sr->ReadToEnd()->Split(linebreak, StringSplitOptions::RemoveEmptyEntries);
		sr->Close();

		Parameters = gcnew ArrayList();

		for(int i=0; i<blocks->Length; i++)
		{
			Parameters->Add(blocks[i]);
		}
	}

	public: void Fix(Options^ options)
	{
		if(options->sgcDowngrade)
		{
			Parameters[0] = "MOXTVersion: 4";

			String^ line;

			for(int i=0; i<Parameters->Count; i++)
			{
				line = (String^)Parameters[i];

				if(line->StartsWith("Hook:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("Pos:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("RelHook:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("Hanger:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("ChildHook:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
				if(line->StartsWith("HitPos:"))
				{
					Parameters->RemoveAt(i);
					i--;
				}
			}
		}
	}

	public: void Save(String^ file)
	{
		StreamWriter^ sw = gcnew StreamWriter(file, false, Encoding::GetEncoding("GBK"));

		for(int i=0; i<Parameters->Count; i++)
		{
			sw->WriteLine((String^)Parameters[i]);
		}

		sw->Close();
	}
};