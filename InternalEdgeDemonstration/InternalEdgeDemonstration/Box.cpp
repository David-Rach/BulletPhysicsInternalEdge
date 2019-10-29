#include "Box.h"

CBox::CBox(btVector3 _InitialSize = btVector3(1,1,1), btVector3 _InitialPosition = btVector3(0,0,0), float _mass = 1.0f)
{
	BoxShape = new btBoxShape(_InitialSize);

	btTransform Transform;
	Transform.setIdentity();
	Transform.setOrigin(_InitialPosition);

	btScalar mass(_mass);

	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
	{
		BoxShape->calculateLocalInertia(mass, localInertia);
	}

	motionState = new btDefaultMotionState(Transform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, BoxShape, localInertia);
	body = new btRigidBody(rbInfo);
	body->setUserPointer(this);
}

CBox::~CBox()
{
	delete body;
	delete BoxShape;
	delete motionState;
}

void CBox::ShowDeug()
{
	CBulletDebugger& debugger = CBulletDebugger::GetInstance();

	float x = static_cast<btBoxShape*>(BoxShape)->getHalfExtentsWithMargin().getX();
	float y = static_cast<btBoxShape*>(BoxShape)->getHalfExtentsWithMargin().getY();
	float z = static_cast<btBoxShape*>(BoxShape)->getHalfExtentsWithMargin().getZ();

	glm::vec3 max(x, y, z);
	glm::vec3 min(-x, -y, -z);

	btTransform objectTrans;
	motionState->getWorldTransform(objectTrans);

	debugger.drawBox(btVector3(max.x, max.y, max.z), btVector3(min.x, min.y, min.z), objectTrans, btVector3(0, 1, 0));
}
