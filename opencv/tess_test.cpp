#include <iostream>
#include <libgen.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
int usage(int argc, char *argv[])
{
    std::cout << "Usage: ./" << basename(argv[0]) << " -i image -o outputbase -l lang -d tessdatapath" << std::endl;
    return 0;
}

int ocr_tesseract(char *img, char *tessdata ="/usr/local/share/tessdata", char *lang="eng")
{
    char *outText;
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(tessdata, lang))
    {
        std::cerr << "Could not initialize tesseract.\n";
        return 1;
    }

    // Open input image with leptonica library
    Pix *image = pixRead(img);
    api->SetImage(image);

    // Get OCR result
    outText = api->GetUTF8Text();
    std::cout << outText << std::endl;

    // Destroy used object and release memory
    api->End();
    delete []outText;
    pixDestroy(&image);
    return 0;
}

int main ( int argc, char *argv[] )
{
   if (argc == 1)
   {
       usage(argc, argv);
       exit(-1);
   }
   ocr_tesseract(argv[1], argv[2], argv[3]);

#if 0
    char *outText;

    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init("/usr/local/share/tessdata/", "ly")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    Pix *image = pixRead("./js.tif");
    api->SetImage(image);
    // Get OCR result
    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);

    // Destroy used object and release memory
    api->End();
    delete [] outText;
    pixDestroy(&image);
#endif

    return 0;
}

