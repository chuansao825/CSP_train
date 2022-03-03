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
	//������
	int n, L, r, t;
	cin >> n >> L >> r >> t;
	//��ά����
	vector<vector<int>> matrix(n+2,vector<int>(n+2,0));
	for (int i = 1; i < n+1; i++)
		for (int j = 1; j < n+1; j++)
			cin>>matrix[i][j];


	//��ǰ׺�;���
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


	//ͳ��
	int result = 0;
	for(int i=1;i<n+1;i++)
		for (int j = 1; j < n+1; j++) {
			//�Ӿ������Ͻ�����
			int i1 = findmax(i-r,1);
			int j1 = findmax(j-r,1);
			
			//�Ӿ������½�����
			int i2 = findmin(i + r, n);
			int j2 = findmin(j + r, n);

			//��ǰ׺�;�������Ӿ���ĺ�
			int sum = b[i2][j2] - b[i2][j1 - 1] - b[i1 - 1][j2] + b[i1 - 1][j1 - 1];

			//ƽ��ֵ
			int num = (i2 - i1 + 1) * (j2 - j1 + 1);
			double mean = (double)sum / (double)num;

			if(mean <= t)
				result++;
		}
	cout << result << endl;
}










