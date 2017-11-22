#include <ecs.hpp>

ecs::Point ecs::Curve::newPoint() const {
    ecs::Point pt(*this);
    return pt;
}

void ecs::PrimeCurve::add(const ecs::Point& p, const ecs::Point& q, ecs::Point& r) const {
    mpz_t m, tmp, rx, ry;
    mpz_inits(m, tmp, rx, ry, NULL);

    const mpz_t& px = p.x();
    const mpz_t& py = p.y();
    const mpz_t& qx = q.x();
    const mpz_t& qy = q.y();

    if(mpz_cmp(px, qx) == 0 && mpz_cmp(py, qy) == 0) { // PDBL
        mpz_set_ui(tmp, 3);   // 3
        _field->mul(px, px, m); // px*px
        _field->mul(m, tmp, m); // 3 * px * px
        _field->add(m, a(), m);   // 3 * px * px + a
        
        mpz_set_ui(tmp, 2);         // 2
        _field->mul(py, tmp, tmp);    // 2 * py
        _field->inv(tmp, tmp);        // 1 / (2 * py)

        _field->mul(m, tmp, m);
    } else { // PADD
        _field->sub(py, qy, m);   // yp - yq
        _field->sub(px, qx, tmp); // xp - xq
        _field->inv(tmp, tmp);    // 1 / (xp - xq)

        _field->mul(m, tmp, m);
    }

    _field->mul(m, m, tmp);
    _field->sub(tmp, px, tmp);
    _field->sub(tmp, qx, rx);

    _field->sub(px, rx, tmp);
    _field->mul(m, tmp, tmp);
    _field->sub(tmp, py, ry);

    r.setX(rx);
    r.setY(ry);
}


void ecs::PrimeCurve::mul(const mpz_t k_times, const ecs::Point& p, ecs::Point& r) const {
    using namespace ecs;
    mpz_t k;
    mpz_init_set(k, k_times);
    Point dbl = p;

    // while first bit isn't 1
    while(!mpz_tstbit(k, 0) && mpz_cmp_ui(k, 0) > 0) {
        add(dbl, dbl, dbl);
        mpz_fdiv_q_2exp(k, k, 1);
    }
    Point acc = dbl;
    mpz_fdiv_q_2exp(k, k, 1);

    while(mpz_cmp_ui(k, 0) > 0) {
        add(dbl, dbl, dbl);

        if(mpz_tstbit(k, 0)) {
            add(acc, dbl, acc);
        }
        mpz_fdiv_q_2exp(k, k, 1);
    }

    r.setX(acc.x());
    r.setY(acc.y());
}