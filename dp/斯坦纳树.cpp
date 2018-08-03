//建立斯坦纳树花费的代价以及方案数,时间复杂度大约为O(n*3^m)。
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define per(i,a,b) for(int i=(b-1);i>=(a);i--)
#define all(V) V.begin(),V.end()
#define sz(a) (int)a.size()
#define de(a) cout<<#a<<" = "<<a<<endl
#define dd(a) cout<<#a<<" = "<<a
typedef long long ll;
typedef pair<int ,int > pii;
typedef vector<int> vi;
//----
 
const int N=55,M=13;
const int mod=1e9+7;
pii f[1<<M][N],g[1<<M][N];//first->value,second->cnt
vector<int> V[N],adt[N];
int tot,vis[N],dis[N],ord[N];
int n,m,q;
pii add(pii a,pii b)
{
    a.fi+=b.fi;a.se=1LL*a.se*b.se%mod;
    if(a.fi>=n)a=mp(n,0);
    return a;
}
void upd(pii &a,pii b)
{
    if(a.fi>b.fi)a=b;
    else if(a.fi==b.fi)a.se=(a.se+b.se)%mod;
}
ll kpow(ll a,ll b)
{
    ll ans=1;
    while(b)
    {
        if(b&1)ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
int main()
{
    while(scanf("%d%d%d",&n,&q,&m)!=EOF)
    {
        rep(i,0,n)V[i].clear();
        while(q--)
        {
            int a,b;
            scanf("%d%d",&a,&b);a--;b--;
            V[a].pb(b);
            V[b].pb(a);
        }
        //build graph
        rep(i,0,1<<m)rep(j,0,n)f[i][j]=g[i][j]=mp(n,0);
        rep(i,0,n)
        {
            if(i<m)f[1<<i][i]=g[1<<i][i]=mp(0,1);
            else f[0][i]=g[0][i]=mp(0,1);
        }
        //init
        rep(mask,0,1<<m)//S
        {
            rep(i,0,n)
            {
                int cur=(i<m)?(1<<i):0;
                if(cur&&!(cur&mask))continue;
                int rem=mask^cur,lbt=rem&-rem;
                if(rem)
                {
                    for(int mask2=(rem-1)&rem;mask2;mask2=(mask2-1)&rem)
                    {
                        if(mask2&lbt)
                        {
                            int u=mask2|cur,v=(rem^mask2)|cur;//T,S-T
                            assert((u|v)==mask);
                            upd(g[mask][i],add(f[u][i],g[v][i]));//co 2
                        }
                    }
                }
                if(g[mask][i].fi<n)adt[g[mask][i].fi].pb(i);
            }
            tot=0;
            for(int i=0,j=0;i<n;i++)//co 1
            {
                for(auto u:adt[i])
                {
                    if(vis[u]!=mask)
                    {
                        vis[u]=mask;
                        dis[u]=n;
                    }
                    if(dis[u]>i)
                    {
                        dis[u]=i;
                        ord[tot++]=u;
                    }
                }
                adt[i].clear();
                for(;j<tot;j++)
                {
                    int u=ord[j];
                    if(dis[u]>i)break;
                    for(auto v:V[u])
                    {
                        int cur=v<m?1<<v:0;
                        if(cur&&!(mask&cur))continue;
                        if(vis[v]!=mask)
                        {
                            vis[v]=mask;
                            dis[v]=n;
                        }
                        if(dis[v]>dis[u]+1)
                        {
                            dis[v]=dis[u]+1;
                            ord[tot++]=v;
                        }
                    }
                }
            }
            rep(i,0,tot)
            {
                int u=ord[i];
                for(auto v:V[u])
                {
                    int mask2=mask|(v<m?1<<v:0);
                    pii tmp=g[mask][u];
                    ++tmp.fi;
                    upd(f[mask2][v],tmp);
                    upd(g[mask2][v],tmp);
                }
            }
        }
        pii ans=mp(n,0);
        rep(i,0,n)upd(ans,g[(1<<m)-1][i]);
        if(ans.fi<n)printf("%lld\n",1LL*ans.se*kpow(ans.fi+1,mod-2)%mod);
        else puts("0");
    }
    return 0;  
}
