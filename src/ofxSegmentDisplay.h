#pragma once

#include "ofVec2f.h"
#include "ofColor.h"
#include "ofPath.h"

namespace ofxSegmentDisplay {

class Unit
{
public:
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
		ofVec2f relative_pos;
		ofVec2f size;
	};
public:
	Unit();
	Style& getStyleRef() { return style_; }
	DotStyle& getDotStyleRef() { return dot_style_; }
	void draw(char ch, bool with_dot=false);
	void draw(char ch, const ofColor& color, bool with_dot=false);
	void draw(char ch, const ofColor& color, const ofColor& blank_color, bool with_dot=false);
private:
	Style style_;
	DotStyle dot_style_;
	
	static const int SEGMENT_NUM_MAX = 16;
	ofPath path_[SEGMENT_NUM_MAX];
	
private:
	void drawDigit(unsigned int bit_flags);
	void drawDigit(unsigned int bit_flags, const ofColor& color);
	void refresh();
	unsigned int getBitFlags(char ch, bool with_dot);
	bool hasDot(char ch);
};

class UnitArray
{
public:
	enum Align {
		LEFT,
		RIGHT
	};

public:
	void setUnitInterval(float interval) { unit_interval_=interval; }
	void setAlign(Align align) { align_=align; }
	void setCombineDot(bool is_combine_dot) { is_combine_dot_=is_combine_dot; }

	Unit::Style& getUnitStyleRef() { return unit_.getStyleRef(); }
	Unit::DotStyle& getUnitDotStyleRef() { return unit_.getDotStyleRef(); }
	
	void draw(const string& str);
	void draw(const string& str, const ofColor& color);
	void draw(const string& str, const ofColor& color, const ofColor& blank_color);
	void draw(float number, int decimal_digit);
	void draw(float number, const ofColor& color, int decimal_digit);
	void draw(float number, const ofColor& color, const ofColor& blank_color, int decimal_digit);
	
private:
	Unit unit_;
	float unit_interval_;
	Align align_;
	bool is_combine_dot_;
};
}
/* EOF */