// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Win64Window.h"

#include <GLFW/glfw3.h>

#include "Core/IO/Log.h"
#include "Core/WindowManager.h"
#include "Core/Application.h"

#include "Event/EventSystem.h"
#include "Renderer/Renderer.h"

namespace Iceblur
{
	bool Win64Window::Create(const WindowProps& props)
	{
		//TODO: Create Graphics API struct for storing GLFW_CONTEXT_VERSION_X for example.

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		//GLFW window hints

		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);

		glfwWindowHint(GLFW_MAXIMIZED, props.Maximized);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//Set window properties

		GLFWmonitor* monitor = nullptr;

		if (props.Fullscreen)
		{
			monitor = glfwGetPrimaryMonitor();
		}

		int refreshRate = props.RefreshRate;
		if (props.UseMonitorRefreshRate)
		{
			refreshRate = mode->refreshRate;
		}

		glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);

		int width = props.resolution.GetWidth();
		int height = props.resolution.GetHeight();

		if (props.UseMonitorResolution)
		{
			width = mode->width;
			height = mode->height;
		}

		m_Window = glfwCreateWindow(width, height, props.Title.c_str(), monitor, nullptr);

		if (!m_Window)
		{
			ICE_ERROR(Error::EFailed::WINDOW_CREATION);
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(m_Window);

		//Should we enable VSync?
		glfwSwapInterval(!props.enableVSync);

		//Example callback for testing, more will be implemented soon
		glfwSetWindowMaximizeCallback(m_Window, &WindowMaximizeCallback);
		glfwSetWindowSizeCallback(m_Window, &WindowSizeCallback);
		glfwSetCursorPosCallback(m_Window, &MousePositionCallback);

		return true;
	}

	void Win64Window::WindowMaximizeCallback(GLFWwindow* window, int maximized)
	{
		WindowMaximizeEvent event(WindowManager::GetStaticWindow(window), maximized);
		EventSystem::Dispatch(event);
	}

	void Win64Window::WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		/* When we resize the window, we want to re-render everything to the screen.
		 * Note that we should not call Application::OnUpdate() as this also calls
		 * other functions that are not relevant for rendering.
		 * One other problem is that Application::OnUpdate also calls
		 * glfwSwapBuffers(), which is quite laggy currently.
		*/

		//Application::GetInstance()->ForceUpdate();
		Renderer::Update(Application::GetInstance()->GetDeltaTime());

		WindowResizeEvent event(WindowManager::GetStaticWindow(window), width, height);
		EventSystem::Dispatch(event);
	}

	void Win64Window::MousePositionCallback(GLFWwindow* window, double x, double y)
	{
		MouseMoveEvent event((float) x, (float) y);
		EventSystem::Dispatch(event);
	}
}
