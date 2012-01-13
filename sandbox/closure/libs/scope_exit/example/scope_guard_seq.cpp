
#include <boost/scope_exit.hpp>
#include <map>
#include <string>
#include <utility>

int main(void) {
    bool commit = false;
    std::string currency("EUR");
    double rate = 1.3326;
    std::map<std::string, double> rates;
    bool currency_rate_inserted =
            rates.insert(std::make_pair(currency, rate)).second;

    BOOST_SCOPE_EXIT( (currency_rate_inserted) (&commit) (&rates)
            (&currency) ) {
        if(currency_rate_inserted && !commit)
            rates.erase(currency);
    } BOOST_SCOPE_EXIT_END

    // ...

    commit = true;

    return 0;
}

