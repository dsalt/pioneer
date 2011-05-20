#ifndef _FONT_H
#define _FONT_H

#include "FontManager.h"

class Font
{
public:
	bool IsValid() const { return valid; }

protected:
	Font(FontManager &fm) : m_fontManager(fm), valid(false) {}

	FontManager &GetFontManager() { return m_fontManager; }

	FT_Face m_face;
	bool valid;

private:
	FontManager &m_fontManager;
};

#endif
