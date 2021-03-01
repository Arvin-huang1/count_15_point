#include "cal_15_point_area.h"

/*****************������*****************/
Rect g_rect;
bool g_DrawFlag = false;
RNG g_rng(12345);

//���λ��ƺ���
void DrawRectangle(Mat& img, Rect box)
{
	//rectangle������
	//tl���Ͻǵĵ㣬br���½ǵĵ�
	//Scalar������ɫ������Ϊ3ͨ��
	//g_rng.uniform(0, 255)�����ɫ
	rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255),
		g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}
//���ص�����
void on_MouseHandle(int event, int x, int y, int flag, void* param)
{
	Mat& image = *(Mat*)param;
	switch (event)
	{
	case EVENT_MOUSEMOVE://�ƶ�
		if (g_DrawFlag) {
			//���㣬g_rect���=��굱ǰλ������-g_rect���Ͻǵ�����
			g_rect.width = x - g_rect.x;
			g_rect.height = y - g_rect.y;
		}
		break;
	case EVENT_LBUTTONDOWN://�������
		g_DrawFlag = true;
		//����g_rect�ĳ�ʼֵ��ͬһ����
		g_rect = Rect(x, y, 0, 0);
		break;
	case EVENT_LBUTTONUP://���̧��
		g_DrawFlag = false;
		//��g_rect���С��0
		//��ʼ��xy������Ϊ��С�����Ͻǵĵ�
		//���ȡ����ֵ
		if (g_rect.width < 0) {
			g_rect.x += g_rect.width;
			g_rect.width *= -1;
		}
		if (g_rect.height < 0) {
			g_rect.y += g_rect.height;
			g_rect.height *= -1;
		}
		//������
		DrawRectangle(image, g_rect);
		break;
	}
}
//���ص��¼�
void MouseEvent()
{
	//׼������
	g_rect = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 600, CV_8UC3), tempImage;
	srcImage = imread("D:\\work\\Projects\\MFCApplication1\\MFCApplication1\\res\\test.jpg");
	srcImage.copyTo(tempImage);
	g_rect = Rect(-1, -1, 0, 0);
	//srcImage = Scalar::all(0);

	//�����������ص�����
	namedWindow("Win");
	setMouseCallback("Win", on_MouseHandle, (void*)&srcImage);

	//�滭
	while (1)
	{
		srcImage.copyTo(tempImage);
		if (g_DrawFlag) {
			DrawRectangle(tempImage, g_rect);
		}
		imshow("Win", tempImage);
		if (waitKey(10) == 27) 
		{
			imwrite("D:/install/1028.jpg", tempImage);
			break;//ESC �˳�
		}
	}
}






int main()
{
	
	//int area = 0;
	//area = cal_15_point_area("res1.txt","res1.png","src.png");
	//cout << "area:" << area << "mm" << endl;
	//system("pause");
	MouseEvent();
	return 0;
}


