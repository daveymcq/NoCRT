/* Encode URL */

string urlencode(string URL)
{
    static int8 encoded_url[2048];

    string hex_lookup_table = "0123456789ABCDEF";
    uint32 index, i;

    index = 0;

    if(StringLength(URL) >= sizeof(encoded_url))
    {
        encoded_url[index] = null;
        return (string)encoded_url;
    }

    MemoryZero(encoded_url, sizeof(encoded_url));
    
    for(i = 0; i < StringLength(URL); i++) 
    {
        if(('a' <= URL[i] && URL[i] <= 'z')
            || ('A' <= URL[i] && URL[i] <= 'Z')
            || ('0' <= URL[i] && URL[i] <= '9')) 
        {
            encoded_url[index++] = URL[i];
        } 

        else 
        {
            encoded_url[index++] = '%';
            encoded_url[index++] = hex_lookup_table[URL[i] >> 0x4];
            encoded_url[index++] = hex_lookup_table[URL[i] & 0xF];
        }
    }

    encoded_url[index] = null;
    return (string)encoded_url;
}

/* Decode URL */

string urldecode(string URL)
{
    static int8 encoded_url[2048];

    string pURL = URL;
    uint32 index = 0;

    if(StringLength(URL) >= sizeof(encoded_url))
    {
        encoded_url[index] = null;
        return (string)encoded_url;
    }

    MemoryZero(encoded_url, sizeof(encoded_url));

    while(*pURL)
    {
       if(*pURL == '%')
       {
           uint8 code[3];

           code[0] = *(pURL + 1);
           code[1] = *(pURL + 2);
           code[2] = null;

           encoded_url[index++] = (uint8)StringToInteger((string)code, FMT_INT_HEXADECIMAL);

           pURL += 3;

           continue;
       }
       
       encoded_url[index++] = *pURL++;
    }

    encoded_url[index] = null;
    return (string)encoded_url;
}
