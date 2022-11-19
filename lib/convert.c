
/* Converts up to an unsigned 64 bit integer to a string.
 Supports hexadecimal, decimal, and binary conversions. */

string UnsignedIntegerToString(uint64 integer, string out_result, uint32 out_result_length, INTFMT base)
{
    static int8 result[65];

    uint64 value;
    string presult;
    uint8 place_values;
    uint8 exponent;
    int8 data;

    presult = result;
    exponent = 1;
    place_values = 0;

    switch(base)
    {
        case FMT_INT_BINARY:

            do
            {
                value = (uint64)(integer / Power(base, exponent));
                exponent++;
                place_values++;

            } while((value > 0) && (place_values < 64));

            while(place_values)
            {
                value = (uint16)(((integer % Power(base, place_values)) - (integer % Power(base, place_values - 1))) / Power(base, place_values - 1));

                data = (value | 0x30);

                *presult = data;
                presult++;
                place_values--;
            }

        break;

        case FMT_INT_DECIMAL:

            do
            {
                value = (uint64)(integer / Power(base, exponent));
                exponent++;
                place_values++;

            } while((value > 0) && (place_values < 20));

            while(place_values)
            {
                value = (uint16)(((integer % Power(base, place_values)) - (integer % Power(base, place_values - 1))) / Power(base, place_values - 1));

                data = (value | 0x30);

                *presult = data;
                presult++;
                place_values--;
            }

        break;

        case FMT_INT_HEXADECIMAL:

            do
            {
                value = (uint64)(integer / Power(base, exponent));
                exponent++;
                place_values++;

            } while((value > 0) && (place_values < 16));

            while(place_values)
            {
                value = (uint16)(((integer % Power(base, place_values)) - (integer % Power(base, place_values - 1))) / Power(base, place_values - 1));

                data = (value | 0x30);

                if(value > 9)
                {
                    data += 7;
                }

                *presult = data;
                presult++;
                place_values--;
            }

        break;
    }

    *presult = null;

    if(out_result)
    {
        MemoryCopy(out_result, result, out_result_length);
        return (string)out_result;
    }

    return (string)result;
}

/* Converts a signed 64 bit integer to a string.
   Supports hexadecimal, decimal, and binary conversions. */

string SignedIntegerToString(int64 integer, string out_result, uint32 out_result_length, INTFMT base)
{
    static int8 result[66];

    string presult = result;
    boolean negative = (integer < 0);

    if(negative)
    {
        *presult++ = '-';
        integer = -integer;
    }

    UnsignedIntegerToString(integer, presult, sizeof(presult), base);

    if(out_result)
    {
        MemoryCopy(out_result, result, out_result_length);
        return (string)out_result;
    }

    return (string)result;
}

string IntegerToString(int64 integer, string out_result, uint32 out_result_length, INTFMT base)
{
    if(integer >= 0)
    {
        return UnsignedIntegerToString((uint64)integer, out_result, out_result_length, base);
    }

    return SignedIntegerToString(integer, out_result, out_result_length, base);
}

/* Convert real8 precision floating point number to a string.
   Supports only decimal conversions. */

string DoubleToString(real8 number, string out_result, uint32 out_result_length)
{
    static int8 result[83];

    string presult = result;
    boolean negative = (number < 0);
    int64 whole = (int64)number;
    real8 fraction = (number - whole);
    INTFMT format = FMT_INT_DECIMAL;

    IntegerToString(whole, presult, 20, format);

    presult += StringLength(presult);
    *presult++ = '.';
    fraction *= Power(10, 15);

    if(negative)
    {
        fraction = -fraction;
    }

    IntegerToString((int64)fraction, presult, 60, format);

    if(out_result)
    {
        MemoryCopy(out_result, result, out_result_length);
        return (string)out_result;
    }

    return (string)result;
}

/* Convert string to an unsigned 64 bit integer.
   Supports hexadecimal, decimal, and binary conversions. */

