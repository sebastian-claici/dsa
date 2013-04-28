package algorithms.longest_common_substring;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.StringTokenizer;

/**
 * Implementation of the longest common substring dynamic programming algorithm.
 *
 * The longest common substring problem is to find the longest string that is a
 * substring of two or more strings.
 *
 * Example: the longest common substring of the strings "ABABC" and "BABCA" is
 * "ABC".
 *
 * Time complexity: O(N * M), where N and M are the lengths of the two strings.
 *
 * @author Sebastian Claici
 */
public class LongestCommonSubstring {

    public static int[] longestCommonSubstring(int[] A, int[] B) {
        /*
         * best[i][j] - length of the longest common substring between
         *      A[0..i] and B[0..j]
         *
         * best[i][j] is computed as follows:
         *      best[i][j] = best[i - 1][j - 1] + 1, if A[i - 1] == B[j - 1]
         *          (we can extend the longest substring by 1)
         *      best[i][j] = max(best[i - 1][j], best[i][j - 1]) otherwise
         */
        int[][] best = new int[A.length + 1][B.length + 1];

        for (int i = 1; i <= A.length; ++i) {
            for (int j = 1; j <= B.length; ++j) {
                if (A[i - 1] == B[j - 1]) {
                    best[i][j] = best[i - 1][j - 1] + 1;
                } else {
                    best[i][j] = Math.max(best[i - 1][j], best[i][j - 1]);
                }
            }
        }

        int size = best[A.length][B.length];
        int[] result = new int[size];

        // Build the result by walking the best array backwards
        int i = A.length, j = B.length;
        while (i != 0 && j != 0) {
            if (A[i - 1] == B[j - 1]) {
                result[--size] = A[i - 1];
                --i;
                --j;
            } else if (best[i - 1][j] > best[i][j - 1]) {
                --i;
            } else {
                --j;
            }
        }

        return result;
    }

    // Test code
    public static void main(String[] args) throws Exception {
        BufferedReader buf = new BufferedReader(new FileReader("lcs.in"));
        StringTokenizer st = new StringTokenizer(buf.readLine());

        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());

        st = new StringTokenizer(buf.readLine());
        int[] A = new int[n];
        for (int i = 0; i < n; ++i)
            A[i] = Integer.parseInt(st.nextToken());

        st = new StringTokenizer(buf.readLine());
        int[] B = new int[m];
        for (int i = 0; i < m; ++i)
            B[i] = Integer.parseInt(st.nextToken());

        int[] result = LongestCommonSubstring.longestCommonSubstring(A, B);
        System.out.println(result.length);
        for (int x : result)
            System.out.printf("%d ", x);
        System.out.println();
    }
}
