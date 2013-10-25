#include "ofxSegmentDisplay.h"

namespace ofxSegmentDisplay
{
template<>
int Unit::usedSegmentNumByType<Unit::_14>()
{
	return 14;
}
template<>
void Unit::refreshByType<Unit::_14>()
{
	float char_width = style_.width-style_.padding.x*2;
	float char_height = style_.height-style_.padding.y*2;
	float skew_ratio = style_.skew/char_height;
	float seg_width_half = style_.segment_width/2.f;
	float h_segment_length_long = char_width-style_.segment_margin*2;
	float h_segment_length_short = char_width/2.f-style_.segment_margin*2;
	float v_segment_length = char_height/2.f-style_.segment_margin*2;
	{
		// horizontal long
		ofPath& path = path_[3];
		path.clear();
		path.moveTo(skew(0, 0, skew_ratio));
		path.lineTo(skew(seg_width_half, -seg_width_half, skew_ratio));
		path.lineTo(skew(h_segment_length_long-seg_width_half, -seg_width_half, skew_ratio));
		path.lineTo(skew(h_segment_length_long, 0, skew_ratio));
		path.lineTo(skew(h_segment_length_long-seg_width_half, seg_width_half, skew_ratio));
		path.lineTo(skew(seg_width_half, seg_width_half, skew_ratio));
		path.close();
		path.translate(ofVec2f(style_.padding.x, style_.height-style_.padding.y));
		copyPath(path_[0], path);
		path_[0].translate(skew(style_.segment_margin, -char_height, skew_ratio));
		path_[3].translate(skew(style_.segment_margin, 0, skew_ratio));
	}
	{
		// horizontal short
		ofPath& path = path_[6];
		path.clear();
		path.moveTo(skew(0, 0, skew_ratio));
		path.lineTo(skew(seg_width_half, -seg_width_half, skew_ratio));
		path.lineTo(skew(h_segment_length_short-seg_width_half, -seg_width_half, skew_ratio));
		path.lineTo(skew(h_segment_length_short, 0, skew_ratio));
		path.lineTo(skew(h_segment_length_short-seg_width_half, seg_width_half, skew_ratio));
		path.lineTo(skew(seg_width_half, seg_width_half, skew_ratio));
		path.close();
		path.translate(ofVec2f(style_.padding.x, style_.height-style_.padding.y));
		copyPath(path_[7], path);
		path_[7].translate(skew(char_width/2.f+style_.segment_margin, -char_height/2.f, skew_ratio));
		path_[6].translate(skew(style_.segment_margin, -char_height/2.f, skew_ratio));
	}
	{
		// vertical side
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
	{
		// vertical above
		ofPath& path = path_[9];
		path.clear();
		path.moveTo(skew(0, 0, skew_ratio));
		path.lineTo(skew(-seg_width_half, -seg_width_half, skew_ratio));
		path.lineTo(skew(-seg_width_half, -v_segment_length+seg_width_half, skew_ratio));
		path.lineTo(skew(seg_width_half, -v_segment_length+seg_width_half, skew_ratio));
		path.lineTo(skew(seg_width_half, -seg_width_half, skew_ratio));
		path.close();
		path.translate(ofVec2f(style_.padding.x, style_.height-style_.padding.y));
		path_[9].translate(skew(char_width/2.f, -char_height/2.f-style_.segment_margin, skew_ratio));
	}
	{
		// vertical below
		ofPath& path = path_[12];
		path.clear();
		path.moveTo(skew(0, 0, skew_ratio));
		path.lineTo(skew(seg_width_half, seg_width_half, skew_ratio));
		path.lineTo(skew(seg_width_half, v_segment_length-seg_width_half, skew_ratio));
		path.lineTo(skew(-seg_width_half, v_segment_length-seg_width_half, skew_ratio));
		path.lineTo(skew(-seg_width_half, seg_width_half, skew_ratio));
		path.close();
		path.translate(ofVec2f(style_.padding.x, style_.height-style_.padding.y));
		path_[12].translate(skew(char_width/2.f, -char_height/2.f+style_.segment_margin, skew_ratio));
	}
	float sqrt2 = sqrt(2);
	float diagonal_segment_w = style_.segment_width/sqrt2;
	float diagonal_length_x = h_segment_length_short - (style_.segment_width);
	float diagonal_length_y = v_segment_length - (style_.segment_width);
	float diagonal_margin = style_.segment_margin+style_.segment_width/2.f;
	{
		// slash
		ofPath& path = path_[13];
		path.clear();
		path.moveTo(skew(0, 0, skew_ratio));
		path.lineTo(skew(0, -diagonal_segment_w, skew_ratio));
		path.lineTo(skew(diagonal_length_x-diagonal_segment_w, -diagonal_length_y, skew_ratio));
		path.lineTo(skew(diagonal_length_x, -diagonal_length_y, skew_ratio));
		path.lineTo(skew(diagonal_length_x, -diagonal_length_y+diagonal_segment_w, skew_ratio));
		path.lineTo(skew(diagonal_segment_w, 0, skew_ratio));
		path.translate(ofVec2f(style_.padding.x, style_.height-style_.padding.y));
		path.close();
		copyPath(path_[10], path);
		path_[10].translate(skew(char_width/2.f+diagonal_margin, -char_height/2.f-diagonal_margin, skew_ratio));
		path_[13].translate(skew(diagonal_margin, -diagonal_margin, skew_ratio));
	}
	{
		// backslash
		ofPath& path = path_[8];
		path.clear();
		path.moveTo(skew(0, 0, skew_ratio));
		path.lineTo(skew(diagonal_segment_w, 0, skew_ratio));
		path.lineTo(skew(diagonal_length_x, diagonal_length_y-diagonal_segment_w, skew_ratio));
		path.lineTo(skew(diagonal_length_x, diagonal_length_y, skew_ratio));
		path.lineTo(skew(diagonal_length_x-diagonal_segment_w, diagonal_length_y, skew_ratio));
		path.lineTo(skew(0, diagonal_segment_w, skew_ratio));
		path.close();
		path.translate(ofVec2f(style_.padding.x, style_.height-style_.padding.y));
		copyPath(path_[11], path);
		path_[11].translate(skew(char_width/2.f+diagonal_margin, -char_height/2.f+diagonal_margin, skew_ratio));
		path_[8].translate(skew(diagonal_margin, -char_height+diagonal_margin, skew_ratio));
	}
}

template<>
bool Unit::hasDotByType<Unit::_14>(char ch)
{
	switch(ch) {
		case '!':
		case '.':
			return true;
	}
	return false;
}

template<>
unsigned int Unit::getBitFlagsByType<Unit::_14>(char ch, bool with_dot)
{
	unsigned int dot_bit = (with_dot||hasDot(ch))?DOT_BIT:0;
	return 0b0011111111111111|dot_bit;
}

}
/* EOF */