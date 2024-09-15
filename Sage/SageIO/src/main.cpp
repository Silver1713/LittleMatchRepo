#include "PNG_Container.hpp"
#define STB_IMAGE_IMPLEMENTATION
const char* image = "../SageIO/image/image_asset.png";

int main()
{

    PNG_Container ctn(image);
    ctn.load_data();
    return 0;
}