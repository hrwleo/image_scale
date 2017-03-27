#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include "cstringt.h"
#include "io.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;
using namespace cv;


vector<string> filenamesGlobal;

vector<string> getFilesName(string path){
	//文件句柄  
	long   hFile = 0;
	//文件信息  
	struct _finddata_t fileinfo;
	string p;
	vector<string>filenames;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFilesName(p.assign(path).append("\\").append(fileinfo.name));
			}
			else
			{
				filenames.push_back(fileinfo.name);  // 直接获取名字即可
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name));  
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	return filenames;
}

int main()
{
	char filePath[150] = "E:\\CAS-PEAL\\test_original";    //********************
	filenamesGlobal = getFilesName(filePath);

	for (int i = 0; i < 986913; i++)
	{
		char imgPath[150];
		strcpy(imgPath, filePath);
		strcat(imgPath, "\\");
		strcat(imgPath, filenamesGlobal[i].c_str());


		//    cvLoadImage( filename, -1 ); 默认读取图像的原通道数
		//    cvLoadImage( filename, 0 ); 强制转化读取图像为灰度图
		//    cvLoadImage( filename, 1 ); 读取彩色图
		IplImage * srcImg = cvLoadImage(imgPath, -1);
		IplImage *detImg = NULL;
		CvSize size;
		double scale1 = 0.1167;  //*******************
		double scale2 = 0.1146;
		//double scale = 0.39;
		/*size.width = srcImg->width*scale1;
		size.height = srcImg->height*scale2;*/
		size.width = 55;
		size.height = 55;
		//创建图片并缩放
		detImg = cvCreateImage(size, srcImg->depth, srcImg->nChannels);
		// ·CV_INTER_NN - 最近-邻居插补
		// ·CV_INTER_LINEAR - 双线性插值（默认方法）
		// ·CV_INTER_AREA - 像素面积相关重采样。当缩小图像时，该方法可以避免波纹的出现。当放大图像时，类似于方法CV_INTER_NN。
		// ·CV_INTER_CUBIC - 双三次插值。
		cvResize(srcImg, detImg, CV_INTER_LINEAR);
		//const char *srcWin = "image";//必须是const char*类型
		//const char *detWin = "scaled";
		////创建窗口
		//cvNamedWindow(srcWin, CV_WINDOW_AUTOSIZE);
		//cvNamedWindow(detWin, CV_WINDOW_AUTOSIZE);
		////在指定窗口中显示图像
		//cvShowImage(srcWin, srcImg);
		//cvShowImage(detWin, detImg);
		////等待按键事件
		//cvWaitKey(); 
		const char *saveName = filenamesGlobal[i].c_str();
		//保存图片
		char imgSavePath[150] = "E:\\CAS-PEAL\\test_original_scale\\";  //********************
		strcat(imgSavePath, filenamesGlobal[i].c_str());

		cvSaveImage(imgSavePath, detImg);    //不要忘记释放 否则会内存泄露

		printf("ok");
		/*cvDestroyWindow(srcWin);
		cvDestroyWindow(detWin);*/
		cvReleaseImage(&srcImg);
		cvReleaseImage(&detImg);
	}

	return 0;
}