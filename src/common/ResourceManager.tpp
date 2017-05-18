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
void ResourceManager<resourceType>::parseBinaryFile() {
	int index = 0;
	m_mResources.clear();
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

template <class resourceType>
bool ResourceManager<resourceType>::saveReadableFile(
	std::string fileOut,
	void (callback)(std::ofstream&, resourceType)
) {
	std::ofstream fileOutStream;
	fileOutStream.open(fileOut);
	if (!fileOutStream.good()) {
		fileOutStream.close();
		return false;
	}

	for (auto res : getParsedResources()) {
		callback(fileOutStream, res.second);
	}

	fileOutStream.close();
	return true;
}
