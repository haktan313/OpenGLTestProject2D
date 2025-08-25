
//TestBase.cpp
#include "TestBase.h"
#include "imgui/imgui.h"

namespace test
{
	TestMenu::TestMenu(TestBase*& currentTestPointer) : currentTest(currentTestPointer)
	{

	}
	void TestMenu::OnImGuiRender()
	{
		for(auto& test : tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				currentTest = test.second();
			}
		}
	}
}