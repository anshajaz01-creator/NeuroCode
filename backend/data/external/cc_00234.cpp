/*
读题不规范，爆零两行泪。
数据不清空，爆零两行泪。
多测不读完，爆零两行泪。
边界不特判，爆零两行泪。
贪心不证明，爆零两行泪。
D P 顺序错，爆零两行泪。
大小少等号，爆零两行泪。
变量不统一，爆零两行泪。
越界不判断，爆零两行泪。
调试不注释，爆零两行泪。
溢出不 l l，爆零两行泪。
*/
#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=100;
int n;
int a[N+1],b[N+1];
double dp[2][N+1][N*N+1];
int main(){
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i]>>b[i];
	for(int i=0;i<=n;i++)for(int j=0;j<=n*100;j++)dp[0][i][j]=-inf;
	dp[0][0][0]=0;
	for(int i=1;i<=n;i++)for(int j=0;j<=n;j++)for(int k=0;k<=n*100;k++){
		dp[i&1][j][k]=max(j&&k>=a[i]?dp[i-1&1][j-1][k-a[i]]+b[i]:-inf,
						  dp[i-1&1][j][k]+b[i]/2.);
	}
	for(int i=1;i<=n;i++){
		double ans=-inf;
		for(int j=0;j<=n*100;j++)ans=max(ans,min(1.*j,dp[n&1][i][j]));
		printf("%lf ",ans);
	}
	return 0;
}