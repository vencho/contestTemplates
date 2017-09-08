#include<vector>
#include<string>
#include<cstdio>
#include<cstdlib>



#include"segtree_template.cpp"
#include"segtree_sample.cpp"


SegmentTree<Cell, long long> T;


int main() {
	int tests,tst;
	scanf("%d", &tests);

	for(int tst = 0; tst < tests; tst++) {
		int n, m;
		scanf("%d%d", &n, &m);
		T.initialise(n, new Ops());
		for(int i = 0; i < m; i++) {
			int c, a, b; 
			long long v;
			scanf("%d%d%d", &c, &a, &b);
			if(c == 0) {
				scanf("%lld", &v);
				T.add(a, b, v);
			} 
			else {
				printf("%lld\n", T.query(a, b));
			}
		}
	}
	return 0;
}

