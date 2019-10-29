#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include <glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CCameraComponent
{
public:
	CCameraComponent(int _width, int _height);
	~CCameraComponent();

	void Update(float deltaTime);
	void SetLookAt(glm::vec3 _val);

	/*Public matrices*/
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectMatrix;

	/*Camera Properties*/
	glm::vec3 m_position;

	/*Parent parent*/
	glm::mat4 * m_parentPosition;
	glm::mat4 * m_parentRotation;
	glm::mat4 * m_parentScale;

	glm::vec3 * m_parentPos;

	bool m_bIsLerp = true;
	bool m_bInheritOrientation = true;

private:
	glm::vec3 m_OldlookAt;
	glm::vec3 m_lookAt;
};
#endif