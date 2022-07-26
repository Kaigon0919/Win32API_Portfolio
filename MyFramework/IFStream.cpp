#include "stdafx.h"
#include "IFStream.h"

IFStream::IFStream(const wchar_t * _filePath) : BaseFileStream(_filePath,L"rb")
{
}

IFStream::~IFStream()
{
}

void IFStream::Read(void * _buffer, int _bufferByteSize, int _readByteSize)
{
	BaseFileStream::Read(_buffer, _bufferByteSize, _readByteSize);
}

void IFStream::Seek(long _offset, int _flag)
{
	BaseFileStream::Seek(_offset, _flag);
}
void IFStream::ReOpen(const wchar_t * _fileName)
{
	BaseFileStream::ReOpen(_fileName, L"rb");
}
