#include<iostream>
#include<queue>
#define MAXN 500
using namespace std;
char a[MAXN][MAXN];//玉米地
int visited[MAXN][MAXN];//标记是否访问过
int ans[MAXN][MAXN];//记录时间
queue<pair<int,int>> q;//bfs需要的队列
pair<int,int> slide[26][2];
int slide_cnt[26];
int N,M;
//四个方向
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
int main(){
	cin>>N>>M;
	int beginx,beginy;
	int endx,endy;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=M;j++){
			cin>>a[i][j];
			if(a[i][j]=='@'){
				beginx = i;beginy = j;
			}
			else if(a[i][j] == '='){
				endx = i;endy = j;
			}
			else if(a[i][j]>='A' && a[i][j]<='Z'){
				int c = a[i][j]-'A';
				slide[c][slide_cnt[c]++] = {i,j};
			}
		}
	}
	for(int i=0;i<MAXN;i++){
		for(int j=0;j<MAXN;j++){
			ans[i][j] = -1;
		}
	}
	q.push({beginx,beginy});
	visited[beginx][beginy] = 1;
	ans[beginx][beginy] = 0;
	while(!q.empty()){
		auto [cx,cy] = q.front();
		q.pop();
		if(cx == endx && cy == endy){
			cout<<ans[cx][cy];
			return 0;
		}
		//在遍历四个方向循环外面进行跳转，不能在里面跳转
		//如果cx上下左右有多个滑梯，将会多个字母入队列，导致计算错误
		if(a[cx][cy]>='A'&&a[cx][cy]<='Z'){
			int c = a[cx][cy] - 'A';
			auto[tx,ty] = (slide[c][0] == make_pair(cx, cy)) ? slide[c][1] : slide[c][0];
			ans[tx][ty] = ans[cx][cy];
			cx = tx;cy = ty;
		}
		for(int i=0;i<4;i++){
			int nx = cx+dx[i];
			int ny = cy+dy[i];
			if(nx>=1 && nx<=N && ny>=1 && ny<=M && a[nx][ny]!='#' && !visited[nx][ny]){
				ans[nx][ny] = ans[cx][cy]+1;
				visited[nx][ny] = 1;
				q.push({nx,ny});
			}
		}
	}
	return 0;
}
/*测试算例（结果是3）
5 6
###=##
#.W.##
#.####
#.@W##
######
*/