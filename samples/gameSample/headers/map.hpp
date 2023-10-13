#ifndef __MAP_H__
#define __MAP_H__

#include <vector>
#include <string>

class Map
{
    std::vector<std::string> map;

public:
    Map();
    void load(const std::vector<std::string> &);
    const std::vector<std::string>& data() const;
};

#endif