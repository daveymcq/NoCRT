#ifndef _NCRT_MEMORY_H
#define _NCRT_MEMORY_H

/* Zero out a memory location. */

uint64 MemoryZero(PVOID , uint64);

/* Rewrite of libc memset(). */

PVOID MemorySet(PVOID , int8, uint64);

/* Rewrite of libc memcpy(). */

PVOID MemoryCopy(PVOID , PVOID , uint64);

/* Bitwies functions: Set and clear bits, convert bits to bytes and vice-versa. */

BIT *ByteToBits(BYTE, BIT *);
BYTE BitsToByte(BIT *);

boolean CheckBit(PVOID , uint8);
boolean SetBit(PVOID , uint8);
boolean ClearBit(PVOID , uint8);
boolean ToggleBit(PVOID , uint8);

#endif
