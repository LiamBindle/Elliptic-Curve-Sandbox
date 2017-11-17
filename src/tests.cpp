#include <ecc.hpp>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

TEST_CASE("Build test", "[build]") {
    mpz_t n, q, p;
    mpz_init(n);
    mpz_init(q);
    mpz_set_ui(n, 0);
    mpz_set_ui(q, 1378194);

    REQUIRE(mpz_cmp(n, q) < 0);
    REQUIRE(tester() == 1);

    ff::PrimeField f;

    f.add(p, q, n);
    f.sub(p, q, n);
    f.mul(p, q, n);
    f.inv(p, q, n);
    f.red(p, q, n);

}


