#include<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>

using namespace std;

cv::Mat makeMask(int rows,int cols, int white_start_col, int white_end_col)
{
    using namespace cv;
    Mat zeros = Mat::zeros(rows, cols, CV_8UC1);
    Mat ones = Mat::ones(rows, white_end_col- white_start_col, CV_8UC1);
    ones = ones*255;

    ones.copyTo(zeros(Rect(white_start_col, 0, white_end_col - white_start_col, rows)));

    return zeros;
}


cv::Mat panaromaImage()
{
    using namespace cv;

    Mat back = imread("Cube/Back.png");
    Size d_size = back.size();

    Mat front, left, right, top, bottom;
    resize(imread("Cube/Front.png"),front,d_size);
    resize(imread("Cube/Left.png"),left,d_size);
    resize(imread("Cube/Right.png"),right,d_size);
    resize(imread("Cube/Top.png"),top,d_size);
    resize(imread("Cube/Bottom.png"),bottom,d_size);

    Rect boundingBox(0,0,d_size.width*4, d_size.height*3);

    detail::MultiBandBlender multiband;

    multiband.prepare(boundingBox);

    multiband.feed(back,makeMask(back.rows,back.cols,0,back.cols),Point(d_size.width,d_size.height));

    multiband.feed(left,makeMask(left.rows,left.cols,0,left.cols),Point(0,d_size.height));

    multiband.feed(right,makeMask(right.rows,right.cols,0,right.cols),Point(d_size.width*2,d_size.height));
    multiband.feed(front,makeMask(front.rows,front.cols,0,front.cols),Point(d_size.width*3,d_size.height));

    multiband.feed(top,makeMask(top.rows,top.cols,0,top.cols),Point(d_size.width,0));
    multiband.feed(bottom,makeMask(bottom.rows,bottom.cols,0,bottom.cols),Point(d_size.width,d_size.height*2));

    Mat output, outputMask;
    multiband.blend(output, outputMask);

    output.convertTo(output,CV_8UC3);

    namedWindow( "Display window", WINDOW_NORMAL );
    imshow("Display window",output);


    waitKey(0);

    return output;

}

int main()
{
   cv::Mat output = panaromaImage();

   cv::imwrite("Output.png",output);
  return 0;

}
