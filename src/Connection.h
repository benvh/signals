#ifndef __EVENTS_CONNECTION_H_
#define __EVENTS_CONNECTION_H_

#include <memory>

#include "ConnectionReference.h"

/**
* A wrapper for ConnectionReference
* Many Connection objects can exist for a single ConnectionReference
*
* When all Connection objects for a specific ConnectionReference are dead
* the Connection will NOT disconnect itself... you have to FORCE it by calling Connection::disconnect()
*/
class Connection {
private:
    std::shared_ptr<ConnectionReference> connRef;

public:

    Connection(std::shared_ptr<ConnectionReference> &connRef) : connRef(connRef) {
    }

    Connection(ConnectionReference *connRefPtr) : connRef(connRefPtr) {
    }

    Connection(Connection const& conn) {
        *this = conn;
    }

    Connection& operator=(Connection const& conn) {
        if(&conn != this) {
            connRef = conn.connRef;
        }
        return *this;
    }

    ~Connection() {
    }

    void disconnect() {
        connRef->disconnect();
    }

    bool isConnected() const {
        return connRef->isConnected();
    }

    bool isMuted() const {
        return connRef->isMuted();
    }

    void mute() {
        connRef->mute();
    }

    void unmute() {
        connRef->unmute();
    }

    int getId() const {
        if(connRef != nullptr && connRef->isConnected()) return connRef->getId();
        return -1;
    }

};

#endif