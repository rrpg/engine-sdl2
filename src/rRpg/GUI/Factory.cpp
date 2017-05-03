#include "GUI/Factory.hpp"
#include "GUI/Actor.hpp"
#include "GUI/Player.hpp"

GraphicFactory::GraphicFactory() {
	m_vGraphics = {
		new GraphicActor(),
		new GraphicPlayer(),
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
