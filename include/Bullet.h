//
// Created by ilya on 12/19/24.
//

#ifndef BULLET_H
#define BULLET_H
#include <Entity.h>

#include "Player.h"

class Player;

static size_t num_of_bullets = 0;

class Bullet  {
public:
    void init(b2World &world, Player &player);
    void update();
    void render(sf::RenderWindow &window) const;
private:
    b2FixtureDef fixtureDef;
    sf::Sprite mSprite;
    b2Body* mBody;
    EntityType entityType = EntityType::Bullet;
    sf::CircleShape mCircle;
};



#endif //BULLET_H
