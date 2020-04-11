#include <map>
#include <string>
#include "ModelResource.h"
#include "ShaderResource.h"
#include "TextureResource.h"

class ResourceManager
{
public:
	void Init();
	static ResourceManager* getInstance();
	std::map<std::string, ModelResource*> modelResourceMap;
	std::map<unsigned int, TextureResource*> textureResourceMap;
	std::map<unsigned int, ShaderResource*> shaderResourceMap;
	void freeResources();
	~ResourceManager();

private:
	static ResourceManager* rmInstance;
	ResourceManager();
	void ReadResourceManagerXML(std::string path);
};