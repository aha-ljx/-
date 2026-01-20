#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

vector<int> buildArray(const string& s){
	int n = s.size();
	/*
    sa存储最终结果信息，sa[i]表示后缀起始字母的序号在第i位
    rank存储排序过程中需要使用的子串的顺序，rank[i]表示从字符串s的第i位开始的子串顺序
    new_rank是每次排序后用来更新rank的数组
	*/
	vector<int> sa(n),rank(n),new_rank(n);
	//初始化
	for(int i=0;i<n;i++){
		sa[i] = i;//将结果数组首先初始化
		rank[i] = s[i];//将排序首先初始化为s的初始字典序，初始字典序已经有可以比较的顺序
	}
	
	//接下来按子串长度由小到大构建
	for(int k=1;k<=n;k*=2){//注意这里是k*=2不是k++因为每次都是2k长度的比较
		//重新定义比较含义，要求使用rank数组里面顺序进行比较排序
		//lamaba表达式里面&表示可以使用该函数体内定义的sa,rank,new_rank；传入参数i,j表示rank里面的序号
		auto cmp = [&](int i,int j){
			if(rank[i]!=rank[j]){
				return rank[i]<rank[j];//这是先比较前k位
			}
			int ri = (i+k<n)?rank[i+k]:-1;
			int rj = (j+k<n)?rank[j+k]:-1;//这是比较k位之后子串
			return ri<rj;
		};
		sort(sa.begin(),sa.end(),cmp);//结果数组里面记载的是每次子串比较之后，后缀排名结果
		
		//更新rank数组
		new_rank[sa[0]] = 0;//sa[0]存储的是当前子串比较之后排名最靠前的后缀的序号
		for(int i=1;i<n;i++){
			new_rank[sa[i]] = new_rank[sa[i-1]] + ((cmp(sa[i-1],sa[i])?1:0));//这里是为了防止当前子串排名一致但是却rank有差异
		}
		rank = new_rank;
		if(rank[sa[n-1]] == n-1) break;//如果当前排名的序号可以延申到n-1时候，说明所有后缀已经排序完成
	}
	return sa;
}

int main(){
	ios::sync_with_stdio(false);//将C++的输入输出与C的输入输出取消关联
	cin.tie(nullptr);//取消cin与cout的关联
	
	string s;
	getline(cin,s);//整行读取s
	
	vector<int> ans;
	ans = buildArray(s);
	for(int i=0;i<ans.size();i++){
		cout<<ans[i]+1<<" ";
	}
	return 0;
}