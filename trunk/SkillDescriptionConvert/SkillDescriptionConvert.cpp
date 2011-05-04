// SkillDescriptionConvert.cpp : main project file.

#include "stdafx.h"

using namespace System;
using namespace System::IO;

String^ colorFormating(String^ line)
{
	String^ result = "";

	array<String^>^ blocks = line->Split(gcnew array<wchar_t>{'^'});
	if(blocks->Length > 1)
	{
		if(blocks[0] != "")
		{
			result += blocks[0];
		}
		for(int i=1; i<blocks->Length; i++)
		{
			if(blocks[i] != "")
			{
				result += "<font color='#" + blocks[i]->Substring(0, 6) + "'>";
				result += blocks[i]->Substring(6);
				result += "</font>";
			}
		}
	}
	return result;
}
int main(array<System::String ^> ^args)
{
	if(args->Length > 0 && File::Exists(args[0]) && args[0]->EndsWith("skillstr.txt"))
	{
		StreamReader^ sr = gcnew StreamReader(args[0]);
		// skip first five lines (file description)
		for(int i=0; i<5; i++)
		{
			sr->ReadLine();
		}
		array<String^>^ skills = sr->ReadToEnd()->Split(gcnew array<wchar_t>{'\"'});
		sr->Close();

		// remove leading and tailing whitespaces
		for(int i=0; i<skills->Length-1; i+=4)
		{
			// check if starts with Unicode [10, 0] (???)
			// or Ends With Unicode [32, 0] (Space)
			/*
			if(skills[i+0]->Length > 4)
			{
				skills[i+0] = skills[i+0]->Substring(1);
			}
			if(skills[i+0]->Length > 2)
			{
				skills[i+0] = skills[i+0]->Substring(0, 2);
			}
			if(skills[i+2]->Length > 4)
			{
				skills[i+2] = skills[i+2]->Substring(1);
			}
			if(skills[i+2]->Length > 2)
			{
				skills[i+2] = skills[i+2]->Substring(0, 2);
			}
			*/
		}

Text::Encoding^ enc = Text::Encoding::GetEncoding("Unicode");

		array<String^>^ description;
		String^ out = "<html encoding='UTF-8'>\n<head>\n</head>\n<body bgcolor='#111111'>\n<table align='center' border='1' color='#ffffff'><tr><th align='center'>Nr.</th><th align='left'>Text</th></tr>\n";

		for(int i=0; i<skills->Length-1; i+=4)
		{
// Line Breaks [13,0,10,0] (\r\n ???)
//array<unsigned char>^ debug = enc->GetBytes(skills[i+3]);

			out += "<tr><td align='center'>" + skills[i+0] + "</td>" + "<td align='left'><b>" + skills[i+1]->Replace("\n", "<br>") + "</b></td>\n";
			out += "<tr><td align='center'>" + skills[i+2] + "</td>" + "<td align='left'>";
			description = skills[i+3]->Split(gcnew array<String^>{"\r\n"}, StringSplitOptions::None);
			for(int n=0; n<description->Length; n++)
			{
				out += colorFormating(description[n]->TrimEnd()) + "<br>";
			}
			out += "</td>\n";
		}

		out += "</table>\n</body>\n</html>";

		StreamWriter^ sw = gcnew StreamWriter(args[0] + ".html");
		sw->Write(out);
		sw->Close();
	}
	else
	{
		Console::WriteLine(L"Invalid File");
		Console::WriteLine(L"Drag \"skillstr.txt\" onto the Application!");
	}
	Console::WriteLine();
	Console::WriteLine(L"Press Enter to Exit...");
	Console::ReadLine();
    return 0;
}
