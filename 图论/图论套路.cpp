最小支配集：一个最小的点集合，使得图上其他点和集合内的某个点相邻。
最大独立集：一个最大的点集合，使得集合内的点两两不相邻。
最大团：一个最大的点集合，使得集合内的点两两相邻。（补图的最大独立集）。
最小点覆盖集：一个最小的点集合，使得图上所有边的两个端点，至少有一个点在集合里。
最小边覆盖集：一个最小的边集合，使得图上所有顶点是集合中至少一条边的一个端点。
最小路径覆盖：一个顶点没有交集的路径集合，使得图上所有顶点在集合中一条路径上。最小路径覆盖=点集大小-最大匹配

一般图的最小支配集、最大独立集、最小点覆盖集不可做，最大团有模版。
最小路径覆盖=点集大小-拆点后最大匹配。
最小边覆盖=(点集大小*2-拆点后最大匹配)/2。

二分图下：
最小点覆盖=最大匹配。
最大独立集=点集大小-最小点覆盖=点集大小-最大匹配。
最小边覆盖=最大独立集。

树（也可以看成二分图）下，这些东西有贪心做法，不用写长长的最大流，方法如下：

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
const int N=100005;
vector<int> V[N];
bool Ans_Set[N],s[N];
int dfn[N],Fa[N];
int Index,n;
void dfs(int a,int fa) {
	dfn[Index++]=a;
	rep(i,0,sz(V[a])) {
		int nxt=V[a][i];
		if(nxt==fa)continue;
		Fa[nxt]=a;
		dfs(nxt,a);
	}
}

//最小支配集
 
/*int solve() {
	int ans=0;
	per(i,0,n) {
		int cur=dfn[i];
		if(!s[cur]) {
			if(!Ans_Set[Fa[cur]]) {
				Ans_Set[Fa[cur]]=true;
				ans++;
			}
			s[cur]=s[Fa[cur]]=s[Fa[Fa[cur]]]=true;
		}
	}
	return ans;
}*/

//最小点覆盖

int solve() {
	int ans=0;
	per(i,1,n) {
		int cur=dfn[i];
		if(!s[cur]&&!s[Fa[cur]]) {
			Ans_Set[Fa[cur]]=true;
			ans++;
			s[cur]=s[Fa[cur]]=true;
		}
	}
	return ans;
}

//最大独立集

/*int solve() {
	int ans=0;
	per(i,0,n) {
		int cur=dfn[i];
		if(!s[cur]) {
			Ans_Set[Fa[cur]]=true;
			ans++;
			s[cur]=s[Fa[cur]]=true;
		}
	}
	return ans;
}*/ 
int main() {
	Index=0;scanf("%d",&n);
	rep(i,1,n) {
		int a,b;scanf("%d%d",&a,&b);
		V[a].pb(b);V[b].pb(a);
	}
	dfs(1,0);
	cout<<solve()<<endl;
	return 0;
}
