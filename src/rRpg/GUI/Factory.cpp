#include "GUI/Factory.hpp"
#include "GUI/Terrain.hpp"
#include "GUI/Object.hpp"
#include "GUI/Actor.hpp"
#include "GUI/Player.hpp"

GraphicFactory::GraphicFactory() {
	m_vGraphics = {
		new GraphicTerrain(),
		new GraphicObject(),
		new GraphicActor(),
		new GraphicPlayer()
	};
}

GraphicFactory::~GraphicFactory() {
	for (auto graphic : m_vGraphics) {
		delete graphic;
	}
}

Graphic *GraphicFactory::_getGraphic(E_Graphics graphic) {
	return m_vGraphics[graphic];
}

GraphicTerrain *GraphicFactory::getGraphicTerrain() {
	return (GraphicTerrain*) _getGraphic(GRAPHIC_TERRAIN);
}

GraphicObject *GraphicFactory::getGraphicObject() {
	return (GraphicObject*) _getGraphic(GRAPHIC_OBJECT);
}

GraphicActor *GraphicFactory::getGraphicActor() {
	return (GraphicActor*) _getGraphic(GRAPHIC_ACTOR);
}

GraphicPlayer *GraphicFactory::getGraphicPlayer() {
	return (GraphicPlayer*) _getGraphic(GRAPHIC_PLAYER);
}
