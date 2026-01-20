#include<iostream>
#include<cstdio>
#include<cstring>
//maxn要大于50000
#define maxn 50010
using namespace std;
int L,M,N;
int rock[maxn];

//判断是否需要移走石头，并且根据移走石头的数目判断是否是合法最短距离。
bool judge(int distance){
	int moverocks = 0;
	int i = 0;
	int now = 0;  //需要加一个now来判断当前石头位置，因为当移走石头后位置序号差不再是1
	bool re;
	while(i < N+1){
		i++;
		re = true;
		if(rock[i] - rock[now] < distance){ //如果当前距离小于假定的最短跳跃距离，移除石头
			moverocks++;
		}
		else{//否则更新当前石头位置
			now = i;
		}
	}
	if(moverocks > M){
		re = false;
	}
	return re;
}

int main(){
	cin>>L>>N>>M;
	for(int i=1;i<=N;i++){
		cin>>rock[i];
	}
	rock[N+1] = L;
	int left = 1; //左边界是1
	int right = L;
	int ans = 0;
	int mid = 0;
	while(left <= right){
		mid = (left+right)/2;
		if(judge(mid)){//如果当前距离通过，就在右侧寻找更大距离，前提是排好序的数组
			ans = mid;
			left = mid+1;
		}
		else{//没有通过就在左侧寻找
			right = mid-1;
		}
	}
	cout << ans << endl;
	return 0;
}