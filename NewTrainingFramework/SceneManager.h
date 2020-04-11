#include <string>
#include <map>
#include "Camera.h"
#include "SceneObject.h"
#include <time.h> 
#include "Light.h"
#include "../Utilities/Math.h"

class SceneManager
{
public:
	int Init();
	void Draw();
	void Update();
	static SceneManager* getInstance();
	Camera* GetActiveCamera();
	void CleanUp();

	Vector3 fogColor;
	float smallRadius, wideRadius;
	Vector3 ambientalLight;
	std::map<int, Light*> lightsMap;
	float ambientalLightRatio;
	Vector3 lightType; //indices: 0-directional, 1-point light, 2-spot light

	~SceneManager();
private:
	static SceneManager* smInstance;
	SceneManager();
	std::string id;
	void ReadSceneManagerXML(std::string path);
	std::map<int, Camera*> cameraResourceMap;
	std::map<std::string, SceneObject*> sceneObjectMap;
	int idActiveCamera;
};