#include <gmp.h>

namespace ff {
    class Field {
    public:
        virtual void add(const mpz_t op1, const mpz_t op2, mpz_t result) const = 0;
        virtual void sub(const mpz_t op1, const mpz_t op2, mpz_t result) const = 0;
        virtual void mul(const mpz_t op1, const mpz_t op2, mpz_t result) const = 0;
        virtual void inv(const mpz_t op1, mpz_t result) const = 0;
    };

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