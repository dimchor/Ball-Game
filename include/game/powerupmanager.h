#pragma once

#include "../wsdl/wsdl_sprite.h"
#include "powerup.h"
#include "paddle.h"
#include "ballmanager.h"
#include "blockmanager.h"

class BallManager;

class PowerupManager {
    public:
        PowerupManager(const wsdl::Renderer&, const std::string&, unsigned int&, Paddle&, BallManager&, BlockManager&);

        void generate(const wsdl::Vector2&, const wsdl::Vector2&, const unsigned int&);
        void logic(bool&);
        void clear();
        void blit() const;

        virtual ~PowerupManager() = default;
    private:
        const wsdl::Renderer* renderer { nullptr };
        std::string assets_dir;
        unsigned int* score { nullptr };
        Paddle* paddle { nullptr };
        BallManager* ballManager { nullptr };
        BlockManager* blockManager { nullptr };

        std::vector<Powerup> powerups;
        void applyEffects(const unsigned int&, bool&);
};
