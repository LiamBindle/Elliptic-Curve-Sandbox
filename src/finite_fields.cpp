#include <finite_fields.hpp>
#include <iostream>

int tester() {
    return 1;
}

void ff::PrimeField::add(const mpz_t op1, const mpz_t op2, mpz_t result) {
    mpz_add(result, op1, op2);
}

void ff::PrimeField::sub(const mpz_t op1, const mpz_t op2, mpz_t result) {
    mpz_sub(result, op1, op2);
}

void ff::PrimeField::mul(const mpz_t op1, const mpz_t op2, mpz_t result) {
    mpz_mul(result, op1, op2);
}

void ff::PrimeField::inv(const mpz_t op1, mpz_t result) {
    mpz_invert(result, op1, p);

}

void ff::PrimeField::red(const mpz_t op1, mpz_t result) {
    mpz_mod(result, op1, p);
}