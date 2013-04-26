package algorithms.longest_common_substring;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.StringTokenizer;

/**
 * @author Sebastian Claici
 */
public class LongestCommonSubstring {

    public static int[] longestCommonSubstring(int[] A, int[] B) {
        int[][] dp = new int[A.length + 1][B.length + 1];

        for (int i = 1; i <= A.length; ++i) {
            for (int j = 1; j <= B.length; ++j) {
                if (A[i - 1] == B[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = Math.max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        int size = dp[A.length][B.length];
        int[] result = new int[size];

        int i = A.length, j = B.length;
        while (i != 0 && j != 0) {
            if (A[i - 1] == B[j - 1]) {
                result[--size] = A[i - 1];
                --i;
                --j;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                --i;
            } else {
                --j;
            }
        }

        return result;
    }

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
