#include "stdafx.h"
#include "rapidxml.hpp"
#include <sstream>
#include <fstream>
#include "SceneManager.h"
#include "ResourceManager.h"
#include <string>
#include <algorithm> 
#include <iostream> 
#include "TerrainObject.h"
#include "Fire.h"
#include "PhysicsEngine.h"
#include "../Utilities/utilities.h" 

using namespace std;
using namespace rapidxml;

int i = 0;

void SceneManager::ReadSceneManagerXML(std::string path)
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
			if (resourceName == "fog")
			{
				for (xml_node<> *pObjectNode = pNode->first_node(); pObjectNode; pObjectNode = pObjectNode->next_sibling())
				{
					string resourceName = pObjectNode->name();

					if (resourceName == "smallRadius")
						smallRadius = stof(pObjectNode->value());
					else if (resourceName == "wideRadius")
						wideRadius = stof(pObjectNode->value());
					else if (resourceName == "fogColor")
					{
						xml_node<> *pRColorNode = pObjectNode->first_node();
						string rColorValue = pRColorNode->value();
						xml_node<> *pGColorNode = pRColorNode->next_sibling();
						string gColorValue = pGColorNode->value();
						xml_node<> *pBColorNode = pGColorNode->next_sibling();
						string bColorValue = pBColorNode->value();
						fogColor.x = stof(rColorValue);
						fogColor.y = stof(gColorValue);
						fogColor.z = stof(bColorValue);
					}
				}
			}
			else if (resourceName == "cameras")
			{
				for (xml_node<> *pCameraNode = pNode->first_node(); pCameraNode; pCameraNode = pCameraNode->next_sibling())
				{
					Camera* camera = new Camera(Vector3(1000, 0, 7), Vector3(0, 0, 0), Vector3(0, 1, 0), 300, 1, 0.2f, 10000, 45, 0);
					xml_attribute<> *pIdAttr = pCameraNode->first_attribute("id");
					string idValue = pIdAttr->value();

					xml_node<> *pPositionNode = pCameraNode->first_node();
					xml_node<> *pXPositionNode = pPositionNode->first_node();
					string xPositionValue = pXPositionNode->value();
					xml_node<> *pYPositionNode = pXPositionNode->next_sibling();
					string yPositionValue = pYPositionNode->value();
					xml_node<> *pZPositionNode = pYPositionNode->next_sibling();
					string zPositionValue = pZPositionNode->value();
					camera->position.x = stof(xPositionValue);
					camera->position.y = stof(yPositionValue);
					camera->position.z = stof(zPositionValue);

					xml_node<> *pTargetNode = pPositionNode->next_sibling();
					xml_node<> *pXTargetNode = pTargetNode->first_node();
					string xTargetValue = pXTargetNode->value();
					xml_node<> *pYTargetNode = pXTargetNode->next_sibling();
					string yTargetValue = pYTargetNode->value();
					xml_node<> *pZTargetNode = pYTargetNode->next_sibling();
					string zTargetValue = pZTargetNode->value();
					camera->target.x = stof(xTargetValue);
					camera->target.y = stof(yTargetValue);
					camera->target.z = stof(zTargetValue);

					xml_node<> *pUpNode = pTargetNode->next_sibling();
					xml_node<> *pXUpNode = pUpNode->first_node();
					string xUpValue = pXUpNode->value();
					xml_node<> *pYUpNode = pXUpNode->next_sibling();
					string yUpValue = pYUpNode->value();
					xml_node<> *pZUpNode = pYUpNode->next_sibling();
					string zUpValue = pZUpNode->value();
					camera->up.x = stof(xUpValue);
					camera->up.y = stof(yUpValue);
					camera->up.z = stof(zUpValue);

					xml_node<> *pTranslationSpeedNode = pUpNode->next_sibling();
					string translationSpeedValue = pTranslationSpeedNode->value();
					xml_node<> *pRotationSpeedNode = pTranslationSpeedNode->next_sibling();
					string rotationSpeedValue = pRotationSpeedNode->value();
					xml_node<> *pFovNode = pRotationSpeedNode->next_sibling();
					string fovValue = pFovNode->value();
					xml_node<> *pNearNode = pFovNode->next_sibling();
					string nearValue = pNearNode->value();
					xml_node<> *pFarNode = pNearNode->next_sibling();
					string farValue = pFarNode->value();
					camera->moveSpeed = stof(translationSpeedValue);
					camera->rotateSpeed = stof(rotationSpeedValue);
					camera->fov = stof(fovValue);
					camera->near1 = stof(nearValue);
					camera->far1 = stof(farValue);

					camera->updateWorldView();

					cameraResourceMap[stoi(idValue)] = camera;
					
				}
			}
			else if (resourceName == "activeCamera")
			{
				xml_node<> *pActiveCameraNode = pNode->first_node();
				string idActiveCameraValue = pActiveCameraNode->value();
				idActiveCamera = stoi(idActiveCameraValue);
			}
			else if (resourceName == "objects")
			{
				for (xml_node<> *pObjectNode = pNode->first_node(); pObjectNode; pObjectNode = pObjectNode->next_sibling())
				{
					Fire* fire = new Fire();
					TerrainObject* terrain = new TerrainObject();
					SceneObject * object = new SceneObject();
					xml_attribute<> *pIdAttr = pObjectNode->first_attribute("id");
					string idValue = pIdAttr->value();

					for (xml_node<> *pObjectChildrenNode = pObjectNode->first_node(); pObjectChildrenNode; pObjectChildrenNode = pObjectChildrenNode->next_sibling())
					{
						const string option = pObjectChildrenNode->name();
						
						if (option == "model")
						{
							object->idModel = pObjectChildrenNode->value();
							object->model = new Model();

							auto aa = ResourceManager::getInstance()->modelResourceMap;

							if ((object->idModel != "generated"))
							{
								object->model->mr = ResourceManager::getInstance()->modelResourceMap[object->idModel];

								if ((ResourceManager::getInstance()->modelResourceMap[object->idModel]->modelVerticesVector.size() == 0))
								{
									object->model->Load();
								}
							}
						}
						else if (option == "shader")
						{
							object->idShader = stoi(pObjectChildrenNode->value());
							object->shader = new Shader();

							auto aa = ResourceManager::getInstance()->shaderResourceMap;

							object->shader->sr = ResourceManager::getInstance()->shaderResourceMap[object->idShader];

							if ((ResourceManager::getInstance()->shaderResourceMap[object->idShader]->vertexShader == 0))
								object->shader->Load();
							else
								object->shader->programId = esLoadProgram(object->shader->sr->vertexShader, object->shader->sr->fragmentShader);
						}
						else if (option == "dispMax")
						{
							fire->dispMax = stof(pObjectChildrenNode->value());
						}
						else if (option == "nrCelule")
						{
							terrain->nrCelule = stoi(pObjectChildrenNode->value());
						}
						else if (option == "dimCelula")
						{
							terrain->dimCelula = stoi(pObjectChildrenNode->value());
						}
						else if (option == "type")
						{
							object->type = pObjectChildrenNode->value();

							if (object->type == "terrain")
							{
								terrain->type = object->type;
								terrain->shader = object->shader;
								terrain->idShader = object->idShader;
								terrain->model = object->model;
								terrain->idModel = object->idModel;

								terrain->InitTerrain();
								object = terrain;
							}
							else if (object->type == "fire")
							{
								fire->type = object->type;
								fire->shader = object->shader;
								fire->idShader = object->idShader;
								fire->model = object->model;
								fire->idModel = object->idModel;

								object = fire;
							}
						}
						else if (option == "blend")
						{
							object->blend = pObjectChildrenNode->value();
						}
						else if (option == "name")
						{
							object->name = pObjectChildrenNode->value();
						}
						else if (option == "color")
						{
							xml_node<> *pRColorNode = pObjectChildrenNode->first_node();
							string rColorValue = pRColorNode->value();
							xml_node<> *pGColorNode = pRColorNode->next_sibling();
							string gColorValue = pGColorNode->value();
							xml_node<> *pBColorNode = pGColorNode->next_sibling();
							string bColorValue = pBColorNode->value();
							object->color.x = stof(rColorValue);
							object->color.y = stof(gColorValue);
							object->color.z = stof(bColorValue);
						}
						else if (option == "textures")
						{
							for (xml_node<> *pTextureNode = pObjectChildrenNode->first_node(); pTextureNode; pTextureNode = pTextureNode->next_sibling())
							{
								xml_attribute<> *pTextureIdAttr = pTextureNode->first_attribute("id");
								string textureIdValue = pTextureIdAttr->value();

								auto aa = ResourceManager::getInstance()->textureResourceMap;
								Texture* texture = new Texture();
								texture->tr = ResourceManager::getInstance()->textureResourceMap[stoi(textureIdValue)];
								texture->textureId = stoi(textureIdValue);

								if (stoi(idValue) == 10)
									int asdd = 3;

								texture->Load();
								object->textures.push_back(texture);
							}
						}
						else if (option == "position")
						{
							xml_node<> *pXPositionNode = pObjectChildrenNode->first_node();
							string xPositionValue = pXPositionNode->value();
							xml_node<> *pYPositionNode = pXPositionNode->next_sibling();
							string yPositionValue = pYPositionNode->value();
							xml_node<> *pZPositionNode = pYPositionNode->next_sibling();
							string zPositionValue = pZPositionNode->value();
							object->position.x = stof(xPositionValue);
							object->position.y = stof(yPositionValue);
							object->position.z = stof(zPositionValue);
						}
						else if (option == "rotation")
						{
							xml_node<> *pXRotationNode = pObjectChildrenNode->first_node();
							string xRotationValue = pXRotationNode->value();
							xml_node<> *pYRotationNode = pXRotationNode->next_sibling();
							string yRotationValue = pYRotationNode->value();
							xml_node<> *pZRotationNode = pYRotationNode->next_sibling();
							string zRotationValue = pZRotationNode->value();
							object->rotation.x = stof(xRotationValue);
							object->rotation.y = stof(yRotationValue);
							object->rotation.z = stof(zRotationValue);
						}
						else if (option == "scale")
						{
							xml_node<> *pXScaleNode = pObjectChildrenNode->first_node();
							string xScaleValue = pXScaleNode->value();
							xml_node<> *pYScaleNode = pXScaleNode->next_sibling();
							string yScaleValue = pYScaleNode->value();
							xml_node<> *pZScaleNode = pYScaleNode->next_sibling();
							string zScaleValue = pZScaleNode->value();
							object->scale.x = stof(xScaleValue);
							object->scale.y = stof(yScaleValue);
							object->scale.z = stof(zScaleValue);
						}

						else if (option == "velocity")
						{
							xml_node<> *pXVelocityValueNode = pObjectChildrenNode->first_node();
							string xVelocityValue = pXVelocityValueNode->value();
							xml_node<> *pYVelocityValueNode = pXVelocityValueNode->next_sibling();
							string yVelocityValue = pYVelocityValueNode->value();
							xml_node<> *pZVelocityValueNode = pYVelocityValueNode->next_sibling();
							string zVelocityValue = pZVelocityValueNode->value();
							object->velocity.x = stof(xVelocityValue);
							object->velocity.y = stof(yVelocityValue);
							object->velocity.z = stof(zVelocityValue);
						}

						else if (option == "radius")
						{
							string value = pObjectChildrenNode->value();
							object->radius = stof(value);
						}

						else if (option == "height")
						{
						xml_node<> *pXHeightNode = pObjectChildrenNode->first_node();
						string xHeightValue = pXHeightNode->value();
						xml_node<> *pYHeightNode = pXHeightNode->next_sibling();
						string yHeightValue = pYHeightNode->value();
						xml_node<> *pZHeightNode = pYHeightNode->next_sibling();
						string zHeightValue = pZHeightNode->value();
						object->height.x = stof(xHeightValue);
						object->height.y = stof(yHeightValue);
						object->height.z = stof(zHeightValue);
						}
						else if (option == "followingCamera")
						{
							for (xml_node<> *pFollowingcameraNode = pObjectChildrenNode->first_node(); pFollowingcameraNode; pFollowingcameraNode = pFollowingcameraNode->next_sibling())
							{
								const string option = pFollowingcameraNode->name();
								if (option == "ox")
									object->isFollowingCameraOx = true;
								else if (option == "oy")
									object->isFollowingCameraOy = true;
								else if (option == "oz")
									object->isFollowingCameraOz = true;
								else if (option == "offset")
								{
									for (xml_node<> *pFollowingcameraOffsetNode = pFollowingcameraNode->first_node(); pFollowingcameraOffsetNode; pFollowingcameraOffsetNode = pFollowingcameraOffsetNode->next_sibling())
									{
										const string offsetAxis = pFollowingcameraOffsetNode->name();
										const string offsetAxisValue = pFollowingcameraOffsetNode->value();

										if (offsetAxis == "x")
											object->position.x = SceneManager::getInstance()->GetActiveCamera()->position.x + stof(offsetAxisValue);
										else if(offsetAxis == "y")
											object->position.y = SceneManager::getInstance()->GetActiveCamera()->position.y + stof(offsetAxisValue);
										else if (offsetAxis == "z")
											object->position.z = SceneManager::getInstance()->GetActiveCamera()->position.z + stof(offsetAxisValue);
									}
									object->UpdateModelMatrix();
								}
							}
						}
						else if (option == "hasPhysics")
						{
							string value = pObjectChildrenNode->value();
							if(value == "Yes")
							{
								PhysicsObject newPhysicsObject = PhysicsObject(SphereCollider(object->position, object->radius));
								newPhysicsObject.sceneObject = object;
								PhysicsEngine::getInstance()->AddPhysicsObject(newPhysicsObject);
							}
						}
					}		

					sceneObjectMap[idValue] = object;
					int a = 3;
				}
			}
			else if (resourceName == "ambientalLight")
			{
				for (xml_node<> *pAmbientalLightPropertyNode = pNode->first_node(); pAmbientalLightPropertyNode; pAmbientalLightPropertyNode = pAmbientalLightPropertyNode->next_sibling())
				{
					string name = pAmbientalLightPropertyNode->name();

					if (name == "color")
					{
						for (xml_node<> *pColorElementNode = pAmbientalLightPropertyNode->first_node(); pColorElementNode; pColorElementNode = pColorElementNode->next_sibling())
						{
							string colorElementName = pColorElementNode->name();

							if (colorElementName == "r")
								ambientalLight.x = stof(pColorElementNode->value());
							else if (colorElementName == "g")
								ambientalLight.y = stof(pColorElementNode->value());
							else if (colorElementName == "b")
								ambientalLight.z = stof(pColorElementNode->value());
						}
					}
					else if (name == "ratio")
						ambientalLightRatio = stof(pAmbientalLightPropertyNode->value());
				}
				int breakpoint = 0;
			}
			else if (resourceName == "lights")
			{
				for (xml_node<> *lightNode = pNode->first_node(); lightNode; lightNode = lightNode->next_sibling())
				{
					Light* light = new Light();
					xml_attribute<> *pIdAttr = lightNode->first_attribute("id");
					int id = stoi(pIdAttr->value());
					light->id = id;

					for (xml_node<> *lightPropertyNode = lightNode->first_node(); lightPropertyNode; lightPropertyNode = lightPropertyNode->next_sibling())
					{
						string lightPropertyName = lightPropertyNode->name();

						if (lightPropertyName == "position")
						{
							for (xml_node<> *pPositionElementNode = lightPropertyNode->first_node(); pPositionElementNode; pPositionElementNode = pPositionElementNode->next_sibling())
							{
								string lightPropertyElementName = pPositionElementNode->name();

								if (lightPropertyElementName == "x")
									light->position.x = stof(pPositionElementNode->value());
								else if (lightPropertyElementName == "y")
									light->position.y = stof(pPositionElementNode->value());
								else if (lightPropertyElementName == "z")
									light->position.z = stof(pPositionElementNode->value());
							}
						}
						else if (lightPropertyName == "diffuseColor")
						{
							for (xml_node<> *pColorElementNode = lightPropertyNode->first_node(); pColorElementNode; pColorElementNode = pColorElementNode->next_sibling())
							{
								string colorElementName = pColorElementNode->name();

								if (colorElementName == "r")
									light->diffColor.x = stof(pColorElementNode->value());
								else if (colorElementName == "g")
									light->diffColor.y = stof(pColorElementNode->value());
								else if (colorElementName == "b")
									light->diffColor.z = stof(pColorElementNode->value());
							}

						}
						else if (lightPropertyName == "specularColor")
						{
							for (xml_node<> *pColorElementNode = lightPropertyNode->first_node(); pColorElementNode; pColorElementNode = pColorElementNode->next_sibling())
							{
								string colorElementName = pColorElementNode->name();

								if (colorElementName == "r")
									light->specColor.x = stof(pColorElementNode->value());
								else if (colorElementName == "g")
									light->specColor.y = stof(pColorElementNode->value());
								else if (colorElementName == "b")
									light->specColor.z = stof(pColorElementNode->value());
							}
						}
						else if (lightPropertyName == "directionLight")
						{
							for (xml_node<> *pDirectionLightElementNode = lightPropertyNode->first_node(); pDirectionLightElementNode; pDirectionLightElementNode = pDirectionLightElementNode->next_sibling())
							{
								string colorElementName = pDirectionLightElementNode->name();

								if (colorElementName == "x")
									light->directionLight.x = stof(pDirectionLightElementNode->value());
								else if (colorElementName == "y")
									light->directionLight.y = stof(pDirectionLightElementNode->value());
								else if (colorElementName == "z")
									light->directionLight.z = stof(pDirectionLightElementNode->value());
							}
						}
						else if (lightPropertyName == "SpecPower")
						{
							light->specPower = stof(lightPropertyNode->value());
						}
						else if (lightPropertyName == "type")
						{
							light->type = lightPropertyNode->value();
						}
					}

					lightsMap[id] = light;
				}
			}
		}
	}
}

