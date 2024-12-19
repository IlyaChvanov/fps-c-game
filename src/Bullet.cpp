//
// Created by ilya on 12/19/24.
//

#include "Bullet.h"
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Player.h"
void Bullet::init(b2World &world, Player& player) {
    b2Vec2 bulletPosition = player.getBody()->GetPosition();
    bulletPosition.x += 400.0f;  // Смещение пули по оси X

    // Создаем тело пули
    b2BodyDef bulletBodyDef;
    bulletBodyDef.type = b2_dynamicBody;
    bulletBodyDef.position = bulletPosition;

    // Создаем тело пули
    mBody = world.CreateBody(&bulletBodyDef);  // Обычный указатель на b2Body
    assert(mBody != nullptr && "Failed to create bullet body!");

    // Создаем форму пули
    b2CircleShape bulletShape;
    bulletShape.m_radius = 0.5f;  // Радиус пули

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bulletShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;

    mBody->CreateFixture(&fixtureDef);  // Создаем фикстуру для пули

    // Устанавливаем скорость пули
    b2Vec2 bulletVelocity(20.0f, 0.0f);  // Скорость пули
    mBody->SetLinearVelocity(bulletVelocity);

    // Инициализируем графический круг для пули (SFML)
    mCircle.setRadius(5.0f);
    mCircle.setFillColor(sf::Color(255, 165, 0));  // Оранжевый цвет
    mCircle.setOrigin(5.0f, 5.0f);  // Центр круга в его центре
    mCircle.setPosition(bulletPosition.x, bulletPosition.y);  // Устанавливаем начальную позицию пули

    std::cout << "Player shoots! end" << std::endl;
}


void Bullet::update() {
    if (mBody) {
        b2Vec2 pos = mBody->GetPosition();
        mCircle.setPosition(pos.x, pos.y);
    }
}

void Bullet::render(sf::RenderWindow &window) const {
    window.draw(mCircle);
}

