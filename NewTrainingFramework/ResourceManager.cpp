#include "stdafx.h"
#include "rapidxml.hpp"
#include "ResourceManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <fstream>

#include "../Utilities/utilities.h" 

using namespace std;
using namespace rapidxml;

void ResourceManager::ReadResourceManagerXML(string path)
{
	xml_document<> doc;
	std::ifstream file(path);
	if (file.is_open())
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		file.close();
		std::string content(buffer.str());
		doc.parse<0>(&content[0]);

		xml_node<> *pRoot = doc.first_node();
		// With the xml example above this is the <document/> node
		for (xml_node<> *pNode = pRoot->first_node(); pNode; pNode = pNode->next_sibling())
		{
			string resourceName = pNode->name();
			if (resourceName =="models")
			{
				for (xml_node<> *pModelsNode = pNode->first_node(); pModelsNode; pModelsNode = pModelsNode->next_sibling())
				{
					ModelResource* mr = new ModelResource();

					xml_attribute<> *pIdAttr = pModelsNode->first_attribute("id");
					string idValue = pIdAttr->value();
					xml_node<> *pPathNode = pModelsNode->first_node();
					string pathValue = pPathNode->value();

					mr->path = pathValue;
					modelResourceMap[idValue] = mr;
				}
			}
			else if (resourceName == "shaders")
			{
				for (xml_node<> *pShadersNode = pNode->first_node(); pShadersNode; pShadersNode = pShadersNode->next_sibling())
				{
					ShaderResource* sr = new ShaderResource();

					xml_attribute<> *pIdAttr = pShadersNode->first_attribute("id");
					string idValue = pIdAttr->value();
					xml_node<> *pVSPathNode = pShadersNode->first_node();
					string VSPathValue = pVSPathNode->value();
					xml_node<> *pFSPathNode = pVSPathNode->next_sibling();
					string FSPathValue = pFSPathNode->value();

					sr->vsPath = VSPathValue;
					sr->fsPath = FSPathValue;
					shaderResourceMap[stoi(idValue)] = sr;
				}
			}
			else if (resourceName == "textures")
			{
				for (xml_node<> *pTexturesNode = pNode->first_node(); pTexturesNode; pTexturesNode = pTexturesNode->next_sibling())
				{
					TextureResource* tr = new TextureResource();

					xml_attribute<> *pIdAttr = pTexturesNode->first_attribute("id");
					string idValue = pIdAttr->value();
					xml_attribute<> *pTypeAttr = pIdAttr->next_attribute();
					string typeValue = pTypeAttr->value();
					xml_node<> *pPathNode = pTexturesNode->first_node();
					string pathValue = pPathNode->value();
					xml_node<> *pMinFilterNode = pPathNode->next_sibling();
					string minFilterValue = pMinFilterNode->value();
					xml_node<> *pMagFilterNode = pMinFilterNode->next_sibling();
					string magFilterValue = pMagFilterNode->value();
					xml_node<> *pWrapSNode = pMagFilterNode->next_sibling();
					string wrapSValue = pWrapSNode->value();
					xml_node<> *pWrapTNode = pWrapSNode->next_sibling();
					string wrapTValue = pWrapTNode->value();

					tr->path = pathValue;
					tr->minFilter = minFilterValue;
					tr->magFilter = magFilterValue;
					tr->wrapS = wrapSValue;
					tr->wrapT = wrapTValue;
					tr->type = typeValue;

					textureResourceMap[stoi(idValue)] = tr;
				}
			}
		}
		int c = 3;
	}
	else cout << "Unable to open file";
	int b = 3;
}

ResourceManager* ResourceManager::rmInstance = NULL;

ResourceManager::ResourceManager()
{
}

ResourceManager * ResourceManager::getInstance()
{
	if (rmInstance == NULL)
		rmInstance = new ResourceManager();
	return rmInstance;
}

void ResourceManager::Init()
{
	ReadResourceManagerXML("..\\resourceManager.xml");
}
