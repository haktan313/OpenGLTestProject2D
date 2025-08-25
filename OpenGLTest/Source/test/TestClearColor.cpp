
//TestClearColor.cpp
#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"

namespace test
{
	TestClearColor::TestClearColor() : clearColor{ 0.2f, 0.3f, 0.8f, 1.0f }
	{

	}
	TestClearColor::~TestClearColor()
	{

	}
	void TestClearColor::OnUpdate(float deltaTime)
	{

	}
	void TestClearColor::OnRender()
	{
		GLDebugCall(glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));
		GLDebugCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", clearColor);
	}
}