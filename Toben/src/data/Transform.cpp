#include "Transform.h"

#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtx/rotate_vector.hpp"

Transform::Transform(glm::vec3 position, glm::vec3 rotation)
	:position(position), rotation(rotation)
{
	UpdateModelMatrix();
}

void Transform::Translate(glm::vec3& translation)
{
	position += translation;
	UpdateModelMatrix();
}

void Transform::Rotate(float amount, glm::vec3& axis)
{
	rotation = glm::rotate(rotation, amount, axis);
	UpdateModelMatrix();
}

void Transform::UpdateModelMatrix()
{
	//glm::mat4 trans = glm::translate(glm::mat4(0), position);
	//glm::mat4 rot = glm::toMat4(glm::quat(rotation));

	//modelMatrix = trans * rot;
	modelMatrix = glm::mat4(1);
}