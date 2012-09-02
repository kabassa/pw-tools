#include "base64.h"

/*
    count all characters until \0 (max 128)
*/
wxUint32 byteLength(wxByte* buffer)
{
    wxUint32 n = 0;
    while(buffer[n] != '\0' && n < 128)
    {
        n++;
    }
    if(n<127)
    {
        return n;
    }
    else
    {
        return 0;
    }
}

/*
    convert character from base64 table index to utf8 table index
*/
wxByte utf8char(wxByte c)
{
    if(c == 63)
    {
        return '-';
    }
    if(c == 62)
	{
	    return '+';
	}
	// BASE64 0-9 (52-61)
	// ASCII 0-9 (48-57)
	if(c >= 52 && c <= 61)
	{
	    return '0'+c-52;
    }
    // BASE64 a-z (26-51)
    // ASCII a-z (97-122)
	if(c >= 26 && c <= 51)
	{
	    return 'a'+c-26;
	}
	// BASE64 A-Z (0-25)
	// ASCII A-Z (65-90)
	if(c >= 0 && c <= 25)
	{
	    return 'A'+c;
	}
	return '='; // 64
}

/*
    convert character from utf8 table index to base64 table index
*/
wxByte base64char(wxByte c)
{
	if(c == '-')
	{
	    return 63;
	}
	if(c == '+')
	{
	    return 62;
	}
	// ASCII 0-9 (48-57)
	// BASE64 0-9 (52-61)
	if(c >= '0' && c <= '9')
	{
	    return c-'0'+52;
    }
    // ASCII a-z (97-122)
	// BASE64 a-z (26-51)
	if(c >= 'a' && c <= 'z')
	{
	    return c-'a'+26;
	}
	// ASCII A-Z (65-90)
	// BASE64 A-Z (0-25)
	if(c >= 'A' && c <= 'Z')
	{
	    return c-'A';
	}
	return 64; // '='
}

/*
    covert 3x utf8 chars to 4x base64 chars
*/
void utf8chars(wxByte* triple, wxByte* quadruple)
{
    quadruple[0] = triple[0] >> 2;
    quadruple[1] = (triple[0] & 3) << 4 | triple[1] >> 4;
    quadruple[2] = (triple[1] & 15) << 2 | triple[2] >> 6;
    quadruple[3] = triple[2] & 63;
}

/*
    covert 4x base64 chars to 3x utf8 chars
*/
wxUint32 base64chars(wxByte* quadruple, wxByte* triple)
{
	triple[0] = quadruple[0] << 2 | quadruple[1] >> 4;
	if(quadruple[2] > 63)
	{
	    return 1;
	}
	triple[1] = quadruple[1] << 4 | quadruple[2] >> 2;
	if(quadruple[3] > 63)
	{
	    return 2;
	}
	triple[2] = quadruple[2] << 6 | quadruple[3];
	return 3;
}

/*
    Encode a wxString (given encoding)
    to a base64 wxString (utf8 representation)
*/
wxString Base64::Encode(wxString in, wxCSConv encoding)
{
    wxByte* cb = (wxByte*)in.mb_str(encoding).release();
    wxByte* buffer = new wxByte[(byteLength(cb)+2)/3*4+1]; // length + 1 for '\0' terminator char
    wxByte* triple = new wxByte[3];
    wxByte* quadruple = new wxByte[4];
    wxUint32 length = byteLength(cb)*4/3+1;

    wxUint32 n = 0;
    for(wxUint32 i=0; i<byteLength(cb); i+=3)
    {
        triple[0] = cb[i];
        triple[1] = cb[i+1];
        triple[2] = cb[i+2];

        utf8chars(triple, quadruple);

        buffer[n] = utf8char(quadruple[0]);
        n++;
        buffer[n] = utf8char(quadruple[1]);
        n++;
        if(n < length)
        {
            buffer[n] = utf8char(quadruple[2]);
        }
        else
        {
            buffer[n] = '=';
        }
        n++;
        if(n < length)
        {
            buffer[n] = utf8char(quadruple[3]);
        }
        else
        {
            buffer[n] = '=';
        }
        n++;
    }

    buffer[n] = '\0';

    wxDELETEA(triple);
    wxDELETEA(quadruple);
    wxDELETEA (cb);

    return wxString((char*)buffer, wxConvUTF8);
}

/*
    Decode a base64 wxString (utf8 representation)
    to a wxString (given encoding)
*/
wxString Base64::Decode(wxString in, wxCSConv encoding)
{
    wxByte* cb = (wxByte*)in.utf8_str().release();
    wxByte* buffer = new wxByte[byteLength(cb)*3/4+1]; // length + 1 for '\0' terminator char
    wxByte* triple = new wxByte[3];
    wxByte* quadruple = new wxByte[4];
    wxUint32 length;

    wxUint32 n = 0;
    for(wxUint32 i=0; i<byteLength(cb); i+=4)
    {
        quadruple[0] = base64char(cb[i]);
        quadruple[1] = base64char(cb[i+1]);
        quadruple[2] = base64char(cb[i+2]);
        quadruple[3] = base64char(cb[i+3]);

        length = base64chars(quadruple, triple);

        if(length>0)
        {
            buffer[n] = triple[0];
            n++;
        }
        if(length>1)
        {
            buffer[n] = triple[1];
            n++;
        }
        if(length>2)
        {
            buffer[n] = triple[2];
            n++;
        }
    }

    buffer[n] = '\0';

    wxDELETEA(triple);
    wxDELETEA(quadruple);
    wxDELETEA(cb);

    return wxString((char*)buffer, encoding);
}
