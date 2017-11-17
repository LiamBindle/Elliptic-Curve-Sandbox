#include <gmp.h>

namespace ff {
    class Field {
    public:
        virtual void add(const mpz_t& op1, const mpz_t& op2, mpz_t& result) = 0;
        virtual void sub(const mpz_t& op1, const mpz_t& op2, mpz_t& result) = 0;
        virtual void mul(const mpz_t& op1, const mpz_t& op2, mpz_t& result) = 0;
        virtual void inv(const mpz_t& op1, const mpz_t& op2, mpz_t& result) = 0;
        virtual void red(const mpz_t& op1, const mpz_t& op2, mpz_t& result) = 0;
    };

    class PrimeField : Field {
    public:
        virtual void add(const mpz_t& op1, const mpz_t& op2, mpz_t& result) override;
        virtual void sub(const mpz_t& op1, const mpz_t& op2, mpz_t& result) override;
        virtual void mul(const mpz_t& op1, const mpz_t& op2, mpz_t& result) override;
        virtual void inv(const mpz_t& op1, const mpz_t& op2, mpz_t& result) override;
        virtual void red(const mpz_t& op1, const mpz_t& op2, mpz_t& result) override;
    };
}