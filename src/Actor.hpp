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
	bool m_bIsTurn = false;
	bool m_bPlayedTurn = false;

	void _setPlayedTurn(bool playedTurn);

	public:
	Actor();
	~Actor();
	void setBehaviour(Behaviour* b);
	void setX(int x);
	void setY(int y);
	void startTurn();
	void endTurn();
	int getX();
	int getY();
	bool isTurn();
	bool playedTurn();
	int getFrame();
	void setFrame(int frame);
	int getTilesetRowIndex();
	void setTilesetRowIndex(int tilesetRowIndex);

	void update(rRpg *engine);
};

#endif
