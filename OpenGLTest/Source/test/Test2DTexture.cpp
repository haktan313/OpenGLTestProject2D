
// Test2DTexture.cpp
#include "Test2DTexture.h"
#include <GL/glew.h>
#include <VertexArray.h>
#include <VertexBuffer.h>
#include <IndexBuffer.h>
#include <Shader.h>
#include <Texture.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <imgui/imgui.h>

namespace test
{
	Test2DTexture::Test2DTexture() : position(200.0f, 200.0f, 0.0f), position2(500.f, 500.f, 0.0f), r(0.0f), increment(0.005f), bUseTexture(true)
	{
		float positions[] = {
		-50.f, -50.f, 0.0f,  0.0f, // Position (x, y) and Texture Coordinates (u, v)
		 50.f, -50.f, 1.0f,  0.0f,
		 50.f,	50.f, 1.0f,  1.0f,
		-50.f,  50.f, 0.0f,  1.0f,
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Enable blending for transparency

		vertexArrayRef = std::make_unique<VertexArray>();
		vertexBufferRef = std::make_unique<VertexBuffer>(positions, sizeof(positions));

		vertexbufferlayoutref = std::make_unique<VertexBufferLayout>();
		vertexbufferlayoutref->Push<float>(2);// Position
		vertexbufferlayoutref->Push<float>(2);// Texture Coordinates (u, v)
		vertexArrayRef->AddBuffer(*vertexBufferRef, *vertexbufferlayoutref);

		indexBufferRef = std::make_unique<IndexBuffer>(indices, 6);

		projection = glm::ortho(0.f, 1280.f, 0.f, 720.f, -1.f, 1.f);// Orthographic projection matrix mean 2d camera range
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));// View matrix to move the camera. First parameter is the matrix you want to apply. With current value we are giving no transformation

		shaderRef = std::make_unique<Shader>("Resources/Shaders/Basic.shader");
		shaderRef->Bind();

		textureRef = std::make_unique<Texture>("res/texture/tottenham.png");
		textureRef->Bind();
		shaderRef->SetUniform1i("textureBase", 0);

		shaderRef->SetUniform1b("useTexture", bUseTexture);
		vertexArrayRef->Unbind();
		vertexBufferRef->Unbind();
		indexBufferRef->Unbind();
		shaderRef->Unbind();
	}
	void Test2DTexture::OnRender()
	{
		GLDebugCall(glClearColor(0.f,0.f,0.f,1.f));
		GLDebugCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
			glm::mat4 mvp = projection * view * model;
			shaderRef->SetUniformMat4f("MVPref", mvp);
			renderer.Draw(*vertexArrayRef, *indexBufferRef, *shaderRef);
		}
		{
			glm::mat4 model2 = glm::translate(glm::mat4(1.0f), position2);
			glm::mat4 mvp2 = projection * view * model2;
			shaderRef->SetUniformMat4f("MVPref", mvp2);
			renderer.Draw(*vertexArrayRef, *indexBufferRef, *shaderRef);
		}
		
	}
	void Test2DTexture::OnImGuiRender()
	{
		ImGui::SliderFloat3("translation", &position.x, 0.0f, 1280.0f);
		ImGui::SliderFloat3("translation2", &position2.x, 0.0f, 1280.0f);

	}
} 