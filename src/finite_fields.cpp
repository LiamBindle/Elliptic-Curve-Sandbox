#include <finite_fields.hpp>
#include <iostream>

int tester() {
    return 1;
}

void ff::PrimeField::add(const mpz_t& op1, const mpz_t& op2, mpz_t& result) {
    std::cout<<"called add\n";
    return;
}

void ff::PrimeField::sub(const mpz_t& op1, const mpz_t& op2, mpz_t& result) {
    std::cout<<"called sub\n";
    return;
}

void ff::PrimeField::mul(const mpz_t& op1, const mpz_t& op2, mpz_t& result) {
    std::cout<<"called mul\n";
    return;
}

void ff::PrimeField::inv(const mpz_t& op1, const mpz_t& op2, mpz_t& result) {
    std::cout<<"called inv\n";
    return;
}

void ff::PrimeField::red(const mpz_t& op1, const mpz_t& op2, mpz_t& result) {
    std::cout<<"called red\n";
    return;
}