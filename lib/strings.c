
/* Rewrite of libc strcpy(). */

uint32 CopyString(string to, string from, uint32 length)
{
    uint32 bytes_copied = 0;

    while(bytes_copied < length)
    {
        if(!(to[bytes_copied] = from[bytes_copied])) break;
        ++bytes_copied; 
    }

    return bytes_copied;
}

/* Rewrite of libc strlen(). */

uint32 StringLength(string str)
{
    uint32 length = 0;
    string pstr = str;

    while(*pstr)
    {
        ++length;
        pstr++;
    }

    return length;
}

/* Rewrite of libc strcat(). */

string StringConcat(string str1, string str2)
{
    CopyString(str1 + StringLength(str1), str2, StringLength(str2));
    return str1;
}

/* Checks equality of two c-strings. */

boolean StringCompare(string string_a, string string_b, boolean case_sensitive)
{
    boolean result = (StringLength(string_a) == StringLength(string_b));

    if(result)
    {
        uint32 offset;

        for(offset = 0; result && (offset < StringLength(string_a)); offset++)
        {
            result = (string_a[offset] == string_b[offset]);
            if(!result && !case_sensitive) result = ((string_a[offset] | 0x20) == (string_b[offset] | 0x20));
        }
    }

    return result;
}

/* Finds first occurrence of a string within another string.
   Returns the index into the string or -1 if non existent. */

int32 FindFirstOccurrenceOfString(string haystack, string needle, boolean case_sensitive)
{
    uint32 index = 0;
    uint32 needle_length = StringLength(needle);
    uint32 haystack_length = StringLength(haystack);

    if(haystack_length >= 2048)
    {
        return -1; 
    }

    if(needle_length > haystack_length)
    {
        return -1; 
    }

    while(index < haystack_length)
    {
        int8 haystack_buffer[2048];
 
        CopyString((string)haystack_buffer, (string)haystack, haystack_length);
        haystack_buffer[needle_length] = 0;

        if(StringCompare(haystack_buffer, needle, case_sensitive))
        {
            return index; 
        }

        index++;
        haystack++;
    }

    return -1; 
}

/* Checks if a string is a number. */

boolean IsNumeric(string str)
{
    string pstr = str;
    uint32 index = 0;
    boolean numeric = (str) ? true : false;
    boolean hex = ((*pstr == '0') && (*(pstr + 1) == 'x'));

    if(hex)
    {
        pstr += 2;
    }

    while((*pstr) && (numeric))
    {
        numeric = (((*pstr >= '0') && (*pstr <= '9')) ||
                   ((index == 0) && (*pstr == '-')) ||
                   ((*pstr == '.')));

        if(hex)
        {
            numeric = numeric || (((*pstr >= 'a') && (*pstr <= 'f')) ||
                                  ((*pstr >= 'A') && (*pstr <= 'F')));
        }

        index++;
        pstr++;
    }

    return numeric;
}

/* Convert wide cstrings to standard cstrings. */

string WideToAscii(wstring src)
{
    static int8 result[256];

    uint16 chars_converted = 0;
    string dst = result;

    while(*src && (chars_converted < sizeof(result)))
    {
        *dst = (int8)*src;
        ++dst;
        ++src;
        ++chars_converted;
    }

    *dst = null;

    return (string)result;
}

/* Removes a single char from an ascii string. */

string RemoveCharFromString(string s, char char_to_remove) 
{
    string src;
    string dst;

    for(src = dst = s; *src; src++) 
    {
        *dst = *src;

        if(*dst != char_to_remove) 
        {
            dst++;
        }
    }

    *dst = null;

    return dst;
}

