#ifndef _NCRT_TYPES_H
#define _NCRT_TYPES_H

#if defined(_MSC_VER)
    #if (_MSC_VER >= 1400)
        #ifndef uint64
             #define uint64 unsigned __int64
        #endif
        
        #ifndef int64
             #define int64 __int64
        #endif
    #endif
#endif

#ifndef uint8
    #define uint8 unsigned char
#endif

#ifndef uint16
    #define uint16 unsigned short
#endif

#ifndef uint32
   #define uint32 unsigned int
#endif

#ifndef uint64
    #define uint64 unsigned long long
#endif

#ifndef int8
    #define int8 char
#endif

#ifndef int16
    #define int16 short
#endif

#ifndef int32
   #define int32 int
#endif

#ifndef int64
    #define int64 long long
#endif

#ifndef wchar
    #define wchar uint16
#endif

#ifndef null
    #define null 0x00
#endif

#ifndef EXIT_SUCCESS
    #define EXIT_SUCCESS 0x00
#endif

#ifndef EXIT_FAILURE
    #define EXIT_FAILURE 0xff
#endif

#ifndef string
    #define string int8 *
#endif

#ifndef wstring
    #define wstring wchar *
#endif

#ifndef real4
    #define real4 float
#endif

#ifndef real8
    #define real8 double
#endif

#ifndef BOOL
    #define BOOL int32
#endif

#ifndef bool
    #define bool int32
#endif

#ifndef boolean
    #define boolean int32
#endif

#ifndef true
    #define true 0x00000001
#endif

#ifndef false
    #define false 0x00000000
#endif

#ifndef TRUE
    #define TRUE 0x00000001
#endif

#ifndef FALSE
    #define FALSE 0x00000000
#endif

#ifdef BIT
    #undef BIT
#endif

#ifdef BYTE
    #undef BYTE
#endif

#ifndef PVOID
    #define PVOID void *
#endif

#ifndef VOID
    #define VOID void
#endif

typedef enum _INTFMT
{
    FMT_INT_BINARY = 2,
    FMT_INT_DECIMAL = 10,
    FMT_INT_HEXADECIMAL = 16

} INTFMT;

#pragma pack(push, 1)

typedef struct _BIT
{
    bool value : 1;

} _BIT_;

typedef union _BYTE
{
    uint8 value;

    struct _BITS
    {
        bool bit_0 : 1;
        bool bit_1 : 1;
        bool bit_2 : 1;
        bool bit_3 : 1;
        bool bit_4 : 1;
        bool bit_5 : 1;
        bool bit_6 : 1;
        bool bit_7 : 1;

    } bits;

} _BYTE_;

#define BIT _BIT_
#define BYTE _BYTE_

#pragma pack(pop)

#endif
