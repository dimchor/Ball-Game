#include "../../include/game/block.h"

Block::Block(const wsdl::Renderer& renderer, std::string assets_dir, std::string file_name, wsdl::Vector2 grid_location, unsigned int hits, unsigned int type)
    : Sprite(renderer, assets_dir + file_name), assets_dir(std::move(assets_dir)), grid_location(std::move(grid_location)), hits_left(std::move(hits)), type(std::move(type)) {
    setLocation({ grid_location.x * getW(), grid_location.y * getH() });
    if (probablyTrue(DROP_PROBABILITY)) {
        drop = randomNumber(1, DROP_NUMBER);
    }
}

const int& Block::getGridX() const {
    return grid_location.x;
}

const int& Block::getGridY() const {
    return grid_location.y;
}

const wsdl::Vector2& Block::getGridLocation() const {
    return grid_location;
}

const unsigned int& Block::getDropCode() const {
    return drop;
}

const unsigned int& Block::getHitsLeft() const {
    return hits_left;
}

const unsigned int& Block::getType() const {
    return type;
}

void Block::hit() {
    hits_left--;
    if (type == TYPE_CLASSIC && hits_left > 0) {
        resetTexture(assets_dir + "block_" + std::to_string(hits_left) + ".png");
    }
}
