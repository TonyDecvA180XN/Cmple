#include "main.h"
#include <iostream>
#include "fmt/format.h"

int main()
{
	std::cout << "Hello world." << std::endl;
	int a = 5;
	fmt::print("The factorial of {} is {}.", a, factorial(a));
	return 0;
}
