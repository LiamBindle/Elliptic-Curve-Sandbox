#ifndef __ECS_H__
#define __ECS_H__

#include <utility>
#include "finite_fields.hpp"

namespace ecs {

    class Point;

    class Curve {
    public:
        Curve(mpz_t a, mpz_t b, const ecs::Field& field) : Curve(a, b, &field) {}
        Curve(mpz_t a, mpz_t b, const ecs::Field* field) {
            _field = field;
            mpz_init_set(_a, a);
            mpz_init_set(_b, b);
        }
        Curve(const char* a, int base_a, 
              const char* b, int base_b, 
              const ecs::Field* field)
        {
            _field = field;
            mpz_init_set_str(_a, a, base_a);
            mpz_init_set_str(_b, b, base_b);    
        }
        const mpz_t& a() const { return _a; }
        const mpz_t& b() const { return _b; }
        const ecs::Field& field() const { return *_field; }

        Point newPoint() const;

    protected:
        mpz_t _a;
        mpz_t _b;
        const ecs::Field* _field;        
    };


    class Point {
    public:
        Point(const Curve& curve): _curve(curve) {
            mpz_inits(_x, _y, NULL);
        }
        Point(Point&& point) : _curve(point._curve), _x(point._x), _y(point._y) {
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

#endif