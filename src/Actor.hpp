#ifndef __ACTOR__
#define __ACTOR__

#include <string>
#include "Behaviour.hpp"

class rRpg;

class Actor {
	private:
	int m_iX = 0;
	int m_iY = 0;
	// @TODO move in TileRenderer class to create
	int m_iFrame = 0;
	int m_iTilesetRowIndex = 0;
	Behaviour* m_behaviour;

	public:
	Actor();
	~Actor();
	void setBehaviour(Behaviour* b);
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	int getFrame();
	void setFrame(int frame);
	int getTilesetRowIndex();
	void setTilesetRowIndex(int tilesetRowIndex);

	void update(rRpg *engine);
};

#endif
