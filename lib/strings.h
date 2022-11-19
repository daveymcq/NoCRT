#ifndef _NCRT_STRINGS_H
#define _NCRT_STRINGS_H

/* Rewrite of libc strcpy(). */

uint32 CopyString(string, string, uint32);

/* Rewrite of libc strlen(). */

uint32 StringLength(string);

/* Rewrite of libc strcat(). */

string StringConcat(string, string);

/* Checks equality of two c-strings. */

boolean StringCompare(string, string, boolean);

/* Finds first occurrence of a string within another string.
   Returns the index into the string or -1 if non existent. */

int32 FindFirstOccurrenceOfString(string, string, boolean);

/* Checks if a string is a number. */

boolean IsNumeric(string);

/* Convert wide cstrings to standard cstrings. */

string WideToAscii(wstring);

/* Removes a single char from an ascii string. */

string RemoveCharFromString(string, char);

#endif
