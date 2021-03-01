#include "cal_15_point_area.h"
/*
	����˵��:ͳ��wafer�����������15�����
	@param
	file_path:		������������ļ�·��
	img_path:		����ͼƬ�ļ�·��
	save_img_path:	��������ͼƬ·��
	@return
	area: �����������15�����������λmm^2��area/25Ϊͳ�������������15�ĸ�����
*/
int cal_15_point_area(string file_path, string img_path, string save_img_path) {
	ifstream infile;
	//ofstream outfile; //���txt
	//��ȡ����txt�ļ�ÿ�е�6�����ݣ�����px_x��px_yΪ��Ҫ�Ŀ�����������
	float _1, px_x, px_y, _4, _5, _6;
	double step_x, step_y;			//�������ؾ���
	int grid[20][20] = { 0 };		//���ÿ����������ĸ���
	int index_i = 0, index_j = 0;	//��������
	int countAll = 0;				//ͳ�ƿ�������
	int count = 0;					//ͳ�ƿ�������15���������
	int area = 0;					//��������15���������������λmm^2
	int pt_circle[4] = { 0 };		//�ֱ�洢wafer��Ӿ��ε����(x_min,y_min),�յ�(x_max,y_max)
	Vec3b vec3b_white = { 255,255,255 };//��ɫ
	bool flag=true;
	
	Mat src = imread(img_path);
	
	//cout << src.size() << endl;
	
	//�����������أ�ȷ��Բ��λ��
	for (int i = 0; i < src.cols; i++)
	{
		for (int j = 0; j < src.rows; j++)
		{
			//����ֵ
			if (flag) 
			{
				if (src.at<Vec3b>(j, i) == vec3b_white) 
				{
					pt_circle[0] = i;
					pt_circle[1] = j;
					pt_circle[2] = i;
					pt_circle[3] = j;
					flag = false;
					
				}
			}
			//��ȡ��Ӿ�������
			if (src.at<Vec3b>(j, i) == vec3b_white)
			{
				if (i < pt_circle[0]) 
				{
					pt_circle[0] = i;
				}
				if (j < pt_circle[1])
				{
					pt_circle[1] = j;
				}
				if (i > pt_circle[2])
				{
					pt_circle[2] = i;
				}
				if (j > pt_circle[3])
				{
					pt_circle[3] = j;
				}

			}
		}
	}
	/*
	//��ӡͼƬ��Ӿ�������
	cout << "(" << pt_circle[0] << "," << pt_circle[1] << ")" << "\t" 
		 << "(" << pt_circle[2] << "," << pt_circle[3] << ")" <<endl;
	*/

	infile.open(file_path.data());			//���ļ����������ļ��������� 
	//outfile.open("point.txt", ios::out);	//����ļ�
	assert(infile.is_open());				//��ʧ��,�����������Ϣ,����ֹ��������

	//�������ؾ���
	step_x = (pt_circle[2] - pt_circle[0]) / 20.0;
	step_y = (pt_circle[3] - pt_circle[1]) / 20.0;

	//��ȡ�������꣬��������
	while (!infile.eof())
	{
		infile >> _1 >> px_x >> px_y >> _4 >> _5 >> _6;//��ȡһ������

		index_i = int((px_x-pt_circle[0]) / (step_x));
		index_j = int((px_y-pt_circle[1]) / (step_y));
		//cout << "index_i: " << index_i << "index_j: " << index_j << endl;
		grid[index_i][index_j] ++;
		countAll++;
	}


	//����ÿ������
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			//cout << grid[i][j] << endl;
			//outfile << "(" << i << "," << j << ")" << "\t" << grid[i][j] << endl;
			if (grid[i][j] >= 15) {
				rectangle(src, Point(int(i*step_x+pt_circle[0]), int(j*step_y+pt_circle[1])),
						Point(int((i + 1)*step_x + pt_circle[0]), int((j + 1)*step_y + pt_circle[1])),
						Scalar(0, 0, 255), 3, LINE_8, 0);
				count++;
			}
			else {
				rectangle(src, Point(int(i*step_x + pt_circle[0]), int(j*step_y + pt_circle[1])),
					Point(int((i + 1)*step_x + pt_circle[0]), int((j + 1)*step_y + pt_circle[1])),
					Scalar(0, 255, 0), 3, LINE_8, 0);
			}

		}
	}
	infile.close();
	//outfile.close();
	//cout << "countAll: " << countAll << endl;
	//cout << "count: " << count << endl;
	area = count * 25;//�����������λmm^2
	imwrite(save_img_path, src);
	//imshow("src", src);
	//waitKey(0);
	//destroyAllWindows();
	return area;
}

