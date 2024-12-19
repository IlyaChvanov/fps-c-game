#include "Player.h"

#include <iostream>

#include "Bullet.h"

Player::Player() : Entity(texturePaths) {
    bullets_.reserve(1000);
}

void Player::init(b2World &world) {
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 100.0f);
    bodyDef.angle = 0.0f;
    bodyDef.fixedRotation = false;

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);  // Размеры прямоугольной формы (например, 2x2)
    createBody(world, *getBodyDef());

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;  // Задаем плотность (масса будет вычисляться на основе плотности)
    fixtureDef.friction = 0.3f;  // Плотность трения (опционально)
    fixtureDef.restitution = 0.5f;  // Коэффициент упругости (опционально)

    world_ = std::make_shared<b2World>(world);
    mBody->CreateFixture(&fixtureDef);
}

void Player::move(float deltaX, float deltaY) {
    mSprite.move(deltaX * m_moveSpeed, deltaY * m_moveSpeed);
    if (mBody) {
        b2Vec2 newPos(mSprite.getPosition().x, mSprite.getPosition().y);
        mBody->SetTransform(newPos, mBody->GetAngle());
    }
}

void Player::shoot() {
    if (mBody) {
        std::cout << "Player shoots! begin" << std::endl;
        auto bullet = std::make_shared<Bullet>();
        bullet->init(*world_, *this);
        std::cout << "player shot " << num_of_bullets++ << std::endl;
        if (bullet == nullptr) {
            std::cerr << "Bullet dissapeared";
        }
        else {
            std::cout << "Bullet exist" << std::endl;
            bullets_.push_back(bullet);
        }
    }
}

void Player::onCollision(Entity& other) {
        if (other.getType() == EntityType::Ground) {
            m_isOnGround = true;
            std::cout << "Player collided with the ground!" << std::endl;
        } else if (other.getType() == EntityType::Enemy) {
            std::cout << "Player collided with an enemy!" << std::endl;
        } else if (other.getType() == EntityType::Bullet) {
            std::cout << "Player collided with a bullet!" << std::endl;
        } else {
            std::cout << "Player collided with an unknown entity!" << std::endl;
        }
    std::cout << "Player collided with another entity!" << std::endl;
}

void Player::update(float deltaTime) {
    if (mBody) {
        const b2Vec2& pos = mBody->GetPosition();
        mSprite.setPosition(pos.x, pos.y);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        jump();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        moveRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        shoot();
    }
    // for (auto& bullet : bullets_) {
    //     bullet->update();
    // }
}

void Player::render(sf::RenderWindow& window) {
    window.draw(mSprite);
    // for (auto& bullet : bullets_) {
    //     bullet->render(window);  // Отрисовываем каждую пулю
    // }
}

void Player::jump() {
    if (m_isOnGround) {
        if (mBody != nullptr) {
            std::cout << "Player jumped!" << std::endl;
            float impulse = mBody->GetMass() * 100;
            std::cout << "Player impulse: " << impulse << std::endl;
            mBody->ApplyLinearImpulse( b2Vec2(0,-impulse), mBody->GetWorldCenter(), true );
            m_isOnGround = false;
            }
        }
}

void Player::moveLeft() {
    move(-1.0f, 0.0f);
}

void Player::moveRight() {
    move(1.0f, 0.0f);
}

shared_ptr<b2BodyDef> Player::getBodyDef() const {
    return std::make_shared<b2BodyDef>(bodyDef);
}