uint64 StringToUnsignedInteger(string str, INTFMT base)
{
    uint64 result;
    string pstr = str;
    uint16 place_values;

    result = 0;

    switch(base)
    {
        case FMT_INT_BINARY:
        {
            if((*pstr == '0') && (*(pstr + 1) == 'x'))
            {
                result = 0xff00ff00ff00ff00;
                break;
            }

            else if((*pstr == '0') && (*(pstr + 1) == 'b'))
            {
                pstr += 2;
            }

            place_values = (uint16)StringLength(pstr);

            while(place_values)
            {
                uint8 data;
                uint64 power;
                uint16 i;

                power = 1;

                if((*pstr <= '1') && (*pstr >= '0'))
                {
                    data = (uint8)(*pstr & 0xF);
                }

                else
                {
                    result = 0xff00ff00ff00ff00;
                    break;
                }

                for(i = (uint16)power; i < place_values; i++)
                {
                    power *= base;
                }

                result += (uint64)(data * power);

                place_values--;
                pstr++;
            }
        }

        break;

        case FMT_INT_DECIMAL:
        {
            if((*pstr == '0') && (*(pstr + 1) == 'x'))
            {
                result = 0xff00ff00ff00ff00;
                break;
            }

            else if((*pstr == '0') && (*(pstr + 1) == 'b'))
            {
                result = 0xff00ff00ff00ff00;
                break;
            }

            place_values = (uint16)StringLength(pstr);

            while(place_values)
            {
                uint8 data;
                uint64 power;
                uint16 i;

                power = 1;

                if((*pstr <= '9') && (*pstr >= '0'))
                {
                    data = (uint8)(*pstr & 0xF);
                }

                else
                {
                    result = 0xff00ff00ff00ff00;
                    break;
                }

                for(i = (uint16)power; i < place_values; i++)
                {
                    power *= base;
                }

                result += (uint64)(data * power);

                place_values--;
                pstr++;
            }
        }

        break;

        case FMT_INT_HEXADECIMAL:
        {
            if((*pstr == '0') && (*(pstr + 1) == 'x'))
            {
                pstr += 2;
            }

            else if((*pstr == '0') && (*(pstr + 1) == 'b'))
            {
                result = 0xff00ff00ff00ff00;
                break;
            }

            place_values = (uint16)StringLength(pstr);

            while(place_values)
            {
                uint8 data;
                uint64 power;
                uint16 i;

                power = 1;

                if((*pstr <= 'f') && (*pstr >= 'A'))
                {
                    data = (uint8)((*pstr | 0x20) - 0x57);
                }

                else if((*pstr <= '9') && (*pstr >= '0'))
                {
                    data = (uint8)(*pstr & 0xF);
                }

                else
                {
                    result = 0xff00ff00ff00ff00;
                    break;
                }

                for(i = (uint16)power; i < place_values; i++)
                {
                    power *= base;
                }

                result += (uint64)(data * power);

                place_values--;
                pstr++;
            }
        }

        break;

        default:

            result = 0xff00ff00ff00ff00;

        break;
    }

    return result;
}

/* Convert string to a signed 64 bit integer.
   Supports hexadecimal, decimal, and binary conversions. */

int64 StringToInteger(string str, INTFMT base)
{
    int64 result = 0;
    string pstr = str;
    boolean negative = (*pstr == '-');

    if(negative)
    {
       result = (int64)StringToUnsignedInteger(pstr + 1, base);
       result = -result;
    }
    
    else
    {
       result = StringToUnsignedInteger(pstr, base);
    }

    return result;
}

/* Convert string to a real8 precision floating point.
   Supports only decimal conversions. */

real8 StringToDouble(string str) 
{
    string pstr = str;

    if(pstr)
    {
        int64 number = 0;
        real8 power = 10.0;
        real8 result = 0.0;
        int16 exponent = 0;
        uint16 number_of_digits = 0;
        uint16 number_of_decimals = 0;
        boolean negative = false;

        if(*pstr == '-')
        {
            negative = true;
            pstr++;
        }

        else if(*pstr == '+')
        {
            pstr++;
        }

        while((*pstr <= '9') && (*pstr >= '0')) 
        {
            result = result * power + (*pstr - '0');
            pstr++;
            number_of_digits++;
        }

        if(*pstr == '.') 
        {
            pstr++;

            while((*pstr <= '9') && (*pstr >= '0')) 
            {
                result = result * power + (*pstr - '0');
                pstr++;
                number_of_digits++;
                number_of_decimals++;
            }

            exponent -= number_of_decimals;
            number = exponent;
        }

        if(number_of_digits == 0) 
        {
            result = 0.0;
            return result;
        }

        if(negative) 
        {
            result = -result;
        }

        if((exponent < -307)  || (exponent > 1024)) 
        {
            result = -1;
            return result;
        }

        if(number < 0) 
        {
            number = -number;
        }

        while(number) 
        {
            if(number & 1) 
            {
                if(exponent < 0) 
                {
                   result /= power;
                } 

                else 
                {
                   result *= power;
                }
            } 

            number >>= 1;
            power *= power;
        }

        return result;
    }

    return 0x00ff00ff00ff00ff;
}

