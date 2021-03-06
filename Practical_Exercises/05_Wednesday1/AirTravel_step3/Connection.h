#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <memory>
    using std::shared_ptr;
    using std::weak_ptr;
#include <string>
    using std::string;
#include <vector>
    using std::vector;

class Airport;

class Connection {
    const string flight;
    vector<weak_ptr<Airport>> airports;
public:
    Connection(const string &flight_)
        : flight(flight_)
    {
        ++instances;
    }
    ~Connection() {
        --instances;
    }
    string getFlight() const {
        return flight;
    }
    const vector<weak_ptr<Airport>> &getAirports() const {
        return airports;
    }
    size_t addAirport(shared_ptr<Airport> ap);
    vector<weak_ptr<Airport>> getComingFrom(size_t to) const;
    vector<weak_ptr<Airport>> getGoingTo(size_t from) const;
    static size_t instances;
};

#endif /* CONNECTION_H_ */
