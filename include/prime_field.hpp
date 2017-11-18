#ifndef __ECS_PF_H__
#define __ECS_PF_H__

#include <finite_fields.hpp>

namespace ecs {
    class PrimeField : public Field {
    public:
        PrimeField(const mpz_t p) { mpz_init_set(this->p, p); }
        virtual void add(const mpz_t op1, const mpz_t op2, mpz_t result) const override;
        virtual void sub(const mpz_t op1, const mpz_t op2, mpz_t result) const override;
        virtual void mul(const mpz_t op1, const mpz_t op2, mpz_t result) const override;
        virtual void inv(const mpz_t op1, mpz_t result) const override;
    protected:
        mpz_t p;
    };
}

#endif