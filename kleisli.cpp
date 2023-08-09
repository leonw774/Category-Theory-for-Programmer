#include <iostream>
#include <functional>
#include <string>
#include <cmath>

/* The embellished type */
template <typename T = int>
class optional {
        T mvalue; 
        bool mvalid;
    public:
        optional(): mvalid(false) {};
        optional(T v): mvalue(v), mvalid(true) {};
        T value() { return mvalue; };
        bool isValid() { return mvalid; }
        std::string toString() const {
            return (mvalid) ? std::to_string(mvalue) : std::string("Invalid");
        };
};

/* The Monad in respect of the embellishment type */
template <template<class> typename C>
class Monad {
    public:
        template <typename I, typename R>
        static C<R> bind(C<R> (*f)(I), C<I> x) {
            return x.isValid() ? f(x.value()) : C<R>();
        };

        /* Composition */
        template <typename I, typename R>
        static std::function<C<R>(I)> compose(auto (*f)(I), C<R> (*g)(auto)) {
            return [f, g] (I x) {
                return bind(g, f(x));
            };
        };
};

/* Morphism 1: double -> optional<double> */
optional<double> safe_reciprocal(double x) {
    if (x) return optional<double>(1.0 / x);
    else return optional<double>();
}

/* Morphism 2: double -> optional<double> */
optional<double> safe_root(double x) {
    if (x >= 0) return optional<double>(sqrt(x));
    else return optional<double>();
}

int main() {
    auto composed = Monad<optional>::compose(safe_root, safe_reciprocal);
    std::cout << composed(0.25).toString() << "\n"; // should be 2
    return 0;
}