#ifndef __ECS_NIST_CURVES_H__
#define __ECS_NIST_CURVES_H__

#include "ecs.hpp"

namespace ecs {

    class NIST_P224 : public ecs::Curve {
    public:
        NIST_P224() : ecs::Curve("-3", 10,
                       "18958286285566608000408668544493926415504680968679321075787234672564",10,
                       nullptr)
        {
            mpz_init_set_str(_prime_modulus, "26959946667150639794667015087019630673557916260026308143510066298881", 10);
            _field = new ecs::PrimeField(_prime_modulus);
        }
        ~NIST_P224() {
            delete _field;
        }
    protected:
        mpz_t _prime_modulus;     
    };

    class NIST_P256 : public ecs::Curve {
    public:
        NIST_P256() : ecs::Curve("-3", 10,
                       "41058363725152142129326129780047268409114441015993725554835256314039467401291",10,
                       nullptr)
        {
            mpz_init_set_str(_prime_modulus, "115792089210356248762697446949407573530086143415290314195533631308867097853951", 10);
            _field = new ecs::PrimeField(_prime_modulus);
        }
        ~NIST_P256() {
            delete _field;
        }
    protected:
        mpz_t _prime_modulus;     
    };

    class NIST_P384 : public ecs::Curve {
    public:
        NIST_P384() : ecs::Curve("-3", 10,
                       "27580193559959705877849011840389048093056905856361568521428707301988689241309860865136260764883745107765439761230575",10,
                       nullptr)
        {
            mpz_init_set_str(_prime_modulus, "39402006196394479212279040100143613805079739270465446667948293404245721771496870329047266088258938001861606973112319", 10);
            _field = new ecs::PrimeField(_prime_modulus);
        }
        ~NIST_P384() {
            delete _field;
        }
    protected:
        mpz_t _prime_modulus;     
    };

}

#endif