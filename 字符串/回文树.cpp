const int N = 1e6 + 7;
char s[N];
int n;//length of s
struct Palindromic_Tree
{
	static const int M=27,N=::N+2;
	int size[N],len;
	struct Node {
		int son[M];
		int ff,len;
	}t[N];
	int last,tot;
	void init() {
	    last=0,tot=1;
	    len=n;
	    memset(t,0,sizeof(Node)*(len+5));
	    memset(size,0,sizeof(int)*(len+5));
	    t[tot++].len=-1;
	    t[0].ff=t[1].ff=1;
	}
	void build(char *s) {
		rep(i,0,len) {
			int c=s[i]-'a';
			int p=last;
			while(s[i-t[p].len-1]!=s[i])p=t[p].ff;
			if(!t[p].son[c]) {
				int v=tot++,k=t[p].ff;
				t[v].len=t[p].len+2;
				while(s[i-t[k].len-1]!=s[i])k=t[k].ff;
				t[v].ff=t[k].son[c];
				t[p].son[c]=v;
			}
			last=t[p].son[c];
			size[t[p].son[c]]++;
		}
	}
};
