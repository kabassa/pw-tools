#pragma once

#include "ecmType.h"

namespace PW
{
	namespace Models
	{
		public ref class ecmACT
		{
			public: ecmACT()
			{
			}
			protected: ~ecmACT()
			{
			}

			public: ArrayList^ Parameters;

			public: void SetAllParameters(array<String^>^ Properties)
			{
				Parameters = gcnew ArrayList(Properties);
			}

			public: void Fix(EcmFixOptions^ options)
			{
				String^ line;
				array<wchar_t>^ seperator = gcnew array<wchar_t>{' '};

				for(int i=0; i<Parameters->Count; i++)
				{
					line = (String^)Parameters[i];

					if(line->StartsWith("PlaySpeed:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("StopChildAct:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("ResetMtl:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("LoopMinNum:"))
					{
						Parameters[i] = "LoopCount: " + ((Convert::ToInt32(((String^)Parameters[i])->Split(seperator)[1]) + Convert::ToInt32(((String^)Parameters[i+1])->Split(seperator)[1])) / 2).ToString();
					}
					if(line->StartsWith("LoopMaxNum:"))
					{
						Parameters->RemoveAt(i);
						i--;
					}
					if(line->StartsWith("EventCount:") && line != "EventCount: 0")
					{
						i++;
						ArrayList^ typelines = gcnew ArrayList();
						array<String^>^ temp;
						int linesCount = Parameters->Count-i;
						int eventCount = 0;
						
						for(int n=0; n<linesCount; n++)
						{
							line = (String^)Parameters[i];
							if(typelines->Count > 0 && (line->StartsWith("EventType:") || n == linesCount-1))
							{
								if(n == linesCount-1)
								{
									typelines->Add(Parameters[i]);
								}
								ecmTYPE^ type = gcnew ecmTYPE();
								type->SetAllParameters(reinterpret_cast<array<String^>^>(typelines->ToArray(String::typeid)));
								if(type->Version < 104)
								{
									type->Fix(options);
									temp = type->GetAllParameters();
									for(int k=0; k<temp->Length; k++)
									{
										Parameters->Add(temp[k]);
									}
									eventCount++;
								}
								typelines->Clear();
							}
							typelines->Add(Parameters[i]);
							Parameters->RemoveAt(i);
						}

						Parameters[i-1] = "EventCount: " + eventCount;
					}
				}
			}

			public: array<String^>^ GetAllParameters()
			{
				array<String^>^ temp = gcnew array<String^>(Parameters->Count);

				for(int i=0; i<temp->Length; i++)
				{
					temp[i] = (String^)Parameters[i];
				}

				return temp;
			}
		};
	}
}