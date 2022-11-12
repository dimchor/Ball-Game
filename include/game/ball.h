#pragma once

#include "../wsdl/wsdl_sprite.h"
#include "paddle.h"
#include "application.h"
#include "blockmanager.h"

class Paddle;
class BlockManager;

class Ball : public wsdl::Sprite {
    public:
        Ball(const wsdl::Renderer&, const std::string&, int, float, const Paddle&, BlockManager&);

        void logic(const bool&);

        void lookUp();
        const int& getSpeedBase() const;
        void setSpeedBase(const int&);
        const float& getSpeedFactor() const;
        void setSpeedFactor(const float&);
        wsdl::Vector2& setVector();
        void setVector(const wsdl::Vector2&);
        const wsdl::Vector2& getVector() const;
    private:
        int speed_base;
        float speed_factor;
        wsdl::Vector2 vector;
        const Paddle* paddle;
        BlockManager* blockManager;

        const Paddle& getPaddle() const;
        std::array<wsdl::Vector2, 4> findHitboxLocation();
};
