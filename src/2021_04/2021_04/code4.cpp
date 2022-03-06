#include<iostream>
#include<string.h>
#include<vector>
#define n_max 1000
#define f_max 100000
#define mod (int)(1e9+7)

using namespace std;



//障碍物数量
int n;
//障碍物坐标
int pos[n_max + 1];
//dp[i]表示a[1]到a[i]的方案数
long long dp[n_max + 1];
//因数表
vector<int> v[f_max + 1];
//标志表
bool flag[f_max + 1];


//打表，求所有数的因数
void Sieve() {
	for (int i = 1; i <= f_max; i++) {
		for (int j = i; j <= f_max; j += i) {
			v[j].push_back(i);
		}
	}
}



void input() {
	cin >> n;
	for (int i = 1; i < n + 1; i++) {
		cin >> pos[i];
	}
}



//以x,y两障碍的坐标为等差数列首尾的值，计算这样的话有几种等差数列
long long cal(int x, int y) {
	long long count = 0;

	//两障碍间的距离
	int d = pos[y] - pos[x];
	for (vector<int>::iterator j = v[d].begin(); j != v[d].end(); j++) {
		int factor = *j;
		if (!flag[factor]) {
			if (factor != d)
				count++;
			flag[factor] = true;
		}
	}
	return count;
}



int main(void) {
	//打表
	Sieve();
	//初始化pos
	memset(pos, 0, (n_max + 1) * sizeof(int));
	memset(dp, 0, (n_max + 1) * sizeof(long long));
	memset(flag, false, (f_max + 1) * sizeof(bool));
	//读输入
	input();


	//DP求解
	dp[1] = 1;
	for (int i = 2; i <= n; i++) {
		//将flag恢复
		memset(flag, false, (f_max + 1) * sizeof(bool));
		for (int j = i - 1; j >= 1; j--) {
			dp[i] = (dp[i] + (dp[j] * cal(j, i)) % mod) % mod;
		}
	}

	cout << dp[n] << endl;

	return 0;
}



//
////蛮力算法骗10分版本
//#include<iostream>
//#include<string.h>
//#include<vector>
//
//
//using namespace std;
//
//
//
////障碍物数量
//int n;
////障碍物坐标
//vector<int> pos;
////方案数
//int plan = 0;
//
//
//void input() {
//	cin >> n;
//	pos = vector<int>(n + 1, -1);
//	for (int i = 1; i < n + 1; i++) {
//		cin >> pos[i];
//	}
//}
//
//
//
//
////求a的因数个数,以及所有因数的值
//int getFactor(int a) {
//	//先用短除法进行因数分解
//	vector<int> array;
//	while (a > 1) {
//		for (int i = 2; i <= a; i++) {
//			while (a % i == 0) {
//				a = a / i;
//				array.push_back(i);
//			}
//		}
//	}
//
//	//统计不同的质数的个数
//	//cum储存不同质数的个数
//	vector<int> cum;
//	int before=0;
//	for (int i = 0; i < array.size(); i++) {
//		if (array[i] != before) {
//			cum.push_back(1);
//		}
//		else {
//			cum.back()++;
//		}
//
//		before = array[i];
//	}
//
//	//计算因数个数
//	int num = 1;
//	for (int i = 0; i < cum.size(); i++) {
//		num = num * (cum[i] + 1);
//	}
//
//	return num;
//}
//
//
//
//
//
//int main(void) {
//	//读输入
//	input();
//
//
//
//	//暴搜
//	//n=2，用求因数的方法
//	//间距
//	if (n == 2) {
//		int d = pos[2] - pos[1];
//		cout << getFactor(d) - 1 << endl;
//	}
//
//
//	//n>2的情况
//	if (n > 2) {
//
//	}
//
//
//
//	return 0;
//}