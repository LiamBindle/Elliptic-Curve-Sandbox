#ifndef __ECS_NIST_CURVES_H__
#define __ECS_NIST_CURVES_H__

#include <ecs.hpp>

namespace ecs {

    class NIST_P224 : public ecs::Curve {
    public:
        NIST_P224();
        ~NIST_P224() {
            delete _field;
        }
    protected:
        mpz_t _prime_modulus;     
    };

    class NIST_P256 : public ecs::Curve {
    public:
        NIST_P256();
        ~NIST_P256() {
            delete _field;
        }
    protected:
        mpz_t _prime_modulus;     
    };

    class NIST_P384 : public ecs::Curve {
    public:
        NIST_P384();
        ~NIST_P384() {
            delete _field;
        }
    protected:
        mpz_t _prime_modulus;     
    };

}

#endif