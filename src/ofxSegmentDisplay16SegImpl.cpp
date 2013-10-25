#include "ofxSegmentDisplay.h"

namespace ofxSegmentDisplay
{
template<>
int Unit::usedSegmentNumByType<Unit::_16>()
{
	return 16;
}
template<>
void Unit::refreshByType<Unit::_16>()
{
	float char_width = style_.width-style_.padding.x*2;
	float char_height = style_.height-style_.padding.y*2;
	float skew_ratio = style_.skew/char_height;
	float seg_width_half = style_.segment_width/2.f;
	float h_segment_length = char_width/2.f-style_.segment_margin*2;
	float v_segment_length = char_height/2.f-style_.segment_margin*2;
	{
		// horizontal
		ofPath& path = path_[5];
		path.clear();
		path.moveTo(skew(0, 0, skew_ratio));
		path.lineTo(skew(seg_width_half, -seg_width_half, skew_ratio));
		path.lineTo(skew(h_segment_length-seg_width_half, -seg_width_half, skew_ratio));
		path.lineTo(skew(h_segment_length, 0, skew_ratio));
		path.lineTo(skew(h_segment_length-seg_width_half, seg_width_half, skew_ratio));
		path.lineTo(skew(seg_width_half, seg_width_half, skew_ratio));
		path.close();
		path.translate(ofVec2f(style_.padding.x, style_.height-style_.padding.y));
		copyPath(path_[4], path);
		copyPath(path_[0], path);
		copyPath(path_[1], path);
		copyPath(path_[8], path);
		copyPath(path_[9], path);
		path_[4].translate(skew(char_width/2.f+style_.segment_margin, 0, skew_ratio));
		path_[0].translate(skew(style_.segment_margin, -char_height, skew_ratio));
		path_[1].translate(skew(char_width/2.f+style_.segment_margin, -char_height, skew_ratio));
		path_[8].translate(skew(style_.segment_margin, -char_height/2.f, skew_ratio));
		path_[9].translate(skew(char_width/2.f+style_.segment_margin, -char_height/2.f, skew_ratio));
		path_[5].translate(skew(style_.segment_margin, 0, skew_ratio));
	}
	{
		// vertical
		ofPath& path = path_[6];
		path.clear();
		path.moveTo(skew(0, 0, skew_ratio));
		path.lineTo(skew(-seg_width_half, -seg_width_half, skew_ratio));
		path.lineTo(skew(-seg_width_half, -v_segment_length+seg_width_half, skew_ratio));
		path.lineTo(skew(0, -v_segment_length, skew_ratio));
		path.lineTo(skew(seg_width_half, -v_segment_length+seg_width_half, skew_ratio));
		path.lineTo(skew(seg_width_half, -seg_width_half, skew_ratio));
		path.close();
		path.translate(ofVec2f(style_.padding.x, style_.height-style_.padding.y));
		copyPath(path_[7], path);
		copyPath(path_[3], path);
		copyPath(path_[2], path);
		copyPath(path_[11], path);
		copyPath(path_[14], path);
		path_[7].translate(skew(0, -char_height/2.f-style_.segment_margin, skew_ratio));
		path_[3].translate(skew(char_width, -style_.segment_margin, skew_ratio));
		path_[2].translate(skew(char_width, -char_height/2.f-style_.segment_margin, skew_ratio));
		path_[11].translate(skew(char_width/2.f, -style_.segment_margin, skew_ratio));
		path_[14].translate(skew(char_width/2.f, -char_height/2.f-style_.segment_margin, skew_ratio));
		path_[6].translate(skew(0, -style_.segment_margin, skew_ratio));
	}
	float sqrt2 = sqrt(2);
	float diagonal_segment_w = style_.segment_width/sqrt2;
	float diagonal_length_x = h_segment_length - (style_.segment_width);
	float diagonal_length_y = v_segment_length - (style_.segment_width);
	float diagonal_margin = style_.segment_margin+style_.segment_width/2.f;
	{
		// slash
		ofPath& path = path_[15];
		path.clear();
		path.moveTo(skew(0, 0, skew_ratio));
		path.lineTo(skew(0, -diagonal_segment_w, skew_ratio));
		path.lineTo(skew(diagonal_length_x-diagonal_segment_w, -diagonal_length_y, skew_ratio));
		path.lineTo(skew(diagonal_length_x, -diagonal_length_y, skew_ratio));
		path.lineTo(skew(diagonal_length_x, -diagonal_length_y+diagonal_segment_w, skew_ratio));
		path.lineTo(skew(diagonal_segment_w, 0, skew_ratio));
		path.translate(ofVec2f(style_.padding.x, style_.height-style_.padding.y));
		path.close();
		copyPath(path_[12], path);
		path_[12].translate(skew(char_width/2.f+diagonal_margin, -char_height/2.f-diagonal_margin, skew_ratio));
		path_[15].translate(skew(diagonal_margin, -diagonal_margin, skew_ratio));
	}
	{
		// backslash
		ofPath& path = path_[10];
		path.clear();
		path.moveTo(skew(0, 0, skew_ratio));
		path.lineTo(skew(diagonal_segment_w, 0, skew_ratio));
		path.lineTo(skew(diagonal_length_x, diagonal_length_y-diagonal_segment_w, skew_ratio));
		path.lineTo(skew(diagonal_length_x, diagonal_length_y, skew_ratio));
		path.lineTo(skew(diagonal_length_x-diagonal_segment_w, diagonal_length_y, skew_ratio));
		path.lineTo(skew(0, diagonal_segment_w, skew_ratio));
		path.close();
		path.translate(ofVec2f(style_.padding.x, style_.height-style_.padding.y));
		copyPath(path_[13], path);
		path_[13].translate(skew(char_width/2.f+diagonal_margin, -char_height/2.f+diagonal_margin, skew_ratio));
		path_[10].translate(skew(diagonal_margin, -char_height+diagonal_margin, skew_ratio));
	}
}

template<>
bool Unit::hasDotByType<Unit::_16>(char ch)
{
	switch(ch) {
		case '!':
		case '.':
			return true;
	}
	return false;
}

template<>
unsigned int Unit::getBitFlagsByType<Unit::_16>(char ch, bool with_dot)
{
	unsigned int dot_bit = (with_dot||hasDot(ch))?DOT_BIT:0;
	return 0b1111111111111111|dot_bit;
}

}
/* EOF */