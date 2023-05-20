#ifndef _IMAGE_H_
#define _IMAGE_H_

class Image{
    public:
        Image() {};
        ~Image();
        void load(const char* filename, int &width, int &height, int &nrComponents, int channel ) ;


        unsigned char* getData() const { return _imgData; }
    protected:
        unsigned char* _imgData;
};
#endif