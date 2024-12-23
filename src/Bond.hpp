#pragma once

#include "ofMain.h"
#include "Particle.hpp"

#ifndef BOND_HPP
#define BOND_HPP

class Bond
{
private:
    Particle* particle1;
    Particle* particle2;
    float restLength;
    float maxLength;
    float elasticity;
public:
    Bond(Particle* a, Particle* b);

    void update();
    void draw();
};

#endif // BOND_HPP