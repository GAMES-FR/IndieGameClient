#ifndef VECTOR_HPP_
# define VECTOR_HPP_

# include <cmath>

namespace Vector {
	class Vec2 {
	public:
		double x;
		double y;

		Vec2(double x = 0.0, double y = 0.0);
		~Vec2();

		Vec2(const Vec2 & v);
		Vec2 & operator=(const Vec2 & v);

		void set(double x, double y);

		double getX() const;
		void setX(double x);

		double getY() const;
		void setY(double x);

		double len() const;
		double dot(const Vec2 & v) const;
		double det(const Vec2 & v) const;
		void rotate( double r);
		double angle() const;
		void setLen(double l);
		void normalize();
	};
	double len(double x, double y);
	double angle(double x, double y);
}

#endif