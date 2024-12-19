#include "Player.h"

Player::Player() : Entity(texturePaths){
    bodyDef.type = b2_dynamicBody;          // ��� ����: ������������
    bodyDef.position.Set(0.0f, 10.0f);      // ��������� ������� (x, y)
    bodyDef.angle = 0.0f;                   // ���� �������� � ��������
    bodyDef.fixedRotation = false;
}

void Player::move(float deltaX, float deltaY) {
    // ����������� ������ �� ������ deltaX � deltaY
    mSprite.move(deltaX * m_moveSpeed, deltaY * m_moveSpeed);  // ���������� ������

    if (mBody) {
        b2Vec2 newPos(mSprite.getPosition().x, mSprite.getPosition().y);
        mBody->SetTransform(newPos, mBody->GetAngle());  // ���������� ���� Box2D
    }
}

void Player::shoot() {
    // ������ ��� �������� (��������, �������� �������)
    // ��� ������ ������, ����� ����� �������� ��� ��� ��������
    std::cout << "Player shoots!" << std::endl;
}

void Player::onCollision(Entity& other) {
    // ������ ��� ��������� ������������ (��������, � ������� ��� �������������)
    // ��� ������ ������, ����� ����� �������� ��� ��� ��������� ��������
    std::cout << "Player collided with another entity!" << std::endl;
}

void Player::update(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        jump();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        moveLeft();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        moveRight();
    }
}

void Player::render(sf::RenderWindow& window) {
    window.draw(mSprite);
}

void Player::jump() {
    if (m_isOnGround) {
        if (mBody) {
            mBody->ApplyForceToCenter(b2Vec2(0, m_jumpForce), true);
            m_isOnGround = false;
            std::cout << "Player jumped!" << std::endl;
        }
    }
}

void Player::moveLeft() {
    // ���������� ������ �����
    move(-1.0f, 0.0f);
    std::cout << "Player moving left!" << std::endl;
}

void Player::moveRight() {
    // ���������� ������ ������
    move(1.0f, 0.0f);
}

shared_ptr<b2BodyDef> Player::getBodyDef() const {
    return std::make_shared<b2BodyDef>(bodyDef);
}
