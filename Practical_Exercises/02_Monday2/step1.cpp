#include <functional>
#include <string>

std::function<void()> f;

int f1() { return 0;}

struct F2 {
    double operator()() const { return 0.0; }
};

std::function<int(const char *)> g;

double g1(const char *) {};
bool g2(const char *) {};

std::function<void(int &)> h;
std::function<void(const int &)> ch;

int main() {
    f = f1;
    f = F2();
    f = []() { return false; };

    g = g1;
    g = g2;

    std::function<void(const char *)> s;
    s = [](std::string) {};
    s = [](const std::string&) {};
//  s = [](std::string &) {};

    std::function<void(const std::string)> t;
//  t = [](const char *) {};

    h = [](int &) {};
    h = [](const int &) {};
//  ch = [](int &) {};
    ch = [](const int &) {};

}
