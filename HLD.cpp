class HLD {
	public:
	void decompose(int N, int root, vector<vector<int> > &adj) {
		whichChain.resize(N+1);
		positionInChain.resize(N+1);
		treesize.resize(N+1);
		calculateTreeSize(root, adj);
		makeNewChain();
		addVertexToChain(root, 0);	
		buildChains(root, 0, adj);
	}
	
	
	vector<int> whichChain;
	vector<int> positionInChain;
	vector<vector<int> > chains;
	vector<int> treesize;

	private:
	void makeNewChain() {
		chains.push_back(vector<int>());
	}

	void addVertexToChain(int v, int c) {
		whichChain[v] = c;
		positionInChain[v] = chains[c].size();
		chains[c].push_back(v);
	}

	void calculateTreeSize(int v, vector<vector<int> > &adj) {
		treesize[v] = 1;
		for(int i = 0; i < adj[v].size(); i++) {
			calculateTreeSize(adj[v][i], adj);
			treesize[v] += treesize[adj[v][i]];
		}
	}

	void buildChains(int v, int chainNum, vector<vector<int> > &adj) {

		int i, j, u, bestu, best;
	
		bestu = -1; best = 0;
		for(i = 0; i < adj[v].size(); i++) {
			u = adj[v][i];
			if(best < treesize[u]) {
				best = treesize[u];
				bestu = u;
			}
		}

		if(bestu == -1) return;
	
		addVertexToChain(bestu, chainNum);
		buildChains(bestu, chainNum, adj);
	
		for(i = 0; i < adj[v].size(); i++) {
			u = adj[v][i];
			if(u != bestu) {
				makeNewChain();
				addVertexToChain(u, chains.size()-1);
				buildChains(u, chains.size()-1, adj);
			}
		}
	}
};

