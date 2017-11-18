#include <ecs.hpp>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>

TEST_CASE("PrimeField::add", "[arithmetic][PrimeField]") {
    char buff[4096];
    std::vector<std::string> tests = {
        "5", /* + */ "10", /* = */ "15",
        "32", /* + */ "0", /* = */ "32",
        "0", /* + */ "92", /* = */ "92",
        "3721687316841", /* + */ "341232176812", /* = */ "4062919493653",

        "7643227867216378216378216378126748362278463278647382678213673821678",  /* + */
        "3621786372816478216783216784632728647281637821637862178647821681",     /* = */
        "1000000000000000000000000000000000000000000000000000000000000000000",

        "97894251564864254842156456425145186612132456456214564515564561516156484845141684521565615645645243745786784521231564562164648",    /* + */
        "4545584464864868486468484684684864848614548656216472647261267461476146143583837678626568697979799764646461466767631364674316767",  /* = */
        "2594788223397521029050944001286802108703981578412649165438103543642"
    };
    
    mpz_t a, b, r, c, p;
    mpz_inits(a, b, r, c, NULL);
    mpz_init_set_str(p, "6646849653589194694594999594911381090925744916469020540392321643359", 10);
    ecs::PrimeField pf(p);

    for(int i = 0; i < tests.size();) {
        mpz_set_str(a, tests[i++].c_str(), 10);
        mpz_set_str(b, tests[i++].c_str(), 10);
        mpz_set_str(c, tests[i++].c_str(), 10);

        pf.add(a, b, r);
        gmp_sprintf(buff, "%s + %s: expected %s, got %Zd", 
            tests[i-3].c_str(), tests[i-2].c_str(), tests[i-1].c_str(), r
        );
        INFO(buff);
        REQUIRE(mpz_cmp(r, c) == 0);
    }
}

TEST_CASE("PrimeField::sub", "[arithmetic][PrimeField]") {
    char buff[4096];
    std::vector<std::string> tests = {
        "5", /* - */ "10", /* = */ "6646849653589194694594999594911381090925744916469020540392321643354",
        "32", /* - */ "0", /* = */ "32",
        "0", /* - */ "92", /* = */ "6646849653589194694594999594911381090925744916469020540392321643267",
        "3721687316841", /* - */ "341232176812", /* = */ "3380455140029",

        "7643227867216378216378216378126748362278463278647382678213673821678",  /* - */
        "3621786372816478216783216784632728647281637821637862178647821681",     /* = */
        "992756427254367043566433566430734542705436724356724275642704356638",

        "97894251564864254842156456425145186612132456456214564515564561516156484845141684521565615645645243745786784521231564562164648",    /* - */
        "4545584464864868486468484684684864848614548656216472647261267461476146143583837678626568697979799764646461466767631364674316767",  /* = */
        "3328176981933216737884785268474636287609960660030602277383268634992"
    };
    
    mpz_t a, b, r, c, p;
    mpz_inits(a, b, r, c, NULL);

    mpz_init_set_str(p, "6646849653589194694594999594911381090925744916469020540392321643359", 10);

    ecs::PrimeField pf(p);

    for(int i = 0; i < tests.size();) {
        mpz_set_str(a, tests[i++].c_str(), 10);
        mpz_set_str(b, tests[i++].c_str(), 10);
        mpz_set_str(c, tests[i++].c_str(), 10);

        pf.sub(a, b, r);
        gmp_sprintf(buff, "%s - %s: expected %s, got %Zd", 
            tests[i-3].c_str(), tests[i-2].c_str(), tests[i-1].c_str(), r
        );
        INFO(buff);
        REQUIRE(mpz_cmp(r, c) == 0);
    }
}

TEST_CASE("PrimeField::mul", "[arithmetic][PrimeField]") {
    char buff[4096];
    std::vector<std::string> tests = {
        "5", /* * */ "10", /* = */ "50",
        "32", /* * */ "0", /* = */ "0",
        "0", /* * */ "92", /* = */ "0",
        "3721687316841", /* * */ "341232176812", /* = */ "1269959464539265977290892",

        "7643227867216378216378216378126748362278463278647382678213673821678",  /* * */
        "3621786372816478216783216784632728647281637821637862178647821681",     /* = */
        "1756911487539512177130431502478748632697673259908636554579600408345",

        "97894251564864254842156456425145186612132456456214564515564561516156484845141684521565615645645243745786784521231564562164648",    /* * */
        "4545584464864868486468484684684864848614548656216472647261267461476146143583837678626568697979799764646461466767631364674316767",  /* = */
        "1045789476414032121339848896900127834789108490931392510659106931618"
    };
    
    mpz_t a, b, r, c, p;
    mpz_inits(a, b, r, c, NULL);


    mpz_init_set_str(p, "6646849653589194694594999594911381090925744916469020540392321643359", 10);

    ecs::PrimeField pf(p);

    for(int i = 0; i < tests.size();) {
        mpz_set_str(a, tests[i++].c_str(), 10);
        mpz_set_str(b, tests[i++].c_str(), 10);
        mpz_set_str(c, tests[i++].c_str(), 10);

        pf.mul(a, b, r);
        gmp_sprintf(buff, "%s * %s: expected %s, got %Zd", 
            tests[i-3].c_str(), tests[i-2].c_str(), tests[i-1].c_str(), r
        );
        INFO(buff);
        REQUIRE(mpz_cmp(r, c) == 0);
    }
}

