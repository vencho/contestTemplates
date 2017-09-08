/////////////////////////////////////////////////////
///////////// Sample start. /////////////////////////
/////////////////////////////////////////////////////

/* FIXME: Add here the members of your tree cell, other than L and R. */
class Cell : public CellBase {
	public:
	long long sum, lazy;
};

class Ops : public Operations<Cell, long long> {
	public:

	/* FIXME: What initial values does a leaf cell have, given its number? Set them. Don't worry about L and R. */
	void initialiseLeaf(Cell &node, int leafNo) {
		node.lazy = node.sum = 0;
	}

	/* FIXME: This node and all nodes above it are guaranteed to be clean. 
	Tell me what the answer is for this node's interval of responsibility. */
	long long answerFromCleanCell(Cell &node) {
		return node.sum;
	}

	/* FIXME: This node is clean, but its children need not be. 
	What must be done to this node for an update if it is at the bottom of the recursion? */
	void addBottom(Cell &node, va_list args) {
		long long v = va_arg(args, long long);
		node.lazy += v;
	}

	/* FIXME: node is guaranteed to be a leaf. How do we push from it? */
	void pushLeaf(Cell &node) {
		node.sum += node.lazy;
		node.lazy = 0;
	}
	
	/* FIXME: left and right are node's children. Any and all of them might be dirty. 
	How to push the dirtiness from node onto its children? */
	void pushNode(Cell &node, Cell &left, Cell &right) {
		left.lazy += node.lazy;
		right.lazy += node.lazy;
		node.sum += 1LL*(node.R-node.L+1)*node.lazy;
		node.lazy = 0;
	}
	
	/* FIXME: How do answers to queries for adjacent intervals combine? 
	Typically sum or maximum. */
	long long answerCombine(long long left, long long right) {
		return left + right;
	}
	
	/* FIXME: left and right are node's children. All three guaranteed to be clean.
	How should the data variables of node be updated using those of left and right
	on the return path of the "add" recursion? (Don't touch lazy variables here.)
	*/
	void fix(Cell &node, Cell &left, Cell &right) {
		node.sum = left.sum + right.sum;
	}
	
#ifdef i_am_debugging
	void print(int w, Cell &node) {
		printf("T[%d]: [%d, %d], sum %lld, lazy %lld\n", w, node.L, node.R, node.sum, node.lazy);		
	}
#endif
};

/////////////////////////////////////////////////////
///////////// Sample end. ///////////////////////////
/////////////////////////////////////////////////////