int SceneManager::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ResourceManager::getInstance()->Init();
	ReadSceneManagerXML("..\\sceneManager.xml");

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	srand(time(NULL));
	for(auto obj : sceneObjectMap)
	{
		obj.second->InitObject();
		float xRandom = rand() % 1000 + 0;
		float yRandom = rand() % 1000 + 0;
		float zRandom = rand() % 1000 + 0;
		float xVelocity = rand() % 100 + 0;
		float yVelocity = rand() % 100 + 0;
		float zVelocity = rand() % 100 + 0;
		obj.second->position = Vector3(xRandom, yRandom, zRandom);
		obj.second->velocity = Vector3(xVelocity, yVelocity, zVelocity);
	}

	return 0;
}

void SceneManager::Draw()
{
	for (auto obj : sceneObjectMap)
	{
		obj.second->Draw();
	}
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::smInstance = NULL;

SceneManager * SceneManager::getInstance()
{
	if (smInstance == NULL)
		smInstance = new SceneManager();
	return smInstance;
}

Camera * SceneManager::GetActiveCamera()
{
	return cameraResourceMap[idActiveCamera];
}

void SceneManager::CleanUp()
{
	//glDeleteBuffers(1, &crocoObject->model->vboId);
}

void SceneManager::Update()
{
	for (auto obj : sceneObjectMap)
	{
		obj.second->Update();
	}
}
