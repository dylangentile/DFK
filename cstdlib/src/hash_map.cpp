#include <hash_map.h>

#define CHTTP_HASHMAP_PRIME 15485863

kuintmax_t
CHTTP_hash(const void* str, size_t len)
{
    kuintmax_t result = 1;

    for(const uint8_t* ptr = (const uint8_t*)str; ptr != (const uint8_t*)str + len; ptr++)
    {
        result *= *ptr; //supposed to roll over
    }

    return result%CHTTP_HASHMAP_PRIME;
}
