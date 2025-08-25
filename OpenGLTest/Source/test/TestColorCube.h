
//TestColorCube.h
#pragma once
#include "TestBase.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <memory>

namespace test
{
	class TestColorCube : public TestBase
	{
		public:
		TestColorCube();
		
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		glm::mat4 projection, view;
		float r,r2, increment, increment2;
		int direction, direction2;// 1 for increasing, -1 for decreasing
		glm::vec3 position, position2;
		bool bUseTexture = false;

		std::unique_ptr<VertexArray> vertexArrayRef;
		std::unique_ptr<VertexBuffer> vertexBufferRef;
		std::unique_ptr<VertexBufferLayout> vertexbufferlayoutref;
		std::unique_ptr<IndexBuffer> indexBufferRef;
		std::unique_ptr<Shader> shaderRef;
	};
}


