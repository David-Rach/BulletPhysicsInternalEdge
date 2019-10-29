#ifndef BULLETDEBUGMANAGER_H
#define BULLETDEBUGMANAGER_H

#include <bullet3/btBulletDynamicsCommon.h>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <iostream>
#include <glew.h>
#include <glfw3.h>

#include "CameraComponent.h"

class CBulletDebugger : public btIDebugDraw
{
public:
	static CBulletDebugger& GetInstance();
	CBulletDebugger(CBulletDebugger const&) = delete;
	void operator=(CBulletDebugger const&) = delete;
	~CBulletDebugger();

	/*An initiate function. It has to be called at least once*/
	void InitDrawBuffers();

	void DrawDebug();
	void SetShader(GLuint _shader);
	void SetCamera(CCameraComponent* _camera);

	/*Overrides*/
	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;
	void reportErrorWarning(const char* warningString) override;
	void draw3dText(const btVector3& location, const char* textString) override;
	void setDebugMode(int debugMode) override;
	int	getDebugMode() const override;

private:
	CBulletDebugger();

	/*Vertex Arrays*/
	GLuint VertexArrayObject;
	GLuint BufferArrayObject;
	GLuint ColorBufferArray;

	/*Lines vertices*/
	std::vector<glm::vec3> m_linesBuffer;
	std::vector<glm::vec3> m_ColorsBuffer;
	std::vector<glm::vec3> m_boxBuffer;

	/*Matrices*/
	glm::mat4 m_scaleMatrix;
	glm::mat4 m_positionMatrix;
	glm::mat4 m_modelMatrix;

	/*Camera*/
	CCameraComponent* m_assignedCamera;
	GLuint m_shader;

	int m_debugMode;
};
#endif