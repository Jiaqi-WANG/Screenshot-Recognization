#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;


void main(void)
{
	namedWindow("Template");
	Mat Template = imread("E:/images/4.jpg");  //direction to your template picture
	imshow("Template", Template);

	namedWindow("Image");
	Mat image = imread("E:/images/3.jpg");  //direction to your source image
	imshow("image", image);


	int rows = Template.rows;
	int cols = Template.cols;
	int summin = 10000000000;
	int ix, jx;

	Mat TemplateGray, imageGray;
	//grayscale
	cvtColor(Template, TemplateGray, COLOR_BGR2GRAY);  
	cvtColor(image, imageGray, COLOR_BGR2GRAY);

	//compare the value difference between the template and each template-sizes part in source image to find out the lowest value
	for (int i = 0; i < (imageGray.rows - rows); i++) {
		for (int j = 0; j < (imageGray.cols - cols); j++) {
			int sum = 0;
			Rect rect(j, i, cols, rows);
			Mat capteur = imageGray(rect);
			for (int x = 0; x < rows; x++) {
				for (int y = 0; y < cols; y++) {
					Scalar iGPixel = capteur.at<uchar>(x, y);
					Scalar TGPixel = TemplateGray.at<uchar>(x, y);
					sum += abs(iGPixel[0] - TGPixel[0]);

				}

			}

			if (sum < summin) {
				summin = sum;
				ix = i;
				jx = j;
			}

		}

	}

	//show the lowest value part with a green rectangle
	Rect r(jx, ix, cols, rows);
	rectangle(image, r, Scalar(0, 255, 0));

	imshow("image", image);

	waitKey(0);
}


