template <class resourceType>
ResourceManager<resourceType>::ResourceManager() :
	m_resourceFile()
{
}

template <class resourceType>
ResourceManager<resourceType>::ResourceManager(const ResourceManager &r) :
	m_mResources(r.m_mResources),
	m_resourceFile()
{
}

template <class resourceType>
ResourceManager<resourceType>::~ResourceManager() {
	_clean();
}

template <class resourceType>
void ResourceManager<resourceType>::_clean() {
	if (m_resourceFile.is_open()) {
		m_resourceFile.close();
	}
}

template <class resourceType>
bool ResourceManager<resourceType>::setResourceFile(std::string resourceFile) {
	_clean();
	m_resourceFile.open(resourceFile, std::ios::binary);
	return m_resourceFile.is_open();
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

template <class resourceType>
bool ResourceManager<resourceType>::compileFile(
	std::string fileIn,
	std::string fileOut,
	bool (rowCallback)(char*, resourceType&)
) {
	std::ifstream fileInStream;
	std::ofstream fileOutStream;
	fileInStream.open(fileIn);
	fileOutStream.open(fileOut);
	bool ret = true;

	while (!fileInStream.eof()) {
		char buf[MAX_CHARS_PER_LINE];
		// @check too long lines
		fileInStream.getline(buf, MAX_CHARS_PER_LINE);

		if (*buf == '\0' || *buf == '#') {
			continue;
		}

		resourceType resource;
		if (!rowCallback(buf, resource)) {
			ret = false;
			break;
		}

		fileOutStream.write((char*)&resource, sizeof(resource));
	}

	fileInStream.close();
	fileOutStream.close();
	return ret;
}
