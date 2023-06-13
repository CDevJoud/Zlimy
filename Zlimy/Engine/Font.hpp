#pragma once
#define FONTSIZE 32156
#include <SFML/Graphics/Font.hpp>

#ifdef _DEBUG
	extern sf::Font sysDefaultFont;
	void InitFont();
#else
	extern sf::Font sysDefaultFont;
	void InitFont();
#endif


#ifdef _DEBUG
	extern unsigned char fontData[];
#endif