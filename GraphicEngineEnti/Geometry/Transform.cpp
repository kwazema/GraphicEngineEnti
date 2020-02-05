#include "precompiledHeader.h"
#include "Transform.h"


glm::mat4 Transform::asMatrix() const
{
	glm::mat4 mat = glm::identity<glm::mat4>();
	return glm::scale(mat, glm::vec3(scale))
		* glm::translate(mat, pos)
		* rot
		;
}
Transform::Transform()
{
	rot = glm::identity<glm::mat4>();
	pos = glm::vec3(0, 0, 0);
}
glm::vec3 Transform::getFront() const {
	glm::mat4 inverted = glm::inverse(asMatrix()); 
	return glm::normalize(glm::vec3(inverted[2]));
}

glm::vec3 Transform::getLeft() const {
	glm::mat4 inverted = glm::inverse(asMatrix());
	return glm::normalize(glm::vec3(inverted[0]));
}

glm::vec3 Transform::getUp() const
{
	glm::mat4 inverted = glm::inverse(asMatrix());
	
	return glm::normalize(glm::vec3(inverted[1]));
}

void Transform::setEulerAngles(float yaw, float pitch, float roll) {


	rot = glm::yawPitchRoll(yaw, pitch, roll);

}

glm::vec3& Transform::getEulerAngles()
{
	glm::vec3 euler(0.0f, 0.0f, 0.0f);
	glm::eulerAngleXYX(euler.x, euler.y, euler.z);

	return euler;
}





float Transform::getDeltaYawToAimTo(glm::vec3 p) const {
	glm::vec3 pos_to_p = p - pos;
	float amount_of_front = glm::dot(getFront(), pos_to_p);
	float amount_of_left = glm::dot(getLeft(), pos_to_p);
	return atan2(amount_of_left, amount_of_front);
}

bool Transform::isInCone(glm::vec3 p, float half_cone) const {
	return fabsf(getDeltaYawToAimTo(p)) < half_cone;
}