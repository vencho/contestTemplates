/////////////////////////////////////////////////////
///////////// DO NOT TOUCH START. ///////////////////
/////////////////////////////////////////////////////

#include<cstdarg>

// #define i_am_debugging


class CellBase { 
	public:
	int L, R;
};

template<class TreeCell, class Answer>
class Operations {
	public:
	Operations<TreeCell, Answer>() {
	}
	virtual void pushNode(TreeCell &node, TreeCell &left, TreeCell &right) = 0;
	virtual void pushLeaf(TreeCell &node) = 0;
	virtual void fix(TreeCell &node, TreeCell &left, TreeCell &right) = 0;
	virtual void initialiseLeaf(TreeCell &node, int leafNo) = 0;
	virtual Answer answerFromCleanCell(TreeCell &node) = 0;
	virtual Answer answerCombine(Answer left, Answer right) = 0;
	virtual void addBottom(TreeCell &node, va_list args) = 0;
#ifdef i_am_debugging
	virtual void print(int w, TreeCell &node) = 0;
#endif
	virtual inline bool recursionBottomCondition(TreeCell &node, int a, int b) {
		return node.L == a && node.R == b;
	}
};

template<class TreeCell, class Answer>
class SegmentTree {
	private:
	std :: vector<TreeCell> T;
	int N;
	Operations<TreeCell, Answer> *Ops;
	
	Answer query_recurse(int a, int b, int w) {

		push(w);

		int M = (T[w].L + T[w].R) / 2;
		if(Ops -> recursionBottomCondition(T[w], a, b)) {
			return Ops -> answerFromCleanCell(T[w]);
		}
		if(b <= M) {
			return query_recurse(a, b, 2*w);
		}
		else if(a >= M+1) {
			return query_recurse(a, b, 2*w+1);
		}
		else {
			return Ops -> answerCombine(query_recurse(a, M, 2*w), query_recurse(M+1, b, 2*w+1));
		}
	}
	
	std::vector<int> bottomNumbers;
	void add_recurse(int a, int b, int w) {

		push(w);

		int M = (T[w].L + T[w].R)/2;
				
		if(Ops -> recursionBottomCondition(T[w], a, b)) {
			bottomNumbers.push_back(w);
			return;
		} 
		else if(b <= M) {
			add_recurse(a, b, 2*w);
		}
		else if(a >= M+1) {
			add_recurse(a, b, 2*w+1);
		}
		else {
			add_recurse(a, M, 2*w);
			add_recurse(M+1, b, 2*w+1);
		}
		

	}

void push(int w) {
	if(T[w].L == T[w].R) {
		Ops -> pushLeaf(T[w]);
	}
	else Ops -> pushNode(T[w], T[2*w], T[2*w+1]);
}


public:

#ifdef i_am_debugging
	void printTree() {
		for(int i = 1; i < T.size(); i++) {
			Ops -> print(i, T[i]);
		}
	}
#endif
	
	void initialise(int N, Operations<TreeCell, Answer> *ops) {
		T.clear();
		int leaves = 1, i;
		while(!(leaves >= N)) leaves += leaves;
		N = leaves;
		
		Ops = ops;

		T.resize(2*N);
		
		for(i = 2*N-1; i >= N; i--) {
			Ops -> initialiseLeaf(T[i], i-N+1);
			T[i].L = T[i].R = i-N+1;
		}
		
		for(i = N-1; i >= 1; i--) {
			T[i].L = T[2*i].L;
			T[i].R = T[2*i+1].R;
			Ops -> fix(T[i], T[2*i], T[2*i+1]);
		}
	}
	
	SegmentTree<TreeCell, Answer>(int n, Operations<TreeCell, Answer> *ops) {
		initialise(n, ops);
	}
	
	SegmentTree<TreeCell, Answer>() {
		
	}
	
	int getLeaves() {
		return N;
	}
	
	void add(int a, int b, ...) {
		int i, w, child;
		va_list args;
		bottomNumbers.clear();		
		if(a <= b) add_recurse(a, b, 1);
		
		for(i = 0; i < bottomNumbers.size(); i++) {
			va_start(args, b);
			w = bottomNumbers[i];
			Ops -> addBottom(T[w], args);
			child = w;
			w /= 2;
			if(w) {
				push(2*w);
				push(2*w+1);
			}
			
			while(1) {
				child = w;
				Ops -> fix(T[w], T[2*w], T[2*w+1]);
				w /= 2;
				if(w == 0) break;
				push(4*w + 1 - child);
			}
			va_end(args);
		}
	}

	Answer query(int a, int b) {
		return query_recurse(a, b, 1);
	}
};

/////////////////////////////////////////////////////
///////////// DO NOT TOUCH END. /////////////////////
/////////////////////////////////////////////////////
