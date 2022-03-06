#include<iostream>
#include<string.h>
#include<vector>
#define n_max 1000
#define f_max 100000
#define mod (int)(1e9+7)

using namespace std;



//�ϰ�������
int n;
//�ϰ�������
int pos[n_max + 1];
//dp[i]��ʾa[1]��a[i]�ķ�����
long long dp[n_max + 1];
//������
vector<int> v[f_max + 1];
//��־��
bool flag[f_max + 1];


//�����������������
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



//��x,y���ϰ�������Ϊ�Ȳ�������β��ֵ�����������Ļ��м��ֵȲ�����
long long cal(int x, int y) {
	long long count = 0;

	//���ϰ���ľ���
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
	//���
	Sieve();
	//��ʼ��pos
	memset(pos, 0, (n_max + 1) * sizeof(int));
	memset(dp, 0, (n_max + 1) * sizeof(long long));
	memset(flag, false, (f_max + 1) * sizeof(bool));
	//������
	input();


	//DP���
	dp[1] = 1;
	for (int i = 2; i <= n; i++) {
		//��flag�ָ�
		memset(flag, false, (f_max + 1) * sizeof(bool));
		for (int j = i - 1; j >= 1; j--) {
			dp[i] = (dp[i] + (dp[j] * cal(j, i)) % mod) % mod;
		}
	}

	cout << dp[n] << endl;

	return 0;
}



//
////�����㷨ƭ10�ְ汾
//#include<iostream>
//#include<string.h>
//#include<vector>
//
//
//using namespace std;
//
//
//
////�ϰ�������
//int n;
////�ϰ�������
//vector<int> pos;
////������
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
////��a����������,�Լ�����������ֵ
//int getFactor(int a) {
//	//���ö̳������������ֽ�
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
//	//ͳ�Ʋ�ͬ�������ĸ���
//	//cum���治ͬ�����ĸ���
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
//	//������������
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
//	//������
//	input();
//
//
//
//	//����
//	//n=2�����������ķ���
//	//���
//	if (n == 2) {
//		int d = pos[2] - pos[1];
//		cout << getFactor(d) - 1 << endl;
//	}
//
//
//	//n>2�����
//	if (n > 2) {
//
//	}
//
//
//
//	return 0;
//}