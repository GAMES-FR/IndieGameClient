#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

#ifndef BONUS_HPP_
# define BONUS_HPP_

# include <cstdlib>

class Bonus
{
public:
	enum Type
	{
		MISSILE,
		HEAL
	};

private:
	Type _type;

public:
	Bonus(Type);

	~Bonus();

	Type getType() const;
};

#endif /* !BONUS_HPP_ */