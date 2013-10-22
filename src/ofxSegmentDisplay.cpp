#include "ofxSegmentDisplay.h"
#include "ofGraphics.h"

namespace ofxSegmentDisplay {
namespace {
	unsigned int DOT_BIT = 0x80000000;
}
void copyPath(ofPath& dst, const ofPath& src)
{
	dst.getCommands() = src.getCommands();
}
ofVec2f skew(float x, float y, float skew_ratio)
{
	return ofVec2f(x-y*skew_ratio, y);
}
Unit::Unit()
{
	for(int i = 0; i < SEGMENT_NUM_MAX; ++i) {
		path_[i].setUseShapeColor(false);
	}
}
void Unit::refresh()
{
	float char_width = style_.width-style_.padding.x*2;
	float char_height = style_.height-style_.padding.y*2;
	float skew_ratio = style_.skew/char_height;
	float seg_width_half = style_.segment_width/2.f;
	switch(style_.type) {
		case _7: {
			float h_segment_length = char_width-style_.segment_margin*2;
			float v_segment_length = char_height/2.f-style_.segment_margin*2;
			{
				// horizontal
				ofPath& path = path_[3];
				path.clear();
				path.moveTo(skew(0, 0, skew_ratio));
				path.lineTo(skew(seg_width_half, -seg_width_half, skew_ratio));
				path.lineTo(skew(h_segment_length-seg_width_half, -seg_width_half, skew_ratio));
				path.lineTo(skew(h_segment_length, 0, skew_ratio));
				path.lineTo(skew(h_segment_length-seg_width_half, seg_width_half, skew_ratio));
				path.lineTo(skew(seg_width_half, seg_width_half, skew_ratio));
				path.lineTo(skew(0, 0, skew_ratio));
				path.close();
				path.translate(ofVec2f(style_.padding.x+style_.segment_margin, char_height-style_.padding.y));
				copyPath(path_[0], path);
				path_[0].translate(skew(0, -char_height, skew_ratio));
				copyPath(path_[6], path);
				path_[6].translate(skew(0, -char_height/2.f, skew_ratio));
			}
			{
				// vertical
				ofPath& path = path_[4];
				path.clear();
				path.moveTo(skew(0, 0, skew_ratio));
				path.lineTo(skew(-seg_width_half, -seg_width_half, skew_ratio));
				path.lineTo(skew(-seg_width_half, -v_segment_length+seg_width_half, skew_ratio));
				path.lineTo(skew(0, -v_segment_length, skew_ratio));
				path.lineTo(skew(seg_width_half, -v_segment_length+seg_width_half, skew_ratio));
				path.lineTo(skew(seg_width_half, -seg_width_half, skew_ratio));
				path.lineTo(skew(0, 0, skew_ratio));
				path.close();
				path.translate(ofVec2f(style_.padding.x, char_height-style_.padding.y-style_.segment_margin));
				copyPath(path_[5], path);
				path_[5].translate(skew(0, -char_height/2.f, skew_ratio));
				copyPath(path_[2], path);
				path_[2].translate(skew(char_width, 0, skew_ratio));
				copyPath(path_[1], path);
				path_[1].translate(skew(char_width, -char_height/2.f, skew_ratio));
			}
		}	break;
		case _14:
			break;
		case _16:
			break;
	}
	style_.updated = false;
}
void Unit::drawDigit(unsigned int bit_flags)
{
	int segment_num = 0;
	switch(style_.type) {
		case _7:
			segment_num = 7;
			break;
		case _14:
			segment_num = 14;
			break;
		case _16:
			segment_num = 16;
			break;
	}
	for(int i = 0; i < segment_num; ++i) {
		if((bit_flags&(1<<i))!=0) {
			path_[i].draw();
		}
	}
	if((bit_flags&DOT_BIT)!=0) {
		ofVec2f pos = ofVec2f(style_.width-style_.padding.x, style_.height-style_.padding.y) + dot_style_.relative_pos;
		switch(dot_style_.shape) {
			case DotStyle::ELLIPSE:
				ofEllipse(pos, dot_style_.size.x, dot_style_.size.y);
				break;
			case DotStyle::RECT:
				ofRect(pos-dot_style_.size/2.f, dot_style_.size.x, dot_style_.size.y);
				break;
		}
	}
	return 0;
}
unsigned int Unit::getBitFlags(char ch, bool with_dot)
{
	switch(style_.type) {
		case _7: {
			unsigned int dot_bit = with_dot?DOT_BIT:0;
			switch(ch) {
				case '0': return 0b00111111|dot_bit;
				case '1': return 0b00000110|dot_bit;
				case '2': return 0b01011011|dot_bit;
				case '3': return 0b01001111|dot_bit;
				case '4': return 0b01100110|dot_bit;
				case '5': return 0b01101101|dot_bit;
				case '6': return 0b01111101|dot_bit;
				case '7': return 0b00000111|dot_bit;
				case '8': return 0b01111111|dot_bit;
				case '9': return 0b01101111|dot_bit;
				case '-': return 0b01000000|dot_bit;
				case '.': return DOT_BIT;
					
				default:
					return 0b00000000|dot_bit;
					break;
			}
		}	break;
		case _14:
			break;
		case _16:
			break;
	}
	return 0;
}

void Unit::draw(char ch, bool with_dot)
{
	if(style_.updated) {
		refresh();
	}
	drawDigit(getBitFlags(ch, with_dot));
}
void Unit::draw(char ch, const ofColor& color, bool with_dot)
{
	ofPushStyle();
	ofSetColor(color);
	draw(ch, with_dot);
	ofPopStyle();
}
void Unit::draw(char ch, const ofColor& color, const ofColor& blank_color, bool with_dot)
{
	if(style_.updated) {
		refresh();
	}
	ofPushStyle();
	unsigned int bit_flags = getBitFlags(ch, with_dot);
	ofSetColor(blank_color);
	drawDigit(~bit_flags);
	ofSetColor(color);
	drawDigit(bit_flags);
	ofPopStyle();
}

void UnitArray::draw(const string& str)
{
	ofPushMatrix();
	if(align_ == LEFT) { 
		for(string::const_iterator ch = str.begin(); ch != str.end(); ++ch) {
			bool with_dot = (*ch != '.' && (ch+1) != str.end() && *(ch+1) == '.');
			unit_.draw((*ch), with_dot);
			if(with_dot) {
				++ch;
			}
			ofTranslate(unit_interval_, 0);
		}
	}
	else if(align_ == RIGHT) {
		bool is_prev_dot = false;
		ofTranslate(-unit_interval_, 0);
		for(string::const_reverse_iterator ch = str.rbegin(); ch != str.rend(); ++ch) {
			bool is_dot = (*ch == '.');
			if(!is_prev_dot && is_dot && (ch+1) != str.rend()) {
				is_prev_dot = true;
				continue;
			}
			bool with_dot = is_prev_dot && !is_dot;
			unit_.draw((*ch), with_dot);
			ofTranslate(-unit_interval_, 0);
			is_prev_dot = is_dot;
			if(is_dot && (ch+1) == str.rend()) {
				unit_.draw('.', false);
			}
		}
	}
	ofPopMatrix();
}
void UnitArray::draw(const string& str, const ofColor& color)
{
	ofPushStyle();
	ofSetColor(color);
	draw(str);
	ofPopStyle();
}
void UnitArray::draw(const string& str, const ofColor& color, const ofColor& blank_color)
{
	ofPushMatrix();
	if(align_ == LEFT) { 
		for(string::const_iterator ch = str.begin(); ch != str.end(); ++ch) {
			bool with_dot = (*ch != '.' && (ch+1) != str.end() && *(ch+1) == '.');
			unit_.draw((*ch), color, blank_color, with_dot);
			if(with_dot) {
				++ch;
			}
			ofTranslate(unit_interval_, 0);
		}
	}
	else if(align_ == RIGHT) { 
		bool is_prev_dot = false;
		ofTranslate(-unit_interval_, 0);
		for(string::const_reverse_iterator ch = str.rbegin(); ch != str.rend(); ++ch) {
			bool is_dot = (*ch == '.');
			if(!is_prev_dot && is_dot && (ch+1) != str.rend()) {
				is_prev_dot = true;
				continue;
			}
			bool with_dot = is_prev_dot && !is_dot;
			unit_.draw((*ch), color, blank_color, with_dot);
			ofTranslate(-unit_interval_, 0);
			is_prev_dot = is_dot;
			if(is_dot && (ch+1) == str.rend()) {
				unit_.draw('.', color, blank_color, false);
			}
		}
	}
	ofPopMatrix();
}

void UnitArray::draw(float number, int decimal_digit)
{
	draw(ofToString(number, decimal_digit));
}
void UnitArray::draw(float number, const ofColor& color, int decimal_digit)
{
	ofPushStyle();
	ofSetColor(color);
	draw(ofToString(number, decimal_digit));
	ofPopStyle();
}
void UnitArray::draw(float number, const ofColor& color, const ofColor& blank_color, int decimal_digit)
{
	draw(ofToString(number, decimal_digit), color, blank_color);
}

}
/* EOF */