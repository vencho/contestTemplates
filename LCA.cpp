class LCA {
	private:
	int N;
	
	int lcaCounter;
	vector<pair<int, int> > lcaSequence; // (vertex, lcaNumber)
	vector<int> firstAppearance, lastAppearance; // of vertex
	vector<vector<pair<int, int> > > dp; // (lcaNumber, position in lca sequence)
	
	void lcaDFS(int v, vector<vector<int> > &adj) {
		int lcac = lcaCounter;
		lcaSequence.push_back(make_pair(v, lcac));
		firstAppearance[v] = lastAppearance[v] = lcaSequence.size()-1;
		lcaCounter++;
		
		int i, u;
		for(i = 0; i < adj[v].size(); i++) {
			u = adj[v][i];
			lcaDFS(u, adj);
			lcaSequence.push_back(make_pair(v, lcac));
			lastAppearance[v] = lcaSequence.size()-1;
		}
	}
	
	

	void calculateRMQ() {
		int i, j, k, len;
		dp.resize(lcaSequence.size());
		
		
		for(i = 0; i < lcaSequence.size(); i++) {
			dp[i].push_back(make_pair(lcaSequence[i].second, i)); // dp[i][0]
		}

		#define MIN(x, y) (((x)<(y))?(x):(y))
		for(j = 1; (1 << j) <= lcaSequence.size(); j++) {
			len = (1 << j);
			for(i = 0; i + len - 1 < lcaSequence.size(); i++) {
				dp[i].push_back(MIN(dp[i][j-1], dp[i+len/2][j-1])); // dp[i][j]
			}
		}
		#undef MIN
	}

	public:	
	int getlca(int u, int v) {
		if(u == v) return u;
		int i = firstAppearance[u];
		int j = lastAppearance[v];
		if(i > j) { int tmp = i; i = j; j = tmp; }
		int len = j-i+1;
		int k = 1, l = 0;
		while(!(k >= len)) { k += k; l++; }
		k /= 2; l--;
		#define MIN(x, y) (((x)<(y))?(x):(y))
		pair<int, int> ans = MIN(dp[i][l], dp[j-k+1][l]);
		#undef MIN
		return lcaSequence[ans.second].first;
	}
	

	void initialise(int N, int root, vector<vector<int> > &adj) {
		this -> N = N;
		lcaCounter = 1;
		firstAppearance.resize(N+1);
		lastAppearance.resize(N+1);
		
		lcaDFS(root, adj);
		calculateRMQ();
	}		
};
