// NEED A PRIME MODULO (OTHERWISE FASTEXP IS BROKEN)
template<long long MOD = 1000000007LL>
struct IntMod {
    long long x;

    IntMod(long long xx) : x(xx % MOD) { }
    IntMod(const IntMod & other) : x(other.x) { }

    IntMod& operator=(const IntMod<MOD> & other) {
        x = (other.x) % MOD;
        return *this;
    }

    IntMod operator+(const IntMod<MOD> & other) const {
        return IntMod<MOD>((x + other.x) % MOD);
    }
    IntMod& operator+=(const IntMod<MOD> & other) {
        *this = *this + other;
        return *this;
    }

    IntMod operator-(const IntMod<MOD> & other) const {
        return IntMod<MOD>((x - other.x + MOD) % MOD);
    }
    IntMod& operator-=(const IntMod<MOD> & other) {
        *this = *this - other;
        return *this;
    }

    IntMod operator*(const IntMod<MOD> & other) const {
        return IntMod<MOD>((x * other.x) % MOD);
    }
    IntMod& operator*=(const IntMod<MOD> & other) {
        *this = *this * other;
        return *this;
    }

    IntMod operator^(const IntMod<MOD> & other) const {
        return __fastexp(other);
    }
    IntMod& operator^=(const IntMod<MOD> & other) {
        *this = (*this) ^ other;
        return *this;
    }

    IntMod operator/(const IntMod<MOD> & other) const {
        return *this * other.__inverse();
    }
    IntMod& operator/=(const IntMod<MOD> & other) {
        *this = *this / other;
        return *this;
    }


    IntMod<MOD> __fastexp(const IntMod<MOD> & e) const {
        long long ans = 1LL, bas = x, exp = e.x;
        while(exp > 0LL) {
            if(exp & 1LL) {
                ans = (bas * ans) % MOD;
            }
            bas = (bas * bas) % MOD;
            exp /= 2LL;
        }

        return IntMod<MOD>(ans);
    }

    IntMod<MOD> __inverse() const {
        return __fastexp(MOD - 2LL);
    }

    operator long long() const { return x; }
};