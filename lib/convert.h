#ifndef _NCRT_CONVERT_H
#define _NCRT_CONVERT_H

/* Converts an unsigned 64 bit integer to a string.
 Supports hexadecimal, decimal, and binary conversions. */

string UnsignedIntegerToString(uint64, string, uint32, INTFMT);

/* Converts a signed 64 bit integer to a string.
   Supports hexadecimal, decimal, and binary conversions. */

string SignedIntegerToString(int64, string, uint32, INTFMT);

/* Calls SignedIntegerToString() if passed a signed integer,
   or UnsignedIntegerToString() if passed an unsigned integer. */

string IntegerToString(int64, string, uint32, INTFMT);

/* Convert real8 precision floating point number to a string.
   Supports only decimal conversions. */

string DoubleToString(real8, string, uint32);

/* Convert string to an unsigned 64 bit integer.
   Supports hexadecimal, decimal, and binary conversions. */

uint64 StringToUnsignedInteger(string, INTFMT);

/* Convert string to a signed 64 bit integer.
   Supports hexadecimal, decimal, and binary conversions. */

int64 StringToInteger(string, INTFMT);

/* Convert string to a real8 precision floating point.
   Supports only decimal conversions. */

real8 StringToDouble(string);

/* Convert wide cstrings to standard cstrings. */

string WideToAscii(wstring);

#endif
