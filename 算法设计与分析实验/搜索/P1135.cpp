#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#define MAXN 205
#define INF 0x3f3f3f3f  // 定义极大值，表示无法到达
using namespace std;
int N,A,B;
int ans;
int k[MAXN],visited[MAXN];
int dist[MAXN];//dist表示到达i的最少步数
//采用DFS进行回溯处理，超时
int dfs(int cost,int currenti,int visited[MAXN]){
	if(currenti<1 || currenti>N || visited[currenti] == 1) return INF;//失败就返回极大值
	if(currenti == B) return cost;//如果到当前节点，就返回
	visited[currenti] = 1;
	int tempup = dfs(cost+1,currenti+k[currenti],visited);
	int tempdown = dfs(cost+1,currenti-k[currenti],visited);
	visited[currenti] = 0;//记得回溯
	return min(tempup,tempdown);
}
//采用BFS寻找
int bfs(){
	memset(dist, -1, sizeof(dist));  // -1表示未访问
    queue<int> q;
    // 初始化起点
    dist[A] = 0;
    q.push(A);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        // 找到终点，直接返回步数
        if (curr == B) {
            return dist[curr];
        }
        // 探索两个方向
        int next1 = curr + k[curr];
        int next2 = curr - k[curr];
        // 处理第一个方向
        if (next1 >= 1 && next1 <= N && dist[next1] == -1) {
            dist[next1] = dist[curr] + 1;
            q.push(next1);
        }
        // 处理第二个方向
        if (next2 >= 1 && next2 <= N && dist[next2] == -1) {
            dist[next2] = dist[curr] + 1;
            q.push(next2);
        }
    }
    // 队列空仍未找到，返回-1
    return -1;
}
int main(){
	cin>>N>>A>>B;
	for(int i=1;i<=N;i++){
		cin>>k[i];
	}
	//ans = dfs(0,A,visited);
	ans = bfs();
	if(ans == INF){
		cout<<-1;
	}
	else{
		cout<<ans;
	}
}