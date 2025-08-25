
//TestClearColor.h
#pragma once
#include "TestBase.h"


namespace test
{
	class TestClearColor : public test::TestBase
	{
	public:
		TestClearColor();
		~TestClearColor() override;
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override; 
	private:
		float clearColor[4];
	};
}

