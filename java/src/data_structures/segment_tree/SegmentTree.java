package data_structures.segment_tree;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;
import java.util.StringTokenizer;

/**
 * This class implements a segment tree data structure.
 * 
 * A segment tree is a tree data structure for storing intervals. It allows
 * querying which of the stored segments contain a given point. A segment tree
 * for a set of n intervals uses O(n * logn) storage and can be built in O(n *
 * logn) time.
 * 
 * For more information: http://en.wikipedia.org/wiki/Segment_tree
 * 
 * @author Sebastian Claici
 * 
 * @param <T>
 *            Any type which can be compared to others of its type.
 */
public class SegmentTree<T extends Comparable<? super T>> {

	public static void main(String[] args) throws Exception {
		BufferedReader buf = new BufferedReader(new FileReader("arbint.in"));
		StringTokenizer st = new StringTokenizer(buf.readLine());

		int N = Integer.parseInt(st.nextToken());
		int M = Integer.parseInt(st.nextToken());
		st = new StringTokenizer(buf.readLine());

		List<Integer> list = new ArrayList<Integer>();
		for (int i = 0; i < N; ++i) {
			int x = Integer.parseInt(st.nextToken());
			list.add(x);
		}

		SegmentTree<Integer> tree = new SegmentTree<Integer>(list);
		for (int i = 0; i < M; ++i) {
			st = new StringTokenizer(buf.readLine());
			int op = Integer.parseInt(st.nextToken());
			int x = Integer.parseInt(st.nextToken());
			int y = Integer.parseInt(st.nextToken());

			if (op == 0) {
				System.out.println(tree.query(x - 1, y - 1));
			} else {
				tree.update(x - 1, x - 1, y);
			}
		}
	}

	private final int size;
	private final T[] tree;
	private Comparator<T> comparator;

	/**
	 * Constructs a segment tree with enough nodes to hold an interval of length
	 * size.
	 * 
	 * @param size
	 *            Length of the top-level interval
	 */
	@SuppressWarnings("unchecked")
	public SegmentTree(int size) {
		this.size = size;
		comparator = null;

		int pow2 = 1;
		while (pow2 <= size)
			pow2 *= 2;
		pow2 *= 2;

		tree = (T[]) new Comparable[pow2];
	}

	/**
	 * Constructs a segment tree with enough nodes to hold an interval of length
	 * size. The comparison function is given by comparator.
	 * 
	 * @param size
	 *            Length of the top-level interval
	 * @param comparator
	 *            Comparator that dictates how larger intervals are constructed
	 *            according to their children.
	 */
	@SuppressWarnings("unchecked")
	public SegmentTree(int size, Comparator<T> comparator) {
		this.size = size;
		this.comparator = comparator;

		int pow2 = 1;
		while (pow2 <= size)
			pow2 *= 2;
		pow2 *= 2;

		tree = (T[]) new Comparable[pow2];
	}

	/**
	 * Constructs a segment tree where each interval of form [x, x] holds
	 * initValue.get(x).
	 * 
	 * @param initValues
	 *            Collection with initial values on intervals of size 1.
	 */
	@SuppressWarnings("unchecked")
	public SegmentTree(Collection<T> initValues) {
		size = initValues.size();
		comparator = null;

		int pow2 = 1;
		while (pow2 <= initValues.size())
			pow2 *= 2;
		pow2 *= 2;

		tree = (T[]) new Comparable[pow2];

		init(1, 0, size - 1, initValues.iterator());
	}

	/**
	 * Constructs a segment tree where each interval of form [x, x] holds
	 * initValue.get(x). The comparison function is given by comparator.
	 * 
	 * @param initValues
	 *            Collection with initial values on intervals of size 1.
	 * @param comparator
	 *            Comparator that dictates how larger intervals are constructed
	 *            according to their children.
	 */
	@SuppressWarnings("unchecked")
	public SegmentTree(Collection<T> initValues, Comparator<T> comparator) {
		size = initValues.size();
		this.comparator = comparator;

		int pow2 = 1;
		while (pow2 <= initValues.size())
			pow2 *= 2;
		pow2 *= 2;

		tree = (T[]) new Comparable[pow2];

		init(1, 0, size - 1, initValues.iterator());
	}

