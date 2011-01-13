#pragma once

#include "gfxFixOptions.h"
#include "gfxHead.h"
#include "gfxBlock000.h" // default block for unknown gfx element ids
#include "gfxBlock100.h"
#include "gfxBlock101.h"
#include "gfxBlock102.h"
#include "gfxBlock110.h"
#include "gfxBlock120.h"
#include "gfxBlock121.h"
#include "gfxBlock122.h"
#include "gfxBlock123.h"
#include "gfxBlock124.h"
#include "gfxBlock125.h"
#include "gfxBlock130.h"
#include "gfxBlock140.h"
#include "gfxBlock150.h"
#include "gfxBlock151.h"
#include "gfxBlock152.h"
#include "gfxBlock160.h"
#include "gfxBlock170.h"
#include "gfxBlock180.h"
#include "gfxBlock190.h"
#include "gfxBlock200.h"
#include "gfxBlock210.h"
#include "gfxBlock211.h"
#include "gfxBlock230.h"

namespace PW
{
	namespace Models
	{
		public ref class GFX
		{
			public: GFX(void)
			{
			}

			protected: ~GFX()
			{
			}

			private: gfxHEAD^ header;
			private: ArrayList^ elements;

			public: void Load(String^ file)
			{
				array<String^>^ linebreak = gcnew array<String^>{"\r\n"};
				StreamReader^ sr = gcnew StreamReader(file, Encoding::GetEncoding("GBK"));
				array<String^>^ blocks = sr->ReadToEnd()->Split(gcnew array<String^>{"GFXELEMENTID: "}, StringSplitOptions::RemoveEmptyEntries);
				sr->Close();

				header = gcnew gfxHEAD();
				header->SetAllParameters(blocks[0]->Split(linebreak, StringSplitOptions::RemoveEmptyEntries));

				elements = gcnew ArrayList();

				int id;
				for(int i=0; i<blocks->Length-1; i++)
				{
					id = Convert::ToInt32(blocks[i+1]->Substring(0, 3));

					//initialize a default block !!!
					elements->Add(gcnew gfxBLOCK000());

					if(id == 100)
					{
						elements[i] = gcnew gfxBLOCK100();
					}
					if(id == 101)
					{
						elements[i] = gcnew gfxBLOCK101();
					}
					if(id == 102)
					{
						elements[i] = gcnew gfxBLOCK102();
					}
					if(id == 110)
					{
						elements[i] = gcnew gfxBLOCK110();
					}
					if(id == 120)
					{
						elements[i] = gcnew gfxBLOCK120();
					}
					if(id == 121)
					{
						elements[i] = gcnew gfxBLOCK121();
					}
					if(id == 122)
					{
						elements[i] = gcnew gfxBLOCK122();
					}
					if(id == 123)
					{
						elements[i] = gcnew gfxBLOCK123();
					}
					if(id == 124)
					{
						elements[i] = gcnew gfxBLOCK124();
					}
					if(id == 125)
					{
						elements[i] = gcnew gfxBLOCK125();
					}
					if(id == 130)
					{
						elements[i] = gcnew gfxBLOCK130();
					}
					if(id == 140)
					{
						elements[i] = gcnew gfxBLOCK140();
					}
					if(id == 150)
					{
						elements[i] = gcnew gfxBLOCK150();
					}
					if(id == 151)
					{
						elements[i] = gcnew gfxBLOCK151();
					}
					if(id == 152)
					{
						elements[i] = gcnew gfxBLOCK152();
					}
					if(id == 160)
					{
						elements[i] = gcnew gfxBLOCK160();
					}
					if(id == 170)
					{
						elements[i] = gcnew gfxBLOCK170();
					}
					if(id == 180)
					{
						elements[i] = gcnew gfxBLOCK180();
					}
					if(id == 190)
					{
						elements[i] = gcnew gfxBLOCK190();
					}
					if(id == 200)
					{
						elements[i] = gcnew gfxBLOCK200();
					}
					if(id == 210)
					{
						elements[i] = gcnew gfxBLOCK210();
					}
					if(id == 211)
					{
						elements[i] = gcnew gfxBLOCK211();
					}
					if(id == 230)
					{
						elements[i] = gcnew gfxBLOCK230();
					}

					blocks[i+1] = "GFXELEMENTID: " + blocks[i+1];
					((gfxBLOCK^)elements[i])->SetAllParameters(blocks[i+1]->Split(linebreak, StringSplitOptions::RemoveEmptyEntries));
				}
			}

			public: void Fix(GfxFixOptions^ options)
			{
				// fix header
				header->Fix(options);

				// fix each block
				for(int b=0; b<elements->Count; b++)
				{
					if(!((gfxBLOCK^)elements[b])->Fix(options))
					{
						elements->RemoveAt(b);
						b--;
					}
					Application::DoEvents();
				}
			}

			public: void Save(String^ file)
			{
				array<String^>^ temp;
				
				temp = header->GetAllParameters();

				// update the current block count in header
				if(temp[temp->Length-1]->StartsWith("GFXELEMENTCOUNT:"))
				{
					temp[temp->Length-1] = "GFXELEMENTCOUNT: " + elements->Count;
				}

				StreamWriter^ sw = gcnew StreamWriter(file, false, Encoding::GetEncoding("GBK"));

				// save the header to file
				for(int i=0; i<temp->Length; i++)
				{
					sw->WriteLine(temp[i]);
				}

				// save all blocks to file
				for(int b=0; b<elements->Count; b++)
				{
					temp = ((gfxBLOCK^)elements[b])->GetAllParameters();
					for(int i=0; i<temp->Length; i++)
					{
						sw->WriteLine(temp[i]);
					}
				}

				sw->Close();
			}
		};
	}
}