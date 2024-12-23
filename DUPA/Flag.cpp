#include "Flag.hpp"
#include "ofMain.h"

// Konstruktor klasy Flag
Flag::Flag():
    row(20), cols(20), spacing(20.0f)
{
    // Inicjalizacja cząsteczek
    for (int y = 0; y < row; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            // Oblicz pozycję cząstki
            glm::vec3 position(
                -(x *spacing), // Środek lewej połowy
                -(y * spacing) + 50.0f , // Nieco poniżej górnej krawędzi
                0
            );

            Particle p(position);

            if (x % cols == 0) // Zaczep cząstki w pierwszej kolumnie
                p.setAnchorPoint();

            // Oblicz współrzędne UV
            float u = static_cast<float>(x * spacing) / (cols - 1);
            float v = static_cast<float>(y * spacing + 50.0f) / (row - 1);
            p.uv = glm::vec2(u, v);

            particles.push_back(p);
        }
    }

    // Tworzenie constraints (ograniczeń)
    for (int y = 0; y < row; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            int id = y * cols + x;

            if (x < cols - 1)
                constraints.emplace_back(&particles[id], &particles[id + 1]);
            if (y < row - 1)
                constraints.emplace_back(&particles[id], &particles[id + cols]);
        }
    }

    // Próba załadowania tekstury
    if (loadTexture()) {
        ofLogNotice() << "Texture successfully loaded!";
    } else {
        ofLogError() << "Failed to load texture!";
    }
}

// Funkcja do ładowania tekstury
bool Flag::loadTexture() {
    ofLogNotice() << "Loading texture from 'flag.png'...";
    textureImage.load("flag.png");

    if (textureImage.isAllocated()) {
        texture = textureImage.getTexture();
        return true;
    } else {
        ofLogError() << "Texture could not be loaded! Ensure 'flag.png' is in the 'data' folder.";
        return false;
    }
}

// Aktualizacja stanu flagi
void Flag::update(float dt) {
    // Aktualizuj pozycje cząstek
    for (auto& p : particles) {
        p.update(dt);
    }

    // Satysfakcja ograniczeń
    for (int i = 0; i < 5; i++) {
        for (auto& c : constraints) {
            c.satisfy();
        }
    }
}

void Flag::draw() {
    // Debugowanie cząsteczek
    // for (const auto& p : particles) {
    //     ofSetColor(255, 0, 0); // Czerwone punkty
    //     ofDrawSphere(p.getPosition(), 5);
    // }

    // Sprawdzenie tekstury
    if (texture.isAllocated()) {
        texture.bind();
        // ofSetColor(255, 255, 255); // Ustawienie koloru na biały, aby tekstura była widoczna
    } else {
        ofLogError() << "Texture not allocated, skipping drawing!";
        return;
    }

    // Stworzenie siatki
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    // Dodanie wierzchołków i współrzędnych UV
    for (const auto& p : particles) {
        mesh.addVertex(p.getPosition()); // Pozycja cząstki w przestrzeni świata
        mesh.addTexCoord(p.uv);          // Współrzędne tekstury
    }

    // Indeksy dla siatki
    for (int y = 0; y < row - 1; y++) {
        for (int x = 0; x < cols - 1; x++) {
            int id = y * cols + x;

            mesh.addIndex(id);
            mesh.addIndex(id + 1);
            mesh.addIndex(id + cols);

            mesh.addIndex(id + 1);
            mesh.addIndex(id + cols + 1);
            mesh.addIndex(id + cols);
        }
    }

    // Rysowanie siatki
    mesh.draw();

    // Wyłącz teksturę
    texture.unbind();
}
