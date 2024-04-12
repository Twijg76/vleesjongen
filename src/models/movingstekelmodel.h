#ifndef VLEESJONGEN_MOVINGSTEKELMODEL_H
#define VLEESJONGEN_MOVINGSTEKELMODEL_H

#include "movablemodel.h"

namespace vlees::model {
class MovingStekelModel : public MovableModel
{
public:
        MovingStekelModel() = default;
        MovingStekelModel(float x, float y, float xgoal, float ygoal) : MovableModel(x, y, xgoal, ygoal, "stekel") {}
};
} // namespace vlees::model

#endif // VLEESJONGEN_MOVINGSTEKELMODEL_H
