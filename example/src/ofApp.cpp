#include "ofApp.h"

namespace {
	float unit_interval_;
	ofxSegmentDisplay::UnitArray::Align align_;
	ofVec2f pos_;
	float number_;
	ofColor color_;
	ofColor blank_color_;
	bool is_combine_dot = true;
	bool all_char = true;
}
//--------------------------------------------------------------
void ofApp::setup(){
	ofxSegmentDisplay::Unit::Style& style = display_.getUnitStyleRef();
	ofxSegmentDisplay::Unit::DotStyle& dot_style = display_.getUnitDotStyleRef();

	param_.setup("setting");
	param_.addSlider("interval", unit_interval_, 0.f, 400.f);
	param_.addVecSlider("pos", pos_, ofVec2f(0,0), ofVec2f(1024,768));
	param_.addColorSlider("color", color_, ofColor(0,0,0,0), ofColor(255,255,255,255));
	param_.addColorSlider("blank color", blank_color_, ofColor(0,0,0,0), ofColor(255,255,255,255));
	param_.addToggle("all char", all_char);
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
	param_.addToggle("combine", is_combine_dot);
	param_.addSlider("shape", (int&)dot_style.shape, 0, 1);
	param_.addVecSlider("pos", dot_style.relative_pos, ofVec2f(-50,-50), ofVec2f(50,50));
	param_.addVecSlider("size", dot_style.size, ofVec2f(0,0), ofVec2f(20,20));
	param_.endGroup();
	param_.endGroup();
	param_.load();
	style.updated = true;
	
	ofLogNotice("start");
	for(unsigned int ch = 0; ch < 256; ++ch) {
		printf("%s", ofToString((unsigned char)ch).c_str());
	}
	ofLogNotice("end");
}

//--------------------------------------------------------------
void ofApp::update(){
	display_.setUnitInterval(unit_interval_);
	display_.setAlign(align_);
	display_.setCombineDot(is_combine_dot);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	float line_height = display_.getUnitStyleRef().height;
	ofPushMatrix();
	ofTranslate(pos_);

	if(blank_color_.a > 0) {
		if(all_char) {
			display_.draw(" !\"#$%&'()*+,-./", color_, blank_color_);
			ofTranslate(0,line_height);
			display_.draw("0123456789:;<=>?", color_, blank_color_);
			ofTranslate(0,line_height);
			display_.draw("@ABCDEFGHIJKLMNO", color_, blank_color_);
			ofTranslate(0,line_height);
			display_.draw("PQRSTUVWXYZ[\\]^_", color_, blank_color_);
			ofTranslate(0,line_height);
			display_.draw("`abcdefghijklmno", color_, blank_color_);
			ofTranslate(0,line_height);
			display_.draw("pqrstuvwxyz{|}~", color_, blank_color_);
		}
		else {
			display_.draw(number_, color_, blank_color_, 2);
		}
	}
	else {
		if(all_char) {
			display_.draw(" !\"#$%&'()*+,-./", color_);
			ofTranslate(0,line_height);
			display_.draw("0123456789:;<=>?", color_);
			ofTranslate(0,line_height);
			display_.draw("@ABCDEFGHIJKLMNO", color_);
			ofTranslate(0,line_height);
			display_.draw("PQRSTUVWXYZ[\\]^_", color_);
			ofTranslate(0,line_height);
			display_.draw("`abcdefghijklmno", color_);
			ofTranslate(0,line_height);
			display_.draw("pqrstuvwxyz{|}~", color_);
		}
		else {
			display_.draw(number_, color_, 2);
		}
	}
	ofPopMatrix();
	if(param_.isOpen()) {
		param_.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
		case OF_KEY_RETURN:
			param_.isOpen()?param_.close():param_.open();
			break;
	}
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

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
