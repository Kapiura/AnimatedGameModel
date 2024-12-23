#pragma once
#include "Particle.hpp"

#ifndef CONSTRAINT_HPP
#define CONSTRAINT_HPP

struct Constraint {
    Particle* p1;
    Particle* p2;
    float restLength;
    float maxLength;
    float elasticity = 1.5f;

    Constraint(Particle* a, Particle* b);

    void satisfy();
    void draw();
};

#endif