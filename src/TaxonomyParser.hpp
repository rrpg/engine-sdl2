#ifndef __TAXONOMY_PARSER__
#define __TAXONOMY_PARSER__

#include "FileParser.hpp"
#include "ActorFactory.hpp"

class TaxonomyParser : public FileParser {
	protected:
	ActorFactory &m_actorFactory;
	bool _parseLine(const char *line);

	public:
	TaxonomyParser(ActorFactory &actorFactory);
};

#endif
