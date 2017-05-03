#ifndef __GRAPHIC__FACTORY__
#define __GRAPHIC__FACTORY__

#include <vector>
#include "GUI.hpp"

enum E_Graphics {GRAPHIC_ACTOR, GRAPHIC_PLAYER};

class GraphicFactory {
	private:
	std::vector<Graphic*> m_vGraphics = {};

	public:
	GraphicFactory();
	~GraphicFactory();
	Graphic *getGraphic(E_Graphics graphic);

};

#endif
