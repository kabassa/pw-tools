#pragma once

#include "task.h"

String^ decrypt(int key, array<unsigned char>^ text)
{
	String^ result = "";
	array<unsigned char>^ dbyte = gcnew array<unsigned char>(2);
	for(int i=0; i<text->Length; i+=2)
	{
		dbyte = BitConverter::GetBytes((short)key);
		// XOR decoding to receive Unicode character code
		dbyte[0] ^= text[i];
		dbyte[1] ^= text[i+1];
		result += BitConverter::ToChar(dbyte, 0);
	}
	return result->TrimEnd(gcnew array<wchar_t>{'\0'});
}

array<unsigned char>^ encrypt(int key, String^ text, int length, bool appendZero)
{
	array<unsigned char>^ result;

	if(appendZero)
	{
		result = gcnew array<unsigned char>(length+2);
	}
	else
	{
		result = gcnew array<unsigned char>(length);
	}

	array<unsigned char>^ dbyte = gcnew array<unsigned char>(2);

	for(int i=0; i<result->Length; i+=2)
	{
		dbyte = BitConverter::GetBytes((short)key);
		result[i] = dbyte[0];
		result[i+1] = dbyte[1];

		if(i/2 < text->Length)
		{
			dbyte = BitConverter::GetBytes(text[i/2]);
			result[i] ^= dbyte[0];
			result[i+1] ^= dbyte[1];
		}				
	}
/*
	if(appendZero)
	{
		dbyte = BitConverter::GetBytes((short)key);
		result[result->Length-2] = dbyte[0];//^(unsigned char)0;
		result[result->Length-1] = dbyte[1];//^(unsigned char)0;
	}
*/
	return result;
}

String^ ByteArray_to_HexString(array<unsigned char>^ value)
{
	return BitConverter::ToString(value);
}

array<unsigned char>^ HexString_to_ByteArray(String^ value)
{
	// Convert from Hex to byte[]
	array<String^>^ hex = value->Split(gcnew array<wchar_t>{'-'});
	array<unsigned char>^ bytes = gcnew array<unsigned char>(hex->Length);
	for(int i=0; i<hex->Length; i++)
	{
		bytes[i] = Convert::ToByte(hex[i], 16);
	}
	return bytes;
}

String^ ByteArray_to_GbkString(array<unsigned char>^ text)
{
	Encoding^ enc = Encoding::GetEncoding("GBK");
	return enc->GetString(text)->Split(gcnew array<wchar_t>{'\0'})[0];
}

array<unsigned char>^ GbkString_to_ByteArray(String^ text, int length)
{
	Encoding^ enc = Encoding::GetEncoding("GBK");
	array<unsigned char>^ target = gcnew array<unsigned char>(length);
	array<unsigned char>^ source = enc->GetBytes(text);
	if(target->Length > source->Length)
	{
		Array::Copy(source, target, source->Length);
	}
	else
	{
		Array::Copy(source, target, target->Length);
	}
	return target;
}

String^ ByteArray_to_UnicodeString(array<unsigned char>^ text)
{
	Encoding^ enc = Encoding::GetEncoding("Unicode");
	return enc->GetString(text)->Split(gcnew array<wchar_t>{'\0'})[0];
}

array<unsigned char>^ UnicodeString_to_ByteArray(String^ text, int length)
{
	Encoding^ enc = Encoding::GetEncoding("Unicode");
	array<unsigned char>^ target = gcnew array<unsigned char>(length);
	array<unsigned char>^ source = enc->GetBytes(text);
	if(target->Length > source->Length)
	{
		Array::Copy(source, target, source->Length);
	}
	else
	{
		Array::Copy(source, target, target->Length);
	}
	return target;
}