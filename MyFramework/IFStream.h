#pragma once
#include "BaseFileStream.h"
class IFStream : protected BaseFileStream
{
public:
	IFStream(const wchar_t* _filePath );
	~IFStream();

public:	
	void Read(void* _buffer, int _bufferByteSize, int _readByteSize);
	void Seek(long _offset, int _Mode = SEEK_CUR);
	void ReOpen(const wchar_t * _fileName);
	inline bool IsOpen()const
	{
		return BaseFileStream::IsOpen();
	}
};

