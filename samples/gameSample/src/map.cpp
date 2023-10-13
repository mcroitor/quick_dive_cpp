#include "map.hpp"
#include <iterator>

Map::Map() {}
void Map::load(const std::vector<std::string> & data) {
    std::copy(
        data.begin(), data.end(), std::back_inserter(map));
}
const std::vector<std::string> &Map::data() const
{
    return map;
}