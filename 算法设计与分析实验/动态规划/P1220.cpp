#include<iostream>
#include<algorithm>
#include<climits>
#include<cstring>
using namespace std;
#define MAXN 55
int n,c;
//动态规划数组，dp[l][r][0]表示到达l处耗电量，dp[l][r][1]表示到达r处的最少耗电量
int dp[MAXN][MAXN][2];
//sum[l][r]表示在l--r之外，即1--(l-1)和(r+1)--n之间功率和
int sum_w[MAXN][MAXN];
int location[MAXN];
int w[MAXN];

//获取区间l--r之外的功率和函数
int getsum_w(int l,int r){
	int cost=0;
	for(int i=1;i<=l-1;i++){
		cost+=w[i];
	}
	for(int i=r+1;i<=n;i++){
		cost+=w[i];
	}
	return cost;
}
//初始化sum_w函数，初始化之后sum_w里面存储的是初始的各种功率和
void init_sum_w(){
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			sum_w[i][j] = getsum_w(i,j);
		}
	}
}


int main(){
	cin>>n>>c;
	memset(dp,127,sizeof(dp));//必须将dp初始化极大值，如果没有初始化，会因为随机值导致运算结果错误
	for(int i=1;i<=n;i++){
		cin>>location[i]>>w[i];
	}
	dp[c][c][0] = 0;dp[c][c][1] = 0;
	init_sum_w();
//状态转移方程
//dp[l][r][0]有两种可以到达方式，一种是l+1到l，一种是r到l。
//dp[l][r][0] = min(dp[l+1][r][0]+sum_w[l+1][r]*d(l+1,l),dp[l+1][r][1]+sum_w[l+1][r]*d(r,l))
	for(int len=2;len<=n;len++){
		for(int l=1;l+len-1<=n;l++){
			int r = l+len-1;
			int temp1 = dp[l+1][r][0]+(location[l+1]-location[l])*sum_w[l+1][r];
			int temp2 = dp[l+1][r][1]+(location[r]-location[l])*sum_w[l+1][r];
			dp[l][r][0] = min(temp1,temp2);
			int temp3 = dp[l][r-1][0]+(location[r]-location[l])*sum_w[l][r-1];
			int temp4 = dp[l][r-1][1]+(location[r]-location[r-1])*sum_w[l][r-1];
			dp[l][r][1] = min(temp3,temp4);
		}
	}
	cout<<min(dp[1][n][0],dp[1][n][1])<<endl;
	return 0;
}