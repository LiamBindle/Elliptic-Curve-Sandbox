#include "finite_fields.hpp"

namespace ecc {

    class Curve {
    public:
        Curve(mpz_t a, mpz_t b, const ff::Field& field) : _field(field) {
            mpz_init_set(_a, a);
            mpz_init_set(_b, b);
        }
        const mpz_t& a() const { return _a; }
        const mpz_t& b() const { return _b; }
        const ff::Field& field() const { return _field; }
    protected:
        mpz_t _a;
        mpz_t _b;
        const ff::Field& _field;        
    };


    class Point {
    public:
        Point(const Curve& curve): _curve(curve) {
            mpz_inits(_x, _y, NULL);
        }

        void setX(const char* v, int base) {
            mpz_set_str(_x, v, base);
        }
        void setY(const char* v, int base) {
            mpz_set_str(_y, v, base);
        }
        const mpz_t& x() const { return _x; }
        const mpz_t& y() const { return _y; }

        void add(const Point& p, const Point& q);

    protected:
        mpz_t _x;
        mpz_t _y;
        const Curve& _curve;
    };
}

