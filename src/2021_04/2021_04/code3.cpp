#include <iostream>
#include<string.h>
#include<string>
#include<vector>

using namespace std;

int N, Tdef, Tmax, Tmin;
string H;

//地址池中的一个ip
struct node {
	//0:未分配,1：待分配，2：被占用，3：过期
	int state;	
	//占有者的主机名
	string owner;
	//过期时刻
	int endt;
};
//地址池
struct node* pool;


//更新pool,t为当前时刻
void updatePool(int t) {
	for (int i = 1; i < N + 1; i++) {
		//处理过期
		if (pool[i].endt <= t) {
			//地址的状态是待分配,该地址的状态变为未分配，且占用者清空，过期时刻清零
			if (pool[i].state == 1) {
				pool[i].state = 0;
				pool[i].owner = "";
				pool[i].endt = 0;
			}
			//地址的状态是占用，地址的状态会由占用自动变为过期，且过期时刻清零
			else if (pool[i].state == 2) {
				pool[i].state = 3;
				pool[i].endt = 0;
			}

		}
	}
}



//检查是否有占用者为发送主机的 IP 地址,有的话返回ip，否则返回0
int find0(string s) {
	for (int i = 1; i < N + 1; i++) {
		if (pool[i].owner == s)
			return i;
	}
	return 0;
}


//找最小的状态为未分配的IP地址，不存在的话返回0
int find1() {
	for (int i = 1; i < N + 1; i++) {
		if (pool[i].state == 0)
			return i;
	}
	return 0;
}


//找最小的状态为过期的IP地址，不存在的话返回0
int find2() {
	for (int i = 1; i < N + 1; i++) {
		if (pool[i].state == 3)
			return i;
	}
	return 0;

}


//计算新的过期时刻,t为当前时刻,endt为报文中的ednt
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
	//读参数输入
	cin >> N >> Tdef >> Tmax >> Tmin>>H;
	//报文数
	int n;
	cin >> n;

	//创建地址池
	pool = new struct node[N+1];
	//初始化地址池
	for (int i = 0; i < N + 1; i++) {
		pool[i].endt = 0;
		pool[i].state = 0;
	}



	//输出的报文序列
	vector<string> output;


	//依次处理n条报文
	while (n--) {
		//时刻
		int t;
		//发送主机,接收主机,报文类型
		string host1, host2, type;
		//IP,过期时刻
		int ip, endt;
		cin >> t >> host1 >> host2 >> type >> ip >> endt;


		//过期处理
		updatePool(t);



		//判断接收主机是否为本机，或者为 *
		if (!(host2 == H || host2=="*")) {
			//判断类型是否为 Request
			if (type != "REQ")
				continue;			
		}
		//类型不是 Discover、Request 之一，则不处理
		if (type != "DIS" && type != "REQ")
			continue;		
		//若接收主机为 *，但类型不是 Discover，或接收主机是本机，但类型是 Discover，则不处理
		if ((host2 == "*" && type != "DIS") || (host2 == H && type == "DIS"))
			continue;


		//处理Discover 报文
		if (type == "DIS") {
			//检查是否有占用者为发送主机的 IP 地址
			int tempip =find0(host1);
			//选取最小的状态为未分配的IP地址
			if (!tempip)
				tempip=find1();
			//选取最小的状态为过期的 IP 地址
			if (!tempip)
				tempip = find2();
			if (!tempip)
				continue;

			//将该IP地址状态设置为待分配，占用者设置为发送主机
			pool[tempip].state = 1;
			pool[tempip].owner = host1;
			//设置过期时刻
			int newendt = getnewendt(t, endt);
			pool[tempip].endt = newendt;

			//发送offer报文
			string str = H + " " + host1 + " " + "OFR" + " " + to_string(tempip) + " " + to_string(newendt);
			output.push_back(str);
		}

		//处理REQ报文
		else if (type == "REQ") {
			//检查接收主机是否为本机
			if (host2 != H) {
				//找到占用者为发送主机且状态为待分配的所有IP地址
				for (int i = 1; i < N + 1; i++) {
					//将其状态设置为未分配，并清空其占用者，清零其过期时刻
					if (pool[i].state == 1 && pool[i].owner == host1) {
						pool[i].state = 0;
						pool[i].owner = "";
						pool[i].endt = 0;
					}
				}

				continue;
			}

			//检查报文中的 IP 地址是否在地址池内，且其占用者为发送主机
			if (!(ip >= 1 && ip <= N && pool[ip].owner == host1)) {
				//发送NAK报文，处理结束
				string str = H + " " + host1 + " " + "NAK" + " " + to_string(ip) + " " + to_string(0);
				output.push_back(str);
				continue;
			}

			//将该 IP 地址的状态设置为占用
			pool[ip].state = 2;
			//设置 IP 地址的过期时刻
			int newendt = getnewendt(t, endt);
			pool[ip].endt = newendt;

			//发送ACK报文
			string str = H + " " + host1 + " " + "ACK" + " " + to_string(ip) + " " + to_string(newendt);
			output.push_back(str);
		}

	}


	//输出所有报文
	for (vector<string>::iterator i = output.begin(); i != output.end(); i++) {
		cout << *i << endl;
	}


	return 0;
}