#ifndef __ACTOR__
#define __ACTOR__

#include <string>
#include "Behaviour.hpp"

class rRpg;
class ActorRace;

class Actor {
	private:
	int m_iHealth = 0;
	unsigned int m_iMaxHealth = 0;

	ActorRace &m_race;

	int m_iX = 0;
	int m_iY = 0;
	// @TODO move in TileRenderer class to create
	int m_iFrameX = 0;
	int m_iFrameY = 0;

	Behaviour* m_behaviour;

	bool m_bIsTurn = false;
	bool m_bPlayedTurn = false;

	void _setPlayedTurn(bool playedTurn);

	public:
	Actor(ActorRace &race);
	Actor(const Actor &L); // copy constructor
	Actor & operator=(const Actor &L); // assignment
	~Actor();
	void setBehaviour(Behaviour* b);

	int getHealth();
	unsigned int getMaxHealth();
	void setHealth(int health);
	void setMaxHealth(unsigned int maxHealth);

	void setX(int x);
	void setY(int y);
	int getX();
	int getY();

	void startTurn();
	void endTurn();
	bool isTurn();
	bool playedTurn();

	int getFrameX();
	void setFrameX(int frameX);
	int getFrameY();
	void setFrameY(int frameY);

	void update(rRpg *engine);
};

#endif
