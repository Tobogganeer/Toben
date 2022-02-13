#pragma once

#include <vector>
#include "../../vendor/glm/vec2.hpp"
#include "../../vendor/glm/vec3.hpp"
#include "../../vendor/glm/vec4.hpp"

#define ASSERT(x) if (!(x)) __debugbreak();

struct BufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSize(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_INT:			return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		case GL_UNSIGNED_SHORT:	return 2;
		}

		ASSERT(false);
		return 0;
	}
};

class BufferLayout
{
public:
	BufferLayout()
		:stride(0) {}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	//template<typename T>
	//void PushNormalized(unsigned int count)
	//{
	//	static_assert(false);
	//}

	inline const std::vector<BufferElement>& GetElements() const { return elements; }
	inline unsigned int GetStride() const { return stride; }

private:
	std::vector<BufferElement> elements;
	unsigned int stride;
};

template<>
inline void BufferLayout::Push<float>(unsigned int count)
{
	elements.push_back({ GL_FLOAT, count, false });
	stride += BufferElement::GetSize(GL_FLOAT) * count;
}

template<>
inline void BufferLayout::Push<unsigned int>(unsigned int count)
{
	elements.push_back({ GL_UNSIGNED_INT, count, false });
	stride += BufferElement::GetSize(GL_UNSIGNED_INT) * count;
}

template<>
inline void BufferLayout::Push<int>(unsigned int count)
{
	elements.push_back({ GL_INT, count, false });
	stride += BufferElement::GetSize(GL_INT) * count;
}

template<>
inline void BufferLayout::Push<unsigned char>(unsigned int count)
{
	elements.push_back({ GL_UNSIGNED_BYTE, count, false });
	stride += BufferElement::GetSize(GL_UNSIGNED_BYTE) * count;
}


template<>
inline void BufferLayout::Push<glm::vec3>(unsigned int count)
{
	count *= 3;
	elements.push_back({ GL_FLOAT, count, false });
	stride += BufferElement::GetSize(GL_FLOAT) * count;
}

template<>
inline void BufferLayout::Push<glm::u16vec2>(unsigned int count)
{
	count *= 2;
	elements.push_back({ GL_UNSIGNED_SHORT, count, true });
	stride += BufferElement::GetSize(GL_UNSIGNED_SHORT) * count;
}

template<>
inline void BufferLayout::Push<glm::u8vec4>(unsigned int count)
{
	count *= 4;
	elements.push_back({ GL_UNSIGNED_BYTE, count, true });
	stride += BufferElement::GetSize(GL_UNSIGNED_BYTE) * count;
}


/*

glm::vec3
glm::vec3
glm::u16vec2
glm::u8vec4

template<>
inline void BufferLayout::PushNormalized<unsigned char>(unsigned int count)
{
	elements.push_back({ GL_UNSIGNED_BYTE, count, true });
	stride += BufferElement::GetSize(GL_UNSIGNED_BYTE) * count;
}

template<>
inline void BufferLayout::PushNormalized<unsigned short>(unsigned int count)
{
	elements.push_back({ GL_UNSIGNED_SHORT, count, true });
	stride += BufferElement::GetSize(GL_UNSIGNED_SHORT) * count;
}
*/