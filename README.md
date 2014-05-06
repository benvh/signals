Signals stuff
-----------------

Simple c++11 signals, just for fun!

## Usage
Just include it and off you go!
    #include "Signals.h"

Examples
---
A Signal will accept any *std::function<...>*

###lambda example
    Signal<void(int, int)> someSignal;
    someSignal.connect( [](int a, int b) { ... });

    someSignal.notify(1337, 7331);

###std::bind example
    class Foobar {
    public:
        void doSomething(int x) {
            ...
        }
    };


    int main(...) {
        Signal<void(int)> someSignal;
        Foobar f;

        someSignal.connect( std::bind(&Foobar::doSomething, &f, std::placeholders::_1) );
        someSignal.notify(5);

        return 0;
    }

## Connections
When connecting a callback to a signal it will return a *Connection* object.
This object can be used to disconnect the callback from the *Signal*!

    class Foobar {
    public:
        void doSomething(int x) {
            ...
        }
    };


    int main(...) {
        Signal<void(int)> someSignal;
        Foobar f;

        Connection someConnection = someSignal.connect( std::bind(&Foobar::doSomething, &f, std::placeholders::_1) );

        ...

        someConnection.disconnect();

        someSignal.notify(6); //won't call doSomething on f because it's disconnected! yay!

        ...
        return 0;
    }


**:-)**
