#ifndef VLEESJONGEN_MODEL_H
#define VLEESJONGEN_MODEL_H

#include <memory>

#include "../events/adjust.h"
#include "../object.h"
#include "../observer.h"

namespace vlees::model {
class Model : public observer::Observer, public observer::Object, public std::enable_shared_from_this<Model>
{
public:
        virtual void adjustPosition(double seconds) = 0;

        void update(std::shared_ptr<event::BaseEvent>& event) override;
};
} // namespace vlees::model

#endif // VLEESJONGEN_MODEL_H
