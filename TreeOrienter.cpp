class TreeOrienter {
	private:
	int N;
	vector<pair<int, int> > e;
	vector<int> begin;
	vector<int> parent;
	vector<vector<int> > adj;

	public:
	TreeOrienter() { }
	
	
	TreeOrienter(int N) {
		initialise(N);
	}

	void initialise(int N) {
		this -> N = N;
		adj.clear();
		begin.clear();
		parent.clear();
		e.clear();
				
		begin.resize(N+1);
		parent.resize(N+1);
		adj.resize(N+1);
	}
	
	void add_edge(int a, int b) {
		e.push_back(make_pair(a, b));
		e.push_back(make_pair(b, a));
	}
	
	void orient(int root) {
		int i;
		
		for(i = 1; i <= N; i++) { 
			begin[i] = parent[i] = 0;
		}

		sort(e.begin(), e.end());

		if(e.size()) begin[e[0].first] = 0;
		for(i = 1; i < e.size(); i++) {
			if(e[i].first != e[i-1].first) {
				begin[e[i].first] = i;
			}
		}

		parent[root] = -1;
		dfs(root);
	}

	vector<int> & getParents() {
		return parent;
	}
	
	vector<vector<int> > &getAdj() {
		return adj;
	}

	void dfs(int v) {
		for(int i = begin[v]; i < e.size() && e[i].first == v; i++) {
			if(parent[v] != e[i].second) {
				parent[e[i].second] = v;
				adj[v].push_back(e[i].second);
				dfs(e[i].second);
			}
		}
	}
	
};

