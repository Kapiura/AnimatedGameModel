#include "Bond.hpp"
#include "Particle.hpp"
#include <glm/glm.hpp>

Bond::Bond(Particle* a, Particle* b):
    particle1(a),
    particle2(b),
    elasticity(1.2f)
{
    restLength = glm::distance(
        a->getPosition(),
        b->getPosition());
    maxLength = restLength * elasticity;
}

void Bond::update()
{
    glm::vec3 delta = particle2->getPosition() - particle1->getPosition();
    float currentLength = glm::length(delta);

    if (currentLength > maxLength)
        currentLength = maxLength;

    if (currentLength > 0.0f) {
        float difference = (currentLength - restLength) / currentLength;

        glm::vec3 correction = delta * 0.5f * difference;

        if (!particle1->isMovable()) {
            particle1->setPosition(particle1->getPosition() + correction);
        }
        if (!particle2->isMovable()) {
            particle2->setPosition(particle2->getPosition() - correction);
        }
    }
}

void Bond::draw()
{
    ofDrawLine(particle1->getPosition(), particle2->getPosition());
}