
//TestColorCube.cpp
#include "TestColorCube.h"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <Renderer.h>
#include <imgui/imgui.h>

namespace test
{
	TestColorCube::TestColorCube() : r(0.2f), r2(0.4f), direction(1), direction2(1), increment(0.005f), increment2(0.005f), position(200.0f, 200.0f, 0.0f), position2(500.f, 500.f, 0.0f), bUseTexture(false)
	{
		float positions[] = {
			-50.f, -50.f,// Position (x, y) 
			 50.f, -50.f,
			 50.f,	50.f,
			-50.f,  50.f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		vertexArrayRef = std::make_unique<VertexArray>();
		vertexBufferRef = std::make_unique<VertexBuffer>(positions, sizeof(positions));

		vertexbufferlayoutref = std::make_unique<VertexBufferLayout>();
		vertexbufferlayoutref->Push<float>(2); // Position
		vertexArrayRef->AddBuffer(*vertexBufferRef, *vertexbufferlayoutref);

		indexBufferRef = std::make_unique<IndexBuffer>(indices, 6);

		projection = glm::ortho(0.f, 1280.f, 0.f, 720.f, -1.f, 1.f); // Orthographic projection matrix
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // View matrix to move the camera

		shaderRef = std::make_unique<Shader>("Resources/Shaders/Basic.shader");
		shaderRef->Bind();
		shaderRef->SetUniform4f("colorRef", 0.2f, 0.3f, 0.8f, 1.0f);

		shaderRef->SetUniform1b("useTexture", bUseTexture);
		vertexArrayRef->Unbind();
		vertexBufferRef->Unbind();
		indexBufferRef->Unbind();
		shaderRef->Unbind();
	}
	void TestColorCube::OnRender()
	{
		GLDebugCall(glClearColor(0.f, 0.f, 0.f, 1.f));
		GLDebugCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		{
			r += increment * direction;
			if (r >= 1.0f)
			{
				r = 1.f;
				direction = -1; // Reverse direction when reaching max value
			}
			else if (r <= 0.0f)
			{
				r = 0.0f;
				direction = 1;
			}

			glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
			glm::mat4 mvp = projection * view * model;

			renderer.Draw(*vertexArrayRef, *indexBufferRef, *shaderRef);
			shaderRef->SetUniformMat4f("MVPref", mvp);
			shaderRef->SetUniform4f("colorRef", r, 0.3f, 0.8f, 1.0f);
		}
		{
			r2 += increment2 * direction2;
			if (r2 >= 1.0f)
			{
				r2 = 1.f;
				direction2 = -1; // Reverse direction when reaching max value
			}
			else if (r2 <= 0.0f)
			{
				r2 = 0.0f;
				direction2 = 1;
			}
			glm::mat4 model = glm::translate(glm::mat4(1.0f), position2);
			glm::mat4 mvp = projection * view * model;

			renderer.Draw(*vertexArrayRef, *indexBufferRef, *shaderRef);
			shaderRef->SetUniformMat4f("MVPref", mvp);
			shaderRef->SetUniform4f("colorRef", r2, 0.3f, 0.8f, 1.0f);
		}

	}
	void TestColorCube::OnImGuiRender()
	{
		ImGui::SliderFloat3("translation", &position.x, 0.0f, 1280.0f);
		ImGui::SliderFloat3("translation2", &position2.x, 0.0f, 1280.0f);
		ImGui::SliderFloat("Speed for Color Change", &increment, 0.001f, 0.1f);
		ImGui::SliderFloat("Speed for Color Change2", &increment2, 0.001f, 0.1f);
	}
}