#include <iostream>
#include "Signal.h"


class Foobar {

public:
    void doSomething(int x) {
        std::cout << "Foobar did something: " << x << std::endl;
    }
};


int main(int argc, char const *argv[])
{
    Signal<void(int)> mySignal;
    Foobar f;

    int lol = 5;

    Connection myConnection = mySignal.connect( std::bind(&Foobar::doSomething, &f , std::placeholders::_1) );
    mySignal.connect( [](int stuff) { std::cout << "lambda did stuff " << stuff << std::endl;  } );

    mySignal.notify(1337);

    std::cout << myConnection.getId() << std::endl;
    myConnection.disconnect();
    std::cout << myConnection.getId() << std::endl;

    mySignal.notify(7331);

    return 0;
}