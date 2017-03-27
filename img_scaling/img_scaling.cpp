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
	//�ļ����  
	long   hFile = 0;
	//�ļ���Ϣ  
	struct _finddata_t fileinfo;
	string p;
	vector<string>filenames;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮  
			//�������,�����б�  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFilesName(p.assign(path).append("\\").append(fileinfo.name));
			}
			else
			{
				filenames.push_back(fileinfo.name);  // ֱ�ӻ�ȡ���ּ���
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


		//    cvLoadImage( filename, -1 ); Ĭ�϶�ȡͼ���ԭͨ����
		//    cvLoadImage( filename, 0 ); ǿ��ת����ȡͼ��Ϊ�Ҷ�ͼ
		//    cvLoadImage( filename, 1 ); ��ȡ��ɫͼ
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
		//����ͼƬ������
		detImg = cvCreateImage(size, srcImg->depth, srcImg->nChannels);
		// ��CV_INTER_NN - ���-�ھӲ岹
		// ��CV_INTER_LINEAR - ˫���Բ�ֵ��Ĭ�Ϸ�����
		// ��CV_INTER_AREA - �����������ز���������Сͼ��ʱ���÷������Ա��Ⲩ�Ƶĳ��֡����Ŵ�ͼ��ʱ�������ڷ���CV_INTER_NN��
		// ��CV_INTER_CUBIC - ˫���β�ֵ��
		cvResize(srcImg, detImg, CV_INTER_LINEAR);
		//const char *srcWin = "image";//������const char*����
		//const char *detWin = "scaled";
		////��������
		//cvNamedWindow(srcWin, CV_WINDOW_AUTOSIZE);
		//cvNamedWindow(detWin, CV_WINDOW_AUTOSIZE);
		////��ָ����������ʾͼ��
		//cvShowImage(srcWin, srcImg);
		//cvShowImage(detWin, detImg);
		////�ȴ������¼�
		//cvWaitKey(); 
		const char *saveName = filenamesGlobal[i].c_str();
		//����ͼƬ
		char imgSavePath[150] = "E:\\CAS-PEAL\\test_original_scale\\";  //********************
		strcat(imgSavePath, filenamesGlobal[i].c_str());

		cvSaveImage(imgSavePath, detImg);    //��Ҫ�����ͷ� ������ڴ�й¶

		printf("ok");
		/*cvDestroyWindow(srcWin);
		cvDestroyWindow(detWin);*/
		cvReleaseImage(&srcImg);
		cvReleaseImage(&detImg);
	}

	return 0;
}