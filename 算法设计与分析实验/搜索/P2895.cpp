#include<iostream>
#include<queue>
#include<vector>
#include<climits>
#define MAXN 305
using namespace std;
int M;
//四个不同方向
int dx[] = {0,1,-1,0,0};
int dy[] = {0,0,0,1,-1};
int stone[MAXN][MAXN];//存储陨石地图
int visited[MAXN][MAXN];//标记是否走过
int ans[MAXN][MAXN];//存储每个点的最小时间
queue<pair<int,int>> q;//bfs队列
int main(){
	cin>>M;
	//必须初始化为-1,为了防止可能出现的t=0的陨石的情况
	for(int i=0;i<MAXN;i++){
		for(int j=0;j<MAXN;j++){
			stone[i][j] = -1;
		}
	}
	for(int i=0;i<M;i++){
		int x,y,t;
		cin>>x>>y>>t;
		//处理陨石烧焦地区，如果有重叠区域，按最早烧焦时间算
		for(int j=0;j<5;j++){
			if(x+dx[j]>=0 && y+dy[j]>=0 && (stone[x+dx[j]][y+dy[j]]==-1 || t<stone[x+dx[j]][y+dy[j]])){
				stone[x+dx[j]][y+dy[j]] = t;
			}
		}
	}
	if (stone[0][0] == -1) {  // 起点本身就是安全格
        cout << 0;
        return 0;
    }
	//初始化
	q.push({0,0});
	visited[0][0] = 1;
	while(!q.empty()){
		auto [cx,cy] = q.front();
		q.pop();
		int s = ans[cx][cy] +1;
		for(int i=1;i<=4;i++){
			int nx = cx + dx[i];
			int ny = cy + dy[i];
			if (nx < 0 || ny < 0) continue;  // 越界
            if (visited[nx][ny]) continue;   // 已访问

            // 判断是否能进入该格子：
            if (stone[nx][ny] == -1) {
                cout << s << endl;
                return 0;
            }
            if (s < stone[nx][ny]) {
                visited[nx][ny] = 1;
                ans[nx][ny] = s;
                q.push({nx, ny});
            }
		}
	}
	cout<<-1;
	return 0;
}