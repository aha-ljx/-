//贪心算法解决，暴力递归会超时

#include<iostream>
#include<algorithm>
using namespace std;
int costall(int n,int current_c,int*wp,int*locationp,int costtotal,int computecost,int flag){
    bool all_zero = true;
    for (int i = 1; i <= n; ++i) {
        if (wp[i] != 0) {
            all_zero = false;
            break;
        }
    }
    if (all_zero) {
        return costtotal; 
    }
	int costcurrent;
	int nextcurrent=-1;
	int i;
	if(flag==1){
		for(i=current_c-1;i>=1;i--){
		    if(wp[i]!=0){
			    nextcurrent=i ;
			    break;
		    }
	    }
	    // 若向左无可用节点（说明只剩向右的节点，此时flag=1的分支无效，跳过）
        if (nextcurrent == -1) {
            // 递归调用flag=0的分支（强制向右）
            return costall(n, current_c, wp, locationp, costtotal, computecost, 0);
        }
	    costtotal += (locationp[current_c]-locationp[nextcurrent])*computecost;
	    computecost -= wp[nextcurrent];
	    int temp_wp = wp[nextcurrent]; // 临时保存，避免递归修改原数组（回溯）
        wp[nextcurrent] = 0;
	    costcurrent = min(costall(n,nextcurrent,wp,locationp,costtotal,computecost,1),costall(n,nextcurrent,wp,locationp,costtotal,computecost,0));
	    wp[nextcurrent] = temp_wp;
	}
	else if(flag==0){
		for(i=current_c+1;i<=n;i++){
		    if(wp[i]!=0){
			    nextcurrent=i ;
			    break;
		    }	
	}
	// 若向右无可用节点（说明只剩向左的节点，此时flag=0的分支无效，跳过）
        if (nextcurrent == -1) {
            // 递归调用flag=1的分支（强制向右）
            return costall(n, current_c, wp, locationp, costtotal, computecost, 1);
        }
		costtotal += (locationp[nextcurrent]-locationp[current_c])*computecost;
	    computecost -= wp[nextcurrent];
	    int temp_wp = wp[nextcurrent]; // 临时保存，避免递归修改原数组（回溯）
        wp[nextcurrent] = 0;
	    costcurrent = min(costall(n,nextcurrent,wp,locationp,costtotal,computecost,1),costall(n,nextcurrent,wp,locationp,costtotal,computecost,0));
	    wp[nextcurrent] = temp_wp;
	}
	return costcurrent;
}

int main(){
	int n,c;
	cin>>n>>c;
	int location[n+1];
	int w[n+1];
	location[0] = 0;w[0] = 0;
	for(int i=1;i<=n;i++){
		cin>>location[i]>>w[i];
	}
	w[c] = 0;
	int cost=0;
	for(int i=1;i<=n;i++){
		cost+=w[i];
	}
	cost -= w[c];
	int ans = 0;
	ans = min(costall(n,c,w,location,ans,cost,1),costall(n,c,w,location,ans,cost,0));
	cout<<ans;
	return 0;
}