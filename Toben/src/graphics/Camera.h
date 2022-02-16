#pragma once

#include "../vendor/glm/mat4x4.hpp"
#include "../vendor/glm/vec3.hpp"

class Camera
{
public:
	const float FOV = 75;
	const float NEAR_PLANE = 0.1f;
	const float FAR_PLANE = 1000.0f;

	glm::mat4 projMatrix;
	glm::mat4 viewMatrix;

	glm::vec3 position;
	glm::vec3 forward;

	Camera();
	void UpdateProjection();
	void Update();

	void Translate(glm::vec3& translation);
	void Rotate(float amount, glm::vec3& axis);
};