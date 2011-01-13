#pragma once

namespace PW
{
	namespace Client
	{
		public ref struct OffsetProfile
		{
			String^ Name;
			array<int>^ TargetBaseChain;
			int TargetDirectionX;
			int TargetDirectionY;
			int TargetDirectionZ;
			int TargetPositionX;
			int TargetPositionY;
			int TargetPositionZ;
		};

		public ref struct ClientValues
		{
			float TargetDirectionX;
			float TargetDirectionY;
			float TargetDirectionZ;
			float TargetPositionX;
			float TargetPositionY;
			float TargetPositionZ;
		};

		public ref class ElementClient
		{
			[DllImport("Kernel32.dll")]
			static bool ReadProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, array<Byte>^ lpBuffer, int nSize, int* lpNumberOfBytesRead);

			public: ElementClient(String^ OffsetProfilesFile)
			{
				if(IO::File::Exists(OffsetProfilesFile))
				{
					try
					{
						IO::StreamReader^ sr = gcnew IO::StreamReader(OffsetProfilesFile, Encoding::Unicode);

						ArrayList^ offsetProfiles = gcnew ArrayList();
						array<wchar_t>^ seperator = gcnew array<wchar_t>{' '};
						String^ line;
						array<String^>^ values;

						while((line = sr->ReadLine()))
						{
							if(line->StartsWith("Name="))
							{
								OffsetProfile^ offsets = gcnew OffsetProfile();
								offsets->Name = line->Substring(5);

								// target base offset chain
								values = sr->ReadLine()->Split(seperator);
								offsets->TargetBaseChain = gcnew array<int>(values->Length);
								for(int i=0; i<values->Length; i++)
								{
									offsets->TargetBaseChain[i] = Int32::Parse(values[i], Globalization::NumberStyles::HexNumber);
								}
								offsets->TargetDirectionX = Int32::Parse(sr->ReadLine(), Globalization::NumberStyles::HexNumber);
								offsets->TargetDirectionY = Int32::Parse(sr->ReadLine(), Globalization::NumberStyles::HexNumber);
								offsets->TargetDirectionZ = Int32::Parse(sr->ReadLine(), Globalization::NumberStyles::HexNumber);
								offsets->TargetPositionX = Int32::Parse(sr->ReadLine(), Globalization::NumberStyles::HexNumber);
								offsets->TargetPositionY = Int32::Parse(sr->ReadLine(), Globalization::NumberStyles::HexNumber);
								offsets->TargetPositionZ = Int32::Parse(sr->ReadLine(), Globalization::NumberStyles::HexNumber);

								offsetProfiles->Add(offsets);
							}
						}

						sr->Close();

						OffsetProfiles = gcnew array<OffsetProfile^>(offsetProfiles->Count);
						offsetProfiles->CopyTo(OffsetProfiles);
					}
					catch(...)
					{
					}
				}
			}

			protected: ~ElementClient()
			{
			}

			public: array<OffsetProfile^>^ OffsetProfiles;

			public: array<String^>^ GetProfileNames()
			{
				array<String^>^ result = gcnew array<String^>(OffsetProfiles->Length);

				for(int i=0; i<result->Length; i++)
				{
					result[i] = OffsetProfiles[i]->Name;
				}

				return result;
			}

			public: ClientValues^ GetProfileValues(OffsetProfile^ Offsets)
			{
				array<Process^>^ procList = Process::GetProcessesByName("elementclient");
				if(procList->Length > 0)
				{
					ClientValues^ result = gcnew ClientValues();

					IntPtr hProcess = procList[0]->Handle;
					array<unsigned char>^ lpBuffer = gcnew array<Byte>(4);

					int baseOffset = 0;
					for(int i=0; i<Offsets->TargetBaseChain->Length; i++)
					{
						ReadProcessMemory((IntPtr)hProcess, IntPtr(baseOffset + Offsets->TargetBaseChain[i]), lpBuffer, 4, nullptr);
						baseOffset = BitConverter::ToInt32(lpBuffer, 0);
					}

					ReadProcessMemory((IntPtr)hProcess, IntPtr(baseOffset + Offsets->TargetDirectionX), lpBuffer, 4, nullptr);
					result->TargetDirectionX = BitConverter::ToSingle(lpBuffer, 0);
					ReadProcessMemory((IntPtr)hProcess, IntPtr(baseOffset + Offsets->TargetDirectionY), lpBuffer, 4, nullptr);
					result->TargetDirectionY = BitConverter::ToSingle(lpBuffer, 0);
					ReadProcessMemory((IntPtr)hProcess, IntPtr(baseOffset + Offsets->TargetDirectionZ), lpBuffer, 4, nullptr);
					result->TargetDirectionZ = BitConverter::ToSingle(lpBuffer, 0);

					ReadProcessMemory((IntPtr)hProcess, IntPtr(baseOffset + Offsets->TargetPositionX), lpBuffer, 4, nullptr);
					result->TargetPositionX = BitConverter::ToSingle(lpBuffer, 0);
					ReadProcessMemory((IntPtr)hProcess, IntPtr(baseOffset + Offsets->TargetPositionY), lpBuffer, 4, nullptr);
					result->TargetPositionY = BitConverter::ToSingle(lpBuffer, 0);
					ReadProcessMemory((IntPtr)hProcess, IntPtr(baseOffset + Offsets->TargetPositionZ), lpBuffer, 4, nullptr);
					result->TargetPositionZ = BitConverter::ToSingle(lpBuffer, 0);

					return result;
				}
				else
				{
					return nullptr;
				}				
			}
		};
	}
}