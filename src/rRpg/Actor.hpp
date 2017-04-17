#ifndef __ACTOR__
#define __ACTOR__

#include <string>
#include "Behaviour.hpp"
#include "Graphic/Actor.hpp"

class rRpg;
class Map;
class ActorRace;

class Actor {
	private:
	int m_iHealth = 0;
	unsigned int m_iMaxHealth = 0;
	unsigned int m_iDefence = 0;
	unsigned int m_iAttack = 0;

	ActorRace &m_race;

	int m_iX = 0;
	int m_iY = 0;

	Behaviour* m_behaviour;
	GraphicActor* m_graphic;

	public:
	Actor(ActorRace &race);
	Actor(const Actor &L); // copy constructor
	Actor & operator=(const Actor &L); // assignment
	~Actor();
	void setBehaviour(Behaviour* b);
	void setGraphic(GraphicActor* b);

	ActorRace &getRace();

	int getHealth();
	unsigned int getMaxHealth();
	unsigned int getDefence();
	unsigned int getAttack();
	void setHealth(int health);
	void setMaxHealth(unsigned int maxHealth);
	void setDefence(unsigned int defence);
	void setAttack(unsigned int attack);

	bool isDead();

	void setX(int x);
	void setY(int y);
	int getX();
	int getY();

	void update(rRpg *engine);
	void render(unsigned int worldTileWidth, unsigned int worldTileHeight, unsigned int displayShiftX, unsigned int displayShiftY);

	bool isNextTo(Actor *actor);
	bool seesActor(Map &map, Actor *actor);

	void attack(Actor *target);
};

#endif
