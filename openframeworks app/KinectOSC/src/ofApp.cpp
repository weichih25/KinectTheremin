#include "ofApp.h"
#include "ofxKinectNuiDraw.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	ofxKinectNui::InitSetting initSetting;
	initSetting.grabVideo = true;
	initSetting.grabDepth = true;
	initSetting.grabAudio = false;
	initSetting.grabLabel = true;
	initSetting.grabSkeleton = true;
	initSetting.grabCalibratedVideo = true;
	initSetting.grabLabelCv = false;
	initSetting.videoResolution = NUI_IMAGE_RESOLUTION_640x480;
	initSetting.depthResolution = NUI_IMAGE_RESOLUTION_640x480;
	kinect.init(initSetting);
//	kinect.setMirror(false); // if you want to get NOT mirror mode, uncomment here
//	kinect.setNearmode(true); // if you want to set nearmode, uncomment here
	kinect.open();

	kinect.addKinectListener(this, &ofApp::kinectPlugged, &ofApp::kinectUnplugged);
	

	ofSetVerticalSync(true);

	kinectSource = &kinect;
	angle = kinect.getCurrentAngle();
	ofSetFrameRate(60);

	videoDraw_ = ofxKinectNuiDrawTexture::createTextureForVideo(kinect.getVideoResolution());
	depthDraw_ = ofxKinectNuiDrawTexture::createTextureForDepth(kinect.getDepthResolution());
	labelDraw_ = ofxKinectNuiDrawTexture::createTextureForLabel(kinect.getDepthResolution());
	skeletonDraw_ = new ofxKinectNuiDrawSkeleton();
	kinect.setVideoDrawer(videoDraw_);
	kinect.setDepthDrawer(depthDraw_);
	kinect.setLabelDrawer(labelDraw_);
	kinect.setSkeletonDrawer(skeletonDraw_);
}

//--------------------------------------------------------------
void ofApp::update() {
	kinectSource->update();

	rightHand2 = rightHand - spine;
	leftHand2 = leftHand - spine;

	sender.setup(HOST, PORT);
	ofxOscMessage m;
	m.addFloatArg(rightHand2.x);
	m.addFloatArg(rightHand2.y);
	m.addFloatArg(rightHand2.z);
	m.addFloatArg(leftHand2.x);
    m.addFloatArg(leftHand2.y);
	m.addFloatArg(leftHand2.z);
	sender.sendMessage(m);
	
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(ofColor::gray);

	// draw video images from kinect camera
	kinect.drawVideo(0, 0, 160*1.5, 120*1.5);
	ofEnableAlphaBlending();
	// draw depth images from kinect depth sensor
	kinect.drawDepth(160*1.5, 0, 160*1.5, 120*1.5);
	// draw players' label images on video images
	kinect.drawLabel(160*1.5, 0, 160*1.5, 120*1.5);
	ofDisableAlphaBlending();
	// draw skeleton images on video images
	kinect.drawSkeleton(160*1.5, 0, 160*1.5, 120*1.5);

	ofPoint* skeletonPoints[ofxKinectNui::SKELETON_COUNT];
	kinect.getSkeletonPoints(skeletonPoints);

	if(kinect.isFoundSkeleton()){
	 for(int i = 0; i < ofxKinectNui::SKELETON_COUNT; i++){
        if(kinect.isTrackedSkeleton(i)){
            for(int j = 0; j < ofxKinectNui::SKELETON_POSITION_COUNT; j++){
                if( j == NUI_SKELETON_POSITION_HAND_RIGHT){
					rightHand = skeletonPoints[i][j];
				}else if( j == NUI_SKELETON_POSITION_HAND_LEFT ){
					leftHand = skeletonPoints[i][j];
				}else if( j == NUI_SKELETON_POSITION_SPINE){
					spine = skeletonPoints[i][j];
				}
            }
        }
	 }
	}

	ofSetColor(255, 255, 255);
	ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 20, 20);
}




//--------------------------------------------------------------
void ofApp::exit() {

	if(videoDraw_) {
		videoDraw_->destroy();
		videoDraw_ = NULL;
	}
	if(depthDraw_) {
		depthDraw_->destroy();
		depthDraw_ = NULL;
	}
	if(labelDraw_) {
		labelDraw_->destroy();
		labelDraw_ = NULL;
	}
	if(skeletonDraw_) {
		delete skeletonDraw_;
		skeletonDraw_ = NULL;
	}
	kinect.setAngle(0);
	kinect.close();
	kinect.removeKinectListener(this);




}

//--------------------------------------------------------------
void ofApp::keyPressed (int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void ofApp::kinectPlugged(){

}

//--------------------------------------------------------------
void ofApp::kinectUnplugged(){

}
