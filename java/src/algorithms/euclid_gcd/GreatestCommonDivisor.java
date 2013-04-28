package algorithms.euclid_gcd;

/**
 * @author Sebastian Claici
 */
public class GreatestCommonDivisor {
    public static int GCDRecursive(int a, int b) {
        if (b == 0)
            return a;
        return GCDRecursive(b, a % b);
    }

    public static int GCDIterative(int a, int b) {
        while (b != 0) {
            int aux = a % b;
            a = b;
            b = aux;
        }

        return a;
    }
}
