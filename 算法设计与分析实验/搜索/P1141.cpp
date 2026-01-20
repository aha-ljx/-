//dfs算法求解
#include<iostream>
#include<string>
#define MAXN 1005
#define MAXM 100005
using namespace std;
int n,m;
int visited[MAXN][MAXN];//存储访问对象,不是来标记是否被访问，而是表示当前坐标是第几组数组
int ans[MAXM];//存储结果
int mig[MAXN][MAXN];//存储迷宫
int dx[] = {-1,1,0,0};
int dy[] = {0,0,1,-1};
void dfs(int x,int y,int currenti,int currentmig){
	//如果当前坐标越界或者已经访问过或者当前迷宫的值不合规定就会直接返回
	if(x>n || x<1 || y<1 || y>n || visited[x][y]!=-1 || mig[x][y]!=currentmig) return;
	visited[x][y] = currenti;
	ans[currenti]++;
	for(int i=0;i<4;i++){
		int nx = x+dx[i];
		int ny = y+dy[i];
		dfs(nx,ny,currenti,!currentmig);
	}
}

int main(){
	cin>>n>>m;
	string s;
	for(int i=1;i<=n;i++){
		cin>>s;
		for(int j=1;j<=n;j++){
			mig[i][j] = s[j-1]-'0';
		}
	}
	//将visited初始化为-1
	for(int i=0;i<MAXN;i++){
		for(int j=0;j<MAXN;j++){
			visited[i][j] = -1;
		}
	}
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		if(visited[x][y]==-1){
			dfs(x,y,i,mig[x][y]);
		}else{
			ans[i] = ans[visited[x][y]];//如果输入的坐标已经访问过了，直接输出结果
		}
	}
	for(int i=1;i<=m;i++){
		cout<<ans[i]<<endl;
	}
	return 0;
}