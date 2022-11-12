#pragma once

#include "../wsdl/wsdl_sprite.h"
#include "application.h"
#include "ball.h"
#include "paddle.h"
#include "blockmanager.h"

class Ball;
class Paddle;
struct Control;

class BallManager {
    public:
        BallManager(const wsdl::Renderer&, const std::string&, const Paddle&, BlockManager&);
        void logic(bool&, const bool&);
        Ball defaultBall();
        void multiply();
        void setSpeedFactor(const float&);
        void blit();
        void reset();
    private:
        const wsdl::Renderer* renderer { nullptr };
        std::string assets_dir;
        std::vector<Ball> balls;
        const Paddle* paddle { nullptr };
        BlockManager* blockManager { nullptr };
};
