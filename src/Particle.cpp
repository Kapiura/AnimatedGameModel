#include "Particle.hpp"
#include "ofMain.h"

Particle::Particle(glm::vec3 position):
position(position),
prevPosition(position),
radius(3.0f),
movable(false)
{
};

void Particle::update(float dt, bool isBeingDragged)
{
    if (movable && isBeingDragged)
    {
        position = glm::vec3(ofGetMouseX(), ofGetMouseY(), position.z);
    }
    else if (movable)
    {
        return;
    }
    else
    {
        glm::vec3 tempPos = position;
        position += position - prevPosition;
        position += glm::vec3(0.0f, 9.81f, 0.0f) * dt * dt;
        prevPosition = tempPos;
    }
}


void Particle::draw()
{
  ofSetColor(0,255,0);
  ofDrawSphere(position, radius);
}