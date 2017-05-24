#ifndef __TAXONOMY_PARSER__
#define __TAXONOMY_PARSER__

#include "Parser/File.hpp"
#include "../ActorFactory.hpp"

class TaxonomyParser : public FileParser {
	protected:
	ActorFactory &m_actorFactory;
	bool _parseLine(const char *line);
	void _loadTilesetTexture(S_ActorRaceData &race);

	public:
	TaxonomyParser(ActorFactory &actorFactory);
};

#endif
