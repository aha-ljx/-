#include<iostream>
#define MAXN 105
using namespace std;
int A[MAXN][MAXN]; //A存储矩阵
int M[MAXN][MAXN];//M负责记忆化搜索
int F[MAXN][MAXN];//F标记点
int ans;
int R,C;
//dx,dy表示四个不同方向
int dx[5] = {0,0,0,1,-1};
int dy[5] = {0,1,-1,0,0};
//每个点都可以从上下左右四个位置过来dp[i][j] = max(dp[i-1][j],dp[i+1][j],dp[i][j-1],dp[i][j+1])+1
int dp(int i,int j){
	//记忆化搜索
	if(F[i][j]) return M[i][j];
	F[i][j] = 1;//标记当前位置已经搜素
	for(int m=1;m<=4;m++){
		int x = dx[m]+i;
		int y = dy[m]+j;
		//当越界时候直接返回
		if(x>0&&y>0&&x<=R&&y<=C&&A[x][y]<A[i][j]){
			dp(x,y);
			M[i][j] = max(M[i][j],M[x][y]+1);
		}
	}
	return M[i][j];
}
int main(){
	cin>>R>>C;
	for(int i=1;i<=R;i++){
		for(int j=1;j<=C;j++){
			cin>>A[i][j];
		}
	}
	for(int i=1;i<=R;i++){
		for(int j=1;j<=C;j++){
			ans = max(ans,dp(i,j));
		}
	}
	cout<<ans+1;
	return 0;
}