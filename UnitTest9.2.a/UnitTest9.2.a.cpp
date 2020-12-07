#include "pch.h"
#include "CppUnitTest.h"
#include "../Project9.2.A/project9.2.a.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest92a
{
	TEST_CLASS(UnitTest92a)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int c;
			Student* p = new Student[5];
			p[0].prizv = "Pastukh";
			p[0].course = 1;
			p[0].grades_in_informatic = 5;
			p[1].prizv = "Petrov";
			p[1].course = 2;
			p[1].grades_in_informatic = 4;
			p[2].prizv = "Ivanov";
			p[2].course = 3;
			p[2].grades_in_informatic = 3;
			p[3].prizv = "Abramov";
			p[3].course = 4;
			p[3].grades_in_informatic = 2;
			p[4].prizv = "Karginov";
			p[4].course = 4;
			p[4].grades_in_informatic = 2;
			c = BinSearch(p, 5, "Ivanov",3,3);
			Assert::AreEqual(c, 2);
		}
	};
}
