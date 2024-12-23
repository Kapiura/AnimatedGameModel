#include "Flag.hpp"

Flag::Flag(glm::vec3 position)
    : rows(50), columns(50), spacing(20.0f)
{
    light.setPosition(0, 0, 300);
    light.setDiffuseColor(ofFloatColor(1.0, 1.0, 1.0));
    light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));
    material.setDiffuseColor(ofFloatColor(0.8, 0.8, 0.8));
    material.setSpecularColor(ofFloatColor(0.5, 0.5, 0.5));
    material.setShininess(64);

    #ifdef TARGET_OPENGLES
    ofEnableNormalizedTexCoords();
    #endif

    img.load("flag.png");

    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    int width = img.getWidth();
    int height = img.getHeight();
    glm::vec2 imageSize(width, height);

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            glm::vec3 particlePos = glm::vec3(
                position.x + (x * spacing),
                position.y + (y * spacing),
                0
            );

            Particle p(particlePos);
            if (x == 0) p.setMovable(true);
            particles.push_back(p);

            mesh.addVertex(particlePos);

            glm::vec2 texCoord = glm::vec2(
                static_cast<float>(x) / (columns - 1) * img.getWidth(),
                static_cast<float>(y) / (rows - 1) * img.getHeight()
            );
            mesh.addTexCoord(texCoord);
        }
    }

    for (int y = 0; y < rows - 1; y++) {
        for (int x = 0; x < columns - 1; x++) {
            int nw = y * columns + x;
            int ne = nw + 1;
            int sw = nw + columns;
            int se = sw + 1;

            mesh.addIndex(nw);
            mesh.addIndex(ne);
            mesh.addIndex(se);

            mesh.addIndex(nw);
            mesh.addIndex(se);
            mesh.addIndex(sw);
        }
    }

    vboMesh = mesh;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            int id = y * columns + x;

            if (x < columns - 1) {
                bonds.emplace_back(&particles[id], &particles[id + 1]);
            }
            if (y < rows - 1) {
                bonds.emplace_back(&particles[id], &particles[id + columns]);
            }
        }
    }
}

void Flag::update(float dt, bool isBeingDragged)
{
    for (auto& el : particles)
        el.update(dt, isBeingDragged);

    for (int i = 0; i < 5; i++)
        for (auto& el : bonds)
            el.update();
    for (int i = 0; i < particles.size(); i++) {
        mesh.setVertex(i, particles[i].getPosition());
    }
    vboMesh = mesh;
}


void Flag::draw()
{
    ofEnableDepthTest();
    ofScale(.50, .50, .50);
    light.enable();
    material.begin();
    img.bind();
    ofPushMatrix();
    if (ofGetKeyPressed())
        vboMesh.draw();
    else
        mesh.draw();
    ofPopMatrix();
    img.unbind();
    material.end();
    light.disable();
    ofDisableDepthTest();
}

bool Flag::isMouseNearParticle(Particle& particle, float threshold)
{
    glm::vec3 mousePos = glm::vec3(ofGetMouseX(), ofGetMouseY(), 0.0f);
    float distance = glm::distance(mousePos, particle.getPosition());
    return distance < threshold;
}

void Flag::addFace(ofMesh& mesh, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) {
	mesh.addVertex(a);
	mesh.addVertex(b);
	mesh.addVertex(c);
}

void Flag::addFace(ofMesh& mesh, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d) {
	addFace(mesh, a, b, c);
	addFace(mesh, a, c, d);
}

void Flag::addTexCoords(ofMesh& mesh, const glm::vec2& a, const glm::vec2& b, const glm::vec2& c) {
	mesh.addTexCoord(a);
	mesh.addTexCoord(b);
	mesh.addTexCoord(c);
}

void Flag::addTexCoords(ofMesh& mesh, const glm::vec2& a, const glm::vec2& b, const glm::vec2& c, const glm::vec2& d) {
	addTexCoords(mesh, a, b, c);
	addTexCoords(mesh, a, c, d);
}

glm::vec3 Flag::getVertexFromImg(ofImage& img, int x, int y) {
	ofColor color = img.getColor(x, y);
	if(color.a > 0) {
		float z = ofMap(color.a, 0, 255, -480, 480);
		return glm::vec3(x - img.getWidth() / 2, y - img.getHeight() / 2, z);
	} else {
		return glm::vec3(0, 0, 0);
	}
}