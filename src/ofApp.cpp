#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(65, 103, 166);

    glm::vec3 center = glm::vec3(ofGetWidth(), 50.0f, -150.0f);

    flag = new Flag(center);
}

void ofApp::exit()
{
	delete flag;
}

//--------------------------------------------------------------
void ofApp::update()
{
    float deltaTime = ofGetLastFrameTime();
    if(windEnabled)
    {
        float wind = ofRandom(-ofNoise(ofGetElapsedTimef()), ofNoise(ofGetElapsedTimef()))/4;
        for (auto& particle : flag->getParticles())
        {
            if (!particle.isMovable())
            {
                if(!changeWindDirectory)
                    particle.applyForce(glm::vec3(std::abs(wind), wind/2, wind));
                else
                    particle.applyForce(glm::vec3(-std::abs(wind), wind/2, wind));
            }
        }
    }
    flag->update(deltaTime, isDragging);
}


//--------------------------------------------------------------
void ofApp::draw()
{
    flag->draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if(key == 'c')
        changeBool(changeWindDirectory);
    if(key == 'w')
        changeBool(windEnabled);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    for (auto& particle : flag->getParticles())
    {
        if (flag->isMouseNearParticle(particle, 20.0f))
        {
            draggedParticle = &particle;
            isDragging = true;
            draggedParticle->setMovable(true);
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    if (isDragging)
    {
        isDragging = false;
        draggedParticle->setMovable(false);
        draggedParticle = nullptr;
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

void ofApp::changeBool(bool& statement)
{
    if(statement)
        statement = false;
    else
        statement = true;
}
