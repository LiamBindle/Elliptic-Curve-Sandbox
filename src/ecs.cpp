#include <ecs.hpp>

ecs::Point ecs::Curve::newPoint() const {
    ecs::Point pt(*this);
    return pt;
}

void ecs::Point::add(const ecs::Point& p, const ecs::Point& q) {
    mpz_t m, tmp;
    mpz_inits(m, tmp, NULL);

    const mpz_t& px = p.x();
    const mpz_t& py = p.y();
    const mpz_t& qx = q.x();
    const mpz_t& qy = q.y();
    const ecs::Field& field = _curve.field();

    if(mpz_cmp(px, qx) == 0 && mpz_cmp(py, qy) == 0) { // PDBL
        mpz_set_ui(tmp, 3);   // 3
        field.mul(px, px, m); // px*px
        field.mul(m, tmp, m); // 3 * px * px
        field.add(m, _curve.a(), m);   // 3 * px * px + a
        
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
    field.sub(tmp, qx, _x);

    field.sub(px, _x, tmp);
    field.mul(m, tmp, tmp);
    field.sub(tmp, py, _y);
}
