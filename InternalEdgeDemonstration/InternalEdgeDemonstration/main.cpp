#include <iostream>
#include <glew.h>
#include <glfw3.h>
#include <bullet3/btBulletDynamicsCommon.h>
#include <vld.h>

#include "BulletDebugManager.h"
#include "ShaderManager.h"
#include "CameraComponent.h"
#include "Box.h"

using namespace std;

struct sWorldInfo
{
	btDefaultCollisionConfiguration* m_collisionConfiguration;
	btCollisionDispatcher* m_dispatcher;
	btBroadphaseInterface * m_overlappingPairCache;
	btSequentialImpulseConstraintSolver* m_solver;
	btDiscreteDynamicsWorld* m_dynamicWorld;
};

GLFWwindow *handleToWindow;
sWorldInfo* worldInfo;
CCameraComponent* camera;
CBox* ground;

bool Init()
{
	/*Initialize GLFW library*/
	if (!glfwInit())
	{
		std::cout << "ERROR!!" << std::endl;
		std::cout << "GLFW failed in initiate" << std::endl;
		system("pause");
		glfwTerminate();
		return false;
	}

	/*Create a window*/
	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);
	handleToWindow = glfwCreateWindow(1200, 800, "Internal Edge Demonstration", NULL, NULL);
	if (!handleToWindow)
	{
		std::cout << "ERROR!!" << std::endl;
		std::cout << "Window failed to open. Handle to window is NULL" << std::endl;
		system("pause");
		glfwTerminate();
		return false;
	}

	/*make this window the current context*/
	glfwMakeContextCurrent(handleToWindow);

	/*initailize GLEW library*/
	GLenum glewChk = glewInit();
	if (GLEW_OK != glewChk)
	{
		std::cout << "Failed to initiate GLEW library. Something is seriously wrong" << std::endl;
		std::cout << stderr, "Error: %s\n", glewGetErrorString(GLEW_VERSION);
		system("pause");
		glfwTerminate();
		return false;
	}

	return true;
}

bool OnGameplayBegin()
{
	GLuint debugShader = CShaderManager::GetInstance().loadShaders("Assets/Shaders/debug.vs","Assets/Shaders/debug.fs");
	
	camera = new CCameraComponent(1200,800);

	worldInfo = new sWorldInfo;

	worldInfo->m_collisionConfiguration = new btDefaultCollisionConfiguration();
	worldInfo->m_dispatcher = new btCollisionDispatcher(worldInfo->m_collisionConfiguration);
	worldInfo->m_overlappingPairCache = new btDbvtBroadphase();
	worldInfo->m_solver = new btSequentialImpulseConstraintSolver;
	worldInfo->m_dynamicWorld = new btDiscreteDynamicsWorld(worldInfo->m_dispatcher, worldInfo->m_overlappingPairCache, worldInfo->m_solver, worldInfo->m_collisionConfiguration);
	worldInfo->m_dynamicWorld->setGravity(btVector3(0, -10, 0));

	CBulletDebugger::GetInstance().InitDrawBuffers();
	CBulletDebugger::GetInstance().SetCamera(camera);
	CBulletDebugger::GetInstance().SetShader(debugShader);
	CBulletDebugger::GetInstance().setDebugMode(btIDebugDraw::DBG_DrawWireframe);

	ground = new CBox(btVector3(1, -1, 1), btVector3(0, -3, 0), 0);
	worldInfo->m_dynamicWorld->addRigidBody(ground->body);

	return true;
}

void LogicLoop()
{

}

void RenderLoop()
{
	ground->ShowDeug();
	CBulletDebugger::GetInstance().DrawDebug();
}

void Shutdown()
{
	delete worldInfo->m_dynamicWorld;
	delete worldInfo->m_solver;
	delete worldInfo->m_overlappingPairCache;
	delete worldInfo->m_dispatcher;
	delete worldInfo->m_collisionConfiguration;
	delete worldInfo;

	delete ground;
	delete camera;

	glfwTerminate();
}

int main()
{
	if (!Init())
	{
		return 0;
	}

	if (!OnGameplayBegin())
	{
		return 0;
	}

	while (!glfwWindowShouldClose(handleToWindow))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.01f, 0.01f, 0.01f, 1.0f);

		RenderLoop();

		glfwSwapBuffers(handleToWindow);
		glfwPollEvents();
	}

	Shutdown();
	return 0;
}