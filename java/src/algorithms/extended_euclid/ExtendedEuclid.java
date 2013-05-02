package algorithms.extended_euclid;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.StringTokenizer;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * Implementation of the extended Euclidean algorithm.
 *
 * @author Sebastian Claici
 */
public class ExtendedEuclid {

    /**
     * The extended Euclidean algorithm is used for finding integer solution
     * for the equation:
     *
     *          a * x + b * y = d
     *
     * where d is the greatest common divisor of a and b.
     *
     * We know that a * x + b * y = d for some x, y; due to the Euclidean
     * algorithm, we must also have:
     *
     *          b * x0 + (a % b) * y0 = d
     *
     * If we rewrite a % b = a - b * (a div b), where a div b is the integer part
     * of a / b, and group terms, we obtain:
     *
     *          b * (x0 - (a div b) * y0 - y) = a * (x - y0)
     *
     * From here, one solution is:
     *
     *          x = y0
     *          y = x0 - (a div b) * y0
     *
     * All that remains is the initial solution. When b == 0, we have that
     * a == d, so the initial solution can simply be:
     *
     *          x = 1
     *          y = 0
     *
     * @param a First coefficient
     * @param b Second coefficient
     * @param d Array of one element that will hold the greatest common divisor of a and b
     * @param x Array of one element that will hold the first variable
     * @param y Array of one element that will hold the second variable
     */
    public static void extendedEuclid(int a, int b, int[] d, int[] x, int[] y) {
        if (b == 0) {
            d[0] = a;
            x[0] = 1;
            y[0] = 0;
        } else {
            int[] x0 = new int[1];
            int[] y0 = new int[1];
            extendedEuclid(b, a % b, d, x0, y0);
            x[0] = y0[0];
            y[0] = x0[0] - a / b * y0[0];
        }
    }

    /*
     * Test code:
     *      Find a solution of a * x + b * y = c with given a, b, c.
     */
    public static void main(String[] args) throws IOException {
        BufferedReader buf = new BufferedReader(new FileReader("euclid3.in"));

        int T = Integer.parseInt(buf.readLine());
        for (int i = 0; i < T; ++i) {
            StringTokenizer st = new StringTokenizer(buf.readLine());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            int c = Integer.parseInt(st.nextToken());

            int[] d = new int[1];
            int[] x = new int[1];
            int[] y = new int[1];
            extendedEuclid(a, b, d, x, y);
            if (c % d[0] != 0) {
                System.out.println(0 + " " + 0);
            } else {
                int x0 = x[0] * (c / d[0]);
                int y0 = y[0] * (c / d[0]);
                System.out.println(x0 + " " + y0);
            }
        }
    }

}
