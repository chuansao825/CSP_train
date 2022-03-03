#include <iostream>
#include <vector>
#include <string.h>

using namespace std;


int findmax(int x,int y) {
	return x > y ? x : y;
}

int findmin(int x,int y) {
	return x < y ? x : y;
}



int main(void) {
	//读输入
	int n, L, r, t;
	cin >> n >> L >> r >> t;
	//二维数组
	vector<vector<int>> matrix(n+2,vector<int>(n+2,0));
	for (int i = 1; i < n+1; i++)
		for (int j = 1; j < n+1; j++)
			cin>>matrix[i][j];


	//算前缀和矩阵
	vector<vector<int>> b(n+2, vector<int>(n+2, 0));
	for(int i=1;i<n+1;i++)
		for (int j = 1; j < n+1; j++) {
			if (i == 1 && j == 1)
				b[i][j] = matrix[i][j];
			else if (i == 1)
				b[i][j] = b[i][j - 1] + matrix[i][j];
			else if (j == 1)
				b[i][j] = b[i - 1][j] + matrix[i][j];
			else
				b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + matrix[i][j];
		}


	//统计
	int result = 0;
	for(int i=1;i<n+1;i++)
		for (int j = 1; j < n+1; j++) {
			//子矩阵左上角坐标
			int i1 = findmax(i-r,1);
			int j1 = findmax(j-r,1);
			
			//子矩阵右下角坐标
			int i2 = findmin(i + r, n);
			int j2 = findmin(j + r, n);

			//用前缀和矩阵计算子矩阵的和
			int sum = b[i2][j2] - b[i2][j1 - 1] - b[i1 - 1][j2] + b[i1 - 1][j1 - 1];

			//平均值
			int num = (i2 - i1 + 1) * (j2 - j1 + 1);
			double mean = (double)sum / (double)num;

			if(mean <= t)
				result++;
		}
	cout << result << endl;
}










