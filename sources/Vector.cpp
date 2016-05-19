#include "Vector.hpp"

double Vector::len(double x, double y)
{
	return (sqrt(x * x + y * y));
}

double Vector::angle(double x, double y)
{
	return (atan2(y, x));
}

Vector::Vec2::Vec2(double _x, double _y) : x(_x), y(_y) {}

Vector::Vec2::~Vec2() {}

Vector::Vec2::Vec2(const Vec2 & v)
{
	this->x = v.getX();
	this->y = v.getY();
}

Vector::Vec2 & Vector::Vec2::operator=(const Vec2 & v)
{
	this->x = v.getX();
	this->y = v.getY();
	return (*this);
}

void Vector::Vec2::set(double _x, double _y)
{
	this->x = _x;
	this->y = _y;
}

double Vector::Vec2::getX() const
{
	return (this->x);
}

void Vector::Vec2::setX(double _x)
{
	this->x = _x;
}

double Vector::Vec2::getY() const
{
	return (this->y);
}

void Vector::Vec2::setY(double _y)
{
	this->y = _y;
}

double Vector::Vec2::len() const
{
	return (sqrt(this->x * this->x + this->y * this->y));
}

double Vector::Vec2::dot(const Vec2 & v) const
{
	return (this->x * v.getX() + this->y * v.getY());
}

double Vector::Vec2::det(const Vec2 & v) const
{
	return (this->x * v.getX() - this->y * v.getY());
}

void Vector::Vec2::rotate( double r)
{
	double 	_x = this->x, _y = this->y, _c = cos(r), _s = sin(r);

    this->x = _x * _c - _y * _s;
    this->y = _x * _s + _y * _c;
}

double Vector::Vec2::angle() const
{
    return (atan2(this->y, this->x));
}

void Vector::Vec2::setLen(double l)
{
    double s = this->len();
    if (s > 0.0) {
        s = l / s;
        this->x *= s;
        this->y *= s;
    } else {
        this->x = l;
        this->y = 0.0;
    }
}

void Vector::Vec2::normalize()
{
    this->setLen(1.0);
}