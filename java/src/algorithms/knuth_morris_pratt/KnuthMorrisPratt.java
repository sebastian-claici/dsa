package algorithms.knuth_morris_pratt;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * @author Sebastian Claici
 */
public class KnuthMorrisPratt {

    public static List<Integer> match(String str, String pattern) {
        List<Integer> matches = new ArrayList<Integer>();

        List<Integer> pi = prefix(pattern);

        int k = 0;
        for (int i = 0; i < str.length(); ++i) {
            while (k >= pattern.length() || (k > 0 && str.charAt(i) != pattern.charAt(k)))
                k = pi.get(k - 1);

            if (str.charAt(i) == pattern.charAt(k))
                ++k;
            if (k == pattern.length())
                matches.add(i - pattern.length() + 1);
        }

        return matches;
    }

    private static List<Integer> prefix(String str) {
        List<Integer> pi = new ArrayList<Integer>();
        for (int i = 0; i < str.length(); ++i)
            pi.add(0);

        int k = 0;
        for (int i = 1; i < str.length(); ++i) {
            while (k > 0 && str.charAt(i) != str.charAt(k))
                k = pi.get(k - 1);

            if (str.charAt(i) == str.charAt(k))
                ++k;
            pi.set(i, k);
        }

        return pi;
    }

    // Test code
    public static void main(String[] args) throws IOException {
        BufferedReader buf = new BufferedReader(new FileReader("strmatch.in"));

        String pattern = buf.readLine();
        String str = buf.readLine();

        List<Integer> matches = match(str, pattern);
        System.out.println(matches.size());
        for (int match : matches)
            System.out.printf("%d ", match);
        System.out.println();
    }
}
