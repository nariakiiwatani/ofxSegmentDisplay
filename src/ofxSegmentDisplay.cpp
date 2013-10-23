#include "ofxSegmentDisplay.h"
#include "ofGraphics.h"

namespace ofxSegmentDisplay {
namespace {
	unsigned int DOT_BIT = 0x80000000;
}
static void copyPath(ofPath& dst, const ofPath& src)
{
	dst.getCommands() = src.getCommands();
}
static ofVec2f skew(float x, float y, float skew_ratio)
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
				path.translate(ofVec2f(style_.padding.x+style_.segment_margin, style_.height-style_.padding.y));
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
				path.translate(ofVec2f(style_.padding.x, style_.height-style_.padding.y-style_.segment_margin));
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

bool Unit::hasDot(char ch)
{
	switch(style_.type) {
		case _7:
			switch(ch) {
				case '!':
				case '.':
					return true;
			}
			break;
		case _14:
			break;
		case _16:
			break;
	}
	return false;
}

unsigned int Unit::getBitFlags(char ch, bool with_dot)
{
	switch(style_.type) {
		case _7: {
			unsigned int dot_bit = (with_dot||hasDot(ch))?DOT_BIT:0;
			switch(ch) {
				case ' ': return 0b00000000|dot_bit;	// 32
				case '!': return 0b00000010|dot_bit;	// 33
				case '"': return 0b00100010|dot_bit;	// 34
				case '#': return 0b01110110|dot_bit;	// 35
				case '$': return 0b01101101|dot_bit;	// 36
				case '%': return 0b00101101|dot_bit;	// 37
				case '&': return 0b01111011|dot_bit;	// 38
				case '\'':return 0b00100000|dot_bit;	// 39
				case '(': return 0b00111001|dot_bit;	// 40
				case ')': return 0b00001111|dot_bit;	// 41
				case '*': return 0b01100011|dot_bit;	// 42
				case '+': return 0b01110000|dot_bit;	// 43
				case ',': return 0b00000100|dot_bit;	// 44
				case '-': return 0b01000000|dot_bit;	// 45
				case '.': return 0b00000000|DOT_BIT;	// 46
				case '/': return 0b01010010|dot_bit;	// 47
				case '0': return 0b00111111|dot_bit;	// 48
				case '1': return 0b00000110|dot_bit;	// 49
				case '2': return 0b01011011|dot_bit;	// 50
				case '3': return 0b01001111|dot_bit;	// 51
				case '4': return 0b01100110|dot_bit;	// 52
				case '5': return 0b01101101|dot_bit;	// 53
				case '6': return 0b01111101|dot_bit;	// 54
				case '7': return 0b00000111|dot_bit;	// 55
				case '8': return 0b01111111|dot_bit;	// 56
				case '9': return 0b01101111|dot_bit;	// 57
				case ':': return 0b01001000|dot_bit;	// 58
				case ';': return 0b01001100|dot_bit;	// 59
				case '<': return 0b01100001|dot_bit;	// 60
				case '=': return 0b01000001|dot_bit;	// 61
				case '>': return 0b01000011|dot_bit;	// 62
				case '?': return 0b01010011|dot_bit;	// 63
				case '@': return 0b01011111|dot_bit;	// 64
				case 'A': return 0b01110111|dot_bit;	// 65
				case 'B': return 0b01111100|dot_bit;	// 66
				case 'C': return 0b00111001|dot_bit;	// 67
				case 'D': return 0b01011110|dot_bit;	// 68
				case 'E': return 0b01111001|dot_bit;	// 69
				case 'F': return 0b01110001|dot_bit;	// 70
				case 'G': return 0b00111101|dot_bit;	// 71
				case 'H': return 0b01110110|dot_bit;	// 72
				case 'I': return 0b00110000|dot_bit;	// 73
				case 'J': return 0b00011110|dot_bit;	// 74
				case 'K': return 0b01110101|dot_bit;	// 75
				case 'L': return 0b00111000|dot_bit;	// 76
				case 'M': return 0b01010101|dot_bit;	// 77
				case 'N': return 0b00110111|dot_bit;	// 78
				case 'O': return 0b00111111|dot_bit;	// 79
				case 'P': return 0b01110011|dot_bit;	// 80
				case 'Q': return 0b01100111|dot_bit;	// 81
				case 'R': return 0b01010000|dot_bit;	// 82
				case 'S': return 0b01101101|dot_bit;	// 83
				case 'T': return 0b00110001|dot_bit;	// 84
				case 'U': return 0b00111110|dot_bit;	// 85
				case 'V': return 0b00101010|dot_bit;	// 86
				case 'W': return 0b01111110|dot_bit;	// 87
				case 'X': return 0b01110110|dot_bit;	// 88
				case 'Y': return 0b01101110|dot_bit;	// 89
				case 'Z': return 0b00011011|dot_bit;	// 90
				case '[': return 0b00111001|dot_bit;	// 91
				case '\\':return 0b01100100|dot_bit;	// 92
				case ']': return 0b00001111|dot_bit;	// 93
				case '^': return 0b00100011|dot_bit;	// 94
				case '_': return 0b00001000|dot_bit;	// 95
				case '`': return 0b00000011|dot_bit;	// 96
				case 'a': return 0b01011111|dot_bit;	// 97
				case 'b': return 0b01111100|dot_bit;	// 98
				case 'c': return 0b01011000|dot_bit;	// 99
				case 'd': return 0b01011110|dot_bit;	// 100
				case 'e': return 0b01111011|dot_bit;	// 101
				case 'f': return 0b01110001|dot_bit;	// 102
				case 'g': return 0b01101111|dot_bit;	// 103
				case 'h': return 0b01110100|dot_bit;	// 104
				case 'i': return 0b00010000|dot_bit;	// 105
				case 'j': return 0b00001110|dot_bit;	// 106
				case 'k': return 0b01110101|dot_bit;	// 107
				case 'l': return 0b00110000|dot_bit;	// 108
				case 'm': return 0b01010100|dot_bit;	// 109
				case 'n': return 0b01010100|dot_bit;	// 110
				case 'o': return 0b01011100|dot_bit;	// 111
				case 'p': return 0b01110011|dot_bit;	// 112
				case 'q': return 0b01100111|dot_bit;	// 113
				case 'r': return 0b01010000|dot_bit;	// 114
				case 's': return 0b01101101|dot_bit;	// 115
				case 't': return 0b01111000|dot_bit;	// 116
				case 'u': return 0b00011100|dot_bit;	// 117
				case 'v': return 0b00011100|dot_bit;	// 118
				case 'w': return 0b01111110|dot_bit;	// 119
				case 'x': return 0b01110110|dot_bit;	// 120
				case 'y': return 0b01101110|dot_bit;	// 121
				case 'z': return 0b01011011|dot_bit;	// 122
				case '{': return 0b00111001|dot_bit;	// 123
				case '|': return 0b00110000|dot_bit;	// 124
				case '}': return 0b00001111|dot_bit;	// 125
				case '~': return 0b01000000|dot_bit;	// 126
				case '': return 0b01011010|dot_bit;	// 127
					
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