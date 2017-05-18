template <class resourceType>
ResourceManager<resourceType>::ResourceManager() :
	m_resourceFile(std::ifstream())
{
}

template <class resourceType>
ResourceManager<resourceType>::~ResourceManager() {
	if (m_resourceFile.is_open()) {
		m_resourceFile.close();
	}
}

template <class resourceType>
void ResourceManager<resourceType>::setResourceFile(std::string resourceFile) {
	m_resourceFile = std::ifstream(resourceFile, std::ios::binary);
}

template <class resourceType>
void ResourceManager<resourceType>::getResource(int index, resourceType &resource) {
	auto storedResource = m_mResources.find(index);
	if (storedResource != m_mResources.end()) {
		resource = storedResource->second;
		return;
	}

	m_resourceFile.seekg((signed) (sizeof(resourceType) * (unsigned) index));
	m_resourceFile.read((char*)&resource, sizeof(resource));
	m_mResources[index] = resource;
}

template <class resourceType>
std::map<int, resourceType> &ResourceManager<resourceType>::getParsedResources() {
	return m_mResources;
}

template <class resourceType>
void ResourceManager<resourceType>::parseFile() {
	int index = 0;
	while (!m_resourceFile.eof()) {
		resourceType resource;
		m_resourceFile.read((char*)&resource, sizeof(resource));
		if (m_resourceFile.eof()) {
			break;
		}
		m_mResources[index] = resource;
		++index;
	}
}
