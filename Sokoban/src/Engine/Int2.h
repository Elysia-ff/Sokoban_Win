#pragma once

struct Int2
{
	int x;
	int y;

	Int2()
		: x(0)
		, y(0)
	{
	}

	Int2(int _x, int _y)
		: x(_x)
		, y(_y)
	{
	}
};

inline bool operator==(Int2 a, Int2 b)
{
	return a.x == b.x && a.y == b.y;
}

inline bool operator!=(Int2 a, Int2 b)
{
	return !operator==(a, b);
}

inline Int2 operator+(Int2 a, Int2 b)
{
	return Int2(a.x + b.x, a.y + b.y);
}

inline Int2 operator-(Int2 a, Int2 b)
{
	return Int2(a.x - b.x, a.y - b.y);
}

inline Int2 operator/(Int2 a, int n)
{
	return Int2(a.x / n, a.y / n);
}
