
//Test2DTexture.h
#pragma once
#include "TestBase.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include <memory>

namespace test
{
	class Test2DTexture : public TestBase
	{
	public:
		Test2DTexture();

		void OnRender() override;
		void OnImGuiRender() override;
	private:
		glm::mat4 projection, view;
		glm::vec3 position, position2;
		float r, increment;
		bool bUseTexture = true;

		std::unique_ptr<VertexArray> vertexArrayRef;
		std::unique_ptr<VertexBuffer> vertexBufferRef;
		std::unique_ptr<VertexBufferLayout> vertexbufferlayoutref;
		std::unique_ptr<IndexBuffer> indexBufferRef;
		std::unique_ptr<Shader> shaderRef;
		std::unique_ptr<Texture> textureRef;
	};
}


