#pragma once

#include "ofMain.h"
#include "Particle.hpp"
#include "Bond.hpp"
#include "ofTexture.h"
#include <vector>
#include <glm/glm.hpp>

#ifndef FLAG_HPP
#define FLAG_HPP

class Flag
{
private:
    int rows;
    int columns;
    float spacing;

    std::vector<Particle> particles;
    std::vector<Bond> bonds;

    ofMesh mesh;
    ofTexture imgTexture;

public:
    Flag(glm::vec3 position);

    std::vector<Particle>& getParticles() { return particles; }
    bool isMouseNearParticle(Particle& particle, float threshold);

    void update(float dt, bool isBeingDragged);
    void draw();
};

#endif  // FLAG_HPP