#ifndef VLEESJONGEN_PORTAALMODEL_H
#define VLEESJONGEN_PORTAALMODEL_H

#include "../position.h"
#include "model.h"
#include <string>

namespace vlees::model {
class PortaalModel : public Model
{
private:
        Position upposition = Position(0, 0);
        Position downposition = Position(0, 0);
        std::string downrichting;
        std::string uprichting;
        char id{};

public:
        PortaalModel(const Position& up, const Position& down, char id);
        PortaalModel();
        Position getUpPosition() const;
        Position getDownPosition() const;
        PortaalModel& operator==(const PortaalModel& other);
        char getId() const;
        void addDown(Position point);
        void adjustPosition(double seconds) override{};
        std::string getUpRichting() const;
        std::string getDownRichting() const;
        void setUpRichting(std::string richting);
        void setDownRichting(std::string richting);
};
} // namespace vlees::model

#endif // VLEESJONGEN_PORTAALMODEL_H
