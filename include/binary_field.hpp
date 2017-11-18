#ifndef __ECS_BF_H__
#define __ECS_BF_H__

#include <finite_fields.hpp>

namespace ecs {
    class BinaryField: public Field {
    public:
        BinaryField(const mpz_t ip) { mpz_init_set(this->ip, ip); nbits = mpz_sizeinbase(ip, 2); }
        virtual void add(const mpz_t op1, const mpz_t op2, mpz_t result) const override;
        virtual void sub(const mpz_t op1, const mpz_t op2, mpz_t result) const override;
        virtual void mul(const mpz_t op1, const mpz_t op2, mpz_t result) const override;
        virtual void inv(const mpz_t op1, mpz_t result) const override;
    protected:
        mpz_t ip;
        size_t nbits;
    };
}

#endif