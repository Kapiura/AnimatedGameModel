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
	ofVboMesh vboMesh;
	ofImage img;
    ofLight light;
    ofMaterial material;

public:
    Flag(glm::vec3 position);

    std::vector<Particle>& getParticles() { return particles; }
    bool isMouseNearParticle(Particle& particle, float threshold);

    void addFace(ofMesh& mesh, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c);
	void addFace(ofMesh& mesh, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d);
	void addTexCoords(ofMesh& mesh, const glm::vec2& a, const glm::vec2& b, const glm::vec2& c);
	void addTexCoords(ofMesh& mesh, const glm::vec2& a, const glm::vec2& b, const glm::vec2& c, const glm::vec2& d);
	glm::vec3 getVertexFromImg(ofImage& img, int x, int y);

    void update(float dt, bool isBeingDragged);
    void draw();
};

#endif  // FLAG_HPP