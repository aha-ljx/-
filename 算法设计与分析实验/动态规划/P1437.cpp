#include<iostream>
#include<cstring>
#include<algorithm>
#define MAXN 55
#define MAXM 1280
using namespace std;
int n,m;
int a[MAXN][MAXN];
int sum[MAXN][MAXN];
int dp[MAXN][MAXN][MAXM];

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n-i+1;j++){
			cin>>a[i][j];
			sum[i][j] = sum[i-1][j]+a[i][j];
		}
	}
	for(int j=1;j<=n;j++){
		for(int i=0;i<=n;i++){
			for(int k=i;k<=m;k++){
				for(int t=0;t<=i+1;t++){
					dp[i][j][k] = max(dp[i][j][k],dp[t][j-1][k-i]+sum[i][j]);
				}
			}
		}
	}
	int ans = max(dp[1][n][m],dp[0][n][m]);
	cout<<ans;
	return 0;
}