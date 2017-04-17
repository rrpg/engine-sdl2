#include "Factory.hpp"
#include "Actor.hpp"

GraphicFactory::GraphicFactory() {
	m_vGraphics = {
		new GraphicActor(),
	};
}

GraphicFactory::~GraphicFactory() {
	for (auto graphic : m_vGraphics) {
		delete graphic;
	}
}

Graphic *GraphicFactory::getGraphic(E_Graphics graphic) {
	return m_vGraphics[graphic];
}
