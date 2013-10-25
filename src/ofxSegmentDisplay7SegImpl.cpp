#include "ofxSegmentDisplay.h"

namespace ofxSegmentDisplay
{
template<>
int Unit::usedSegmentNumByType<Unit::_7>()
{
	return 7;
}
template<>
void Unit::refreshByType<Unit::_7>()
{
	float char_width = style_.width-style_.padding.x*2;
	float char_height = style_.height-style_.padding.y*2;
	float skew_ratio = style_.skew/char_height;
	float seg_width_half = style_.segment_width/2.f;
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
		path.close();
		path.translate(ofVec2f(style_.padding.x, style_.height-style_.padding.y));
		copyPath(path_[0], path);
		copyPath(path_[6], path);
		path_[0].translate(skew(style_.segment_margin, -char_height, skew_ratio));
		path_[6].translate(skew(style_.segment_margin, -char_height/2.f, skew_ratio));
		path_[3].translate(skew(style_.segment_margin, 0, skew_ratio));
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
		path.close();
		path.translate(ofVec2f(style_.padding.x, style_.height-style_.padding.y));
		copyPath(path_[5], path);
		copyPath(path_[2], path);
		copyPath(path_[1], path);
		path_[5].translate(skew(0, -char_height/2.f-style_.segment_margin, skew_ratio));
		path_[2].translate(skew(char_width, -style_.segment_margin, skew_ratio));
		path_[1].translate(skew(char_width, -char_height/2.f-style_.segment_margin, skew_ratio));
		path_[4].translate(skew(0, -style_.segment_margin, skew_ratio));
	}
}

template<>
bool Unit::hasDotByType<Unit::_7>(char ch)
{
	switch(ch) {
		case '!':
		case '.':
			return true;
	}
	return false;
}

template<>
unsigned int Unit::getBitFlagsByType<Unit::_7>(char ch, bool with_dot)
{
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
	}
	return 0b00000000|dot_bit;
}

}
/* EOF */