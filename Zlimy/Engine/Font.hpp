////#pragma once
////#define FONTSIZE 32156
////#include <SFML/Graphics/Font.hpp>
////
////#ifdef _DEBUG
////	sf::Font sysDefaultFont;
////	void InitFont();
////#else
////	extern sf::Font sysDefaultFont;
////	extern void InitFont();
////#endif
////
////
////#ifdef _DEBUG
////	extern unsigned char fontData[];
////#endif
//
//#pragma once
//#ifndef FONT_HPP
//#define FONT_HPP
//
//#define FONTSIZE 32156
//#include <SFML/Graphics/Font.hpp>
//
//#ifdef _DEBUG
//extern sf::Font sysDefaultFont;
//void InitFont();
//#else
//extern sf::Font sysDefaultFont;
//#endif
//
//#ifdef _DEBUG
//extern unsigned char fontData[];
//#endif
//
//#endif // !FONT_HPP
#pragma once
#include <SFML/Graphics.hpp>
#define FONTSIZE 32156
namespace IExtreme::Engine::Ugr
{
	class SysDefFont
	{
	public:
		void Clean()
		{
			delete this->font;
			for (int i = 0; i < this->FontData.size(); i++)
				this->FontData.pop_back();
			this->FontData.clear();
			this->FontData.shrink_to_fit();
		}
		void Init()
		{
			this->font = new sf::Font();
			this->font->loadFromMemory(this->FontData.data(), this->FontData.size());
		}
		sf::Font* Get()
		{
			return this->font;
		}
	private:

		sf::Font* font = nullptr;
		//static unsigned char FontData[FONTSIZE];
		std::vector<unsigned char> FontData;
	};
}