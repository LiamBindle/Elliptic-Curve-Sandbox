#ifndef __ECS_FF_H__
#define __ECS_FF_H__

#include <gmp.h>

namespace ecs {
    class Field {
    public:
        virtual void add(const mpz_t op1, const mpz_t op2, mpz_t result) const = 0;
        virtual void sub(const mpz_t op1, const mpz_t op2, mpz_t result) const = 0;
        virtual void mul(const mpz_t op1, const mpz_t op2, mpz_t result) const = 0;
        virtual void inv(const mpz_t op1, mpz_t result) const = 0;
    };
}

#endif