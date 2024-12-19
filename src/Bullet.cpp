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
    bulletPosition.x += 400.0f;  // �������� ���� �� ��� X

    // ������� ���� ����
    b2BodyDef bulletBodyDef;
    bulletBodyDef.type = b2_dynamicBody;
    bulletBodyDef.position = bulletPosition;

    // ������� ���� ����
    mBody = world.CreateBody(&bulletBodyDef);  // ������� ��������� �� b2Body
    assert(mBody != nullptr && "Failed to create bullet body!");

    // ������� ����� ����
    b2CircleShape bulletShape;
    bulletShape.m_radius = 0.5f;  // ������ ����

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bulletShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;

    mBody->CreateFixture(&fixtureDef);  // ������� �������� ��� ����

    // ������������� �������� ����
    b2Vec2 bulletVelocity(20.0f, 0.0f);  // �������� ����
    mBody->SetLinearVelocity(bulletVelocity);

    // �������������� ����������� ���� ��� ���� (SFML)
    mCircle.setRadius(5.0f);
    mCircle.setFillColor(sf::Color(255, 165, 0));  // ��������� ����
    mCircle.setOrigin(5.0f, 5.0f);  // ����� ����� � ��� ������
    mCircle.setPosition(bulletPosition.x, bulletPosition.y);  // ������������� ��������� ������� ����

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

