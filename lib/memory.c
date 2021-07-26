
/* Zero out a memory location. */

uint64 MemoryZero(void *address, uint64 length)
{
    uint64 bytes_zeroed = 0;
    int8 *paddress = (int8 *)address;

    while(length) 
    {
        paddress[bytes_zeroed++] = 0x00;
        length--;
    }

    return bytes_zeroed;
}

/* Rewrite of libc memset(). */

void *MemorySet(void *address, int8 value, uint64 length)
{
    uint64 bytes_set = 0;
    int8 *paddress = (int8 *)address;

    while(bytes_set < length)
    {
        paddress[bytes_set] = value;
        bytes_set += sizeof(value);
    }

    return address;
}

/* Rewrite of libc memcpy(). */

void *MemoryCopy(void *dest, void *src, uint64 length)
{
    uint64 bytes_copied = 0;
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

bool CheckBit(uint64 *address, uint8 bit)
{
    return ((*address >> bit) & 1);
}

bool SetBit(uint64 *address, uint8 bit)
{
    *address |= (1 << bit);
    return CheckBit(address, bit);
}

bool ClearBit(uint64 *address, uint8 bit)
{
    *address &= ~(1 << bit);
    return !CheckBit(address, bit);
}

bool ToggleBit(uint64 *address, uint8 bit)
{
    bool current_state, previous_state;
    previous_state = CheckBit(address, bit);
    *address ^= (1 << bit);
    current_state = CheckBit(address, bit);
    return (previous_state != current_state);
}

