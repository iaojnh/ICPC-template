struct Hash_table {
    static const int V=1000003;
    int fst[V],nxt[V];
    int ctm,ptm[V],T;
    int val[V];
    vector<pair<ll,int>> key;
    void init() { T=0; ctm++; key.clear(); }
    void add(ll s) {
        int S=s%V;
        if (ptm[S]!=ctm) ptm[S]=ctm,fst[S]=-1;
        for (int j=fst[S];j!=-1;j=nxt[j]) if (key[j].fi==s) {
            key[j].se++;
            return;
        }
        nxt[T]=fst[S],fst[S]=T; key.pb(mp(s,1));
        T++;
    }
    int operator [](ll s) {
        int S=s%V;
        if (ptm[S]!=ctm) return 0;
        for (int j=fst[S];j!=-1;j=nxt[j]) if (key[j].fi==s)
            return key[j].se;
        return 0;
    }
}V;