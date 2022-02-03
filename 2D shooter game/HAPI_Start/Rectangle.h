#pragma once
class Rectangle
{
public:
	float left, right, top, bottom;

	Rectangle() = default;

	Rectangle(float l, float r, float t, float b) :
		left(l), right(r), top(t), bottom(b) {}

	float Width() const { return right - left; }
	float Height() const { return bottom - top; }

	void Translate(float dx, float dy)
	{
		left += dx;
		right += dx;
		top += dy;
		bottom += dy;
	}

	void ClipTo(const Rectangle& other)
	{
		if (left < other.left)
			left = other.left;
		if (right > other.right)
			right = other.right;
		if (top < other.top)
			top = other.top;
		if (bottom > other.bottom)
			bottom = other.bottom;
	}
};

