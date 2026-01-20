//BFS问题求解
#include<iostream>
#include<queue>
#include<vector>

using namespace std;
//马可以移动的8个方向
int dx[] = {2,2,-2,-2,1,1,-1,-1};
int dy[] = {1,-1,1,-1,2,-2,2,-2};
int main(){
	int n,m,x,y;
	cin>>n>>m>>x>>y;
	vector<vector<int>> dist(n,vector<int>(m,-1));//初始化矩阵全部为-1
	queue<pair<int,int>> q;//bfs队列
	dist[x-1][y-1] = 0;
	q.push({x-1,y-1});
	while(!q.empty()){
		auto [cx,cy] = q.front();
		q.pop();
		//遍历8个方向
		for(int i=0;i<8;i++){
			int nextx = cx+dx[i];
			int nexty = cy+dy[i];
			//检查是否越界以及是否已经访问
			if(nextx>=0 && nextx<n && nexty>=0 && nexty<m && dist[nextx][nexty] == -1){
				dist[nextx][nexty] = dist[cx][cy]+1;
				q.push({nextx,nexty});
			}
		}
	}	
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cout<<dist[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}