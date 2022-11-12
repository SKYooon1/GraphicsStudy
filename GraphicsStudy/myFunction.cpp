#include "myFunction.h"

char* readFile(const char*& fileName) {
	std::ifstream in;
	in.open(fileName);

	if (!in.is_open())
	{
		std::cerr << "The file is not exist." << std::endl;
		return {};
	}

	in.seekg(0, std::ios::end);

	const int size = in.tellg();

	char* buf = new char[size];

	in.seekg(0, std::ios::beg);

	in.read(buf, size);

	return buf;
}

void convertCoordinateWinToGl(const int x, const int y, float& ox, float& oy,
	const int width, const int height)
{
	const float w{ static_cast<float>(width) };
	const float h{ static_cast<float>(height) };
	ox = { (static_cast<float>(x) - (w / 2.0f)) * (1.0f / (w / 2.0f)) };
	oy = { -(static_cast<float>(y) - (h / 2.0f)) * (1.0f / (h / 2.0f)) };
}
