#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define LL long long
#define inf 2147483647
LL n,a[100006],b[100006],MIN,pos[100006],siz,sum,minn;
bool vis[100006];
LL ans;
void dfs(int x)
{
    if(vis[x])return ;
    sum+=a[x];    //记录环内每个点的总和 
    siz++;        //环内有多少个点 
    MIN=min(MIN,a[x]);    //环内最小值 
    vis[x]=1;    //打上标记 
    dfs(pos[x]);    //下一个点 
}
int main()
{
    scanf("%d",&n);
    minn=MIN=inf;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&a[i]);
        b[i]=a[i];
        minn=min(minn,a[i]);    //记录序列最小值 
    }
    sort(b+1,b+1+n);    //排序 
    for(int i=1;i<=n;i++)
        pos[i]=lower_bound(b+1,b+1+n,a[i])-b;    //记录排序后的位置 
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            dfs(i);
            ans+=min(sum+MIN+minn*(siz+1),sum+MIN*(siz-2));
/*
        方法一：交换序列最小值和环内最小值 + 序列最小值 * 环内点数 
        方法二：环内最小值*环内点数。 
*/ 
            siz=0; sum=0; MIN=inf;
        }
    }
    printf("%lld",ans);
}
