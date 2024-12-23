#pragma once

#include <vector>
#include <glm/glm.hpp>

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

class Particle
{
    private:
    glm::vec3 position;
    glm::vec3 prevPosition;
    bool hasAnchorPoint;

    public:
    glm::vec2 uv;
    Particle(glm::vec3 pos);

    glm::vec3 getPosition() const { return position; };
    glm::vec3 getPosition() { return position; };
    void setPosition(const glm::vec3& pos) { position = pos; }
    void setAnchorPoint() { hasAnchorPoint = true; };
    void removeAnchorPoint() { hasAnchorPoint = false; };
    bool isPinned() const { return hasAnchorPoint; };

    void update(float dt);
    void draw();
};

#endif