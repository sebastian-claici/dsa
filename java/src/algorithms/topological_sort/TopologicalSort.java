package algorithms.topological_sort;

import java.io.*;
import java.util.*;

/**
 * Implementation of a graph data structure. This example only
 * creates directed, unweighted graphs. Each graph is represented
 * by a set of nodes, and an adjacency list for each node.
 *
 * This is a simple implementation just for the sake of the topological
 * sort algorithm.
 *
 * @author Sebastian Claici
 */
public class TopologicalSort {

    public static class Graph<T> {

        private final Set<T> nodes;
        private final Map<T, List<T>> edges;

        /**
         * Creates an empty graph with no nodes and no edges.
         */
        public Graph() {
            nodes = new HashSet<T>();
            edges = new HashMap<T, List<T>>();
        }

        /**
         * Creates a graph with nodes taken from the nodes collection.
         *
         * @param nodes Initial set of nodes for this graph.
         */
        public Graph(Collection<T> nodes) {
            this.nodes = new HashSet<T>(nodes);
            this.edges = new HashMap<T, List<T>>();
        }

        /**
         * Adds an edge between src and dst.
         *
         * @param src Start node of the edge.
         * @param dst End node of the edge.
         */
        public void addEdge(T src, T dst) {
            nodes.add(src);
            nodes.add(dst);
            if (edges.containsKey(src)) {
                edges.get(src).add(dst);
            } else {
                List<T> list = new ArrayList<T>();
                list.add(dst);
                edges.put(src, list);
            }
        }

        /**
         * Retrieve a topological sort of this graph.
         *
         * A topological sort of a directed graph is a linear ordering of its
         * vertices such that for every directed edge u-v from node u to node v,
         * u comes before v in the ordering.
         *
         * For more information: http://en.wikipedia.org/wiki/Topological_sorting
         *
         * @return A list of nodes such that if u-v is an edge in the graph,
         *      then u comes before v in the list.
         */
        public List<T> topologicalSort() {
            // inDegree represents the amount of edges coming into each node
            Map<T, Integer> inDegree = new HashMap<T, Integer>();
            for (T node : nodes)
                inDegree.put(node, 0);

            for (T node : edges.keySet()) {
                for (T neighbour : edges.get(node)) {
                    inDegree.put(neighbour, inDegree.get(neighbour) + 1);
                }
            }

            Queue<T> queue = new LinkedList<T>();
            for (T node : nodes)
                if (inDegree.get(node) == 0)
                    queue.add(node);

            /*
             * Gradually remove nodes that have no incoming edges; remove all edges
             * starting in the removed node, and add all nodes that now have in-degree
             * 0 to the queue.
             */
            List<T> result = new ArrayList<T>();
            while (!queue.isEmpty()) {
                T node = queue.poll();
                result.add(node);

                if (!edges.containsKey(node))
                    continue;

                for (T neighbour : edges.get(node)) {
                    int degree = inDegree.get(neighbour);
                    --degree;
                    if (degree == 0)
                        queue.add(neighbour);
                    inDegree.put(neighbour, degree);
                }
            }

            return result;
        }
    }

    // Test code
    public static void main(String[] args) throws IOException {
        BufferedReader buf = new BufferedReader(new FileReader("topsort.in"));
        StringTokenizer st = new StringTokenizer(buf.readLine());

        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());

        Graph<Integer> graph = new Graph<Integer>();
        for (int i = 0; i < M; ++i) {
            st = new StringTokenizer(buf.readLine());
            int src = Integer.parseInt(st.nextToken());
            int dst = Integer.parseInt(st.nextToken());
            graph.addEdge(src, dst);
        }

        List<Integer> result = graph.topologicalSort();
        for (int x : result) {
            System.out.printf("%d ", x);
        }
        System.out.println();
    }
}
