#pragma once

#include "../wsdl/wsdl_sprite.h"
#include "application.h"
#include "block.h"

class PowerupManager;
class Block;

class BlockManager {
    public:
        BlockManager(const wsdl::Renderer&, const std::string&, const Board&, unsigned int&, std::unique_ptr<PowerupManager>&); // loads from file automatically

        std::tuple<const std::vector<Block>::iterator, bool> findBlockAt(const int&, const int&) const; // (iterator, found) = findBlockAt();
        void destroyBlock(const wsdl::Vector2&, const wsdl::Vector2&, std::vector<Block>::iterator);
        void hitBlock(const wsdl::Vector2&, const wsdl::Vector2&, std::vector<Block>::iterator);
        void multiplyTNTs();
        void normalizeBlocks();
        bool isEmpty() const;
        void blit() const;
    private:
        const wsdl::Renderer* renderer { nullptr };
        std::unique_ptr<PowerupManager>* powerupManager;
        std::string assets_dir;
        Board board;
        unsigned int* score { nullptr };
        mutable std::vector<Block> blocks;
};
