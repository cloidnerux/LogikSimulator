#pragma once

#include <memory>
#include <cstring>

template<class T>
class RingBuffer
{
private:
	T * buffer;
	int currentPos;
	int size;
public:
	RingBuffer()
	{
		size = 1;
		buffer = new T[size];
		std::memset(buffer, 0, sizeof(T)*size);
		currentPos = 0;
	}

	//Size will be incrementet by 1
	RingBuffer(int Size)
	{
		size = Size + 1;			//We want 1 more element than specified, so a 0 element RingBuffer is still 1 element big
		buffer = new T[size];
		std::memset(buffer, 0, sizeof(T)*size);
		currentPos = 0;
	}

	RingBuffer(const RingBuffer * a)
	{
		size = a->size;
		buffer = new T[size];
		#ifdef _MSC_VER
		memcpy_s(buffer, size, a.buffer, size);
		#else
		std::memcpy(buffer, a.buffer, size);
		#endif
	}
	RingBuffer(const RingBuffer & a)
	{
		size = a.size;
		buffer = new T[size];
		#ifdef _MSC_VER
		memcpy_s(buffer, size, a.buffer, size);
		#else
		std::memcpy(buffer, a.buffer, size);
		#endif
	}

	~RingBuffer()
	{
		delete buffer;
	}

	//Get the first inserted element(size insertions back)
	T GetFirst()
	{
		return buffer[(currentPos + 1) % size];
	}

	//Get the last element instered
	T GetLast()
	{
		return buffer[currentPos];
	}
	void push_back(T elem)
	{
		currentPos++;
		currentPos %= size;
		buffer[currentPos] = elem;
	}
};
