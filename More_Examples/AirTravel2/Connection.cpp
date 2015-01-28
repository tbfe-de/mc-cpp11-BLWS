#include "Airport.h"
#include "Connection.h"

using namespace std;

size_t Connection::addAirport(shared_ptr<Airport> ap) {
	const auto result = airports.size();
	airports.push_back(ap);
	return result;
}

vector<weak_ptr<Airport>> Connection::getGoingTo(size_t from) const {
	vector<weak_ptr<Airport>> result;
	while (++from < airports.size())
		result.emplace_back(airports.at(from));
	return result;
}

vector<weak_ptr<Airport>> Connection::getComingFrom(size_t to) const {
	vector<weak_ptr<Airport>> result;
	for (size_t i = 0; i < to; ++i)
		result.emplace_back(airports.at(i));
	return result;
}

size_t Connection::instances;
