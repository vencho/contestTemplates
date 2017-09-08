class SuffixArray {
	public:

/*
Test:
abracadabra0AbRa4Cad14abra
11 20 16 21 12 17 14 25 10 15 22 7 0 3 18 5 13 23 8 1 4 19 6 24 9 2
*/
	static void constructSuffixArray(string &s, vector<int> &A, vector<int> &B, vector<int> &lcp) {
		firstStep(s, A, B);
		for(int T = 1;; T = 2*T) {
			if(oneStep(A, B, T)) break;
		}
		constructLCP(s, A, B, lcp);
	}
	
	private:
	static string *x;

	static void constructLCP(string &s, vector<int> &A, vector<int> &B, vector<int> &lcp) {
		int N = A.size();
		lcp.resize(N);

		if(B[0] == N-1) {
			lcp[B[0]] = -1;
		}
		else {
			lcp[B[0]] = matchNaively(s, 0, A[B[0] + 1], 0);
		}
		
		for(int i = 1; i < N; i++) {
			if(B[i] == N-1) {
				lcp[B[i]] = -1;
				continue;
			}
		lcp[B[i]] = matchNaively(s, i, A[B[i]+1], lcp[B[i-1]]-1);
		}
	}
	
	static int matchNaively(string &s, int x, int y, int guaranteed) {
		if(guaranteed < 0) guaranteed = 0;
		x += guaranteed;
		y += guaranteed;
		int k;
		for(k = 0; x+k < s.length() && y+k < s.length(); k++) {
			if(s[x+k] != s[y+k]) break;
		}
		return k + guaranteed;
	}
	
	static bool lss(int i, int j) {
		if( (*x)[i] != (*x)[j] ) return (*x)[i] < (*x)[j];
		return i < j;
	}
	
	static void firstStep(string &s, vector<int> &A, vector<int> &B) {
		A.resize(s.length());
		B.resize(s.length());
		for(int i = 0; i < s.length(); i++) {
			A[i] = i;
		}

		x = &s;
		sort(A.begin(), A.end(), lss);
		for(int i = 0; i < s.length(); i++) {
			if(i == 0 || s[A[i]] != s[A[i-1]]) {
				B[A[i]] = i;
			}
			else {
				B[A[i]] = B[A[i-1]];
			}
		}
	}
	
	static bool oneStep(vector<int> &A, vector<int> &B, int T) {
		
		int N = A.size();
		vector<int> bCount, C;
		bCount.resize(N);
		C.resize(N);
		
		for(int i = 0; i < N; i++) {
			bCount[i] = 0;
		}
		
		for(int i = N-T; i < N; i++) {
			int val = i;
			C[ B[val] + bCount[B[val]] ] = val;
			bCount[B[val]]++;
		}
		
		for(int i = 0; i < N; i++) {
			int val = A[i] - T;
			if(val < 0) continue;
			C[ B[val] + bCount[B[val]] ] = val;
			bCount[B[val]]++;
		}
		
		A = C;
		
		vector<int> D;
		D.resize(N);
		bool done = true;
		
		if(N) D[A[0]] = 0;
		for(int i = 1; i < N; i++) {
			if(B[A[i-1]] != B[A[i]] || A[i-1] + T >= N || B[A[i-1] + T] != B[A[i] + T]) {
				D[A[i]] = i;
			}
			else {
				D[A[i]] = D[A[i-1]];
				done = false;				
			}
		}
		B = D;
		return done;
	}
	
};
string * SuffixArray::x;

