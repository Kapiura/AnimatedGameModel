#include "Particle.hpp"
#include "ofMain.h"

Particle::Particle(glm::vec3 pos):
position(pos), prevPosition(pos), hasAnchorPoint(false)
{
  color.r = ofRandom(0.0f, 255.0f);
  color.g = ofRandom(0.0f, 255.0f);
  color.b = ofRandom(0.0f, 255.0f);
}

void Particle::draw()
{
  ofSetColor(color);
  ofDrawSphere(position, radius);
}

void Particle::update(float dt)
{
    if (hasAnchorPoint == true)
    {
        return;
    }

    glm::vec3 temp = position;
    position += position - prevPosition;
    position += glm::vec3(0.0f, -9.81f,0) * dt * dt;
    prevPosition = temp;
}