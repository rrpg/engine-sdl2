#ifndef __ACTOR_RACE__
#define __ACTOR_RACE__

#include "types.hpp"
#include <string>
#include <memory>
#include <vector>

class Actor;

class ActorRace {
	private:
	S_ActorRaceData m_data;

	public:
	ActorRace(S_ActorRaceData data);
	std::shared_ptr<Actor> createActor();
	std::string getTilesetName();
	int getSpriteX();
	int getSpriteY();
	void loadTilesetResource();
};

#endif
