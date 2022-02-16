#include "Camera.h"
#include "Graphics.h"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtx/rotate_vector.hpp"

Camera::Camera()
{
	float aspectRatio = Display::GetWidth() / Display::GetHeight();
	projMatrix = glm::perspective(FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);

	position = glm::vec3(0, 0, 0);
	forward = glm::vec3(0, 0, 1);

	viewMatrix = glm::lookAt(position, position + forward, glm::vec3(0, 1, 0));
}

void Camera::UpdateProjection()
{
	float aspectRatio = Display::GetWidth() / Display::GetHeight();

	projMatrix = glm::perspective(FOV, aspectRatio, NEAR_PLANE, FAR_PLANE);
}

void Camera::Update()
{
	viewMatrix = glm::lookAt(position, position + forward, glm::vec3(0, 1, 0));
}

void Camera::Translate(glm::vec3& translation)
{
	position += translation;
}

void Camera::Rotate(float amount, glm::vec3& axis)
{
	forward = glm::rotate(forward, amount, axis);
}