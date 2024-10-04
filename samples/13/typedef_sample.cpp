#include <vector>

typedef unsigned char age_type;
typedef unsigned long long duration_type;

using distance_type = double;

using vector = std::vector<distance_type>;
using const_iterator = vector::const_iterator;

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;

typedef unsigned char uint8_t;

int main()
{
    age_type age;
    duration_type seconds;

    vector distances {1, 2, 3, 4, 5};
    // std::vector<distance_type> distances {1, 2, 3, 4, 5};
    // for(std::vector<distance_type>::const_iterator it = distances.begin(); it != distances.end(); ++it)
    for(const_iterator it = distances.begin(); it != distances.end(); ++it)
    {
        // Do something with the iterator
    }
    return 0;
}