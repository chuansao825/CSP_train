#include <iostream>
#include <string.h>
using namespace std;




int main(void) {
	int n, m, l;

	//读输入
	cin >> n >> m >> l;

	//读数组
	int** matrix = new int* [n];
	for (int i = 0; i < n; i++) {
		matrix[i] = new int[m];
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> matrix[i][j];
		

	//统计
	int* level = new int[l];
	//初始化为0
	memset(level, 0, l*sizeof(int));
	for (int i=0;i<n;i++)
		for (int j = 0; j < m; j++) {
			int index = matrix[i][j];
			level[index]++;
		}


	//输出
	for (int i = 0; i < l - 1; i++)
		cout << level[i] << " ";
	cout << level[l - 1] << endl;


	return 0;
}