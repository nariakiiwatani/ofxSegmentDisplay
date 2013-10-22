#include "testApp.h"

namespace {
	float unit_interval_;
	ofVec2f pos_;
	ofxSegmentDisplay::UnitArray::Align align_;
	ofxSegmentDisplay::Unit::Style style_;
	ofxSegmentDisplay::Unit::DotStyle dot_style_;
	float number_;
	ofColor color_;
	ofColor blank_color_;
	bool refresh = true;
	/*
	enum Type {
		_7,
		_14,
		_16,
	};
	struct Style {
		Type type;
		float width;
		float height;
		ofVec2f padding;
		float skew;
		float segment_margin;
		float segment_width;
		
		bool updated;
	};
	struct DotStyle {
		enum {
			ELLIPSE,
			RECT
		} shape;
		float w,h;
		ofVec2f relative_pos;
	};
	*/
}
//--------------------------------------------------------------
void testApp::setup(){

	param_.setup("setting");
	param_.addToggle("refresh", refresh);
	param_.addSlider("interval", unit_interval_, 0.f, 400.f);
	param_.addVecSlider("pos", pos_, ofVec2f(0,0), ofVec2f(1024,768));
	param_.addColorSlider("color", color_, ofColor(0,0,0,0), ofColor(255,255,255,255));
	param_.addColorSlider("blank color", blank_color_, ofColor(0,0,0,0), ofColor(255,255,255,255));
	param_.addSlider("number", number_, -90.f, 90.f);
	param_.beginGroup("style");
	param_.addSlider("align", (int&)align_, 0, 1);
	param_.addSlider("type", (int&)style_.type, 0, 2);
	param_.addSlider("width", style_.width, 0.f, 200.f);
	param_.addSlider("height", style_.height, 0.f, 400.f);
	param_.addVecSlider("padding", style_.padding, ofVec2f(0,0), ofVec2f(100,100));
	param_.addSlider("skew", style_.skew, 0.f, 200.f);
	param_.addSlider("segment margin", style_.segment_margin, 0.f, 20.f);
	param_.addSlider("segment width", style_.segment_width, 0.f, 100.f);
	param_.beginGroup("dot");
	param_.addSlider("shape", (int&)dot_style_.shape, 0, 1);
	param_.addVecSlider("pos", dot_style_.relative_pos, ofVec2f(-50,-50), ofVec2f(50,50));
	param_.addVecSlider("size", dot_style_.size, ofVec2f(0,0), ofVec2f(20,20));
	param_.endGroup();
	param_.endGroup();
	param_.load();
	refresh = true;
}

//--------------------------------------------------------------
void testApp::update(){
	if(refresh) {
		display_.getUnitStyleRef() = style_;
		display_.getUnitDotStyleRef() = dot_style_;
		display_.getUnitStyleRef().updated = true;
		refresh = false;
	}
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
