#include <prime_field.hpp>

void ecs::PrimeField::add(const mpz_t op1, const mpz_t op2, mpz_t result) const {
    mpz_add(result, op1, op2);
    mpz_mod(result, result, p);
}

void ecs::PrimeField::sub(const mpz_t op1, const mpz_t op2, mpz_t result) const {
    mpz_sub(result, op1, op2);
    mpz_mod(result, result, p);
}

void ecs::PrimeField::mul(const mpz_t op1, const mpz_t op2, mpz_t result) const {
    mpz_mul(result, op1, op2);
    mpz_mod(result, result, p);
}

void ecs::PrimeField::inv(const mpz_t op1, mpz_t result) const {
    mpz_invert(result, op1, p);
}