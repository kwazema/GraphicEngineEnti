#include "precompiledHeader.h"
#include "Camera.h"

Camera::Camera() {

}

void Camera::updateViewProjection() {
	view_proj = view * proj;

}

void Camera::lookAt(glm::vec3 new_eye, glm::vec3 new_target, glm::vec3 new_up_aux) {
	pos = new_eye;
	target = new_target;
	
	view = glm::lookAt(pos, target, new_up_aux);
	updateViewProjection();
}

void Camera::setProjectionParams(
	float new_fov_vertical_radians,
	float new_aspect_ratio,
	float new_z_min,
	float new_z_max
) {

	fov_vertical_radians = new_fov_vertical_radians;
	aspect_ratio = new_aspect_ratio;
	z_min = new_z_min;
	z_max = new_z_max;

	
	proj = glm::perspective(
		fov_vertical_radians,
		aspect_ratio,
		z_min,
		 z_max
	);
	updateViewProjection();

}