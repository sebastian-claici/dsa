package data_structures.disjoint_set;

/**
 * This class implements a disjoint-set data structure.
 * 
 * A disjoint-set data structure is a data structure that keeps track of a set
 * of elements partitioned into a number of disjoint (nonoverlapping) subsets. A
 * union-find algorithm is an algorithm that performs two operations on such a
 * data structure:
 * 
 * <ul>
 * <li>Find: determine which subset a particular element is in.</li>
 * <li>Union: Join two subsets into a single subset.</li>
 * </ul>
 * 
 * For more information:
 * http://en.wikipedia.org/wiki/Disjoint-set_data_structure
 * 
 * @author Sebastian Claici
 * 
 */
public class DisjointSet {

	private final int[] parent;
	private final int[] rank;

	/**
	 * Constructs a disjoint-set of a specified size.
	 * 
	 * @param size
	 *            Size of the resulting data-structure.
	 */
	public DisjointSet(int size) {
		parent = new int[size];
		rank = new int[size];
		
		for (int i = 0; i < size; ++i) {
			parent[i] = i;
			rank[i] = 0;
		}
	}

	/**
	 * Returns the subset in which x is located.
	 * 
	 * @param x
	 *            The node for which we want to find the enclosing subset.
	 * @return The root node of the subset in which x is located.
	 */
	public int find(int x) {
		if (x == parent[x])
			return x;

		/*
		 * To speed-up future queries, we apply path compression; for any
		 * particular node all we care about is the root node of the component
		 * in which it is in. Thus, all intermediary paths can be compressed
		 * into one that leads from the node we just queried to the root
		 * element.
		 */
		return parent[x] = find(parent[x]);
	}

	/**
	 * Join the subsets in which x and y are located into one subset.
	 * 
	 * @param x
	 *            Element found in the first subset.
	 * @param y
	 *            Element found in the second subset.
	 */
	public void union(int x, int y) {
		int px = find(x);
		int py = find(y);

		/*
		 * When we unite two components, the one that is "heavier" (has more
		 * elements attached) becomes the parent of the other. This effectively
		 * balances the tree; if no element is "heavier", then one component is
		 * chosen at random to be the root.
		 */
		if (rank[px] < rank[py]) {
			parent[px] = py;
		} else {
			parent[py] = px;
		}

		if (rank[px] == rank[py])
			++rank[px];
	}

	/**
	 * Query whether the elements x and y are in the same component.
	 * 
	 * @param x
	 *            Element to be queried.
	 * @param y
	 *            Element to be queried.
	 * @return <b>true</b> if x and y are in the same component, <b>false</b>
	 *         otherwise.
	 */
	public boolean sameComponent(int x, int y) {
		return find(x) == find(y);
	}
}
