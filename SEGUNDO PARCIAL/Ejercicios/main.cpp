#include <functional>
#include <iostream>
using namespace std;

template<typename T>
struct t2t {
    typedef T t;
};

template<typename R, typename V1, typename V2>
struct fixpoint {
    typedef std::function<R(V1, V2)> func_t;
    typedef function<func_t(func_t)> tfunc_t;
    typedef function<func_t(tfunc_t)> yfunc_t;

    class loopfunc_t {
    public:
        func_t operator()(loopfunc_t v) const {
            return func(v);
        }

        template<typename L>
        loopfunc_t(const L &l) : func(l) {}

        typedef V1 Parameter1_t;
        typedef V2 Parameter2_t;

    private:
        std::function<func_t(loopfunc_t)> func;
    };

    static yfunc_t fix;
};

template<typename R, typename V1, typename V2>
typename fixpoint<R, V1, V2>::yfunc_t fixpoint<R, V1, V2>::fix = [](tfunc_t f) -> func_t {
    return [f](fixpoint<R, V1, V2>::loopfunc_t x) { return f(x(x)); }
    ([f](fixpoint<R, V1, V2>::loopfunc_t x) -> fixpoint<R, V1, V2>::func_t {
        auto &ff = f;
        return [ff, x](typename decltype(x)::Parameter1_t v1,
                       typename decltype(x)::Parameter2_t v2) {
            return ff(x(x))(v1, v2);
        };
    });
};

int main(int argc, char *argv[]) {
    auto term = [](int a) -> int {
        return a * a;
    };

    auto next = [](int a) -> int {
        return ++a;
    };

    auto sum = fixpoint<int, int, int>::fix(
            [term, next](std::function<int(int, int)> sum1) -> std::function<int(int, int)> {
                auto &term1 = term;
                auto &next1 = next;
                return [term1, next1, sum1](int a, int b) mutable -> int {
                    if (a > b)
                        return 0;
                    else
                        return term1(a) + sum1(next1(a), b);
                };
            });

    std::cout << sum(1, 10) << std::endl; //385

    return 0;
}
