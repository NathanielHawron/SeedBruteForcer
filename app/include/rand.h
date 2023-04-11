#pragma once
/*
    A c++ port of java.util.random
*/

#include <cstdint>
#include <stdexcept>

class Random{
private:
    //Random function without the overhead of instantiation
    static int32_t s_next(int64_t seed, int32_t bits) {
        int64_t oldseed, nextseed;
        int64_t cseed = seed;
        while(true) {
            oldseed = cseed;
            nextseed = (oldseed * multiplier + addend) & mask;
            if(cseed == oldseed){
                seed = nextseed;
                break;
            }
        }
        return (int32_t)(nextseed >> (48 - bits));
    }
public:
    //Function version of Random::nextInt(int32_t n);
    static int32_t randomInt(int64_t seed, uint32_t n){
        seed = initialScramble(seed);

        if ((n & -n) == n)  // i.e., n is a power of 2
            return (int)((n * (long)s_next(seed,31)) >> 31);

        int bits, val;
        do {
            bits = s_next(seed,31);
            val = bits % n;
        } while (bits - val + (n-1) < 0);
        return val;

    }
    /** use serialVersionUID from JDK 1.1 for interoperability */
private:
    static const int64_t serialVersionUID = 3905348978240129619L;

private:
    /**
     * The internal state associated with this pseudorandom number generator.
     * (The specs for the methods in this class describe the ongoing
     * computation of this value.)
     */
    //Atomic long
    const int64_t seed;

    static const int64_t multiplier = 0x5DEECE66DLL;
    static const int64_t addend = 0xBLL;
    static const int64_t mask = (1LL << 48) - 1;

public:
    Random(int64_t seed):seed(this->initialScramble(seed)){

    }
private:
    static int64_t initialScramble(int64_t seed){
        return (seed^multiplier)&mask;
    }

    /**
     * Generates the next pseudorandom number. Subclasses should
     * override this, as this is used by all other methods.
     *
     * <p>The general contract of {@code next} is that it returns an
     * {@code int} value and if the argument {@code bits} is between
     * {@code 1} and {@code 32} (inclusive), then that many low-order
     * bits of the returned value will be (approximately) independently
     * chosen bit values, each of which is (approximately) equally
     * likely to be {@code 0} or {@code 1}. The method {@code next} is
     * implemented by class {@code Random} by atomically updating the seed to
     *  <pre>{@code (seed * 0x5DEECE66DL + 0xBL) & ((1L << 48) - 1)}</pre>
     * and returning
     *  <pre>{@code (int)(seed >>> (48 - bits))}.</pre>
     *
     * This is a linear congruential pseudorandom number generator, as
     * defined by D. H. Lehmer and described by Donald E. Knuth in
     * <i>The Art of Computer Programming,</i> Volume 3:
     * <i>Seminumerical Algorithms</i>, section 3.2.1.
     *
     * @param  bits random bits
     * @return the next pseudorandom value from this random number
     *         generator's sequence
     * @since  1.1
     */
protected:
    int32_t next(int32_t bits) {
        int64_t oldseed, nextseed;
        int64_t seed = this->seed;
        while(true) {
            oldseed = seed;
            nextseed = (oldseed * multiplier + addend) & mask;
            if(seed == oldseed){
                seed = nextseed;
                break;
            }
        }
        return (int32_t)(nextseed >> (48 - bits));
    }
public:
    /**
     * Returns a pseudorandom, uniformly distributed {@code int} value
     * between 0 (inclusive) and the specified value (exclusive), drawn from
     * this random number generator's sequence.  The general contract of
     * {@code nextInt} is that one {@code int} value in the specified range
     * is pseudorandomly generated and returned.  All {@code n} possible
     * {@code int} values are produced with (approximately) equal
     * probability.  The method {@code nextInt(int n)} is implemented by
     * class {@code Random} as if by:
     *  <pre> {@code
     * public int nextInt(int n) {
     *   if (n <= 0)
     *     throw new IllegalArgumentException("n must be positive");
     *
     *   if ((n & -n) == n)  // i.e., n is a power of 2
     *     return (int)((n * (long)next(31)) >> 31);
     *
     *   int bits, val;
     *   do {
     *       bits = next(31);
     *       val = bits % n;
     *   } while (bits - val + (n-1) < 0);
     *   return val;
     * }}</pre>
     *
     * <p>The hedge "approximately" is used in the foregoing description only
     * because the next method is only approximately an unbiased source of
     * independently chosen bits.  If it were a perfect source of randomly
     * chosen bits, then the algorithm shown would choose {@code int}
     * values from the stated range with perfect uniformity.
     * <p>
     * The algorithm is slightly tricky.  It rejects values that would result
     * in an uneven distribution (due to the fact that 2^31 is not divisible
     * by n). The probability of a value being rejected depends on n.  The
     * worst case is n=2^30+1, for which the probability of a reject is 1/2,
     * and the expected number of iterations before the loop terminates is 2.
     * <p>
     * The algorithm treats the case where n is a power of two specially: it
     * returns the correct number of high-order bits from the underlying
     * pseudo-random number generator.  In the absence of special treatment,
     * the correct number of <i>low-order</i> bits would be returned.  Linear
     * congruential pseudo-random number generators such as the one
     * implemented by this class are known to have short periods in the
     * sequence of values of their low-order bits.  Thus, this special case
     * greatly increases the length of the sequence of values returned by
     * successive calls to this method if n is a small power of two.
     *
     * @param n the bound on the random number to be returned.  Must be
     *        positive.
     * @return the next pseudorandom, uniformly distributed {@code int}
     *         value between {@code 0} (inclusive) and {@code n} (exclusive)
     *         from this random number generator's sequence
     * @throws IllegalArgumentException if n is not positive
     * @since 1.2
     */

    int32_t nextInt(int32_t n) {
        if (n <= 0){
            throw new std::invalid_argument("n must be positive");
        }

        if ((n & -n) == n)  // i.e., n is a power of 2
            return (int)((n * (long)next(31)) >> 31);

        int bits, val;
        do {
            bits = next(31);
            val = bits % n;
        } while (bits - val + (n-1) < 0);
        return val;
    }
};