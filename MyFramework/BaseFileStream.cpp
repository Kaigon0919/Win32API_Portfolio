#include "stdafx.h"
#include "BaseFileStream.h"

BaseFileStream::BaseFileStream(const wchar_t * _fileName, const wchar_t * _flag)
{
	_wfopen_s(&m_File, _fileName, _flag);
}

BaseFileStream::~BaseFileStream()
{
	fclose(m_File);
}

void BaseFileStream::Seek(long offset, int _flag)
{
	if (m_File)
	{
		fseek(m_File, offset, _flag);
	}
}

void BaseFileStream::Write(void * _buffer, int _byteLength)
{
	if (!m_File)
	{
		return;
	}

	fwrite(_buffer, _byteLength, 1, m_File);
}

void BaseFileStream::Read(void * _buffer, int _bufferSize, int _readSize)
{
	if (!m_File)
	{
		return;
	}
	// ����ũ�Ⱑ ������ ������ ũ�⺸�� ũ�ٸ�
	_readSize = _readSize < _bufferSize ? _bufferSize : _readSize;

	fread_s(_buffer, _bufferSize, _readSize, 1, m_File);
}

void BaseFileStream::ReOpen(const wchar_t * _fileName, const wchar_t * _flag)
{
	_wfopen_s(&m_File, _fileName, _flag);
}