	/**
	 * Update the value in the interval [left, right] to be val.
	 * 
	 * Complexity: O(logn)
	 * 
	 * @param left
	 *            Left edge of the interval to be updated.
	 * @param right
	 *            Right edge of the interval to be updated.
	 * @param val
	 *            Value with which to update the interval [left, right].
	 */
	public void update(int left, int right, T val) {
		update(1, 0, size - 1, left, right, val);
	}

	/**
	 * Return the value associated with the interval [left, right].
	 * 
	 * Complexity: O(logn)
	 * 
	 * @param left
	 *            Left edge of the queried interval.
	 * @param right
	 *            Right edge of the queried interval.
	 * @return The value associated with the interval [left, right].
	 */
	public T query(int left, int right) {
		return query(1, 0, size - 1, left, right);
	}

	private void init(int node, int left, int right, Iterator<T> iter) {
		if (left == right) {
			tree[node] = iter.next();
		} else {
			int mid = left + (right - left) / 2;
			init(2 * node, left, mid, iter);
			init(2 * node + 1, mid + 1, right, iter);

			/*
			 * Update the current node with the maximum of the two children
			 * according to the comparator (if present), or the natural ordering
			 * otherwise.
			 */
			T leftRes = tree[2 * node];
			T rightRes = tree[2 * node + 1];
			if (leftRes == null) {
				if (rightRes == null)
					tree[node] = leftRes;
				tree[node] = rightRes;
			} else if (rightRes == null) {
				tree[node] = leftRes;
			} else {
				int comp = 0;
				if (comparator != null) {
					comp = comparator.compare(leftRes, rightRes);
				} else {
					comp = leftRes.compareTo(rightRes);
				}

				if (comp > 0)
					tree[node] = leftRes;
				else
					tree[node] = rightRes;
			}
		}
	}

	private void update(int node, int left, int right, int x, int y, T val) {
		if (x <= left && right <= y) {
			tree[node] = val;
		} else {
			int mid = left + (right - left) / 2;
			if (x <= mid)
				update(2 * node, left, mid, x, y, val);
			if (y > mid)
				update(2 * node + 1, mid + 1, right, x, y, val);

			/*
			 * Update the current node with the maximum of the two children
			 * according to the comparator (if present), or the natural ordering
			 * otherwise.
			 */
			T leftRes = tree[2 * node];
			T rightRes = tree[2 * node + 1];
			if (leftRes == null) {
				if (rightRes == null)
					tree[node] = leftRes;
				tree[node] = rightRes;
			} else if (rightRes == null) {
				tree[node] = leftRes;
			} else {
				int comp = 0;
				if (comparator != null) {
					comp = comparator.compare(leftRes, rightRes);
				} else {
					comp = leftRes.compareTo(rightRes);
				}

				if (comp > 0)
					tree[node] = leftRes;
				else
					tree[node] = rightRes;
			}
		}
	}

	private T query(int node, int left, int right, int x, int y) {
		if (x <= left && right <= y) {
			return tree[node];
		} else {
			int mid = left + (right - left) / 2;

			T leftRes = null, rightRes = null;
			if (x <= mid)
				leftRes = query(2 * node, left, mid, x, y);
			if (y > mid)
				rightRes = query(2 * node + 1, mid + 1, right, x, y);

			if (leftRes == null) {
				if (rightRes == null)
					return leftRes;
				return rightRes;
			} else if (rightRes == null) {
				return leftRes;
			} else {
				int comp = 0;
				if (comparator != null) {
					comp = comparator.compare(leftRes, rightRes);
				} else {
					comp = leftRes.compareTo(rightRes);
				}

				if (comp > 0)
					return leftRes;
				else
					return rightRes;
			}
		}
	}
}
