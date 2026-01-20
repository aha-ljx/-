#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<iomanip>//控制输入输出的格式
#include<climits>
using namespace std;

struct Point{
	double x,y;
};

int main(){
	int n;
	cin>>n;
	vector<Point> points(n+1);//points[0]是原点
	points[0].x = 0.0;points[0].y = 0.0;
    for(int i=1;i<=n;i++){
    	cin>>points[i].x>>points[i].y;
	}
	
	//预计算两点之间距离
	vector<vector<double>> dist(n+1,vector<double>(n+1,0.0));//初始化方式
	for(int i=0;i<=n;i++){
		for(int j=0;j<=n;j++){
			double dx = points[i].x - points[j].x;
			double dy = points[i].y - points[j].y;
			dist[i][j] = sqrt(dx*dx+dy*dy);
		}
	}
	
	//dp[mask][u]表示访问过mask中的节点，当前在u的最短距离
	int total_nodes = n+1;
	//用二进制表示节点是否被访问
	vector<vector<double>> dp(1<<total_nodes,vector<double>(total_nodes,1e18));
    dp[1<<0][0] = 0.0;//初始状态：仅访问起点0
    
    //枚举所有可能访问状态
    for(int mask = 1;mask<(1<<total_nodes);mask++){
    	//寻找当前节点
    	for(int u=0;u<total_nodes;u++){
    		if(!(mask &(1<<u))) continue;//只有找到当前停留的节点才能继续
    		if(dp[mask][u] >= 1e18) continue;
    		for(int v=0;v<total_nodes;v++){
    			if(!(mask &(1<<v))){//只有当前节点没有访问才访问
    				int new_mask = mask | (1<<v);//记录当前节点
    				dp[new_mask][v] = min(dp[new_mask][v],dp[mask][u]+dist[u][v]);
				}
			}
		}
	}
	//所有节点都被访问时候的最短距离
	double ans = 1e18;
	int full_mask = (1<<total_nodes) - 1;
	for(int u=0;u<total_nodes;u++){
		ans = min(ans,dp[full_mask][u]);//寻找停留在不同位置的最小值
	}
	cout<<fixed<<setprecision(2)<<ans<<endl;//结果输出两位小数
	return 0;
	
}