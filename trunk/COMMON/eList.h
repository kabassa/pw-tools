#pragma once

using namespace System;
using namespace System::Text;
using namespace System::Collections;
using namespace System::Windows::Forms;

public ref class eList
{
	public: eList(void)
	{
	}

	protected: ~eList()
	{
	}

	public: String^ listName;// -> from config file
	public: array<unsigned char>^ listOffset;  // -> length from config file, values from elements.data
	public: array<String^>^ elementFields; // -> length & values from config file
	public: array<String^>^ elementTypes; // -> length & values from config file
	public: array<array<Object^>^>^ elementValues; // list.length from elements.data, elements.length from config file

	// return a field of an element in string representation
	public: String^ GetValue(int ElementIndex, int FieldIndex)
	{
		if(FieldIndex > -1)
		{
			Object^ value = elementValues[ElementIndex][FieldIndex];
			String^ type = elementTypes[FieldIndex];

			if(type == "int16")
			{
				return Convert::ToString((short)value);
			}
			if(type == "int32")
			{
				return Convert::ToString((int)value);
			}
			if(type == "int64")
			{
				return Convert::ToString((long)value);
			}
			if(type == "float")
			{
				return Convert::ToString((float)value);
			}
			if(type == "double")
			{
				return Convert::ToString((double)value);
			}
			if(type->Contains("byte:"))
			{
				// Convert from byte[] to Hex String
				array<unsigned char>^ b = (array<unsigned char>^)value;
				return BitConverter::ToString(b)->TrimEnd('\0');
			}
			if(type->Contains("wstring:"))
			{
				Encoding^ enc = Encoding::GetEncoding("Unicode");
				return enc->GetString((array<unsigned char>^)value)->TrimEnd('\0');
			}
			if(type->Contains("string:"))
			{
				Encoding^ enc = Encoding::GetEncoding("GBK");
				return enc->GetString((array<unsigned char>^)value)->TrimEnd('\0');
			}
		}
		return "";
	}

	public: void SetValue(int ElementIndex, int FieldIndex, String^ Value)
	{
		String^ type = elementTypes[FieldIndex];

		if(type == "int16")
		{
			elementValues[ElementIndex][FieldIndex] = Convert::ToInt16(Value);
			return;
		}
		if(type == "int32")
		{
			elementValues[ElementIndex][FieldIndex] = Convert::ToInt32(Value);
			return;
		}
		if(type == "int64")
		{
			elementValues[ElementIndex][FieldIndex] = Convert::ToInt64(Value);
			return;
		}
		if(type == "float")
		{
			elementValues[ElementIndex][FieldIndex] = Convert::ToSingle(Value);
			return;
		}
		if(type == "double")
		{
			elementValues[ElementIndex][FieldIndex] = Convert::ToDouble(Value);
			return;
		}
		if(type->Contains("byte:"))
		{
			// Convert from Hex to byte[]
			array<String^>^ hex = Value->Split(gcnew array<wchar_t>{'-'});
			array<unsigned char>^ b = gcnew array<unsigned char>(Convert::ToInt32(type->Substring(5)));
			for(int i=0; i<hex->Length; i++)
			{
				b[i] = Convert::ToByte(hex[i], 16);
			}
			elementValues[ElementIndex][FieldIndex] = b;
			return;
		}
		if(type->Contains("wstring:"))
		{
			Encoding^ enc = Encoding::GetEncoding("Unicode");
			array<unsigned char>^ target = gcnew array<unsigned char>(Convert::ToInt32(type->Substring(8)));
			array<unsigned char>^ source = enc->GetBytes(Value);
			if(target->Length > source->Length)
			{
				Array::Copy(source, target, source->Length);
			}
			else
			{
				Array::Copy(source, target, target->Length);
			}
			elementValues[ElementIndex][FieldIndex] = target;
			return;
		}
		if(type->Contains("string:"))
		{
			Encoding^ enc = Encoding::GetEncoding("GBK");
			array<unsigned char>^ target = gcnew array<unsigned char>(Convert::ToInt32(type->Substring(7)));
			array<unsigned char>^ source = enc->GetBytes(Value);
			if(target->Length > source->Length)
			{
				Array::Copy(source, target, source->Length);
			}
			else
			{
				Array::Copy(source, target, target->Length);
			}
			elementValues[ElementIndex][FieldIndex] = target;
			return;
		}
		return;
	}
	// delete Item
	public: void RemoveItem(int itemIndex)
	{
		array<array<Object^>^>^ newValues = gcnew array<array<Object^>^>(elementValues->Length-1);
		Array::Copy(elementValues, 0, newValues, 0, itemIndex);
		int length = newValues->Length-itemIndex;
		Array::Copy(elementValues, itemIndex+1, newValues, itemIndex, newValues->Length-itemIndex);
		elementValues = newValues;
	}

	// add Item
	public: void AddItem(array<Object^>^ itemValues)
	{
		array<array<Object^>^>^ newValues = gcnew array<array<Object^>^>(elementValues->Length+1);
		Array::Resize(elementValues, elementValues->Length+1);
		elementValues[elementValues->Length-1] = itemValues;
	}
	// export item to unicode textfile
	public: void ExportItem(String^ file, int index)
	{
		System::IO::StreamWriter^ sw = gcnew System::IO::StreamWriter(file, false, Encoding::Unicode);
		for(int i=0; i<elementTypes->Length; i++)
		{
			sw->WriteLine(elementFields[i] + "(" + elementTypes[i] + ")=" + GetValue(index, i));
		}
		sw->Close();
	}
	// import item from unicode textfile
	public: void ImportItem(String^ file, int index)
	{
		System::IO::StreamReader^ sr = gcnew System::IO::StreamReader(file, Encoding::Unicode);
		for(int i=0; i<elementTypes->Length; i++)
		{
			SetValue(index, i, sr->ReadLine()->Split(gcnew array<wchar_t>{'='})[1]);
		}
		sr->Close();
	}
	// add all new elements into the elementValues
	public: ArrayList^ JoinElements(eList^ newList, int listID, bool addNew, bool backupNew, bool replaceChanged, bool backupChanged, bool removeMissing, bool backupMissing, String^ dirBackupNew, String^ dirBackupChanged, String^ dirBackupMissing)
	{
		array<array<Object^>^>^ newElementValues = newList->elementValues;
		array<String^>^ newElementTypes = newList->elementTypes;

		ArrayList^ report = gcnew ArrayList();
		bool exists;

		// check which elements are missing (removed)
		for(int n=0; n<elementValues->Length; n++)
		{
			Application::DoEvents();
			exists = false;
			for(int e=0; e<newElementValues->Length; e++)
			{
				if(this->GetValue(n, 0) == newList->GetValue(e, 0))
				{
					exists = true;
				}
			}
			if(!exists)
			{
				if(dirBackupMissing && System::IO::Directory::Exists(dirBackupMissing))
				{
					ExportItem(dirBackupMissing + "\\List_" + listID.ToString() + "_Item_" + this->GetValue(n, 0) + ".txt", n);
				}
				if(removeMissing)
				{
					report->Add("- MISSING ITEM (*removed): " + ((int)elementValues[n][0]).ToString());
					RemoveItem(n);
					n--;
				}
				else
				{
					report->Add("- MISSING ITEM (*not removed): " + ((int)elementValues[n][0]).ToString());
				}
			}
		}

		for(int e=0; e<newElementValues->Length; e++)
		{
			Application::DoEvents();
			// check if the element with this id already exists
			exists = false;
			for(int n=0; n<elementValues->Length; n++)
			{
				if(this->GetValue(n, 0) == newList->GetValue(e, 0))
				{
					exists = true;
					// check if this item is different
					if(this->elementValues[n]->Length != newList->elementValues[e]->Length)
					{
						// invalid amount of values !!!
						report->Add("<> DIFFERENT ITEM (*not replaced, invalid amount of values): " + this->GetValue(n, 0));
					}
					else
					{
						// compare all values of current element
						for(int i=0; i<this->elementValues[n]->Length; i++)
						{
							if(this->GetValue(n, i) != newList->GetValue(e, i))
							{
								if(backupChanged && System::IO::Directory::Exists(dirBackupChanged))
								{
									ExportItem(dirBackupChanged + "\\List_" + listID.ToString() + "_Item_" + this->GetValue(n, 0) + ".txt", n);
								}
								if(replaceChanged)
								{
									report->Add("<> DIFFERENT ITEM (*replaced): " + this->GetValue(n, 0));
									elementValues[n] = newList->elementValues[e];
								}
								else
								{
									report->Add("<> DIFFERENT ITEM (*not replaced): " + this->GetValue(n, 0));
								}
								break;
							}
						}
					}
					break;
				}
			}
			if(!exists)
			{
				if(backupNew && System::IO::Directory::Exists(dirBackupNew))
				{
					newList->ExportItem(dirBackupNew + "\\List_" + listID.ToString() + "_Item_" + newList->GetValue(e, 0) + ".txt", e);
				}
				if(addNew)
				{
					AddItem(newElementValues[e]);
					report->Add("+ NEW ITEM (*added): " + this->GetValue(elementValues->Length-1, 0));
				}
				else
				{
					report->Add("+ NEW ITEM (*not added): " + this->GetValue(elementValues->Length-1, 0));
				}
			}
		}

		return report;
	}
};