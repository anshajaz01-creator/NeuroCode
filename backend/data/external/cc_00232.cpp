#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;
int n,a[110],b[110],sum;
float ans[110],dp[110][10010];
int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[i],&b[i]);
	for(int i=0;i<110;i++)
		for(int j=0;j<10010;j++)
			dp[i][j]=-1e9;
	dp[0][0]=0;
	for(int i=1;i<=n;i++)
	{
		sum+=a[i];
		for(int j=i;j>=0;j--)
			for(int k=sum;k>=0;k--)
			{
				dp[j][k]+=1.0*b[i]/2;
				if(k>=a[i]&&j)
					dp[j][k]=max(dp[j][k],dp[j-1][k-a[i]]+b[i]);
				ans[j]=max(ans[j],min(dp[j][k],(float)k));
			}
	}
	for(int i=1;i<=n;i++)
		printf("%f ",ans[i]);
	printf("\n");
	return 0;
}