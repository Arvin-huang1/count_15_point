#include "cal_15_point_area.h"
/*
	函数说明:统计wafer网格颗粒大于15的面积
	@param
	file_path:		输入颗粒坐标文件路径
	img_path:		输入图片文件路径
	save_img_path:	保存网格图片路径
	@return
	area: 网格颗粒大于15的总面积，单位mm^2，area/25为统计网格颗粒大于15的个数。
*/
int cal_15_point_area(string file_path, string img_path, string save_img_path) {
	ifstream infile;
	//ofstream outfile; //输出txt
	//读取颗粒txt文件每行的6个数据，其中px_x、px_y为需要的颗粒像素坐标
	float _1, px_x, px_y, _4, _5, _6;
	double step_x, step_y;			//网格像素距离
	int grid[20][20] = { 0 };		//存放每个网格颗粒的个数
	int index_i = 0, index_j = 0;	//网格索引
	int countAll = 0;				//统计颗粒个数
	int count = 0;					//统计颗粒大于15的网格个数
	int area = 0;					//颗粒大于15的网格总面积，单位mm^2
	int pt_circle[4] = { 0 };		//分别存储wafer外接矩形的起点(x_min,y_min),终点(x_max,y_max)
	Vec3b vec3b_white = { 255,255,255 };//白色
	bool flag=true;
	
	Mat src = imread(img_path);
	
	//cout << src.size() << endl;
	
	//遍历所有像素，确定圆的位置
	for (int i = 0; i < src.cols; i++)
	{
		for (int j = 0; j < src.rows; j++)
		{
			//赋初值
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
			//获取外接矩形坐标
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
	//打印图片外接矩形坐标
	cout << "(" << pt_circle[0] << "," << pt_circle[1] << ")" << "\t" 
		 << "(" << pt_circle[2] << "," << pt_circle[3] << ")" <<endl;
	*/

	infile.open(file_path.data());			//将文件流对象与文件连接起来 
	//outfile.open("point.txt", ios::out);	//输出文件
	assert(infile.is_open());				//若失败,则输出错误消息,并终止程序运行

	//网格像素距离
	step_x = (pt_circle[2] - pt_circle[0]) / 20.0;
	step_y = (pt_circle[3] - pt_circle[1]) / 20.0;

	//读取颗粒坐标，划分网格
	while (!infile.eof())
	{
		infile >> _1 >> px_x >> px_y >> _4 >> _5 >> _6;//读取一行数据

		index_i = int((px_x-pt_circle[0]) / (step_x));
		index_j = int((px_y-pt_circle[1]) / (step_y));
		//cout << "index_i: " << index_i << "index_j: " << index_j << endl;
		grid[index_i][index_j] ++;
		countAll++;
	}


	//遍历每个网格
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
	area = count * 25;//返回面积，单位mm^2
	imwrite(save_img_path, src);
	//imshow("src", src);
	//waitKey(0);
	//destroyAllWindows();
	return area;
}

