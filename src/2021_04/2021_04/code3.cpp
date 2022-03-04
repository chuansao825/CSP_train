#include <iostream>
#include<string.h>
#include<string>
#include<vector>

using namespace std;

int N, Tdef, Tmax, Tmin;
string H;

//��ַ���е�һ��ip
struct node {
	//0:δ����,1�������䣬2����ռ�ã�3������
	int state;	
	//ռ���ߵ�������
	string owner;
	//����ʱ��
	int endt;
};
//��ַ��
struct node* pool;


//����pool,tΪ��ǰʱ��
void updatePool(int t) {
	for (int i = 1; i < N + 1; i++) {
		//�������
		if (pool[i].endt <= t) {
			//��ַ��״̬�Ǵ�����,�õ�ַ��״̬��Ϊδ���䣬��ռ������գ�����ʱ������
			if (pool[i].state == 1) {
				pool[i].state = 0;
				pool[i].owner = "";
				pool[i].endt = 0;
			}
			//��ַ��״̬��ռ�ã���ַ��״̬����ռ���Զ���Ϊ���ڣ��ҹ���ʱ������
			else if (pool[i].state == 2) {
				pool[i].state = 3;
				pool[i].endt = 0;
			}

		}
	}
}



//����Ƿ���ռ����Ϊ���������� IP ��ַ,�еĻ�����ip�����򷵻�0
int find0(string s) {
	for (int i = 1; i < N + 1; i++) {
		if (pool[i].owner == s)
			return i;
	}
	return 0;
}


//����С��״̬Ϊδ�����IP��ַ�������ڵĻ�����0
int find1() {
	for (int i = 1; i < N + 1; i++) {
		if (pool[i].state == 0)
			return i;
	}
	return 0;
}


//����С��״̬Ϊ���ڵ�IP��ַ�������ڵĻ�����0
int find2() {
	for (int i = 1; i < N + 1; i++) {
		if (pool[i].state == 3)
			return i;
	}
	return 0;

}


//�����µĹ���ʱ��,tΪ��ǰʱ��,endtΪ�����е�ednt
int getnewendt(int t,int endt) {
	int newendt;
	if (endt == 0)
		newendt = t + Tdef;
	else {
		if ((endt - t) > Tmax)
			newendt = t + Tmax;
		else if ((endt - t) < Tmin)
			newendt = t + Tmin;
		else
			newendt = endt;
	}

	return newendt;
}





int main(void) {
	//����������
	cin >> N >> Tdef >> Tmax >> Tmin>>H;
	//������
	int n;
	cin >> n;

	//������ַ��
	pool = new struct node[N+1];
	//��ʼ����ַ��
	for (int i = 0; i < N + 1; i++) {
		pool[i].endt = 0;
		pool[i].state = 0;
	}



	//����ı�������
	vector<string> output;


	//���δ���n������
	while (n--) {
		//ʱ��
		int t;
		//��������,��������,��������
		string host1, host2, type;
		//IP,����ʱ��
		int ip, endt;
		cin >> t >> host1 >> host2 >> type >> ip >> endt;


		//���ڴ���
		updatePool(t);



		//�жϽ��������Ƿ�Ϊ����������Ϊ *
		if (!(host2 == H || host2=="*")) {
			//�ж������Ƿ�Ϊ Request
			if (type != "REQ")
				continue;			
		}
		//���Ͳ��� Discover��Request ֮һ���򲻴���
		if (type != "DIS" && type != "REQ")
			continue;		
		//����������Ϊ *�������Ͳ��� Discover������������Ǳ������������� Discover���򲻴���
		if ((host2 == "*" && type != "DIS") || (host2 == H && type == "DIS"))
			continue;


		//����Discover ����
		if (type == "DIS") {
			//����Ƿ���ռ����Ϊ���������� IP ��ַ
			int tempip =find0(host1);
			//ѡȡ��С��״̬Ϊδ�����IP��ַ
			if (!tempip)
				tempip=find1();
			//ѡȡ��С��״̬Ϊ���ڵ� IP ��ַ
			if (!tempip)
				tempip = find2();
			if (!tempip)
				continue;

			//����IP��ַ״̬����Ϊ�����䣬ռ��������Ϊ��������
			pool[tempip].state = 1;
			pool[tempip].owner = host1;
			//���ù���ʱ��
			int newendt = getnewendt(t, endt);
			pool[tempip].endt = newendt;

			//����offer����
			string str = H + " " + host1 + " " + "OFR" + " " + to_string(tempip) + " " + to_string(newendt);
			output.push_back(str);
		}

		//����REQ����
		else if (type == "REQ") {
			//�����������Ƿ�Ϊ����
			if (host2 != H) {
				//�ҵ�ռ����Ϊ����������״̬Ϊ�����������IP��ַ
				for (int i = 1; i < N + 1; i++) {
					//����״̬����Ϊδ���䣬�������ռ���ߣ����������ʱ��
					if (pool[i].state == 1 && pool[i].owner == host1) {
						pool[i].state = 0;
						pool[i].owner = "";
						pool[i].endt = 0;
					}
				}

				continue;
			}

			//��鱨���е� IP ��ַ�Ƿ��ڵ�ַ���ڣ�����ռ����Ϊ��������
			if (!(ip >= 1 && ip <= N && pool[ip].owner == host1)) {
				//����NAK���ģ��������
				string str = H + " " + host1 + " " + "NAK" + " " + to_string(ip) + " " + to_string(0);
				output.push_back(str);
				continue;
			}

			//���� IP ��ַ��״̬����Ϊռ��
			pool[ip].state = 2;
			//���� IP ��ַ�Ĺ���ʱ��
			int newendt = getnewendt(t, endt);
			pool[ip].endt = newendt;

			//����ACK����
			string str = H + " " + host1 + " " + "ACK" + " " + to_string(ip) + " " + to_string(newendt);
			output.push_back(str);
		}

	}


	//������б���
	for (vector<string>::iterator i = output.begin(); i != output.end(); i++) {
		cout << *i << endl;
	}


	return 0;
}