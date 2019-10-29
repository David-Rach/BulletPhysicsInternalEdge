#include "BulletDebugManager.h"

CBulletDebugger & CBulletDebugger::GetInstance()
{
	static CBulletDebugger Instance;
	return Instance;
}

CBulletDebugger::CBulletDebugger()
{

}

CBulletDebugger::~CBulletDebugger()
{
}

void CBulletDebugger::InitDrawBuffers()
{
	glGenVertexArrays(1, &VertexArrayObject);
	glGenBuffers(1, &BufferArrayObject);
	glGenBuffers(1, &ColorBufferArray);
	
}

void CBulletDebugger::DrawDebug()
{
	glUseProgram(m_shader);

	if (m_linesBuffer.size() != 0)
	{
		glBindVertexArray(VertexArrayObject);
		glBindBuffer(GL_ARRAY_BUFFER, BufferArrayObject);
		glBufferData(GL_ARRAY_BUFFER, m_linesBuffer.size() * sizeof(glm::vec3), &m_linesBuffer[0], GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, ColorBufferArray);
		glBufferData(GL_ARRAY_BUFFER, m_ColorsBuffer.size() * sizeof(glm::vec3), &m_ColorsBuffer[0], GL_DYNAMIC_DRAW);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);

		//Lets make our models matrix first
		m_positionMatrix = glm::translate(glm::vec3(0, 0, 0));
		m_scaleMatrix = glm::scale(glm::vec3(1, 1, 1));
		m_modelMatrix = m_positionMatrix * m_scaleMatrix;

		//and now hand it over to our shader to use
		glUniformMatrix4fv(glGetUniformLocation(m_shader, "Model"), 1, GL_FALSE, &m_modelMatrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(m_shader, "View"), 1, GL_FALSE, &m_assignedCamera->ViewMatrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(m_shader, "Projection"), 1, GL_FALSE, &m_assignedCamera->ProjectMatrix[0][0]);

		//Draw the polys
		glBindVertexArray(VertexArrayObject);
		glDrawArrays(GL_LINES, 0, m_linesBuffer.size());
		glBindVertexArray(0);

		m_linesBuffer.clear();
		m_ColorsBuffer.clear();
	}
}

void CBulletDebugger::SetShader(GLuint _shader)
{
	m_shader = _shader;
}

void CBulletDebugger::SetCamera(CCameraComponent * _camera)
{
	m_assignedCamera = _camera;
}

void CBulletDebugger::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color = btVector3(1,1,1))
{
	/*Convert from bullet into glm*/
	glm::vec3 Origin(from.getX(), from.getY(), from.getZ());
	glm::vec3 Destination(to.getX(), to.getY(), to.getZ());
	glm::vec3 Color(color.getX(), color.getY(), color.getZ());

	/*Pop them into a vector...*/
	m_linesBuffer.push_back(Origin);
	m_linesBuffer.push_back(Destination);
	m_ColorsBuffer.push_back(Color);
	m_ColorsBuffer.push_back(Color);
}

void CBulletDebugger::drawContactPoint(const btVector3 & PointOnB, const btVector3 & normalOnB, btScalar distance, int lifeTime, const btVector3 & color)
{
	btVector3 Min = PointOnB - btVector3(0.1f, 0.1f, 0.1f);
	btVector3 Max = PointOnB + btVector3(0.1f, 0.1f, 0.1f);;

	btVector3 Destination = PointOnB + (normalOnB * 2.0f);

	drawBox(Min, Max, color);
	drawLine(PointOnB, Destination, color);
}

void CBulletDebugger::reportErrorWarning(const char * warningString)
{
}

void CBulletDebugger::draw3dText(const btVector3 & location, const char * textString)
{
}

void CBulletDebugger::setDebugMode(int debugMode)
{
}

int CBulletDebugger::getDebugMode() const
{
	return 0;
}
