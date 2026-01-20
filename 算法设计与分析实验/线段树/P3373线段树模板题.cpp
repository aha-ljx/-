#include<iostream>
#include<vector>
#define MAXN 100010
#define ll long long
using namespace std;
ll m;
//线段树
struct Node {
    ll sum;
    ll lazy_mul;//懒标记乘法，记录当前节点包裹的树的乘法
    ll lazy_add;//懒标记加法，记录当前节点包裹的树的加法
} tree[4 * MAXN];//这里的4*MAXN是为了防止出现单树却按照完全二叉树编号情况

void build(int node,int l,int r,vector<ll> &a){
	if(l == r){
		tree[node].sum = a[l];
		tree[node].lazy_mul = 1;//初始化乘法为1无影响
		tree[node].lazy_add = 0;
		return;
	}
	int mid = (l+r)/2;
	build(node*2,l,mid,a);
	build(node*2+1,mid+1,r,a);
	tree[node].sum = (tree[node*2].sum+tree[node*2+1].sum)%m;
	tree[node].lazy_add = 0;
	tree[node].lazy_mul = 1;
}
//更新节点的子树状态函数，实时更新
void push_down(int node,int l,int r){
	if (l == r) {
        // 叶子节点，没有子节点，直接清空懒标记即可
        tree[node].lazy_add = 0;
        tree[node].lazy_mul = 1;
        return;
    }
	if(tree[node].lazy_add!=0 || tree[node].lazy_mul!=1){
		int mid = (l+r)/2;
		int left_len = mid - l + 1;
		int right_len = r - mid;
		//更新左子树
		//左子树最新的sum = old_sum*new_mul + new_add*old_len
		tree[node*2].sum = (tree[node*2].sum*tree[node].lazy_mul+tree[node].lazy_add*left_len)%m;
		tree[node*2].lazy_add = (tree[node*2].lazy_add*tree[node].lazy_mul+tree[node].lazy_add)%m;
		tree[node*2].lazy_mul = (tree[node*2].lazy_mul*tree[node].lazy_mul)%m;
	
	    //更新右子树
	    tree[node*2+1].sum = (tree[node*2+1].sum*tree[node].lazy_mul+tree[node].lazy_add*right_len)%m;
		tree[node*2+1].lazy_add = (tree[node*2+1].lazy_add*tree[node].lazy_mul+tree[node].lazy_add)%m;
		tree[node*2+1].lazy_mul = (tree[node*2+1].lazy_mul*tree[node].lazy_mul)%m;

        //清空当前节点的懒标记
        tree[node].lazy_add = 0;
        tree[node].lazy_mul = 1;
	}
}
//更新乘法函数
void update_mul(int node,int l,int r,int begin,int end,ll k){
	//当前区域在变化区间以外的时候直接返回
	if(begin>r || end<l) return;
	//当前区域完全在变化区间里面的时候
	if(begin<=l && end>=r){
		tree[node].sum = (tree[node].sum*k)%m;
		tree[node].lazy_add = (tree[node].lazy_add*k)%m;
		tree[node].lazy_mul = (tree[node].lazy_mul*k)%m;
		return;
	}
	push_down(node,l,r);//首先更新子树
	//当前区域部分覆盖变化区间的时候
	int mid = (l+r)/2;
	//更新左右子树乘法
	update_mul(node*2,l,mid,begin,end,k);
	update_mul(node*2+1,mid+1,r,begin,end,k);
	tree[node].sum = (tree[node*2].sum+tree[node*2+1].sum)%m;
}
//更新加法函数
void update_add(int node, int l, int r, int start, int end, long long k) {
    if (start > r || end < l) return;
    if (start <= l && r <= end) {
        tree[node].sum = (tree[node].sum + k * (r - l + 1)) % m;
        tree[node].lazy_add = (tree[node].lazy_add + k) % m;
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    update_add(node * 2, l, mid, start, end, k);
    update_add(node * 2 + 1, mid + 1, r, start, end, k);
    tree[node].sum = (tree[node * 2].sum + tree[node * 2 + 1].sum) % m;
}
//查询函数
ll query(int node, int l, int r, int start, int end) {
    if (start > r || end < l) return 0;
    //当前区间完全在变化区间里面的时候，表示查询到了，直接返回
    if (start <= l && r <= end) {
        return tree[node].sum;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    ll left_sum = query(node * 2, l, mid, start, end);
    ll right_sum = query(node * 2 + 1, mid + 1, r, start, end);
    return (left_sum + right_sum) % m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q >> m;

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    build(1, 1, n, a);

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            update_mul(1, 1, n, x, y, k);
        } else if (op == 2) {
            int x, y, k;
            cin >> x >> y >> k;
            update_add(1, 1, n, x, y, k);
        } else if (op == 3) {
            int x, y;
            cin >> x >> y;
            cout << query(1, 1, n, x, y) << endl;
        }
    }

    return 0;
}