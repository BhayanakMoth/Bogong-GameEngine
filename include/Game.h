#pragma once

#include "Shaders.hpp"
#include <memory>
#include "Keyboard.h"
#include "Mouse.h"
#include "Surface.hpp"
#include "Camera.h"
#include "Globals.h"
#include "Models/Cube.hpp"
#include "Models/Plane.hpp"
#include <GLFW/glfw3.h>
#include "Rendering/SampleScene.hpp"
#include "Screen.hpp"
namespace bogong {
	class Game
	{
	private:
		std::shared_ptr<Screen> scr;
		std::shared_ptr<SampleScene> scene;
		std::shared_ptr<FPCamera> camera;
		bool isMouseEnabled = false;
		bool canToggle = true;
		float timer = 0.0f;
		glm::vec3 clearcolor= glm::vec3(0.0f,0.0,0.f);
		public:
		Game();
		void Update(const std::shared_ptr<bogong::Keyboard> &kbd, const std::shared_ptr<bogong::Mouse>& mouse, float delta,GLFWwindow * window);
		void Draw(float delta) const;
	};
}
