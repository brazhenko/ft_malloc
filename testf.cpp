#include <sstream>
#include <string>
#include <iostream>

int main()
{
	float a;
	std::string s = "39.7341312";
	std::stringstream ss(s);
	ss >> a;
	printf("%f\n", a);
	std::cout << a << std::endl;
}
