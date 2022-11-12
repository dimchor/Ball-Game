#include "../../include/game/blockmanager.h"

BlockManager::BlockManager(const wsdl::Renderer& renderer, const std::string& assets_dir, const Board& board, unsigned int& score, std::unique_ptr<PowerupManager>& powerupManager)
    : renderer(&renderer), assets_dir(assets_dir), board(board), score(&score), powerupManager(&powerupManager) {
    for (int i = 0; i < this->board.size(); i++) {
        for (int j = 0; j < this->board.at(0).size(); j++) {
            switch (this->board.at(i).at(j)) {
                case '1':
                case '2':
                case '3': {
                    const unsigned int hits = (unsigned int)(this->board.at(i).at(j)) - 48;
                    blocks.push_back(Block(renderer, assets_dir, "block_" + std::to_string(hits) + ".png", { j, i }, hits, TYPE_CLASSIC)); // why -48? to convert char into unsigned int (see ASCII table)
                    break;
                }
                case 'T':
                    blocks.push_back(Block(renderer, assets_dir, "block_t.png", { j, i }, 1, TYPE_TNT));
                    break;
                default:
                    break;
            }
            // more block options can be added by adding case statements
        }
    }
}

std::tuple<const std::vector<Block>::iterator, bool> BlockManager::findBlockAt(const int& x, const int& y) const {
    bool found = false;
    std::vector<Block>::iterator i = blocks.begin();
    while (i != blocks.end()) {
        if (i->getX() / BLOCK_W == x && i->getY() / BLOCK_H == y) {
            found = true;
            break;
        }
        i++;
    }
    return std::make_tuple(i, found);
}

void BlockManager::destroyBlock(const wsdl::Vector2& location, const wsdl::Vector2& vector, std::vector<Block>::iterator block) {
    (*score) += BLOCK_POINTS;
    powerupManager->get()->generate(location, vector, block->getDropCode());
    blocks.erase(block);
}

void BlockManager::hitBlock(const wsdl::Vector2& location, const wsdl::Vector2& vector, std::vector<Block>::iterator block) {
    block->hit();
    if (block->getType() == TYPE_CLASSIC) {
        if (block->getHitsLeft() > 0) {
            return;
        }
        destroyBlock(location, vector, block);
    } else if (block->getType() == TYPE_TNT) {
        const std::array<wsdl::Vector2, 4> possible_neighbouring_blocks { 
            wsdl::Vector2(block->getGridX() + 1, block->getGridY()), 
            wsdl::Vector2(block->getGridX() - 1, block->getGridY()), 
            wsdl::Vector2(block->getGridX(), block->getGridY() + 1), 
            wsdl::Vector2(block->getGridX(), block->getGridY() - 1) 
        };
        destroyBlock(location, vector, block);
        for (const wsdl::Vector2& grid_loc : possible_neighbouring_blocks) {
            auto [neighbouring_block, found] = findBlockAt(grid_loc.x, grid_loc.y);
            if (!found) {
                continue;
            }
            const wsdl::Vector2 normal_loc(grid_loc.x * BLOCK_W, grid_loc.y * BLOCK_H); // not very accurate position
            if (neighbouring_block->getType() == TYPE_CLASSIC) {
                destroyBlock(normal_loc, vector, neighbouring_block);
            } else if (neighbouring_block->getType() == TYPE_TNT) {
                hitBlock(normal_loc, vector, neighbouring_block);
            }
        }
    }
}

void BlockManager::multiplyTNTs() {
    std::vector<const Block*> tnt_blocks;
    for (const auto& block : blocks) {
        if (block.getType() == TYPE_TNT) {
            tnt_blocks.push_back(&block);
        }
    }
    
    for (const auto& tnt_block : tnt_blocks) {
        const std::array<wsdl::Vector2, 4> possible_neighbouring_blocks { 
            wsdl::Vector2(tnt_block->getGridX() + 1, tnt_block->getGridY()), 
            wsdl::Vector2(tnt_block->getGridX() - 1, tnt_block->getGridY()), 
            wsdl::Vector2(tnt_block->getGridX(), tnt_block->getGridY() + 1), 
            wsdl::Vector2(tnt_block->getGridX(), tnt_block->getGridY() - 1) 
        };
        for (const wsdl::Vector2& grid_loc : possible_neighbouring_blocks) {
            auto [neighbouring_block, found] = findBlockAt(grid_loc.x, grid_loc.y);
            if (!found) {
                continue;
            }
            if (neighbouring_block->getType() == TYPE_CLASSIC) {
                *neighbouring_block = std::move(Block(*renderer, assets_dir, "block_t.png", neighbouring_block->getGridLocation(), 1, TYPE_TNT));
            }
        }
    }
}

void BlockManager::normalizeBlocks() {
    for (auto& block : blocks) {
        if (block.getType() != TYPE_CLASSIC) {
            continue;
        }
        block = std::move(Block(*renderer, assets_dir, "block_1.png", block.getGridLocation(), 1, TYPE_CLASSIC));
    }  
}

bool BlockManager::isEmpty() const {
    return blocks.empty();
}

void BlockManager::blit() const {
    for (auto& i : blocks) {
        i.blit();
    }
}
