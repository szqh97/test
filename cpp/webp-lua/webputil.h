#include <webp/encode.h>
#include <string>
#include "metadata.h"

using namespace std;

int ReadYUV(const uint8_t* const data, size_t data_size, WebPPicture* const pic);

int ReadPicture(const string* file_name, WebPPicture* const pic, int keep_alpha, Metadata* const metatdata );
