#include "Font.h"

#include <iostream>

int Font::LoadFontFile(const std::string &name)
{
	int err;
	FT_Library lib = m_fontManager.GetFreeTypeLibrary();

	if (!(err = FT_New_Face(lib, (GetPiUserDir() + name).c_str(), 0, &m_face))) return 0;
	if (!(err = FT_New_Face(lib, (PIONEER_DATA_DIR "/fonts/" + name).c_str(), 0, &m_face))) return 0;
	if (!(err = FT_New_Face(lib, name.c_str(), 0, &m_face))) return 0;

	return err;
}