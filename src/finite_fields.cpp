#include <finite_fields.hpp>
#include <iostream>

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


void ff::BinaryField::add(const mpz_t op1, const mpz_t op2, mpz_t result) {
    mpz_xor(result, op1, op2);
}

void ff::BinaryField::sub(const mpz_t op1, const mpz_t op2, mpz_t result) {
    mpz_xor(result, op1, op2);
}

void ff::BinaryField::mul(const mpz_t op1, const mpz_t op2, mpz_t result) {
    mpz_t b;
    mpz_init2(b, nbits);
    mpz_set(b, op2);

    if(mpz_tstbit(op1, 0)) {
        mpz_set(result, b);
    } else {
        mpz_set_ui(result, 0);
    }

    for(size_t i = 1; i < nbits; ++i) {
        mpz_mul_2exp(b, b, 1);
        if(mpz_tstbit(b, nbits-1)) {
            mpz_xor(b, b, ip);
        }
        if(mpz_tstbit(op1, i)) {
            mpz_xor(result, result, b);
        }
    }
}

void ff::BinaryField::inv(const mpz_t op1, mpz_t result) {
    //

}

void ff::BinaryField::red(const mpz_t op1, mpz_t result) {
    //
}