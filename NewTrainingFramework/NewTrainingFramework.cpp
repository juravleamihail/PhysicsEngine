// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "rapidxml.hpp"
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include <list>
#include <tuple>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Camera.h"
#include <filesystem>
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SphereCollider.h"
#include "IntersectData.h"
#include "Plane.h"
#include "BoxCollider.h"
#include "PhysicsEngine.h"

#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include

using namespace std;
using namespace rapidxml;

GLfloat alpha = 0;

int Init ( ESContext *esContext )
{
	return SceneManager::getInstance()->Init();
}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	SceneManager::getInstance()->Draw();

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	alpha += deltaTime;
	SceneManager::getInstance()->Update();
	PhysicsEngine::getInstance()->Update(deltaTime);
	SceneManager::getInstance()->GetActiveCamera()->deltaTime = deltaTime;
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case 'W':
			SceneManager::getInstance()->GetActiveCamera()->moveOz(-100);
			break;
		case 'S':
			SceneManager::getInstance()->GetActiveCamera()->moveOz(100);
			break;
		case 'A':
			SceneManager::getInstance()->GetActiveCamera()->moveOx(-100);
			break;
		case 'D':
			SceneManager::getInstance()->GetActiveCamera()->moveOx(100);
			break;
		case 'Q':
			SceneManager::getInstance()->GetActiveCamera()->moveOy(-100);
			break;
		case 'E':
			SceneManager::getInstance()->GetActiveCamera()->moveOy(100);
			break;
		case VK_UP:
			SceneManager::getInstance()->GetActiveCamera()->rotateOx(10);
			break;
		case VK_DOWN:
			SceneManager::getInstance()->GetActiveCamera()->rotateOx(-10);
			break;
		case VK_LEFT:
			SceneManager::getInstance()->GetActiveCamera()->rotateOy(10);
			break;
		case VK_RIGHT:
			SceneManager::getInstance()->GetActiveCamera()->rotateOy(-10);
			break;
		default:
			break;
		}
	}
}

void CleanUp()
{
	SceneManager::getInstance()->CleanUp();
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();
	


	printf("Press any key...\n");
	_getch();

	
	return 0;
}