TEST_CASE("PrimeField::inv", "[arithmetic][PrimeField]") {
    char buff[4096];
    std::vector<std::string> tests = {
        "5", "13",
        "3721863782167841", "26959946667150639794667015087019630673557916260026308143510066298881",
        "16959946667150639794667015087019630673557916260026308143510066298881", "26959946667150639794667015087019630673557916260026308143510066298881",
        "7959946667150639794667015087019630673557916260026308143510066298881", "26959946667150639794667015087019630673557916260026308143510066298881",
        "9959946667150639794667015087019630673557916260026308143510066298881", "26959946667150639794667015087019630673557916260026308143510066298881",
        "26959946666150639794667015077019630673557942260026308143510066298881", "26959946667150639794667015087019630673557916260026308143510066298881",
        "59945667150639794667015087019630673557916260026108144510066298881", "26959946667150639794667015087019630673557916260026308143510066298881",
        "26959946667150639794667015087019630673557916260026308510066298884", "26959946667150639794667015087019630673557916260026308143510066298881",
    };
    
    mpz_t a, b, r, c, p;
    mpz_inits(a, b, r, c, p, NULL);

    for(int i = 0; i < tests.size();) {
        mpz_set_str(a, tests[i++].c_str(), 10);
        mpz_set_str(p, tests[i++].c_str(), 10);
        mpz_set_si(c, 1);
        ecs::PrimeField pf(p);
        pf.inv(a, r);
        pf.mul(a, r, r);
        gmp_sprintf(buff, "%s/%s mod %s: expected 1, got %Zd", 
            tests[i-2].c_str(), tests[i-2].c_str(), tests[i-1].c_str(), r
        );
        INFO(buff);
        REQUIRE(mpz_cmp(r, c) == 0);
    }
}

TEST_CASE("BinaryField::mul", "[arithmetic][BinaryField]") {
    char buff[4096];
    std::vector<std::string> tests = {
        "10101", "01101", "100101", "10010",
        "01101", "10101", "100101", "10010",
        "01010011", "11001010", "100011011", "00000001",
        "11001010", "01010011", "100011011", "00000001"
    };
    
    mpz_t a, b, ip, r, c;
    mpz_inits(a, b, ip, r, c, NULL);

    for(int i = 0; i < tests.size();) {
        mpz_set_str(a, tests[i++].c_str(), 2);
        mpz_set_str(b, tests[i++].c_str(), 2);
        mpz_set_str(ip, tests[i++].c_str(), 2);
        mpz_set_str(c, tests[i++].c_str(), 2);
        ecs::BinaryField bf(ip);
        bf.mul(a, b, r);
        gmp_sprintf(buff, "%s * %s mod %s: expected %s, got %Zd", 
            tests[i-4].c_str(), tests[i-3].c_str(), tests[i-2].c_str(), tests[i-1].c_str(), r
        );
        INFO(buff);
        REQUIRE(mpz_cmp(r, c) == 0);
    }
}

TEST_CASE("BinaryField::inv", "[arithmetic][BinaryField]") {
    char buff[4096];
    std::vector<std::string> tests = {
        "10101", "100101",
        "01101", "100101",
        "01010011", "100011011",
        "11001010", "100011011"
    };
    
    mpz_t a, ip, r;
    mpz_inits(a, ip, r, NULL);

    for(int i = 0; i < tests.size();) {
        mpz_set_str(a, tests[i++].c_str(), 2);
        mpz_set_str(ip, tests[i++].c_str(), 2);
        ecs::BinaryField bf(ip);
        bf.inv(a, r);
        bf.mul(a, r, r);
        gmp_sprintf(buff, "%s / %s mod %s: expected 1, got %Zd", 
            tests[i-2].c_str(), tests[i-2].c_str(), tests[i-1].c_str(), r
        );
        INFO(buff);
        REQUIRE(mpz_cmp_ui(r, 1) == 0);
    }
}

