#pragma once
#include "ofMain.h"
#include <glm/glm.hpp>

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

class Particle
{
private:
    glm::vec3 position;
    glm::vec3 prevPosition;
    glm::vec3 uvMap;
    float radius;
    bool movable;
    ofColor color;

public:
    Particle(glm::vec3 position);

    glm::vec3 getPosition() const { return position; };
    glm::vec3 getPosition() { return position; };

    bool isMovable() const { return movable;};

    void setMovable(bool statement) { movable = statement; };
    void setPosition(glm::vec3 pos) { position = pos; };
    void applyForce(const glm::vec3& force) { position += force; };

    void update(float dt, bool isBeingDragged);
    void draw();
};

#endif