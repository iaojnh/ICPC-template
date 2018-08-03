const int N=100005;
stack<int> s;
vector<int> v[N];
int dfn[N],low[N],instack[N],npoint[N];
int cnt=0;
int index=0;
void tarjan(int a,int fa)
{
    dfn[a]=low[a]=++index;
    s.push(a);
    instack[a]=1;
    for(int i=0;i<v[a].size();i++)
    {
        int point=v[a][i];
        if(point==fa)continue;
        if(!dfn[point])
        {
            tarjan(point,a);
            low[a]=min(low[a],low[point]);
        }
        else if(instack[point])low[a]=min(low[a],dfn[point]);
    }
    if(dfn[a]==low[a])
    {
        cnt++;
        while(s.top()!=a)
        {
            npoint[s.top()]=cnt;
            instack[s.top()]=0;
            s.pop();
        }
        npoint[s.top()]=cnt;
        instack[s.top()]=0;
        s.pop();
    }
}
