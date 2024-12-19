#pragma once
#include <list>
#include <unordered_map>
#include <vector>
#include <memory>

#include "Entity.h"
#include "Bullet.h"

class Bullet;

class Player : public Entity {
public:
    Player();
    ~Player() override = default;

    void init(b2World &world) override;
    void move(float deltaX, float deltaY) override;
    void shoot() override;
    void onCollision(Entity& other) override;
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    void jump();
    void moveLeft();
    void moveRight();
    shared_ptr<b2BodyDef> getBodyDef() const;
    const std::vector<std::shared_ptr<Bullet>>& getBullets() const {
        return bullets_;
    }

private:
    float m_moveSpeed{ 1.5f };
    float m_jumpForce{ 15.0f };
    bool m_isOnGround{ true };
    b2BodyDef bodyDef;
    EntityType m_entityType = EntityType::Player;
    std::shared_ptr<b2World> world_;
    std::vector<std::shared_ptr<Bullet>> bullets_;
    static inline const std::unordered_map<std::string, path> texturePaths = {
        {"idle", path("Image/main-character/Idle.gif")},
    };
};
