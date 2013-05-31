package algorithms.depth_first_search;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.StringTokenizer;

/**
 * @author Sebastian Claici
 */
public class ConnectedComponents {
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
                List<T> adjacencyList = edges.get(src);
                adjacencyList.add(dst);
                edges.put(src, adjacencyList);
            } else {
                List<T> adjacencyList = new ArrayList<T>();
                adjacencyList.add(dst);
                edges.put(src, adjacencyList);
            }

            if (edges.containsKey(dst)) {
                List<T> adjacencyList = edges.get(dst);
                adjacencyList.add(src);
                edges.put(dst, adjacencyList);
            } else {
                List<T> adjacencyList = new ArrayList<T>();
                adjacencyList.add(src);
                edges.put(dst, adjacencyList);
            }
        }

        public int connectedComponents() {
            int result = 0;

            Set<T> visited = new HashSet<T>();
            for (T node : nodes) {
                if (!visited.contains(node)) {
                    ++result;
                    dfs(node, visited);
                }
            }

            return result;
        }

        private void dfs(T node, Set<T> visited) {
            visited.add(node);

            if (!edges.containsKey(node))
                return;

            for (T next : edges.get(node)) {
                if (!visited.contains(next))
                    dfs(next, visited);
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader buf = new BufferedReader(new FileReader("dfs.in"));
        StringTokenizer st = new StringTokenizer(buf.readLine());

        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());

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

        System.out.println(graph.connectedComponents());
    }
}
