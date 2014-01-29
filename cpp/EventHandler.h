#ifndef _EVENT_HANDLER_H_
#define _EVENT_HANDLER_H_
template <class T>
class EventHandler
{
public:
    virtual void OnEvent(const T&, int eventId) = 0;
    virtual ~EventHandler(){}
};
#endif
