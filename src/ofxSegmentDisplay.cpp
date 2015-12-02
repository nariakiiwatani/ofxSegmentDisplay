#include "ofxSegmentDisplay.h"
#include "ofGraphics.h"

namespace ofxSegmentDisplay {
Unit::Unit()
{
	for(int i = 0; i < SEGMENT_NUM_MAX; ++i) {
		path_[i].setUseShapeColor(false);
	}
}
void Unit::refresh()
{
	switch(style_.type) {
		case _7: refreshByType<_7>(); break;
		case _14: refreshByType<_14>(); break;
		case _16: refreshByType<_16>(); break;
	}
	style_.updated = false;
}
void Unit::drawDigit(unsigned int bit_flags)
{
	int segment_num = 0;
	switch(style_.type) {
		case _7: segment_num = usedSegmentNumByType<_7>(); break;
		case _14: segment_num = usedSegmentNumByType<_14>(); break;
		case _16: segment_num = usedSegmentNumByType<_16>(); break;
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
				ofDrawEllipse(pos, dot_style_.size.x, dot_style_.size.y);
				break;
			case DotStyle::RECT:
				ofDrawRectangle(pos-dot_style_.size/2.f, dot_style_.size.x, dot_style_.size.y);
				break;
		}
	}
	return 0;
}

bool Unit::hasDot(char ch)
{
	switch(style_.type) {
		case _7: return hasDotByType<_7>(ch);
		case _14: return hasDotByType<_14>(ch);
		case _16: return hasDotByType<_16>(ch);
	}
	return false;
}

unsigned int Unit::getBitFlags(char ch, bool with_dot)
{
	switch(style_.type) {
		case _7: return getBitFlagsByType<_7>(ch, with_dot);
		case _14: return getBitFlagsByType<_14>(ch, with_dot);
		case _16: return getBitFlagsByType<_16>(ch, with_dot);
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
		if(is_combine_dot_) {
			for(string::const_iterator ch = str.begin(); ch != str.end(); ++ch) {
				bool with_dot = (*ch != '.' && (ch+1) != str.end() && *(ch+1) == '.');
				unit_.draw(*ch, with_dot);
				if(with_dot) {
					++ch;
				}
				ofTranslate(unit_interval_, 0);
			}
		}
		else {
			for(string::const_iterator ch = str.begin(); ch != str.end(); ++ch) {
				unit_.draw(*ch);
				ofTranslate(unit_interval_, 0);
			}
		}
	}
	else if(align_ == RIGHT) {
		if(is_combine_dot_) {
			bool is_prev_dot = false;
			ofTranslate(-unit_interval_, 0);
			for(string::const_reverse_iterator ch = str.rbegin(); ch != str.rend(); ++ch) {
				bool is_dot = (*ch == '.');
				if(!is_prev_dot && is_dot && (ch+1) != str.rend()) {
					is_prev_dot = true;
					continue;
				}
				bool with_dot = is_prev_dot && !is_dot;
				unit_.draw(*ch, with_dot);
				ofTranslate(-unit_interval_, 0);
				is_prev_dot = is_dot;
				if(is_dot && (ch+1) == str.rend()) {
					unit_.draw('.', false);
				}
			}
		}
		else {
			ofTranslate(-unit_interval_, 0);
			for(string::const_reverse_iterator ch = str.rbegin(); ch != str.rend(); ++ch) {
				unit_.draw(*ch);
				ofTranslate(-unit_interval_, 0);
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
		if(is_combine_dot_) {
			for(string::const_iterator ch = str.begin(); ch != str.end(); ++ch) {
				bool with_dot = (*ch != '.' && (ch+1) != str.end() && *(ch+1) == '.');
				unit_.draw(*ch, color, blank_color, with_dot);
				if(with_dot) {
					++ch;
				}
				ofTranslate(unit_interval_, 0);
			}
		}
		else {
			for(string::const_iterator ch = str.begin(); ch != str.end(); ++ch) {
				unit_.draw(*ch, color, blank_color);
				ofTranslate(unit_interval_, 0);
			}
		}
	}
	else if(align_ == RIGHT) {
		if(is_combine_dot_) {
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
		else {
			ofTranslate(-unit_interval_, 0);
			for(string::const_reverse_iterator ch = str.rbegin(); ch != str.rend(); ++ch) {
				unit_.draw(*ch, color, blank_color);
				ofTranslate(-unit_interval_, 0);
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