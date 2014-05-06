#ifndef __EVENTS_SIGNAL_H_
#define __EVENTS_SIGNAL_H_

#include <functional>
#include <list>
#include <unordered_map>
#include <memory>

#include "ConnectionReference.h"
#include "Connection.h"

template<class Fn>
class Signal {

private:
    int nextConnectionId;
    std::list< std::shared_ptr<ConnectionReference> > connectionReferences;
    std::unordered_map<int, std::function<Fn> > callbackMap;



    //Called automagically by ConnectionReference objects, yay! (such evil)
    void connectionDisconnected(ConnectionReference& conn) {
        for(auto it = connectionReferences.begin(); it != connectionReferences.end(); it++) {

            if((*it)->getId() == conn.getId()) {
                callbackMap.erase((*it)->getId());
                connectionReferences.erase(it);
                //break; or not? right? right...?! :(
            }

        }
    }

public:

    Signal() : nextConnectionId(0) {
    }

    Connection connect(std::function<Fn> callback) {
        connectionReferences.push_back( std::shared_ptr<ConnectionReference>(new ConnectionReference(++nextConnectionId, std::bind(&Signal<Fn>::connectionDisconnected, this, std::placeholders::_1))) );
        callbackMap[nextConnectionId] = callback;

        return Connection( connectionReferences.back() );
    }

    template<class... Args>
    void notify(Args... args) {
        for(auto connRef : connectionReferences) {
            if(!connRef->isMuted()) {
                callbackMap[connRef->getId()](std::forward<Args>(args)...);
            }
        }
    }

};

#endif