#include "myFunction.h"

unsigned int Vertex::totalVertexNum_{};

Vertex::Vertex() :
	x_{ -1 + urd(gen) + urd(gen) }, y_{ -1 + urd(gen) + urd(gen) },
	size_{ 0.05f },
	red_{ urd(gen) }, green_{ urd(gen) }, blue_{ urd(gen) }
{
	totalVertexNum_++;
}

Vertex::Vertex(const float x, const float y) :
	x_{ x }, y_{ y },
	size_{ 0.05f },
	red_{ urd(gen) }, green_{ urd(gen) }, blue_{ urd(gen) }
{
	totalVertexNum_++;
}

Vertex::~Vertex() {
	totalVertexNum_--;
}

void Vertex::reset() {
	setPos(-1 + urd(gen) + urd(gen), -1 + urd(gen) + urd(gen));
	setSize(0.05f);
	setRgb(urd(gen), urd(gen), urd(gen));
}

void Vertex::setPos(const float x, const float y) {
	x_ = x;
	y_ = y;
}
void Vertex::setX(const float x) { x_ = x; }
void Vertex::setY(const float y) { y_ = y; }

void Vertex::setSize(const float s) { size_ = s; }

void Vertex::setRgb(const float r, const float g, const float b) {
	red_ = r; green_ = g; blue_ = b;
}
void Vertex::setRed(const float r) { red_ = r; }
void Vertex::setGreen(const float g) { green_ = g; }
void Vertex::setBlue(const float b) { blue_ = b; }

Square::Square() : Vertex()
{
	vboPositionVector_.resize(2);
	vboColorVector_.resize(2);
}

Square::Square(const float x, const float y) : Vertex(x, y) {
	vboPositionVector_.resize(2);
	vboColorVector_.resize(2);
}

Square::~Square() {
	totalSquareNum_--;
}

GLuint Square::initBuffer() {
	float position[]{
		// 첫번째 삼각형
		size_, size_, 0.0,		// 우상단
		size_, -size_, 0.0,		// 우하단
		-size_, size_, 0.0,		// 좌상단
		// 두번째 삼각형
		size_, -size_, 0.0,		// 우하단
		-size_, -size_, 0.0,	// 좌하단
		-size_, size_, 0.0
	};

	// VAO 객체 생성 및 바인딩
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	// VBO 객체 생성 및 바인딩
	glGenBuffers(1, vboPositionVector_.data());
	glBindBuffer(GL_ARRAY_BUFFER, vboPositionVector_.at(0));

	// position 데이터 입력
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, position, GL_STREAM_DRAW);

	// 현재 바인딩된 VBO를 attribute 지정 및 활성화
	// GLint positionAttribute = glGetAttribLocation();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
	glEnableVertexAttribArray(0);
	

}

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
