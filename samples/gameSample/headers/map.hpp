#ifndef __MAP_H__
#define __MAP_H__

#include "point.hpp"
#include <vector>
#include <string>

class Map
{
    std::vector<std::string> map;

public:
    Map();
    void Load(const std::vector<std::string> &);
    bool IsWall(Point) const;
    const std::vector<std::string>& Data() const;
};

#endif