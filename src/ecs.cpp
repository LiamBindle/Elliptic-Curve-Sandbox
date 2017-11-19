#include <ecs.hpp>

ecs::Point ecs::Curve::newPoint() const {
    ecs::Point pt(*this);
    return pt;
}

void ecs::Point::add(const ecs::Point& p, const ecs::Point& q, ecs::Point& r) {
    mpz_t m, tmp, rx, ry;
    mpz_inits(m, tmp, rx, ry, NULL);

    const mpz_t& px = p.x();
    const mpz_t& py = p.y();
    const mpz_t& qx = q.x();
    const mpz_t& qy = q.y();
    const ecs::Field& field = r._curve.field();

    if(mpz_cmp(px, qx) == 0 && mpz_cmp(py, qy) == 0) { // PDBL
        mpz_set_ui(tmp, 3);   // 3
        field.mul(px, px, m); // px*px
        field.mul(m, tmp, m); // 3 * px * px
        field.add(m, r._curve.a(), m);   // 3 * px * px + a
        
        mpz_set_ui(tmp, 2);         // 2
        field.mul(py, tmp, tmp);    // 2 * py
        field.inv(tmp, tmp);        // 1 / (2 * py)

        field.mul(m, tmp, m);
    } else { // PADD
        field.sub(py, qy, m);   // yp - yq
        field.sub(px, qx, tmp); // xp - xq
        field.inv(tmp, tmp);    // 1 / (xp - xq)

        field.mul(m, tmp, m);
    }

    field.mul(m, m, tmp);
    field.sub(tmp, px, tmp);
    field.sub(tmp, qx, rx);

    field.sub(px, rx, tmp);
    field.mul(m, tmp, tmp);
    field.sub(tmp, py, ry);

    mpz_set(r._x, rx);
    mpz_set(r._y, ry);
}


void ecs::Point::mul(const mpz_t k_times, const ecs::Point& p, ecs::Point& r) {
    using namespace ecs;
    mpz_t k;
    mpz_init_set(k, k_times);
    Point dbl = p;

    // while first bit isn't 1
    while(!mpz_tstbit(k, 0) && mpz_cmp_ui(k, 0) > 0) {
        Point::add(dbl, dbl, dbl);
        mpz_fdiv_q_2exp(k, k, 1);
    }
    Point acc = dbl;
    mpz_fdiv_q_2exp(k, k, 1);

    while(mpz_cmp_ui(k, 0) > 0) {
        Point::add(dbl, dbl, dbl);

        if(mpz_tstbit(k, 0)) {
            Point::add(acc, dbl, acc);
        }
        mpz_fdiv_q_2exp(k, k, 1);
    }

    mpz_set(r._x, acc._x);
    mpz_set(r._y, acc._y);
}