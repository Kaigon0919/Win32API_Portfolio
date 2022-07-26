#include "stdafx.h"
#include "OFStream.h"

OFStream::OFStream(const wchar_t * _filePath) : BaseFileStream(_filePath,L"wb")
{
}

OFStream::~OFStream()
{
}

void OFStream::Write(void * _buffer, int _byteSize)
{
	BaseFileStream::Write(_buffer, _byteSize);
}
