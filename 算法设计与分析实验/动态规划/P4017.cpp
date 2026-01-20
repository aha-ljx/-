#include<iostream>
#include<vector>
#include<queue>
#define MAXN 5005
using namespace std;
const int MOD = 80112002;
int num[MAXN];//存储每个节点的食物链的条数
vector<int>p[MAXN];//图p保存点与点之间关系
queue<int>q;//队列q用于拓扑排序
int in[MAXN],out[MAXN];//用于记录每个节点的入度和出度
int ans;
int n,m;
int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		out[x]++;in[y]++;
		p[x].push_back(y);//建立一条边
	}
	for(int i=1;i<=n;i++){
		if(!in[i]){//寻找入度为0的点，初始化食物链条数
			num[i] = 1;
			q.push(i);//把i入队开始拓扑排序 
		}
	}
	//拓扑排序，寻找入度为0的点，不断更新入度，并且把入度为0的点入队。
	while(!q.empty()){
		int current = q.front();//取出当前排序到的点
		q.pop();//弹出当前点
		int len = p[current].size();//更新当前点相关的点的入度
		for(int i=0;i<len;i++){
			int next = p[current][i];
			--in[next];
			num[next] = (num[current]+num[next])%MOD;//类似于动态规划，食物链条数等于入度点条数加上当前条数
			if(!in[next]) q.push(p[current][i]);//若下一个点入度为0，进入队列
		}
	}
	for(int i=1;i<=n;i++){
		if(!out[i]){//累加所有出度为0的点
			ans=(num[i]+ans)%MOD;
		}
	}
	cout<<ans;
	return 0;
}
