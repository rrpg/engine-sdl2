#ifndef __RESOURCE_MANAGER__
#define __RESOURCE_MANAGER__

#include <fstream>
#include <map>

template <class resourceType> class ResourceManager {
	private:
	std::map<int, resourceType> m_mResources = {};
	std::ifstream m_resourceFile;

	public:
	ResourceManager();
	~ResourceManager();
	void setResourceFile(std::string resourceFile);
	void getResource(int index, resourceType &resource);
	std::map<int, resourceType> &getParsedResources();
	void parseFile();
};

#include "ResourceManager.tpp"

#endif
