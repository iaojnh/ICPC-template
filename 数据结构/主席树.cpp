const int N=100005;
const int NN=2000005;
int data[N]={0};
int pos[N]={0};
vector<int> V;
int s=0;
int l[NN]={0},r[NN]={0},c[NN]={0},total=0,Null=1;
int treenode[N]={0};
void buildtree(int &x, int ll,int rr)
{
    x=++total;
    if(ll<rr)
    {
        buildtree(l[x],ll,(ll+rr)>>1);
		buildtree(r[x],((ll+rr)>>1)+1,rr);
    }
}
int in(int y,int num)
{
    int root=++total;
    int x=root;
    int ll=1,rr=s;
    c[x]=c[y]+1;
    while(ll<rr)
    {
        int mid=(ll+rr)>>1;
        if(num<=mid)
        {
            l[x]=++total;
            r[x]=r[y];
            x=l[x];y=l[y];
            rr=mid;
        }
        else
        {
            l[x]=l[y];
            r[x]=++total;
            x=r[x];y=r[y];
            ll=mid+1;
        }
        c[x]=c[y]+1;
    }
    return root;
}
int query(int a,int b,int k)
{
    int x=treenode[a-1],y=treenode[b];
    int ll=1,rr=s;
    while(ll<rr)
    {
        int mid=(ll+rr)>>1;
        int lnum=c[l[y]]-c[l[x]];
        if(lnum>=k)
        {
            x=l[x];y=l[y];
            rr=mid;
        }
        else
        {
            k-=lnum;
            x=r[x];y=r[y];
            ll=mid+1;
        }
    }
    return ll;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)scanf("%d",&data[i]);
//----------
    for(int i=1;i<=n;++i)V.push_back(data[i]);
    sort(V.begin(),V.end());
    V.erase(unique(V.begin(),V.end()),V.end());
    for(int i=1;i<=n;++i)pos[i]=lower_bound(V.begin(),V.end(),data[i])-V.begin()+1;
//----------
    s=V.size();
    buildtree(Null,1,s);
    treenode[0]=1;
    for(int i=1;i<=n;i++)treenode[i]=in(treenode[i-1],pos[i]);
//----------
    while(m--)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        printf("%d\n",V[query(a,b,c)-1]);
    }
    return 0;
}
