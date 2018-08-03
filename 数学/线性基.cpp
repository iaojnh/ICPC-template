struct Gauss {
	int cnt;
	ll st, lb[25];
	void init() {
		cnt = 0, st = 0;
		rep(i, 0, 61) lb[i] = 0;
	}
	void add(ll w) {
		st |= w;
		for (int i = 60; i >=0; --i) {
			if ((w >> i & 1) && !lb[i]) {
				lb[i] = w, ++cnt;
				break;
			}
			w = min(w, w ^ lb[i]);
		}
	}
}
