#include "../../include/game/powerupmanager.h"

PowerupManager::PowerupManager(const wsdl::Renderer& renderer, const std::string& assets_dir, unsigned int& score, Paddle& paddle, BallManager& ballManager, BlockManager& blockManager) 
    : renderer(&renderer), assets_dir(assets_dir), score(&score), paddle(&paddle), ballManager(&ballManager), blockManager(&blockManager) {}

void PowerupManager::applyEffects(const unsigned int& code, bool& darkest_pit_of_hell) {
    (*score) += POWERUP_POINTS;
    switch(code) {
        case 1:
            paddle->enlarge();
            break;
        case 2:
            paddle->contract();
            break;
        case 3:
            ballManager->multiply();
            break;
        case 4:
            ballManager->setSpeedFactor(FAST);
            break;
        case 5:
            darkest_pit_of_hell = true;
            break;
        case 6:
            blockManager->multiplyTNTs();
            break;
        case 7:
            blockManager->normalizeBlocks();
            break;
        case 8:
            ballManager->setSpeedFactor(SLOW);
            break;
        default:
            break;
    }
}

void PowerupManager::generate(const wsdl::Vector2& location, const wsdl::Vector2&  vector, const unsigned int& code) {
    if (code == 0) {
        return;
    }
    powerups.push_back(Powerup(*renderer, assets_dir + "up_" + std::to_string(code) + ".png", location, vector, code));

}

void PowerupManager::logic(bool& darkest_pit_of_hell) {
    if (darkest_pit_of_hell) {
        clear();
        return;
    }

    powerups.erase(std::remove_if(powerups.begin(), powerups.end(), [this, &darkest_pit_of_hell] (const Powerup& powerup) {
        if (powerup.getY() > powerup.getRenderer().getWindow().getRect().h) { // - powerup.getW()
            return true;
        }
        if (SDL_HasIntersection(&paddle->getRect(), &powerup.getRect())) {
            applyEffects(powerup.getCode(), darkest_pit_of_hell);
            return true;
        }
        return false;
    }), powerups.end());

    for (auto& i : powerups) {
        i.logic();
    }
}

void PowerupManager::clear() {
    powerups.clear();
}

void PowerupManager::blit() const {
    for (const auto& i : powerups) {
        i.blit();
    }
}
