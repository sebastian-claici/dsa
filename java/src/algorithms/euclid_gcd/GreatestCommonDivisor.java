package algorithms.euclid_gcd;

/**
 * @author Sebastian Claici
 */
public class GreatestCommonDivisor {
    /**
     * Recursive implementation of the Euclidean algorithm for finding
     * the greatest common divisor of two integers.
     *
     * @param a first integer
     * @param b second integer
     * @return the greatest common divisor of a and b
     */
    public static int GCDRecursive(int a, int b) {
        if (b == 0)
            return a;
        return GCDRecursive(b, a % b);
    }

    /**
     * Iterative implementation of the Euclidean algorithm for finding
     * the greatest common divisor of two integers.
     *
     * @param a first integer
     * @param b second integer
     * @return the greatest common divisor of a and b
     */
    public static int GCDIterative(int a, int b) {
        while (b != 0) {
            int aux = a % b;
            a = b;
            b = aux;
        }

        return a;
    }
}
