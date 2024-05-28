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


// LISTE.CPP
Liste	*init_liste();
void	delete_liste(Liste *liste);
int		add_elem(Liste *liste, std::string elem);
void	move_elem(Liste *liste, Terme terme);
Liste	*create_liste(std::string str);
void	print_liste(Liste *liste);

// UTILS.CPP
double	ft_abs(double nb);
double	ft_sqrt(double number);
bool	is_whole(float num);
int		ft_pgcd(int a, int b);
void	print_fraction(int b, int a);
bool	valid_chars(const char *s);
bool	valid_coeff(std::string coeff);
void	replace_all(std::string &src, std::string from, std::string to);
void	prepare_equation(std::string &raw);
bool	check_sides(std::string left, std::string right);


#endif