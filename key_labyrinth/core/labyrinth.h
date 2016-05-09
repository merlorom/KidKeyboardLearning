#include "tile.h"

#include <vector>

namespace KeyLabyrinth {

class Labyrinth {
public:
    Labyrinth();

    std::vector<std::vector<Tile>>& tiles();

private:
    std::vector<std::vector<Tile>> tiles_;
};

inline std::vector<std::vector<Tile>>& Labyrinth::tiles() {
    return tiles_;
}

}
