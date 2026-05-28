//
//  TreeObservable.cpp
//  Part5_ObserverPattern
//

#include "TreeObservable.h"
#include <string>

TreeObservable::TreeObservable(const std::string& sourceId)
    : sourceId(sourceId)
{
}

void TreeObservable::sendMessage(const std::string& message)
{
    lastMessage = message;
    notifyObservers();
}

std::string TreeObservable::getSourceId() const
{
    return sourceId;
}

std::string TreeObservable::getLastMessage() const
{
    return lastMessage;
}