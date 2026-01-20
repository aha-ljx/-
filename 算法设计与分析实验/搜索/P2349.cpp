// 注意1：本题vis数组未实际使用，因为同一节点可能有多个最优状态（不同dist/pre）
// 注意2：优先队列按dist[v]排序，但核心判断是综合值，不影响结果但需注意逻辑一致性
// 注意3：ll类型选择原因：边权较大时（如1e5），int总长度会溢出（100*1e5=1e7，接近int上限）
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#define MAXN 105       // 必要注释：节点最大数量（题目约束n≤100）
#define inf 0x3f3f3f3f // 必要注释：无穷大（int型安全值，避免溢出）
using namespace std;
typedef long long ll;  // 必要注释：定义长整型，防止边权/总长度溢出

// 全局变量区（必要注释：说明每个变量的核心作用）
int n,m,cnt;            // n:节点数 m:边数 cnt:邻接表边的计数器（从1开始）
int head[MAXN];         // 邻接表头节点数组：head[u]表示u的第一条边的下标
ll pre[MAXN],dist[MAXN];// pre[i]:到节点i的路径中最长边的长度 | dist[i]:到节点i的路径总长度
bool vis[MAXN];         // 访问标记（本题未实际使用，仅预留）

// 必要注释：优先队列节点结构体（Dijkstra小根堆用）
struct Node{
	int to;             // 节点编号
	ll val;             // 优先队列排序键值（存储dist[to]）
	Node(){};           // 空构造函数（默认初始化）
	// 必要注释：带参构造函数，快速初始化val和to
	Node(ll _val,int _to):to(_to),val(_val){}
	// 必要注释：重载<运算符，实现小根堆（优先队列默认大根堆，反向重载）
	bool operator < (const Node&a)const noexcept{
		return val>a.val; // val越小，优先级越高
	}
};

// 必要注释：邻接表边结构体（存储无向边）
struct edge{
	int to;             // 边的终点
	ll val;             // 边的权值（路径长度/时间）
	int next;           // 下一条边的下标（链式存储）
}edge[2008<<1];         // 必要注释：2008<<1=4016，无向边需存双向，数组大小翻倍

// 必要注释：邻接表加边函数（inline内联减少调用开销）
inline void add(int u,int v,ll w){
	edge[++cnt].to = v;        // 边计数器+1，赋值终点v
	edge[cnt].val = w;         // 赋值边权w
	edge[cnt].next = head[u];  // 新边指向u原第一条边
	head[u] = cnt;             // 更新u的头节点为当前边
	return;
}

// 必要注释：变种Dijkstra算法（求1→n的最小「总长度+最长边长度」）
// 参数u：起点（本题固定为1）
void dijkstra(int u){
	priority_queue<Node> q;   // 优先队列（小根堆），维护待处理节点
	while(!q.empty()) q.pop();// 清空队列（防止残留数据干扰）
	// 必要注释：初始化所有节点状态
	for(int i=1;i<=n;i++){
		dist[i] = inf;    // 初始总长度为无穷大
		vis[i] = false;   // 初始未访问
		pre[i] = 0;       // 初始最长边为0（无路径）
	}
	dist[u] = 0;              // 起点总长度为0
	q.push(Node(0,1));        // 起点入队：val=dist[1]=0，to=1
	// 必要注释：优先队列循环（贪心扩展最优节点）
	while(!q.empty()){
		int u = q.top().to;   // 取当前总长度最小的节点
		ll t = dist[u];       // 记录该节点的总长度
		q.pop();              // 弹出队列
		// 必要注释：遍历u的所有出边（邻接表链式遍历）
		for(int i=head[u];i;i=edge[i].next){ 
			int v= edge[i].to;// 边的终点v
			// 核心注释：松弛条件——比较「当前综合值」和「新综合值」
			// dist[v]+pre[v]：v当前的「总长度+最长边长度」
			// t+edge[i].val+max(edge[i].val,pre[u])：u→v的新综合值
			if((dist[v]+pre[v]>t+edge[i].val+max(edge[i].val,pre[u]))){
			    pre[v] = max(pre[u],edge[i].val); // 更新v的最长边（u的最长边 vs 当前边权）
			    dist[v] = edge[i].val+t;          // 更新v的总长度（u的总长度 + 当前边权）
			    q.push(Node(dist[v],v));          // 新状态入队，继续扩展
		    }
		}	
	}
	return;
}

int main(){
	// 必要注释：输入节点数和边数
	cin>>n>>m;
	int A,B;                 // 边的起点A、终点B
	ll C;                    // 边权C（路径长度/时间）
	// 必要注释：输入m条无向边，构建邻接表
	for(int i=1;i<=m;i++){
		cin>>A>>B>>C;
		add(A,B,C);          // 添加A→B的边
		add(B,A,C);          // 添加B→A的边（无向边双向存储）
	}
	dijkstra(1);             // 执行Dijkstra，起点为1
	// 必要注释：输出终点n的最小综合值（总长度+最长边长度）
	cout<<dist[n]+pre[n];
	return 0; // 补充：main函数建议加return 0，规范
}