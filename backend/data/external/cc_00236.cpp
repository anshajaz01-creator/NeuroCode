#include <bits/stdc++.h>
using namespace std;

int dp[4][102][10002];

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int n;
	cin>>n;
	vector<int> a(n+1), b(n+1);
	vector<double> sol(n+1, 0);
	int sumc=0, suml=0;;
	for(int i=1;i<=n;++i){
		cin>>a[i]>>b[i];	
		sumc+=a[i];
		suml+=b[i];
	}
	for(int k=0;k<=n+1;++k){
		for(int c=0;c<=sumc+1;++c){
			dp[0][k][c]=dp[1][k][c]=-(1<<30);
		}
	}
	dp[0][0][0]=dp[1][0][0]=0;
	for(int ir=1;ir<=n;++ir){
		for(int k=ir;~k;--k){
			for(int c=sumc;~c;--c){
				int i=ir%2;
				if(c>=a[ir]&&k>0) dp[i][k][c]=max(dp[1-i][k][c], dp[1-i][k-1][c-a[ir]]+b[ir]);
				else dp[i][k][c]=dp[1-i][k][c];
			}
		}
	}
	for(int c=0;c<=sumc;++c){
		for(int k=1;k<=n;++k){
			sol[k]=max(sol[k], min(dp[n%2][k][c]/2.0+suml/2.0, double(c)));
		}
	}

	for(int i=1;i<=n;++i) cout<<fixed<<setprecision(10)<<sol[i]<<" ";
	cout<<"\n";
	return 0;
}
