//树上多少对点的距离小于等于k
vector<pii> V[N];
vector<int> dep;
int size,f[N],s[N],root,ans,done[N],d[N];
int n,k;

void getroot(int a,int fa)
{
    s[a]=1;f[a]=0;
    rep(i,0,sz(V[a]))
    {
    	int nex=V[a][i].fi;
    	if(nex==fa||done[nex])continue;
      getroot(nex,a);
      s[a]+=s[nex];
      f[a]=max(f[a],s[nex]);
    }
    f[a]=max(f[a],size-s[a]);
    if(f[a]<f[root])root=a;
}
void getdep(int a,int fa)
{
	dep.pb(d[a]);;
	s[a]=1;
	rep(i,0,sz(V[a]))
	{
		int nex=V[a][i].fi;
		if(nex==fa||done[nex])continue;
		d[nex]=d[a]+V[a][i].se;
		getdep(nex,a);
		s[a]+=s[nex];
	}
}
int calc(int a,int val)
{
	dep.clear();d[a]=val;
	getdep(a,0);
	sort(all(dep));
	int ret=0;
	for(int l=0,r=sz(dep)-1;l<r;)
	{
		if(dep[l]+dep[r]<=k)ret+=r-l++;
		else r--;
	}
	return ret;
}
void work(int a)
{
	ans+=calc(a,0);
	done[a]=1;
	rep(i,0,sz(V[a]))
	{
		int nex=V[a][i].fi;
		if(done[nex])continue;
		ans-=calc(nex,V[a][i].se);
		f[0]=size=s[a];
		getroot(nex,root=0);
		work(root);
	}
}
int main()
{
	while(scanf("%d%d",&n,&k)!=EOF)
	{
		if(n==0||k==0)break;
		rep(i,1,n+1)V[i].clear(),done[i]=0;
		rep(i,1,n)
		{
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			V[a].pb({b,c});
			V[b].pb({a,c});
		}
		f[0]=size=n;
		getroot(1,root=0);
		ans=0;
		work(root);
		printf("%d\n",ans);
	}
	return 0;	
}
