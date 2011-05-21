#include "FontManager.h"
#include "TextureFont.h"
#include "VectorFont.h"
#include "GuiScreen.h"

FontManager::FontManager()
{
	FT_Error err = FT_Init_FreeType(&m_library);
	if (err != 0) {
		fprintf(stderr, "Couldn't create FreeType library context (%d)\n", err);
		abort();
	}
}

FontManager::~FontManager()
{
	FT_Done_FreeType(m_library);
}

TextureFont *FontManager::GetTextureFont(const std::string &name)
{
	std::map<std::string, TextureFont*>::iterator i = m_textureFonts.find(name);
	if (i != m_textureFonts.end())
		return (*i).second;

	// try user dir then data dir
	TextureFont *font = new TextureFont(*this, GetPiUserDir() + name + ".ini");
	if (!font->IsValid()) {
		delete font;
		font = new TextureFont(*this, PIONEER_DATA_DIR "/fonts/" + name + ".ini");
	}
	if (!font->IsValid()) {
		fprintf(stderr, "Failed to load anything for texture font \"%s\"\n - aborting", name.c_str());
		abort();
	}

	m_textureFonts.insert( std::make_pair(name, font) );

	return font;
}

VectorFont *FontManager::GetVectorFont(const std::string &name)
{
	std::map<std::string, VectorFont*>::iterator i = m_vectorFonts.find(name);
	if (i != m_vectorFonts.end())
		return (*i).second;

	// try user dir, data dir then absolute
	VectorFont *font = new VectorFont(*this, GetPiUserDir() + name + ".ini");
	if (!font->IsValid()) {
		delete font;
		font = new VectorFont(*this, PIONEER_DATA_DIR "/fonts/" + name + ".ini");
	}
	if (!font->IsValid()) {
		delete font;
		font = new VectorFont(*this, name + ".ini"); // assume absolute path
	}
	if (!font->IsValid()) {
		fprintf(stderr, "Failed to load anything for vector font \"%s\"\n - aborting", name.c_str());
		abort();
	}
	m_vectorFonts.insert( std::make_pair(name, font) );

	return font;
}
