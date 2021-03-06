#include "../include/Camera.h"
#include "../include/Keyboard.h"
#include "../include/Mouse.h"
#include "../Imgui/imgui.h"
#include<string>
namespace bogong {
	class Mouse;
}
glm::mat4 bogong::Camera::GetProjection()
{
	return projection;
}
glm::mat4 bogong::Camera::GetView()
{
	return view;
}
bogong::FPCamera::FPCamera()
{
	projection = glm::perspective(glm::radians(45.0f), float(screenWidth) / float(screenHeight), 0.1f, 100.0f);
	view = lookAt(cameraPos, cameraPos + cameraFront, up);
}
void bogong::FPCamera::ClearMouse(const std::shared_ptr<Mouse>& mouse)
{
	prevMouseX = mouse->x;
	prevMouseY = mouse->y;
	currMouseX = mouse->x;
	currMouseY = mouse->y;
}
void bogong::FPCamera::Update(const std::shared_ptr<Keyboard>& kbd, const std::shared_ptr<Mouse>& mouse, float delta)
{
	float camSpeed =0.0f;
	if (kbd->isKeyPressed(KEY::KEY_SHIFT)) {
		camSpeed = 2.0f*delta;
	}
	else {
		camSpeed = cameraSpeed * delta;
	}

	if (kbd->isKeyPressed(KEY_W) || kbd->isKeyRepeating(KEY_W))
	{
		cameraPos += camSpeed * cameraFront;
	}
	if (kbd->isKeyPressed(KEY_S) || kbd->isKeyRepeating(KEY_S))
	{
		cameraPos -= camSpeed * cameraFront;
	}
	if (kbd->isKeyPressed(KEY_A) || kbd->isKeyRepeating(KEY_A))
	{
		cameraPos -= normalize(cross(cameraFront, up)) * camSpeed;
	}
	if (kbd->isKeyPressed(KEY_D) || kbd->isKeyRepeating(KEY_D))
	{
		cameraPos += normalize(cross(cameraFront, up)) * camSpeed;
	}
	prevMouseX = currMouseX;
	prevMouseY = currMouseY;
	currMouseX = mouse->x;
	currMouseY = mouse->y;
	float xoffset = currMouseX - prevMouseX;
	float yoffset = prevMouseY - currMouseY;

	std::string pos = "Pos X: " + std::to_string(cameraPos.x) + " Y: " + std::to_string(cameraPos.y)+ " Z: " + std::to_string(cameraPos.z);

	std::string frontpos = "Front X: " + std::to_string(cameraFront.x) + " Y: " + std::to_string(cameraFront.y) + " Z: " + std::to_string(cameraFront.z);

	if (debug) {
		ImGui::Begin("Camera debug.");
		ImGui::SetWindowPos(ImVec2(800, 0));
		ImGui::Text(pos.c_str());
		ImGui::Text(frontpos.c_str());
		ImGui::End();
	}
	xoffset = 0.05*xoffset;
	yoffset = 0.05*yoffset;
	yaw += xoffset;
	pitch += yoffset;
	pitch = glm::clamp(pitch, -89.0f, 89.0f);
	glm::vec3 direction;
	direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw))*cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
	view = lookAt(cameraPos, cameraPos + cameraFront, up);
}
