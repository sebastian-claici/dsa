package algorithms.eratosthenes_sieve;

import java.util.ArrayList;
import java.util.BitSet;
import java.util.List;

/**
 * Implementation of the sieve of Eratosthenes algorithm for finding
 * all prime numbers up to a specified limit.
 *
 * @author Sebastian Claici
 */
public class EratosthenesSieve {

    /**
     * Returns a list of all prime numbers up to (and including) N.
     *
     * Time complexity: O(N * log(log(N)))
     *
     * @param N Upper bound up to which primes should be computed.
     * @return A list of integers representing the prime numbers up to N.
     */
    public static List<Integer> sieve(int N) {
        List<Integer> primes = new ArrayList<Integer>();

        // Initially all numbers are considered prime
        BitSet bitSet = new BitSet(N);
        bitSet.flip(0, bitSet.size());

        for (int i = 2; i <= N; ++i) {
            if (bitSet.get(i)) {
                primes.add(i);

                long limit = (long) i * i;
                if (limit > N)
                    continue;

                // Mark all multiples of i as non-prime
                for (int j = i * i; j <= N; j += i)
                    bitSet.set(j, false);
            }
        }

        return primes;
    }

    // Test code
    public static void main(String[] args) {
        List<Integer> primes = sieve(100);
        int[] primesTo100 = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
                59, 61, 67, 71, 73, 79, 83, 89, 97};

        boolean correct = true;
        for (int i = 0; i < primes.size(); ++i)
            if (primes.get(i) != primesTo100[i]) {
                correct = false;
                break;
            }

        if (!correct)
            System.out.println("Wrong answer");
        else
            System.out.println("Correct");
    }
}
