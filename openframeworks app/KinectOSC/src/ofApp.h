#pragma once

#include "ofMain.h"
#include "ofxKinectNui.h"
#include "ofxKinectNuiPlayer.h"
#include "ofxKinectNuiRecorder.h"
#include "ofxOsc.h"

#define HOST "127.0.0.1"
#define PORT 12345

class ofxKinectNuiDrawTexture;
class ofxKinectNuiDrawSkeleton;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void exit();
		void keyPressed  (int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void kinectPlugged();
		void kinectUnplugged();

		int angle;
		ofxKinectNui kinect;
		ofxBase3DVideo* kinectSource;
		ofxOscSender sender;
	
		// Please declare these texture pointer and initialize when you want to draw them
		ofxKinectNuiDrawTexture*	videoDraw_;
		ofxKinectNuiDrawTexture*	depthDraw_;
		ofxKinectNuiDrawTexture*	labelDraw_;
		ofxKinectNuiDrawSkeleton*	skeletonDraw_;

		ofPoint leftHand;
		ofPoint rightHand;
		ofPoint leftHand2;
		ofPoint rightHand2;
		ofPoint spine;
		
};
