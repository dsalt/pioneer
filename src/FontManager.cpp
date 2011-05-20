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

	// no dot after last slash (or start of string, if no slash) => append ".ttf"
	size_t dot = name.find_last_of('.');
#if defined(_WIN32)
	size_t slash = name.find_last_of("\\/");
#else
	size_t slash = name.find_last_of('/');
#endif
	const char *const suffix = (dot <= slash) ? ".ttf" : "";

	// try user dir, data dir then absolute
	VectorFont *font = new VectorFont(*this, (GetPiUserDir() + name + suffix).c_str());
	if (!font->IsValid()) {
		delete font;
		font = new VectorFont(*this, (PIONEER_DATA_DIR "/fonts/" + name + suffix).c_str());
	}
	if (!font->IsValid()) {
		delete font;
		font = new VectorFont(*this, (name + suffix).c_str()); // assume absolute path
	}
	if (!font->IsValid()) {
		fprintf(stderr, "Failed to load anything for vector font \"%s\"\n - aborting", name.c_str());
		abort();
	}
	m_vectorFonts.insert( std::make_pair(name, font) );

	return font;
}
