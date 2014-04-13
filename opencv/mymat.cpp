int main ( int argc, char *argv[] )
{
    Mat image;
    if (argc != 2 ) {
        cout << argc << "no image data\n";
        return -1;
    }
    image = imread(argv[1], 1);
    Mat c (image, Rect(10, 10, 100, 100));
    int sz[3] = {2,2,2};
    //Mat E (200, 200, CV_8UC3, Scalar(0,0,255));
    Mat M = Mat(3, 3, CV_8UC3);
    randu(M, Scalar::all(0), Scalar::all(255));
    cout << image.channels() << endl;
    cout << image.depth() << endl;
    cout << image.cols << ", " << image.rows << endl;
    

    Mat J;
    uchar table[256];
    int divideWith = 10;

    for (int i = 0; i < 256; ++i)
       table[i] = (uchar)(divideWith * ((255-i)/divideWith));

    Mat lookUpTable(1, 256, CV_8U);
    uchar* p = lookUpTable.data;
    for( int i = 0; i < 256; ++i)
        p[i] = table[i];
    LUT(image, lookUpTable, J);

    //namedWindow("Display Image",CV_WINDOW_AUTOSIZE);
    imshow("display image",J);
    waitKey(0);

    return 0;
}

