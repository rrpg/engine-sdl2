#ifndef __ACTOR__
#define __ACTOR__

#include <string>
#include "Behaviour.hpp"

class rRpg;
class Map;
class ActorRace;

class Actor {
	private:
	int m_iHealth = 0;
	unsigned int m_iMaxHealth = 0;

	ActorRace &m_race;

	int m_iX = 0;
	int m_iY = 0;

	Behaviour* m_behaviour;

	public:
	Actor(ActorRace &race);
	Actor(const Actor &L); // copy constructor
	Actor & operator=(const Actor &L); // assignment
	~Actor();
	void setBehaviour(Behaviour* b);

	ActorRace &getRace();

	int getHealth();
	unsigned int getMaxHealth();
	void setHealth(int health);
	void setMaxHealth(unsigned int maxHealth);

	void setX(int x);
	void setY(int y);
	int getX();
	int getY();

	void update(rRpg *engine);

	bool seesActor(Map &map, Actor *actor);
};

#endif
