#pragma once

#include "eList.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;

public ref class eListCollection
{
	public: eListCollection(String^ configFile, String^ elFile)
	{
		Lists = Load(configFile, elFile);
	}

	protected: ~eListCollection()
	{
	}

	public: String^ ConfigFile;
	public: array<eList^>^ Lists;

	public: void RemoveItem(int ListIndex, int ElementIndex)
	{
		Lists[ListIndex]->RemoveItem(ElementIndex);
	}
	public: void AddItem(int ListIndex, array<Object^>^ ItemValues)
	{
		Lists[ListIndex]->AddItem(ItemValues);
	}
	public: String^ GetOffset(int ListIndex)
	{
		return BitConverter::ToString(Lists[ListIndex]->listOffset);
	}

	public: void SetOffset(int ListIndex, String^ Offset)
	{
		if(Offset != "")
		{
			// Convert from Hex to byte[]
			array<String^>^ hex = Offset->Split(gcnew array<wchar_t>{'-'});
			Lists[ListIndex]->listOffset = gcnew array<unsigned char>(hex->Length);
			for(int i=0; i<hex->Length; i++)
			{
				Lists[ListIndex]->listOffset[i] = Convert::ToByte(hex[i], 16);
			}
		}
		else
		{
			Lists[ListIndex]->listOffset = gcnew array<unsigned char>(0);
		}
	}

	public: String^ GetValue(int ListIndex, int ElementIndex, int FieldIndex)
	{
		return Lists[ListIndex]->GetValue(ElementIndex, FieldIndex);
	}

	public: void SetValue(int ListIndex, int ElementIndex, int FieldIndex, String^ Value)
	{
		Lists[ListIndex]->SetValue(ElementIndex, FieldIndex, Value);
	}

	public: String^ GetType(int ListIndex, int FieldIndex)
	{
		return Lists[ListIndex]->GetType(FieldIndex);
	}

	private: Object^ readValue(BinaryReader^ br, String^ type)
	{
		if(type == "int16")
		{
			return br->ReadInt16();
		}
		if(type == "int32")
		{
			return br->ReadInt32();
		}
		if(type == "int64")
		{
			return br->ReadInt64();
		}
		if(type == "float")
		{
			return br->ReadSingle();
		}
		if(type == "double")
		{
			return br->ReadDouble();
		}
		if(type->Contains("byte:"))
		{
			return br->ReadBytes(Convert::ToInt32(type->Substring(5)));
		}
		if(type->Contains("wstring:"))
		{
			return br->ReadBytes(Convert::ToInt32(type->Substring(8)));
		}
		if(type->Contains("string:"))
		{
			return br->ReadBytes(Convert::ToInt32(type->Substring(7)));
		}
		return nullptr;
	}

	private: void writeValue(BinaryWriter^ bw, Object^ value, String^ type)
	{
		if(type == "int16")
		{
			bw->Write((short)value);
			return;
		}
		if(type == "int32")
		{
			bw->Write((int)value);
			return;
		}
		if(type == "int64")
		{
			bw->Write((long)value);
			return;
		}
		if(type == "float")
		{
			bw->Write((float)value);
			return;
		}
		if(type == "double")
		{
			bw->Write((double)value);
			return;
		}
		if(type->Contains("byte:"))
		{
			bw->Write((array<unsigned char>^)value);
			return;
		}
		if(type->Contains("wstring:"))
		{
			bw->Write((array<unsigned char>^)value);
			return;
		}
		if(type->Contains("string:"))
		{
			bw->Write((array<unsigned char>^)value);
			return;
		}
	}

	private: Hashtable^ loadRules(String^ file)
	{
		StreamReader^ sr = gcnew StreamReader(file);
		Hashtable^ result = gcnew Hashtable();
		String^ key = "";
		String^ value = "";
		String^ line;
		while((line = sr->ReadLine()))
		{
			System::Windows::Forms::Application::DoEvents();

			if(line != "" && !line->StartsWith("#"))
			{
				if(line->Contains("|"))
				{
					key = line->Split(gcnew array<wchar_t>{'|'})[0];
					value = line->Split(gcnew array<wchar_t>{'|'})[1];
				}
				else
				{
					key = line;
					value = "";
				}
				result->Add(key, value);
			}
		}
		sr->Close();

		return result;
	}

	public: array<eList^>^ Load(String^ configFile, String^ elFile)
	{
		ConfigFile = configFile->Substring(configFile->LastIndexOf("\\"));
		StreamReader^ sr = gcnew StreamReader(configFile);
		array<eList^>^ Li = gcnew array<eList^>(Convert::ToInt32(sr->ReadLine()));
		String^ line;
		for(int i=0; i<Li->Length; i++)
		{
			System::Windows::Forms::Application::DoEvents();

			while((line = sr->ReadLine()) == "")
			{
			}
			Li[i] = gcnew eList();
			Li[i]->listName = line;
			Li[i]->listOffset = nullptr;
			String^ offset = sr->ReadLine();
			if(offset != "AUTO")
			{
				Li[i]->listOffset = gcnew array<unsigned char>(Convert::ToInt32(offset));
			}
			Li[i]->elementFields = sr->ReadLine()->Split(gcnew array<wchar_t>{';'});
			Li[i]->elementTypes = sr->ReadLine()->Split(gcnew array<wchar_t>{';'});
		}
		sr->Close();

		// Read the Values
		FileStream^ fs =File::OpenRead(elFile);
		BinaryReader^ br = gcnew BinaryReader(fs);

		// go through all lists
		for(int l=0; l<Li->Length; l++)
		{
			System::Windows::Forms::Application::DoEvents();

			// read offset
			if(Li[l]->listOffset)
			{
				// offset > 0
				if(Li[l]->listOffset->Length>0)
				{
					Li[l]->listOffset = br->ReadBytes(Li[l]->listOffset->Length);
				}
			}
			// autodetect offset (for list 20 & 100)
			else
			{
				if(l == 20)
				{
					array<unsigned char>^ head = br->ReadBytes(4);
					array<unsigned char>^ count = br->ReadBytes(4);
					array<unsigned char>^ body = br->ReadBytes(BitConverter::ToInt32(count, 0));
					array<unsigned char>^ tail = br->ReadBytes(4);
					Li[l]->listOffset = gcnew array<unsigned char>(head->Length + count->Length + body->Length + tail->Length);
					Array::Copy(head, 0, Li[l]->listOffset, 0, head->Length);
					Array::Copy(count, 0, Li[l]->listOffset, 4, count->Length);
					Array::Copy(body, 0, Li[l]->listOffset, 8, body->Length);
					Array::Copy(tail, 0, Li[l]->listOffset, 8+body->Length, tail->Length);
				}
				if(l == 100)
				{
					array<unsigned char>^ head = br->ReadBytes(4);
					array<unsigned char>^ count = br->ReadBytes(4);
					array<unsigned char>^ body = br->ReadBytes(BitConverter::ToInt32(count, 0));
					Li[l]->listOffset = gcnew array<unsigned char>(head->Length + count->Length + body->Length);
					Array::Copy(head, 0, Li[l]->listOffset, 0, head->Length);
					Array::Copy(count, 0, Li[l]->listOffset, 4, count->Length);
					Array::Copy(body, 0, Li[l]->listOffset, 8, body->Length);
				}
			}

			// read list (58)
			if(l==58)
			{
				if(Li[l]->elementTypes[0]->Contains("AUTO"))
				{
					array<unsigned char>^ pattern = (Encoding::GetEncoding("GBK"))->GetBytes("facedata\\");
					__int64 sourcePosition = br->BaseStream->Position;
					int listLength = -72-pattern->Length;
					bool run = true;
					while(run)
					{
						run = false;
						for(int i=0; i<pattern->Length; i++)
						{
							listLength++;
							if(br->ReadByte() != pattern[i])
							{
								run = true;
								break;
							}
						}
					}
					br->BaseStream->Position = sourcePosition;
					Li[l]->elementTypes[0] = "byte:" + listLength;
				}

				Li[l]->elementValues = gcnew array<array<Object^>^>(1);
				Li[l]->elementValues[0] = gcnew array<Object^>(Li[l]->elementTypes->Length);
				Li[l]->elementValues[0][0] = readValue(br, Li[l]->elementTypes[0]);
			}
			// read lists
			else
			{
				Li[l]->elementValues = gcnew array<array<Object^>^>(br->ReadInt32());

				// go through all elements of a list
				for(int e=0; e<Li[l]->elementValues->Length; e++)
				{
					Li[l]->elementValues[e] = gcnew array<Object^>(Li[l]->elementTypes->Length);

					// go through all fields of an element
					for(int f=0; f<Li[l]->elementValues[e]->Length; f++)
					{
						Li[l]->elementValues[e][f] = readValue(br, Li[l]->elementTypes[f]);
					}
				}
			}
		}
		br->Close();
		fs->Close();

		return Li;
	}
	public: void Save(String^ elFile)
	{
		if(File::Exists(elFile))
		{
			File::Delete(elFile);
		}

		FileStream^ fs = gcnew FileStream(elFile, FileMode::Create, FileAccess::Write);
		BinaryWriter^ bw = gcnew BinaryWriter(fs);

		// go through all lists
		for(int l=0; l<Lists->Length; l++)
		{
			System::Windows::Forms::Application::DoEvents();

			if(Lists[l]->listOffset->Length>0)
			{
				bw->Write(Lists[l]->listOffset);
			}

			if(l != 58)
			{
				bw->Write(Lists[l]->elementValues->Length);
			}

			// go through all elements of a list
			for(int e=0; e<Lists[l]->elementValues->Length; e++)
			{
				// go through all fields of an element
				for(int f=0; f<Lists[l]->elementValues[e]->Length; f++)
				{
					writeValue(bw, Lists[l]->elementValues[e][f], Lists[l]->elementTypes[f]);
				}
			}
		}
		bw->Close();
		fs->Close();
	}

	public: void Export(String^ RulesFile, String^ TargetFile)
	{
		// Load the rules
		Hashtable^ rules = loadRules(RulesFile);

		if(File::Exists(TargetFile))
		{
			File::Delete(TargetFile);
		}

		FileStream^ fs = gcnew FileStream(TargetFile, FileMode::Create, FileAccess::Write);
		BinaryWriter^ bw = gcnew BinaryWriter(fs);

		// go through all lists
		for(int l=0; l<Lists->Length; l++)
		{
			if(!rules->ContainsKey("REMOVELIST:" + l))
			{
				if(rules->ContainsKey("REPLACEOFFSET:" + l))
				{
					// Convert from Hex to byte[]
					array<String^>^ hex = ((String^)rules["REPLACEOFFSET:" + l])->Split(gcnew array<wchar_t>{'-', ' '});
					if(hex->Length>1)
					{
						array<unsigned char>^ b = gcnew array<unsigned char>(hex->Length);
						for(int i=0; i<hex->Length; i++)
						{
							b[i] = Convert::ToByte(hex[i], 16);
						}
						if(b->Length > 0)
						{
							bw->Write(b);
						}
					}
				}
				else
				{
					if(Lists[l]->listOffset->Length > 0)
					{
						bw->Write(Lists[l]->listOffset);
					}
				}

				if(l != 58)
				{
					bw->Write(Lists[l]->elementValues->Length);
				}

				// go through all elements of a list
				for(int e=0; e<Lists[l]->elementValues->Length; e++)
				{
					// go through all fields of an element
					for(int f=0; f<Lists[l]->elementValues[e]->Length; f++)
					{
						System::Windows::Forms::Application::DoEvents();

						if(!rules->ContainsKey("REMOVEVALUE:" + l + ":" + f))
						{
							writeValue(bw, Lists[l]->elementValues[e][f], Lists[l]->elementTypes[f]);
						}
					}
				}
			}
		}

		bw->Close();
		fs->Close();
	}
};