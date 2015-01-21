#ifndef DATABUFFER_H
#define DATABUFFER_H

#include <cstdlib>

namespace SMPP
{
    class DataBuffer
    {
    public:
        DataBuffer();
        DataBuffer(size_t size);
        DataBuffer(const DataBuffer& rhs);
        DataBuffer& operator=(const DataBuffer& rhs);
        ~DataBuffer();

        void Alloc(size_t size);
        size_t Size() const;
        unsigned char *Data();
        const unsigned char *Data() const;
        void Clear();

    private:
        void Release();

        size_t size_;
        unsigned char* data_;
    };
}
#endif // DATABUFFER_H
