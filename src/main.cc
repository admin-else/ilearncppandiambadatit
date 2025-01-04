#include "app.hh"
#include <exception>
#include <iostream>
#include <ostream>


using std::exception, std::endl, std::cerr;

int main() {
    try {
        App app;
        app.run();
    } catch (const exception &e) {
        cerr << typeid(e).name()<< ":> " << e.what() << endl;
        return 1;
    }
    return 0;
}