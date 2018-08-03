//根到所有询问点不联通的炸边代价，洛谷
const int N=250005;
const int mod=1e9+7;
vector<pii> V[N];
int Index=0;
int trn[N],rtrn[N];
int Fa[20][N],Dep[N],st[20][N];
int S[N];
int data[N];
void dfs(int a,int fa,int dep)
{
    Fa[0][a]=fa;
    Dep[a]=dep;
    trn[++Index]=a;
    rtrn[a]=Index;
    rep(i,0,sz(V[a]))
    {
        pii nex=V[a][i];
        if(nex.first==fa)continue;
        st[0][nex.first]=nex.second;
        dfs(nex.first,a,dep+1);
    }
}
int lca(int a,int b)
{
    if(Dep[a]<Dep[b])swap(a,b);
    per(i,0,20)if((1<<i)<=Dep[a]-Dep[b])a=Fa[i][a];
    if(a==b)return a;
    per(i,0,20)if(Fa[i][a]!=Fa[i][b])a=Fa[i][a],b=Fa[i][b];
    assert(Fa[0][a]==Fa[0][b]);
    return Fa[0][a];
}
int cmp(int a,int b)
{
    return rtrn[a]<rtrn[b];
}
vector<pii> vec[N];
int exi[N];
ll Dfs(int a,int fa,ll hd)
{
    ll ans=0;
    rep(i,0,sz(vec[a]))
    {
        if(fa==vec[a][i].first)continue;
        ans+=Dfs(vec[a][i].first,a,vec[a][i].second);
    }
    vec[a].clear();
    if(exi[a])return hd;
    return min(ans,hd);
}
int Min(int a,int b)
{
    int ans=0x3f3f3f3f;
    if(Dep[a]<Dep[b])swap(a,b);
    per(i,0,20)if((1<<i)<=Dep[a]-Dep[b])
    {
        ans=min(ans,st[i][a]);
        a=Fa[i][a];
    }
    return ans;
}
int main()
{
    int n;
    scanf("%d",&n);
    memset(st,0x3f,sizeof(st));
    rep(i,1,n)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        V[a].pb(mp(b,c));
        V[b].pb(mp(a,c));
    }
    dfs(1,0,1);
    rep(i,1,20)rep(j,1,n+1)Fa[i][j]=Fa[i-1][Fa[i-1][j]],st[i][j]=min(st[i-1][j],st[i-1][Fa[i-1][j]]);
    int q;
    scanf("%d",&q);
    while(q--)
    {
        int m;
        scanf("%d",&m);
        rep(i,0,m)scanf("%d",&data[i]);
        rep(i,0,m)exi[data[i]]=1;
        sort(data,data+m,cmp);
        int p=0;
        S[p++]=data[0];
        rep(i,1,m)
        {
            int u=data[i];
            int v=S[p-1];
            int Lca=lca(u,v);
            for(;p>1;v=S[p-1])
            {
                int w=S[p-2];
                if(Dep[w]>=Dep[Lca])
                {
                    vec[v].pb(mp(w,Min(v,w)));
                    vec[w].pb(mp(v,Min(v,w)));
                    p--;
                }
                else break;
            }
            if(Lca!=v)
            {
                vec[Lca].pb(mp(v,Min(Lca,v)));
                vec[v].pb(mp(Lca,Min(Lca,v)));
                p--;
                S[p++]=Lca;
            }
            S[p++]=u;
        }
        while(p>1)
        {
            assert(S[p-1]!=S[p-2]);
            vec[S[p-1]].pb(mp(S[p-2],Min(S[p-1],S[p-2])));
            vec[S[p-2]].pb(mp(S[p-1],Min(S[p-1],S[p-2])));
            p--;
        }
        int root=S[0];
        if(root!=1)
        {
            vec[1].pb(mp(root,Min(1,root)));
            vec[root].pb(mp(1,Min(1,root)));
        }
        printf("%lld\n",Dfs(1,-1,0x3f3f3f3f3f3f3f3f));
        rep(i,0,m)exi[data[i]]=0;
    }
    return 0;	
}