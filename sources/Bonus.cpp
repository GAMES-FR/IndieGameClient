#include "Bonus.hpp"

Bonus::Bonus(Bonus::Type type)
{
	this->_type = type;
}

Bonus::~Bonus()
{

}

Bonus::Type Bonus::getType() const
{
	return (this->_type);
}