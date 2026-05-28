//
//  TreeObservable.h
//  Part5_ObserverPattern
//


#ifndef TreeObservable_h
#define TreeObservable_h

#include <ql/patterns/observable.hpp>
#include <string>

class TreeObservable : public QuantLib::Observable
{
public:
    TreeObservable(const std::string& sourceId);
    
    void sendMessage(const std::string& message);
    std::string getSourceId() const;
    std::string getLastMessage() const;

private:
    std::string sourceId;
    std::string lastMessage;
};

#endif /* TreeObservable_h */