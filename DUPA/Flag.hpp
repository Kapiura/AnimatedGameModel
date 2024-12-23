#include "Particle.hpp"
#include "Constraint.hpp"
#include <vector>
#include "ofImage.h"
#include "ofPixels.h"

#ifndef FLAG_HPP
#define FLAG_HPP

class Flag
{
    public:
    Flag();

    int row;
    int cols;
    float spacing;
    ofImage textureImage;
    ofTexture texture;

    std::vector<Particle> particles;
    std::vector<Constraint> constraints;

    void update(float dt);
    void draw();
    bool loadTexture();
};

#endif
