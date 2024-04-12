#ifndef VLEESJONGEN_BASEEVENT_H
#define VLEESJONGEN_BASEEVENT_H

namespace vlees::event {
class BaseEvent
{
private:
        bool handled = false;

public:
        BaseEvent();
        virtual ~BaseEvent();
};
} // namespace vlees::event

#endif // VLEESJONGEN_BASEEVENT_H
