#include "CameraComponent.h"

CCameraComponent::CCameraComponent(int _width, int _height)
{
	m_position = glm::vec3(0.f, 0.f, -20.f);

	//make our projection matrix
	ProjectMatrix = glm::perspective(glm::radians(45.0f), (float)_width / (float)_height, 0.1f, 100000.0f);

	//make view matrix
	ViewMatrix = glm::lookAt
	(
		m_position,			//Camera is where now?
		glm::vec3(0, 0, 0),	//Camera looks at what now?
		glm::vec3(0,1,0)	//Camera head is what way now?
	);
}

CCameraComponent::~CCameraComponent()
{
}

void CCameraComponent::Update(float deltaTime)
{
	ViewMatrix = glm::lookAt
	(
		m_position,				//Camera is where now?
		m_lookAt,				//Camera looks at what now?
		glm::vec3(0, 1, 0)		//Camera head is what way now?
	);
}

void CCameraComponent::SetLookAt(glm::vec3 _val)
{
	//m_OldlookAt = m_lookAt;
	m_lookAt = _val;
}
