#include "Constraint.hpp"
#include <glm/glm.hpp>
#include "ofMain.h"

Constraint::Constraint(Particle* a, Particle* b):
p1(a), p2(b)
{
    restLength = glm::distance(a->getPosition(), b->getPosition());
    maxLength = restLength * elasticity;
};

void Constraint::satisfy()
{
    glm::vec3 delta = p2->getPosition() - p1->getPosition();
    float currentLength = glm::length(delta);

    if (currentLength > maxLength)
        currentLength = maxLength;

    float difference = (currentLength - restLength) / currentLength;

    if (!p1->isPinned() && !p2->isPinned())
    {
        p1->setPosition(p1->getPosition() + delta * 0.5f * difference);
        p2->setPosition(p2->getPosition() - delta * 0.5f * difference);
    }
    else if (!p1->isPinned())
    {
        p1->setPosition(p1->getPosition() + delta * difference);
    }
    else if (!p2->isPinned())
    {
        p2->setPosition(p2->getPosition() - delta * difference);
    }

}

void Constraint::draw()
{
    ofDrawLine(p1->getPosition(), p2->getPosition());
}