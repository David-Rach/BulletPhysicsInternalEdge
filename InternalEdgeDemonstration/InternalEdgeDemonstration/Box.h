#ifndef BOX_H
#define BOX_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/matrix.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include "BulletDebugManager.h"

class CBox
{
public:
	CBox(btVector3 _InitialSize, btVector3 _InitialPosition, float _mass);
	~CBox();

	void ShowDeug();

	btRigidBody* body;
	btCollisionShape* BoxShape;
	btDefaultMotionState* motionState;
};
#endif