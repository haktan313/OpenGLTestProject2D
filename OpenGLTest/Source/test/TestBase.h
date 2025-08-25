
//TestBase.h
#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <string>

namespace test
{
	class TestBase
	{
	public:
		TestBase() {}
		virtual ~TestBase() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};
	class TestMenu : public TestBase
	{
	public:
		TestMenu(TestBase*& currentTestPointer);

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Registering test: " << name << std::endl;
			tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	private:
		TestBase*& currentTest;
		std::vector<std::pair<std::string, std::function<TestBase*()>>> tests;
	};
}