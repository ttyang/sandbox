
struct point {
    int x;
    int y;
};

BOOST_AUTO_TEST_CASE( operator_error ) {
    bool BOOST_LOCAL_FUNCTION(const point& p, const point& q) {
        return p.x == q.x && p.y == q.y;
    } BOOST_LOCAL_FUNCTION(operator==) // Error: Cannot use `operator==`.

    point a; a.x = 1; a.y = 2;
    point b = a;
    BOOST_CHECK( a == b );
}

