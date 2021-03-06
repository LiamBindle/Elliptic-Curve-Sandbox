#ifndef __ECS_H__
#define __ECS_H__

#include <utility>
#include <finite_fields.hpp>
#include <prime_field.hpp>
#include <binary_field.hpp>

#define NIST_CURVES

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

        virtual void add(const Point& p, const Point& q, Point& r) const = 0;
        virtual void mul(const mpz_t k, const Point& p, Point& r) const;

    protected:
        mpz_t _a;
        mpz_t _b;
        const ecs::Field* _field;        
    };

    class PrimeCurve: public Curve {
    public:
        using Curve::Curve;
        virtual void add(const Point& p, const Point& q, Point& r) const override;
    };

    class BinaryCurve: public Curve {
    public:
        using Curve::Curve;
        virtual void add(const Point& p, const Point& q, Point& r) const override;
    };


    class Point {
    public:
        Point(const Curve& curve) {
            mpz_inits(_x, _y, NULL);
        }
        Point(const Point& copy) {
            mpz_init_set(_x, copy._x);
            mpz_init_set(_y, copy._y);
        }
        Point(Point&& point) : _x(point._x), _y(point._y) {
        }


        void setX(const char* v, int base) {
            mpz_set_str(_x, v, base);
        }
        void setY(const char* v, int base) {
            mpz_set_str(_y, v, base);
        }
        void setX(const mpz_t& x) {
            mpz_set(_x, x);
        }
        void setY(const mpz_t& y) {
            mpz_set(_y, y);
        }
        const mpz_t& x() const { return _x; }
        const mpz_t& y() const { return _y; }

    protected:
        mpz_t _x;
        mpz_t _y;
    };
}

#ifdef NIST_CURVES
    #include "nist_curves.hpp"
#endif

#endif