#include "pch.h"

GTEST_API_ int main(int argc, char** argv)
{
	std::cout << "Running main() test \n";
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}