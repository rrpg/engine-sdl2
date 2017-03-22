#ifndef __BEHAVIOUR__
#define __BEHAVIOUR__

class rRpg;
class Actor;

class Behaviour {
	public:
	virtual bool update(rRpg *engine, Actor *actor) = 0;
	virtual ~Behaviour() {};
};

#endif
