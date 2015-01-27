#include "DataBuffer.h"
#include <cstring>

namespace SMPP
{
    DataBuffer::DataBuffer() : size_(0), data_(0)
    {
    }

    DataBuffer::DataBuffer(size_t size) : size_(size), data_(0)
    {
        Alloc(size_);
    }

    DataBuffer::DataBuffer(const DataBuffer &rhs)
    {
        Release();
        Alloc(rhs.Size());
        memcpy(data_, rhs.Data(), Size());
    }

    DataBuffer& DataBuffer::operator=(const DataBuffer& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }

        Release();
        Alloc(rhs.Size());
        memcpy(data_, rhs.Data(), Size());

        return *this;
    }


    DataBuffer::~DataBuffer()
    {
        Release();
    }

    void DataBuffer::Alloc(size_t size)
    {
        Release();
        data_ = new unsigned char[size];
        size_ = size;
        Clear();
    }

    void DataBuffer::Release()
    {
        if (NULL != data_)
        {
            delete [] data_;
            data_ = NULL;
        }
    }

    size_t DataBuffer::Size() const
    {
        return size_;
    }

    unsigned char* DataBuffer::Data()
    {
        return data_;
    }

    const unsigned char* DataBuffer::Data() const
    {
        return data_;
    }

    void DataBuffer::Clear()
    {
        bzero(data_, size_);
    }

    DataBuffer operator+(const DataBuffer& b1, const DataBuffer& b2)
    {
        DataBuffer res(b1.Size() + b2.Size());

        unsigned char* data = res.Data();
        memcpy(data, b1.Data(), b1.Size());
        memcpy(data + b1.Size(), b2.Data(), b2.Size());

        return res;
    }
}
