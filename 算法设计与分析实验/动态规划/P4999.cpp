#include<iostream>
#include<cstring>
using namespace std;
typedef long long ll;
const int N=51,MOD = 1e9+7;

ll pow10[N],dp[N],a[N],count[N],tmpcount[N],ans;
/*
pow10[N]代表10的幂次
dp[i]代表i位数字中0~9每个数字出现的次数
a[i]表示一个数的第i位（从个位开始）是多少
count[i]表示区间[1-x]之内数字i出现的次数
tmpcount[i]存储count[i]，用于在计算前缀和的时候充当减数
*/
//初始化dp和pow10
void init(){
	pow10[0]=1;
	for(int i=1;i<30;i++){
		//关键方程
		dp[i] = (dp[i-1]*10%MOD+pow10[i-1])%MOD;
		pow10[i] = 10*pow10[i-1]%MOD;
	}
}
void solve(ll x){
	int len=0;
	while(x){
		a[++len] = x%10;
		x /= 10;
	}
	for(int i=len;i>=1;i--){
		//先把每个数字加上低一位数字dp[i-1]出现的次数*重复次数a[i]次
		for(int j=0;j<10;j++){
			count[j]+=dp[i-1]*a[i];count[j]%=MOD;
		}
		//再处理当前位数字0~a[i]-1之间的数字出现的次数
		for(int j=0;j<a[i];j++){
			count[j]+=pow10[i-1];count[j]%=MOD;
		}
		//当当前位数字为a[i]时，不能直接*10^(i-1)，因为此时已经到最大数字范围里了，如527是500到527不是500到599
		ll lastnum = 0;
		//计算剩余数字
		for(int j=i-1;j>=1;j--){
			lastnum = lastnum*10 +a[j];lastnum%=MOD;
		}
		//加1是因为有数字0
		count[a[i]]+=lastnum+1;count[a[i]]%=MOD;
	    //减去前导为0的情况
		count[0]-=pow10[i-1];count[0]=(count[0]+MOD)%MOD;
	}
}
int main(){
	init();
	ll l, r, T;
	cin>>T;
	for (int q=0;q<T;q++)
	{
		ans=0; cin>>l>>r;
		solve(r); //前缀和思想相减 r 和 l-1。
		for (int i=0;i<10;i++) (tmpcount[i]=count[i]),count[i]=0; //复制 count，记得清零
		solve(l-1);
		for (int i=0;i<10;i++) ans=(ans+i*(tmpcount[i]-count[i]+MOD)%MOD)%MOD,count[i]=0; //累加答案，记得清零 count。
		cout<<ans<<'\n';
	}
	return 0;
}