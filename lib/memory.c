
/* Zero out a memory location. */

uint64 MemoryZero(PVOID address, uint64 length)
{
    uint32 bytes_zeroed = 0;
    int8 *paddress = (int8 *)address;

    while(length) 
    {
        paddress[bytes_zeroed++] = 0x00;
        length--;
    }

    return bytes_zeroed;
}

/* Rewrite of libc memset(). */

PVOID MemorySet(PVOID address, int8 value, uint64 length)
{
    uint32 bytes_set = 0;
    int8 *paddress = (int8 *)address;

    while(bytes_set < length)
    {
        paddress[bytes_set] = value;
        bytes_set += sizeof(value);
    }

    return address;
}

/* Rewrite of libc memcpy(). */

PVOID MemoryCopy(PVOID dest, PVOID src, uint64 length)
{
    uint32 bytes_copied = 0;
    int8 *pdest = (int8 *)dest;
    int8 *psrc = (int8 *)src;

    while(length - bytes_copied)
    {
        *pdest++ = *psrc++;
        bytes_copied++;
    }

    return dest;
}

/* Bitwies functions: Set and clear bits, convert bits to bytes and vice-versa. */

BIT *ByteToBits(BYTE b, BIT *bits)
{
    static BIT result[8];
    uint8 bit;
    
    for(bit = 0; bit < 8; bit++)
    {
        result[8 - (bit + 1)].value = (b.value >> bit);
    }

    if(bits)
    {
        MemoryCopy((string)bits, (string)result, sizeof(bits));
        return bits;
    }

    return result;
}

BYTE BitsToByte(BIT *bits)
{
    BYTE result;
    uint8 bit;

    for(bit = 0; bit < 8; bit++)
    {
        result.value |= (bits[8 - (bit + 1)].value << bit);
    }

    return result;
}

boolean CheckBit(PVOID address, uint8 bit)
{
    uint8 *paddress = (uint8 *)address;

    if(paddress)
    {
        return ((*paddress >> bit) & 1);
    }

    return false;
}

boolean SetBit(PVOID address, uint8 bit)
{
    uint8 *paddress = (uint8 *)address;

    if(paddress)
    {
        *paddress |= (1 << bit);
        return CheckBit(paddress, bit);
    }

    return false;
}

boolean ClearBit(PVOID address, uint8 bit)
{
    uint8 *paddress = (uint8 *)address;

    if(paddress)
    {
        *paddress &= ~(1 << bit);
        return !CheckBit(paddress, bit);
    }

    return false;
}

boolean ToggleBit(PVOID address, uint8 bit)
{
    uint8 *paddress = (uint8 *)address;

    if(paddress)
    {
        boolean current_state;
        boolean previous_state;

        previous_state = CheckBit(paddress, bit);
        *paddress ^= (1 << bit);
        current_state = CheckBit(paddress, bit);
        return (previous_state != current_state);
    }

    return false;
}
