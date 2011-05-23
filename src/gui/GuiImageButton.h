#ifndef _GUIIMAGEBUTTON_H
#define _GUIIMAGEBUTTON_H

#include "GuiWidget.h"
#include "GuiButton.h"
		
#include <string>

namespace Gui {
	class ImageButton: public Button {
	public:
		ImageButton(const std::string &img_normal);
		ImageButton(const std::string &img_normal, const std::string &img_pressed);
		virtual void Draw();
		virtual ~ImageButton();
		virtual void GetSizeRequested(float size[2]);
	private:
		void LoadImages(const std::string *img_normal, const std::string *img_pressed);
		Image *m_imgNormal;
		Image *m_imgPressed;
	};
}

#endif /* _GUIIMAGEBUTTON_H */
