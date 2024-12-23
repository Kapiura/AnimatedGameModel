#include "Flag.hpp"

Flag::Flag(glm::vec3 position):
rows(20),
columns(20),
spacing(20.0f)
{
    for(int y = 0; y < rows; y++)
        for(int x = 0; x < columns; x++)
        {
            glm::vec3 particlePos = glm::vec3(
                position.x + (x * spacing),
                position.y + (y * spacing),
                0
            );
            Particle p(particlePos);
            if (x == 0)
                p.setMovable(true);
            particles.push_back(p);
        }

    for(int y = 0; y < rows; y++)
        for(int x = 0; x < columns; x++)
        {
            int id = y * columns + x;

            if(x < columns - 1)
            {
                bonds.emplace_back(&particles[id], &particles[id + 1]);
            }
            if(y < rows - 1)
            {
                bonds.emplace_back(&particles[id], &particles[id + columns]);
            }
        }
}

void Flag::update(float dt, bool isBeingDragged)
{
    for(auto& el: particles)
        el.update(dt,isBeingDragged);
    for (int i = 0; i < 5; i++)
        for(auto& el: bonds)
            el.update();
}

void Flag::draw()
{
    for(auto& el: particles)
    {
        el.draw();
    }
    for(auto& el: bonds)
        el.draw();
}

bool Flag::isMouseNearParticle(Particle& particle, float threshold)
{
    glm::vec3 mousePos = glm::vec3(ofGetMouseX(), ofGetMouseY(), 0.0f);
    float distance = glm::distance(mousePos, particle.getPosition());
    return distance < threshold;
}
