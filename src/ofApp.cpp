#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //map.load("map.PNG");
    map.load("star.jpg");
    //mapPixels = map.getPixels();
    countryList.open(ofToDataPath("country-list.csv"), ofFile::ReadOnly);
    ofBuffer buffer = countryList.readToBuffer();
    // add collection to dropdown gui
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    map.draw(0,0,ofGetWidth(),ofGetHeight());
    for (int i = 0; i < countries.size(); i++) {
        countries[i].drawWireframe();
    }

}

void ofApp::recursiveParsePixels(int x, int y, ofMesh& country) {
// when using for loop to iterate, EXC_BAD_ACCESS
// NEED TO INCREASE STACK SIZE i think

    
    // check if pixel is in pixelHistory
    vector<ofPoint>::iterator pixelItr = find(pixelHistory.begin(),pixelHistory.end(),ofPoint(x,y));
    // when using find, EXC_BAD_ACCESS
    if (pixelItr != pixelHistory.end()) { return; } // ofPoint in vector
    else { pixelHistory.push_back(ofPoint(x,y)); } // ofPoint not found
    //cout << "Parsing pixel " + ofToString(x) + ", " + ofToString(y) << endl;
    
    /*
    vector<ofPoint>::iterator pixelItr;
    for (pixelItr = pixelHistory.begin(); pixelItr != pixelHistory.end(); pixelItr++) {
        if (pixelItr->x == x && pixelItr->y == y) { return; }
    }
    pixelHistory.push_back(ofPoint(x,y));
    */

    //map.update();
    ofColor c = map.getColor(x,y);
    if (c.getLightness() >= 100) { // if pixel is white, keep going
        recursiveParsePixels(x+1,y,country);
        recursiveParsePixels(x-1,y,country);
        recursiveParsePixels(x,y+1,country);
        recursiveParsePixels(x,y-1,country);
    }
    else { // if pixel is not white, add vertex to mesh
        country.addVertex(ofPoint(x,y));
        country.addColor(ofColor(255,0,0));
        //cout << "Added vertex " + ofToString(x) + ", " + ofToString(y) + " to mesh" << endl;
    }
    return;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
void ofApp::mousePressed(int x, int y, int button){
    
    // implement path to shape generation when clicked on country
    // add country to collection with tag name
    
    ofMesh country;
    recursiveParsePixels(x, y, country);
    countries.push_back(country);

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
