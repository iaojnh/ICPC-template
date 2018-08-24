/ *
  * 斜率优化：(FZU 2302/18省赛I)
  * 转移方程：dp[i]=Max(dp[j]+(sum[i]-sum[j])^2) (0<=j<i)
  * 将右项分解，得：
  * dp[i]=dp[j]+sum[i]^2+sum[j]^2-2*sum[i]*sum[j] -> dp[j]+sum[j]^2=dp[i]-sum[i]^2+2*sum[i]*sum[j]
  * 对于直线y=kx+b
  * 将只与j相关的变量做y，只与i相关的变量做b，与两者都相关的做kx，k与i相关，x与j相关。
  * 这个例子中，令y=dp[j]+sum[j],k=2*sum[i],x=sum[j],b=dp[i]-sum[i]^2，斜率固定且已知，我们的目的是让这条直线的截距尽可能大。
  * 于是我们对于之前的点，用单调队列维护一个上凸壳即可。就可以O(1)转移了。
*/
#include<bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define pw(x) (1ll << (x))
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(),(x).end()
#define rep(i,l,r) for(int i=(l);i<(r);++i)
#define per(i,l,r) for(int i=(r)-1;i>=(l);--i)
#define dd(x) cout << #x << " = " << x << ", "
#define de(x) cout << #x << " = " << x << endl

//-----
ll data[500005];
ll dp[500005]={0},sum[500005]={0};
pii q[500005];
int main()
{
    int n,k;
    while(scanf("%d%d",&n,&k)!=EOF)
    {
        int front=0,rear=-1;
        rep(i,1,n+1)scanf("%lld",&data[i]);
        rep(i,1,n+1)sum[i]=sum[i-1]+data[i];
        rep(i,1,n+1)
        {
            ll x=2*sum[i-1],y=dp[i-1]+sum[i-1]*sum[i-1];
            while(rear-front+1>=2)
            {
                if((y-q[rear].second)*(q[rear].first-q[rear-1].first)<=(q[rear].second-q[rear-1].second)*(x-q[rear].first))rear--;
                else break;
            }
            q[++rear]=mp(x,y);
            while(rear-front+1>=2)
            {
                if(sum[i]*(q[front+1].first-q[front].first)>=q[front+1].second-q[front].second)front++;
                else break;
            }
            dp[i]=q[front].second-sum[i]*q[front].first+sum[i]*sum[i]+k;
        }
        printf("%lld\n",dp[n]);
    }
    return 0;
}
