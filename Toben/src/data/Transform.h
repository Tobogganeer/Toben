#pragma once

#include "../vendor/glm/mat4x4.hpp"
#include "../vendor/glm/vec3.hpp"
#include "../vendor/glm/gtc/quaternion.hpp"
#include "../vendor/glm/gtx/quaternion.hpp"

class Transform
{
public:
	glm::vec3 position;
	glm::quat rotation;
	glm::mat4 modelMatrix;

	Transform(glm::vec3 position = { 0, 0, 0 }, glm::vec3 rotation = { 0, 0, 0 });

	void Translate(glm::vec3& translation);
	void Rotate(float amount, glm::vec3& axis);
private:
	void UpdateModelMatrix();
};

