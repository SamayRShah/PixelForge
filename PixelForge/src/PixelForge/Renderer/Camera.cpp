#include "pfpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
namespace PixelForge {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top) 
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), 
		  m_ViewMatrix(1.0f), m_Position({0, 0, 0}) {
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top) {
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix() {
		glm::mat4 m4Trans = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(m4Trans);

		// ** OpenGL is column major ** 
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}