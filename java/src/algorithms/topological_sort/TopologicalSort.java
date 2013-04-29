package algorithms.topological_sort;

import java.io.*;
import java.util.*;

/**
 * @author Sebastian Claici
 */
public class TopologicalSort {

    public static class Graph<T> {

        private final Set<T> nodes;
        private final Map<T, List<T>> edges;

        public Graph() {
            nodes = new HashSet<T>();
            edges = new HashMap<T, List<T>>();
        }

        public Graph(Collection<T> nodes) {
            this.nodes = new HashSet<T>(nodes);
            this.edges = new HashMap<T, List<T>>();
        }

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

        public List<T> topologicalSort() {
            Map<T, Integer> in_degree = new HashMap<T, Integer>();
            for (T node : nodes)
                in_degree.put(node, 0);

            for (T node : edges.keySet()) {
                for (T neighbour : edges.get(node)) {
                    in_degree.put(neighbour, in_degree.get(neighbour) + 1);
                }
            }

            Queue<T> queue = new LinkedList<T>();
            for (T node : nodes)
                if (in_degree.get(node) == 0)
                    queue.add(node);

            List<T> result = new ArrayList<T>();
            while (!queue.isEmpty()) {
                T node = queue.poll();
                result.add(node);

                if (!edges.containsKey(node))
                    continue;

                for (T neighbour : edges.get(node)) {
                    int degree = in_degree.get(neighbour);
                    --degree;
                    if (degree == 0)
                        queue.add(neighbour);
                    in_degree.put(neighbour, degree);
                }
            }

            return result;
        }
    }

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
