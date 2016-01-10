#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

typedef struct
{
	int X, Y;
} Vector2;

enum COLORS
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHT_GREY = 7,
	DARK_GREY = 8,
	LIGHT_BLUE = 9,
	LIGHT_GREEN = 10,
	LIGHT_CYAN = 11,
	LIGHT_RED = 12,
	LIGHT_MAGENTA = 13,
	LIGHT_BROWN = 14,
	WHITE = 15
};

class Color
{
	unsigned char foreground, background;

public:
	Color() {};
	Color(int fore, int back)
	{
		setForeground((unsigned char) fore);
		setBackground((unsigned char) back);
	}

	Color(COLORS fore, COLORS back)
	{
		setForeground((unsigned char) fore);
		setBackground((unsigned char) back);
	}

	void setColor(COLORS fore, COLORS back)
	{
		setForeground((unsigned char) fore);
		setBackground((unsigned char) back);
	}

	void setColor(int fore, int back)
	{
		setForeground((unsigned char) fore);
		setBackground((unsigned char) back);
	}

	void setForeground(unsigned char fore)
	{
		foreground = fore;
	}

	void setBackground(unsigned char back)
	{
		background = back;
	}

	unsigned char getForeground()
	{
		return foreground;
	}

	unsigned char getBackground()
	{
		return background;
	}
};

class Framebuffer
{
	uint8_t* videoMem;
	uint8_t  attribute;
	int x;
	int y;
	bool isHex;

	Color current_color;

	void putNumber(int x, int base);
	void updateCursor();
	void scroll();

	const char* parseGraphicsSequence(const char* str);
	const char* parseEscape(const char* str);

public:
	Framebuffer();

	void clear();
	void putch(char s);
	void setHex(bool neu);
	void setColors(Color farbe);
	void setCursor(int _x, int _y);
	void setCursor(Vector2 n);
	Vector2 getCursor();

	Framebuffer& operator << (const char* s);
	Framebuffer& operator << (int z);
	Framebuffer& operator << (uint32_t z);
	Framebuffer& operator << (Color f);

};

#endif
