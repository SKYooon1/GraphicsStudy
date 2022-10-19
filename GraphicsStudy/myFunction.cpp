#include "myFunction.h"

Vertex::Vertex() : x_{ -1 + urd(gen) + urd(gen) }, y_{ -1 + urd(gen) + urd(gen) },
size_{ 0.05f }, red_{ urd(gen) }, green_{ urd(gen) }, blue_{ urd(gen) }
{
	totalVertexNum_++;
}
Vertex::~Vertex()
{
	totalVertexNum_--;
}

int Vertex::totalVertexNum_{};

void Vertex::reset()
{
	setPos(-1 + urd(gen) + urd(gen), -1 + urd(gen) + urd(gen));
	setSize(0.01f);
	setRgb(urd(gen), urd(gen), urd(gen));
}

void Vertex::setPos(const float x, const float y)
{
	x_ = x;
	y_ = y;
}

void Vertex::setSize(const float s)
{
	size_ = s;
}

void Vertex::setRgb(const float r, const float g, const float b)
{
	red_ = r; green_ = g; blue_ = b;
}

char* readFile(const char*& fileName)
{
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
