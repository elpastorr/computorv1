#ifndef COMPUTOR_HPP
# define COMPUTOR_HPP

# include <sstream>
# include <iostream>
# include <string>
# include <algorithm>

typedef struct Terme {
	std::string elem;
	int	exposant;
	float	coeff;
	Terme	*next;
} Terme;

typedef struct Liste {
	Terme	*first;
} Liste;

#endif