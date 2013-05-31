package algorithms.breadth_first_search;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

/**
 * @author Sebastian Claici
 */
public class BreadthFirstSearch {

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

        public Map<T, Integer> distances(T src) {
            Map<T, Integer> result = new HashMap<T, Integer>();
            bfs(src, result);

            for (T node : nodes) {
                if (!result.containsKey(node))
                    result.put(node, -1);
            }

            return result;
        }

        private void bfs(T src, Map<T, Integer> result) {
            Queue<T> queue = new LinkedList<T>();
            Set<T> visited = new HashSet<T>();

            result.put(src, 0);
            queue.add(src);
            visited.add(src);
            while (!queue.isEmpty()) {
                T node = queue.poll();

                if (!edges.containsKey(node))
                    continue;

                int d = result.get(node);
                for (T next : edges.get(node)) {
                    if (!visited.contains(next)) {
                        visited.add(next);
                        result.put(next, d + 1);
                        queue.add(next);
                    }
                }
            }
        }

    }

    public static void main(String[] args) throws IOException {
        BufferedReader buf = new BufferedReader(new FileReader("bfs.in"));
        StringTokenizer st = new StringTokenizer(buf.readLine());

        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());
        int S = Integer.parseInt(st.nextToken());

        List<Integer> v = new ArrayList<Integer>();
        for (int i = 1; i <= N; ++i)
            v.add(i);

        Graph<Integer> graph = new Graph<Integer>(v);
        for (int i = 0; i < M; ++i) {
            st = new StringTokenizer(buf.readLine());
            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());
            graph.addEdge(x, y);
        }

        System.out.println(graph.distances(S));
    }
}
