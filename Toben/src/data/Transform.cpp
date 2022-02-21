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
	rotation = glm::rotate(rotation, glm::radians(amount), axis);
	UpdateModelMatrix();
}

void Transform::UpdateModelMatrix()
{
	glm::mat4 trans = glm::translate(glm::mat4(1), position);
	glm::mat4 rot = glm::toMat4(rotation);
	//glm::mat4 rot = glm::mat4(1);
	//modelMatrix = trans;
	modelMatrix = trans * rot;
	//modelMatrix = glm::mat4(1);
}