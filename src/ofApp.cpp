const int TILES_X = 100;
static const int TILES_Y = 100;
static const int SIZE_X = 10;
static const int SIZE_Y = 10;

#include "ofApp.h"

void ofApp::setup() {
  ofSetFrameRate(60);
  ofBackground(0);
  ofPlanePrimitive plane;

  mesh = new ofMesh[TILES_X * TILES_Y];
  mutant = new bool[TILES_X * TILES_Y];
  degX = -100;
  degY = 15;

  for (int y = 0; y < TILES_Y; y++){
    for (int x = 0; x < TILES_X; x++){
      // set of width and height
      plane.set(SIZE_X, SIZE_Y);
      plane.setResolution(2, 2);
      //get mesh
      mesh[x + y * TILES_X] = plane.getMesh();
      

      // repeat for the number of vertices
      for (int j = 0; j < mesh[x+y*TILES_X].getVertices().size(); j++) {
        // extract the coordinates of the vertices
        glm::vec3 vert = mesh[x+y*TILES_X].getVertices()[j];
        // update X,Y coordinate
        vert.x += SIZE_X * x - (TILES_X * SIZE_X) * 0.5;
        vert.y += SIZE_Y * y - (TILES_Y * SIZE_Y) * 0.5;
        mesh[x + y * TILES_X].setVertex(j, vert);
      }
    }
  }
}

void ofApp::update() {
  for (int x = 0; x < TILES_X; x++){
    for (int y = 0; y < TILES_Y; y++){
      // repeat for the number of vertices
      for (int j = 0; j < mesh[x+y*TILES_X].getVertices().size(); j++) {
        // extract the coordinates of the vertices
        glm::vec3 pos = mesh[x+y*TILES_X].getVertices()[j];
        // update Z coordinates with random numbers
        pos.z = ofRandom(-10, 0);
        mesh[x + y * TILES_X].setVertex(j, pos);
      }
    }
  }

  for (int i = 0; i< TILES_X * TILES_Y; i++){
    mutant[i] = false;
  }
  
  if (int(ofGetElapsedTimef()*100) % 5 == 0){
    for (int i = 0; i < 1; i++){
      int r = 10;
      int x = ofRandom(r+1, TILES_X-r-1);
      int y = ofRandom(r+1, TILES_Y-r-1);

      for(int deg = 0; deg < 360; deg++){
        int rx = cos(deg*(3.14156/180)) * r;
        int ry = sin(deg*(3.14156/180)) * r;
        mutant[(x+rx) + (y+ry) * TILES_X] = true;
        int z = ofRandom(-300, 300);
        // xtract the coordinates of the first vertex
        glm::vec3 pos = mesh[(x+rx) + (y+ry) * TILES_X].getVertices()[0];
        // update Z coordinates with random numbers
        pos.z = z;
        mesh[(x+rx) + (y+ry) * TILES_X].setVertex(0, pos);
      }
    }
  }
}
  
void ofApp::draw() {
	cam.begin();
  degX += 1;
  degY += 0;
  ofRotateXDeg(degX);
  ofRotateYDeg(degY);
  ofRotateZDeg(0);

  for ( int i = 0; i < TILES_X * TILES_Y; i++){
    if (mutant[i] == true){
      ofSetColor(0, 0, 255);
    }else{
      ofSetColor(255, 255, 255);
    }

    mesh[i].drawWireframe();
  }
  cam.end();
}
