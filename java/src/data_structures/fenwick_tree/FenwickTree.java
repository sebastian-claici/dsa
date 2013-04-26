package data_structures.fenwick_tree;

import java.util.Collection;

/**
 * This class implements a Fenwick tree data structure.
 * 
 * A Fenwick tree or binary indexed tree is a data structure providing efficient
 * methods for calculation and manipulation of the prefix sums of a table of
 * values.
 * 
 * For more information: http://en.wikipedia.org/wiki/Fenwick_tree
 * 
 * @author Sebastian Claici
 * 
 */
public class FenwickTree {
	/*
	 * The element at position i in a Fenwick tree stores the cumulative
	 * frequency for the range [i - 2 ^ r + 1, i], where r is the lowest set bit
	 * in the binary representation of i.
	 */

	private final int size;
	private final int[] tree;

	/**
	 * Constructs a Fenwick tree from init. Each element in the resulting tree
	 * will hold the cumulative frequency up to that point according to the
	 * iterator of the Collection.
	 * 
	 * @param init
	 *            A Collection with the initial values.
	 */
	public FenwickTree(Collection<Integer> init) {
		size = init.size();
		tree = new int[init.size() + 1];

		int i = 1;
		for (Integer value : init)
			update(i++, value);
	}

	/**
	 * Constructs a Fenwick tree of a specified size. Each element in the tree
	 * will be initially 0.
	 * 
	 * @param size
	 *            Size of the tree to be constructed.
	 */
	public FenwickTree(int size) {
		this.size = size;
		tree = new int[size + 1];
	}

	/**
	 * Queries the cumulative frequency at id.
	 * 
	 * @param id
	 *            The index (1-based) to query.
	 * @return An integer representing the cumulative frequency up to id
	 *         (inclusive).
	 */
	public int query(int id) {
		int result = 0;
		while (id > 0) {
			result += tree[id];
			/*
			 * To query an index, we need all indices that were not included in
			 * previous intervals of form [i - 2 ^ r + 1, i]. That is, we need
			 * to find the next lowest number that does not have the lowest bit
			 * in i set. (id & -id) represents the lowest bit in id; by
			 * subtracting this we reach the next number we need to query.
			 */
			id -= (id & -id);
		}

		return result;
	}

	/**
	 * Queries the cumulative frequency in the range [left, right].
	 * 
	 * @param left
	 *            Leftmost index of the range being queried.
	 * @param right
	 *            Rightmost index of the range being queried.
	 * @return An integer representing the cumulative frequency between left and
	 *         right (both inclusive).
	 */
	public int query(int left, int right) {
		return query(right) - query(left - 1);
	}

	/**
	 * Updates the value at index id by adding toAdd to it.
	 * 
	 * @param id
	 *            Index which should be updated.
	 * @param toAdd
	 *            Amount to add to the element at index id.
	 */
	public void update(int id, int toAdd) {
		while (id <= size) {
			tree[id] += toAdd;
			/*
			 * To update an index, we need to update all indices that subsume
			 * the current range [i - 2 ^ r + 1, i]. That is, we need to find
			 * the next highest number that has the lowest bit of i unset.
			 */
			id += (id & -id);
		}
	}

	/**
	 * Find an index k in the Fenwick tree such that the cumulative frequency up
	 * to k is exactly equal to sum.
	 * 
	 * @param sum
	 *            Sum for which an index should be found.
	 * @return The index (1-based) in the tree where this occurs, or -1 if no
	 *         index satisfies the requirements.
	 */
	public int find(int sum) {
		int bitmask = 1;
		for (; bitmask <= size; bitmask *= 2)
			;

		for (int i = 0; bitmask != 0; bitmask /= 2) {
			if (i + bitmask <= size) {
				if (tree[i + bitmask] <= sum) {
					i += bitmask;
					sum -= tree[i];
					if (sum == 0)
						return i;
				}
			}
		}

		return -1;
	}
}
