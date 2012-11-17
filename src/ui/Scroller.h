// Copyright © 2008-2012 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef UI_SCROLLER_H
#define UI_SCROLLER_H

#include "Container.h"

namespace UI {

class HBox;
class VSlider;

class Scroller : public Container {
public:
	virtual Point PreferredSize();
	virtual void Layout();

	Scroller *SetInnerWidget(Widget *widget);
	void RemoveInnerWidget();
	Widget *GetInnerWidget() const { return m_innerWidget; }

	float GetScrollPosition() const;
	void SetScrollPosition(float v);

protected:
	friend class Context;
	Scroller(Context *context) : Container(context), m_innerWidget(0), m_slider(0) {}

	virtual void RemoveWidget(Widget *widget);

private:
	Widget *m_innerWidget;
	VSlider *m_slider;

	sigc::connection m_onMouseWheelConn;

	void OnScroll(float value);
	bool OnMouseWheel(const MouseWheelEvent &event);
};

}

#endif