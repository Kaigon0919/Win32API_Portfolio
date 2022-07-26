#pragma once
#include "BaseFileStream.h"
class OFStream : public BaseFileStream
{
public:
	OFStream(const wchar_t * _filePath);
	~OFStream();
public:
	void Write(void * _buffer, int _byteSize);
};

