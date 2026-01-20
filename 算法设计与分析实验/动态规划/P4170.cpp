#include<iostream>
#include<string>
#include<algorithm>
#define MAXN 55
using namespace std;
//dp[i][j]表示区间i到j内最少涂色数
int dp[MAXN][MAXN];
int main(){
	string s;
	cin >> s;
	int n = s.size();
	s = " "+s;//下标从1开始
	//初始化长度为1的区间，当长度为1时只需要涂色1次
	for(int i=1;i<=n;i++){
		dp[i][i]=1;
	}
	//按区间从小到大开始涂色
	for(int len = 2;len<=n;len++){
		for(int i=1;i<=n-len+1;i++){
			int j = i+len-1;
			dp[i][j] = 1e9;//初始化每段为极大值
			for(int k=i;k<j;k++){
				dp[i][j] = min(dp[i][k]+dp[k+1][j],dp[i][j]);
			}
			//如果区间两端颜色相同，可以缩短区间长度进行优化
			if(s[i] == s[j]){
				dp[i][j] = min(dp[i][j],dp[i][j-1]);
			}
		}
	}
	cout<<dp[1][n]<<endl;
	return 0;
}