#include "../../include/game/ballmanager.h"

BallManager::BallManager(const wsdl::Renderer& renderer, const std::string& assets_dir, const Paddle& paddle, BlockManager& blockManager) 
    : renderer(&renderer), assets_dir(assets_dir), paddle(&paddle), blockManager(&blockManager) {
    reset();
}

Ball BallManager::defaultBall() {
    return Ball(*renderer, assets_dir + "ball.png", 4, NORMAL, *paddle, *blockManager);
}

void BallManager::logic(bool& darkest_pit_of_hell, const bool& ready) {
    for (auto& i : balls) {
        i.logic(ready);
    }

    balls.erase(std::remove_if(balls.begin(), balls.end(), [](const Ball& ball){
        // darkest pit of hell
        if (ball.getY() >= ball.getRenderer().getWindow().getRect().h - ball.getW()) {
            return true;
        }
        return false;
    }), balls.end());

    if (balls.size() == 0) {
        darkest_pit_of_hell = true;
    }
}

void BallManager::multiply() {
    std::vector<Ball> new_balls;
    for (unsigned int i = 0; i < balls.size(); i++) {
        Ball new_ball(balls[i]);
        new_ball.setVector().reverseX();
        new_ball.setVector().reverseY();
        new_balls.push_back(std::move(new_ball));
    }

    balls.insert(balls.end(), std::make_move_iterator(new_balls.begin()), std::make_move_iterator(new_balls.end()));
}

void BallManager::setSpeedFactor(const float& factor) {
    for (auto& i : balls) {
        i.setSpeedFactor(factor);
    }
}

void BallManager::blit() {
    for (auto& i : balls) {
        i.blit();
    }
}

void BallManager::reset() {
    balls.clear();
    balls.push_back(defaultBall());
    balls.front().lookUp();
}
