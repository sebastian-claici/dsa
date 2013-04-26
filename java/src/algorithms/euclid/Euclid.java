package algorithms.euclid;


/**
 * @author Sebastian Claici
 */
public class Euclid {

    public static int GCDRecursive(int a, int b) {
        if (b == 0)
            return a;
        return GCDRecursive(b, a % b);
    }

    public static int GCDIterative(int a, int b) {
        if (a < b) {
            int aux = a;
            a = b;
            b = aux;
        }

        while (b != 0) {
            int aux = a % b;
            a = b;
            b = aux;
        }

        return a;
    }
}
