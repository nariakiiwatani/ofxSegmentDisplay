#include "testApp.h"

namespace {
	float unit_interval_;
	ofxSegmentDisplay::UnitArray::Align align_;
	ofVec2f pos_;
	float number_;
	ofColor color_;
	ofColor blank_color_;
}
//--------------------------------------------------------------
void testApp::setup(){
	ofxSegmentDisplay::Unit::Style& style = display_.getUnitStyleRef();
	ofxSegmentDisplay::Unit::DotStyle& dot_style = display_.getUnitDotStyleRef();

	param_.setup("setting");
	param_.addSlider("interval", unit_interval_, 0.f, 400.f);
	param_.addVecSlider("pos", pos_, ofVec2f(0,0), ofVec2f(1024,768));
	param_.addColorSlider("color", color_, ofColor(0,0,0,0), ofColor(255,255,255,255));
	param_.addColorSlider("blank color", blank_color_, ofColor(0,0,0,0), ofColor(255,255,255,255));
	param_.addSlider("number", number_, -90.f, 90.f);
	param_.beginGroup("style");
	param_.addToggle("refresh", style.updated);
	param_.addSlider("align", (int&)align_, 0, 1);
	param_.addSlider("type", (int&)style.type, 0, 2);
	param_.addSlider("width", style.width, 0.f, 200.f);
	param_.addSlider("height", style.height, 0.f, 400.f);
	param_.addVecSlider("padding", style.padding, ofVec2f(0,0), ofVec2f(100,100));
	param_.addSlider("skew", style.skew, 0.f, 200.f);
	param_.addSlider("segment margin", style.segment_margin, 0.f, 20.f);
	param_.addSlider("segment width", style.segment_width, 0.f, 100.f);
	param_.beginGroup("dot");
	param_.addSlider("shape", (int&)dot_style.shape, 0, 1);
	param_.addVecSlider("pos", dot_style.relative_pos, ofVec2f(-50,-50), ofVec2f(50,50));
	param_.addVecSlider("size", dot_style.size, ofVec2f(0,0), ofVec2f(20,20));
	param_.endGroup();
	param_.endGroup();
	param_.load();
	style.updated = true;
}

//--------------------------------------------------------------
void testApp::update(){
	display_.setUnitInterval(unit_interval_);
	display_.setAlign(align_);
}

//--------------------------------------------------------------
void testApp::draw(){
	ofPushMatrix();
	ofTranslate(pos_);
	if(blank_color_.a > 0) {
		display_.draw(number_, color_, blank_color_, 2);
	}
	else {
		display_.draw(number_, color_, 2);
	}
	ofPopMatrix();
	param_.draw();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
