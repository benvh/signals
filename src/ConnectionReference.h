#ifndef __EVENTS_CONNECTION_HANDLER_H_
#define __EVENTS_CONNECTION_HANDLER_H_

#include <functional>
#include <memory>

/**
* This guy holds and id to the callback inside the Signal and disconnection callback to remove it from the signal...
* Only one ConnectionReference per id should exist per Signal
*/
class ConnectionReference {
private:
    int id;
    std::function<void(ConnectionReference&)> disconnectCallback;

    bool connected;
    bool muted;

    ConnectionReference(ConnectionReference const& conn);
    ConnectionReference& operator=(ConnectionReference const& conn);

public:
    ConnectionReference(int id, std::function<void(ConnectionReference &)> disconnectCallback)
            : id(id), disconnectCallback(disconnectCallback), connected(true), muted(false) {
    }

    ~ConnectionReference() {
        disconnect();
    }

    int getId() const {
        return id;
    }

    void disconnect() {
        if(connected) {
            connected = false;
            disconnectCallback(*this);
        }
    }

    bool isMuted() const {
        return muted;
    }

    bool isConnected() const {
        return connected;
    }

    void mute() {
        muted = true;
    }

    void unmute() {
        muted = false;
    }
};

#endif