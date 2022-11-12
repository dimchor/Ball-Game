#include "../../include/game/powerup.h"

Powerup::Powerup(const wsdl::Renderer& renderer, const std::string& file_path)
    : wsdl::Sprite(renderer, file_path) {}

Powerup::Powerup(const wsdl::Renderer& renderer, const std::string& file_path, const wsdl::Vector2& location, const wsdl::Vector2& vector, const unsigned int& code)
    : Powerup(renderer, file_path) {
        setLocation(location);
        setVector(vector);
        setVector().reverseX();
        setVector().reverseY();
        this->code = code;
}

wsdl::Vector2& Powerup::setVector() {
    return vector;
}

void Powerup::setVector(const wsdl::Vector2& vector) {
    this->vector = vector;
}

const wsdl::Vector2& Powerup::getVector() const {
    return vector;
} 

const unsigned int& Powerup::getCode() const {
    return code;
}

void Powerup::logic() {
    setLocation({ getX() + getVector().x, getY() + getVector().y });
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

    if (getVector().y < 6) { // accelerating gravity up to 6
        setVector({ getVector().x, getVector().y + 1 });
    }
}
