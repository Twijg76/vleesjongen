#include "portaalmodel.h"

vlees::model::PortaalModel::PortaalModel(const vlees::Position& up, const vlees::Position& down, char idd)
    : upposition(up), downposition(down), id(idd)
{
}

vlees::Position vlees::model::PortaalModel::getUpPosition() const { return upposition; }
vlees::Position vlees::model::PortaalModel::getDownPosition() const { return downposition; }
vlees::model::PortaalModel::PortaalModel()
{
        upposition = Position(0, 0);
        downposition = Position(0, 0);
}
vlees::model::PortaalModel& vlees::model::PortaalModel::operator==(const vlees::model::PortaalModel& other)
{
        // compare id's
        if (this->id == other.id) {
                return *this;
        }
}
char vlees::model::PortaalModel::getId() const { return id; }
void vlees::model::PortaalModel::addDown(vlees::Position point) { downposition = point; }
std::string vlees::model::PortaalModel::getUpRichting() const { return uprichting; }
std::string vlees::model::PortaalModel::getDownRichting() const { return downrichting; }
void vlees::model::PortaalModel::setUpRichting(std::string richt) { this->uprichting = std::move(richt); }
void vlees::model::PortaalModel::setDownRichting(std::string richt) { this->downrichting = std::move(richt); }
