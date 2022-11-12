#include "../../include/game/ball.h"

Ball::Ball(const wsdl::Renderer& renderer, const std::string& file_path, int speed_base, float speed_factor, const Paddle& paddle, BlockManager& blockManager)
    :Sprite(renderer, file_path), speed_base(speed_base), speed_factor(speed_factor), paddle(&paddle), blockManager(&blockManager) {
    lookUp();
    //hitbox_location = { wsdl::Vector2(0, 0), wsdl::Vector2(0, 0), wsdl::Vector2(0, 0), wsdl::Vector2(0, 0) };
}

const Paddle& Ball::getPaddle() const {
    return *paddle;
}

std::array<wsdl::Vector2, 4> Ball::findHitboxLocation() {
    std::array<wsdl::Vector2, 4> hitbox_location;
    hitbox_location[0] = { getX() + getW() / 2, getY() }; // top point
    hitbox_location[1] = { getX() + getW(), getY() + getH() / 2 }; // right point
    hitbox_location[2] = { getX() + getW() / 2, getY() + getH() }; // bottom point
    hitbox_location[3] = { getX(), getY() + getH() / 2 }; // left point
    /*

        o
    o       o
        o

    */
    return hitbox_location;
}

void Ball::logic(const bool& ready) {
    // ready state
    if (ready) { // placed here and not at the end to avoid glitches
        setLocation({ getPaddle().getX() + getPaddle().getW() / 2 - getW() / 2,
                      getPaddle().getY() - getH() - 5 });
        return;
    } else {
        setLocation({ getX() + getVector().x, getY() + getVector().y });
    }
    
    // left and right walls
    if (getX() <= 0) { // window.width - ball.diameter
        setX(1); // to avoid glitches
        setVector().reverseX();
    }

    if (getX() >= getRenderer().getWindow().getRect().w - getW()) {
        setX(getRenderer().getWindow().getRect().w - getW() - 1); // to avoid glitches
        setVector().reverseX();
    }

    // ceiling 
    if (getY() <= 0) { 
        setY(1); // to avoid glitches
        setVector().reverseY();
    }

    // find ball's position in advance
    SDL_Rect ball_rect = getRect();
    ball_rect.x += getVector().x;
    ball_rect.y += getVector().y;

    // paddle interaction
    if (SDL_HasIntersection(&ball_rect, &getPaddle().getRect())) {
        int loc = getX() - getPaddle().getX(); // ball's location in paddle
        int paddle_section = getPaddle().getW() / (2 * getSpeedBase() * getSpeedFactor()); // vec.x values are [-speed * speed_factor + 1, speed * speed_factor - 1] (see reverse function), which are in total 2 * total speed 
        int new_vx = - getSpeedBase() * getSpeedFactor() + 1; // vec.x values shouldn't be equal to total speed because that would lead to vec.y be equal to 0 later on...
        // calculate the new angle
        int i = 0;
        while (i < loc && new_vx < getSpeedBase() * getSpeedFactor() - 1) { // why getSpeedBase() * getSpeedFactor() - 1? have a look above...
            i += paddle_section;
            new_vx++;
        }
        // fix y position so that it doesn't phase too much
        if (loc <= getW() + 1 || loc >= getPaddle().getW() - getW() - 1) {
            setVector().reverseY();
        } else {
            setY(getPaddle().getY() - getH() - 1);
        }
        
        setVector().x = new_vx;
        //setVector().reverseY(); // unstable...
        setVector().y = -sqrt(pow(getSpeedBase() * getSpeedFactor(), 2) - pow(getVector().x, 2)); // improvement... pythagoras theorem basically
    }

    // block interaction
    std::array<wsdl::Vector2, 4> hitbox_location = findHitboxLocation();
    for(auto& i : hitbox_location) {
        std::vector<Block>::iterator block;
        bool found;

        // firstly, let's find out ball's next position
        // we can do this by adding our vector to our current position
        const wsdl::Vector2 next { i.x + getVector().x, i.y + getVector().y };
        std::tie(block, found) = blockManager->findBlockAt(next.x / BLOCK_W, next.y / BLOCK_H);
        if (found) {
            /*
                A--------B
                |        |
                D--------C
            */
            // secondly, let's distinguish the sides of a block
            // if the ball is touching A -- D or B -- C , reverseX()
            //          -//-           A -- B and D -- C, reverseY()
            // it's important to note that sides A -- D and B -- C have constant x
            //                     and similarly A -- B and D -- C have constant y
            if ((i.x <= block->getX() && next.x >= block->getX()) ||
                (i.x >= block->getX() + BLOCK_W && next.x <= block->getX() + BLOCK_W)) { // sides A -- D and B -- C
                setVector().reverseX();
            }
            if ((i.y <= block->getY() && next.y >= block->getY()) ||
                (i.y >= block->getY() + BLOCK_H && next.y <= block->getY() + BLOCK_H)) { // sides A -- B and D -- C
                setVector().reverseY();
            }
            
            blockManager->hitBlock(getLocation(), getVector(), block);
            break;
        }
    }
}

void Ball::lookUp() {
    vector = { 0, int(- getSpeedBase() * getSpeedFactor()) };
}

const int& Ball::getSpeedBase() const {
    return speed_base;
}

void Ball::setSpeedBase(const int& speed_base) {
    this->speed_base = speed_base;
}

const float& Ball::getSpeedFactor() const {
    return speed_factor;
}

void Ball::setSpeedFactor(const float& speed_factor) {
    this->speed_factor = speed_factor;
}

const wsdl::Vector2& Ball::getVector() const {
    return vector;
}

wsdl::Vector2& Ball::setVector() {
    return vector;
}

void Ball::setVector(const wsdl::Vector2& vector) {
    this->vector = vector;
}
