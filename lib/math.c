
/* Returns the value of integer {base} raised to the power of {exponent} */

int64 Power(int64 base, int64 exponent)
{
    int64 result = 1;

    while(exponent)
    {
        if(exponent & 1) 
        {
            result *= base;
        }

        exponent >>= 1;
        base *= base;
    }

    return result;
}
