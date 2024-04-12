
#ifndef VLEESJONGEN_MOVINGBLOKMODEL_H
#define VLEESJONGEN_MOVINGBLOKMODEL_H
#include "movablemodel.h"

namespace vlees::model {
class MovingBlokModel : public MovableModel
{
public:
        MovingBlokModel() = default;
        MovingBlokModel(float x, float y, float xgoal, float ygoal) : MovableModel(x, y, xgoal, ygoal, "blok") {}
};
} // namespace vlees::model

#endif // VLEESJONGEN_MOVINGBLOKMODEL_H