TEST_CASE("PADD", "[addition][PrimeField][Point]") {
    char buff[4096];
    std::vector<std::string> tests = {
        "-1", "3", "127", // a, b, p
        "16", "20",  // = P
        "41", "120", // = Q
        "86", "81",  // = R
    };

    for(int i = 0; i < tests.size();) {
        mpz_t a, b, prime, xr, yr;
        mpz_init_set_str(a, tests[i++].c_str(), 10);
        mpz_init_set_str(b, tests[i++].c_str(), 10);
        mpz_init_set_str(prime, tests[i++].c_str(), 10);
        ecs::PrimeField pf(prime);
        ecs::Curve curve(a, b, pf);

        ecs::Point p(curve);
        p.setX(tests[i++].c_str(), 10);
        p.setY(tests[i++].c_str(), 10);
        ecs::Point q(curve);
        q.setX(tests[i++].c_str(), 10);
        q.setY(tests[i++].c_str(), 10);
        
        mpz_init_set_str(xr, tests[i++].c_str(), 10);
        mpz_init_set_str(yr, tests[i++].c_str(), 10);
        
        ecs::Point r(curve);
        ecs::Point::add(p, q, r);

        gmp_sprintf(buff, "a=%Zd, b=%Zd, p=%Zd:    (%Zd, %Zd) + (%Zd, %Zd):    expected (%Zd, %Zd), got (%Zd, %Zd)", 
            a, b, prime, p.x(), p.y(), q.x(), q.y(), xr, yr, r.x(), r.y()
        );
        INFO(buff);
        REQUIRE(mpz_cmp(r.x(), xr) == 0);
        REQUIRE(mpz_cmp(r.y(), yr) == 0);
    }
}

TEST_CASE("Point Addition", "[addition][PrimeField][Point]") {
    char buff[4096];
    std::vector<std::string> tests = {
        "-3", "18958286285566608000408668544493926415504680968679321075787234672564", "26959946667150639794667015087019630673557916260026308143510066298881", // a, b, p
        "19277929113566293071110308034699488026831934219452440156649784352033", "19926808758034470970197974370888749184205991990603949537637343198772",  // = P
        "19277929113566293071110308034699488026831934219452440156649784352033", "19926808758034470970197974370888749184205991990603949537637343198772",  // = Q
        "11838696407187388799350957250141035264678915751356546206913969278886", "2966624012289393637077209076615926844583158638456025172915528198331",   // = R

        "-3", "18958286285566608000408668544493926415504680968679321075787234672564", "26959946667150639794667015087019630673557916260026308143510066298881", // a, b, p
        "19277929113566293071110308034699488026831934219452440156649784352033", "19926808758034470970197974370888749184205991990603949537637343198772",  // = P
        "11838696407187388799350957250141035264678915751356546206913969278886", "2966624012289393637077209076615926844583158638456025172915528198331",  // = Q
        "23495795443371455911734272815198443231796705177085412225858576936196", "17267899494408073472134592504239670969838724875111952463975956982053"    // = R
    };

    for(int i = 0; i < tests.size();) {
        mpz_t a, b, prime, xr, yr;
        mpz_init_set_str(a, tests[i++].c_str(), 10);
        mpz_init_set_str(b, tests[i++].c_str(), 10);
        mpz_init_set_str(prime, tests[i++].c_str(), 10);
        ecs::PrimeField pf(prime);
        ecs::Curve curve(a, b, pf);

        ecs::Point p(curve);
        p.setX(tests[i++].c_str(), 10);
        p.setY(tests[i++].c_str(), 10);
        ecs::Point q(curve);
        q.setX(tests[i++].c_str(), 10);
        q.setY(tests[i++].c_str(), 10);
        
        mpz_init_set_str(xr, tests[i++].c_str(), 10);
        mpz_init_set_str(yr, tests[i++].c_str(), 10);
        
        ecs::Point r(curve);
        ecs::Point::add(p, q, r);

        ecs::NIST_P224 p224;
        ecs::Point p1 = p224.newPoint();
        ecs::Point p2 = p224.newPoint();
        ecs::Point p3 = p224.newPoint();
        p1.setX(p.x());
        p1.setY(p.y());
        p2.setX(q.x());
        p2.setY(q.y());

        ecs::Point::add(p1, p2, p1);
        REQUIRE(mpz_cmp(p1.x(), r.x()) == 0);
        REQUIRE(mpz_cmp(p1.y(), r.y()) == 0);

        gmp_sprintf(buff, "a=%Zd, b=%Zd, p=%Zd:    (%Zd, %Zd) + (%Zd, %Zd):    expected (%Zd, %Zd), got (%Zd, %Zd)", 
            a, b, prime, p.x(), p.y(), q.x(), q.y(), xr, yr, r.x(), r.y()
        );
        INFO(buff);
        REQUIRE(mpz_cmp(r.x(), xr) == 0);
        REQUIRE(mpz_cmp(r.y(), yr) == 0);
    }
}