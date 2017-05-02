#ifndef __ACTOR__
#define __ACTOR__

#include <string>
#include "Behaviour/Behaviour.hpp"
#include "Graphic/Actor.hpp"

class rRpg;
class Map;
class ActorRace;

enum E_ActorOrientation {LEFT, RIGHT};

class Actor {
	private:
	int m_iHealth = 0;
	int m_iMaxHealth = 0;
	int m_iDefence = 0;
	int m_iAttack = 0;

	ActorRace &m_race;

	int m_iX = 0;
	int m_iY = 0;
	E_ActorOrientation m_eOrientation = LEFT;

	Behaviour* m_behaviour;
	GraphicActor* m_graphic;

	// to know when to display actor health
	uint32_t m_iLastTimeHit = 0;

	public:
	Actor(ActorRace &race);
	Actor(const Actor &L); // copy constructor
	Actor & operator=(const Actor &L); // assignment
	~Actor();
	void setBehaviour(Behaviour* b);
	void setGraphic(GraphicActor* b);

	ActorRace &getRace();

	int getHealth();
	int getMaxHealth();
	int getDefence();
	int getAttack();
	void setHealth(int health);
	void setMaxHealth(int maxHealth);
	void setDefence(int defence);
	void setAttack(int attack);

	bool isDead();

	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	E_ActorOrientation getOrientation();

	void setLastTimeHit();
	uint32_t getLastTimeHit();

	void update(rRpg *engine);
	void render(int displayShiftX, int displayShiftY);

	bool isNextTo(Actor *actor);
	bool seesActor(Map &map, Actor *actor);

	void attack(Actor *target);
};

#endif
