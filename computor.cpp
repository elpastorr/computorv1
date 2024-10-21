#include "computor.hpp"

void	print_complex(float a, float b, double sqrt)
{
	if (is_whole(b / (2 * a)) || !is_whole(2 * a) || !is_whole(b))
		std::cout << b / (2 * a);
	else
		print_fraction(static_cast<int>(b), static_cast<int>(2 * a));
	std::cout << " + ";
	if (is_whole(sqrt / (2 * a)) || !is_whole(2 * a) || !is_whole(sqrt))
		std::cout << sqrt / (2 * a) << "i" << std::endl;
	else
	{
		print_fraction(static_cast<int>(b), static_cast<int>(2 * a));
		std::cout << std::endl;
	}
	if (is_whole(b / 2 * a) || !is_whole(2 * a) || !is_whole(b))
		std::cout << b / (2 * a);
	else
		print_fraction(static_cast<int>(b), static_cast<int>(2 * a));
	std::cout << " - ";
	if (is_whole(sqrt / (2 * a)) || !is_whole(2 * a) || !is_whole(sqrt))
		std::cout << sqrt / (2 * a) << "i"  << std::endl;
	else
	{
		print_fraction(static_cast<int>(b), static_cast<int>(2 * a));
		std::cout << std::endl;
	}
}

void	simplify_equation(Liste *left, Liste *right)
{
	Terme	*current = right->first;
	Terme	*temp;

	while (current != NULL)
	{
		if (current->coeff != 0)
		{
			temp = current->next;
			move_elem(left, *current);
		}
		current = temp;
	}
	delete_liste(right);
}

int	print_reduced_form(Liste *equation)
{
	Terme	*current = equation->first;
	int		max_exp = 0;
	bool	neg_coeff = false;
	bool	writed = false;
	std::stringstream tmp;
	std::string temp;

	std::cout << "Reduced form: ";
	while (current != NULL)
	{
		if (current->coeff != 0)
		{
			if (max_exp < current->exposant)
				max_exp = current->exposant;
			if (neg_coeff == false)
				std::cout << current->coeff << " * X^" << current->exposant;
			else
			{
				tmp << current->coeff;
				temp = tmp.str();
				std::cout << temp.substr(1, temp.length() - 1) << " * X^" << current->exposant;
				tmp.str("");
				temp.clear();
			}
			if (current->next != NULL)
			{
				if (current->next->coeff >= 0)
				{
					std::cout << " + ";
					neg_coeff = false;
				}
				else
				{
					std::cout << " - ";
					neg_coeff = true;
				}
			}
			writed = true;
		}
		current = current->next;
	}
	if (writed == false)
		std::cout << "0";
	std::cout << " = 0" << std::endl << "Polynomial degree: " << max_exp << std::endl;
	if (max_exp > 2)
	{
		std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
		return 42;
	}
	return max_exp;
}

int	reduce_form(Liste *equation)
{
	Terme	*current = equation->first;
	Terme	*temp;
	Terme	*tmp;

	while (current != NULL)
	{
		tmp = current;
		temp = current->next;
		while (temp != NULL)
		{
			if (temp->exposant == current->exposant)
			{
				current->coeff += temp->coeff;
				tmp->next = temp->next;
				delete temp;
				temp = tmp;
			}
			tmp = temp;
			temp = temp->next;
		}
		current = current->next;
	}
	return (print_reduced_form(equation));
}

void	solve_X0(Liste *equation)
{
	Terme	*current = equation->first;
	while (current != NULL)
	{
		if (current->exposant == 0)
		{
			if (current->coeff == 0)
				std::cout << "Each real number is a solution" << std::endl;
			else
				std::cout << "This polynomial equation is impossible" << std::endl;			
		}
		current = current->next;
	}
}

void	solve_X1(Liste *equation)
{
	Terme	*current = equation->first;
	float	a;
	float	b;
	float	x;

	while (current != NULL)
	{
		if (current->exposant == 1)
			a = current->coeff;
		else if (current->exposant == 0)
			b = current->coeff;
		current = current->next;
	}
	std::cout << "aX + b; a = " << a << " b = " << b << "; X = -b / a" << std::endl;
	std::cout << "The solution is:" << std::endl;
	if (b == 0)
		std::cout << 0 << std::endl;
	else
	{
		x = -b / a;
		if (is_whole(x) || !is_whole(a) || !is_whole(b))
			std::cout << x << std::endl;
		else
		{
			print_fraction(static_cast<int>(-b), static_cast<int>(a));
			std::cout << std::endl;
		}
	}
}

void	solve_X2(Liste *equation)
{
	Terme	*current = equation->first;
	float	a;
	float	b;
	float	c;
	float	delta;
	float	x1;
	float	x2;
	double	sqrt;
	bool	b_set = false;
	bool	c_set = false;

	while (current != NULL)
	{
		if (current->exposant == 2)
			a = current->coeff;
		else if (current->exposant == 1)
		{
			b = current->coeff;
			b_set = true;
		}
		else if (current->exposant == 0)
		{
			c = current->coeff;
			c_set = true;
		}
		current = current->next;
	}
	if (b_set == false)
		b = 0.0;
	if (c_set == false)
		c = 0.0;

	std::cout << "aX^2 + bX + c; a = " << a << " b = " << b << " c = " << c << "; delta = b^2 - 4ac" << std::endl;

	delta = (b * b) - (4 * a * c);
	std::cout << "delta = " << delta << std::endl;
	if (delta > 0)
	{
		sqrt = static_cast<float>(ft_sqrt(static_cast<double>(delta)));
		std::cout << "sqrt(delta) = " << sqrt << std::endl;
		x1 = (-b + sqrt) / (2 * a);
		x2 = (-b - sqrt) / (2 * a);
		std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
		if (is_whole(x1) || !is_whole(2 * a) || !is_whole(-b + sqrt))
			std::cout << x1 << std::endl;
		else
		{
			print_fraction(static_cast<int>(-b + sqrt), static_cast<int>(2 * a));
			std::cout << std::endl;
		}
		if (is_whole(x2) || !is_whole(2 * a) || !is_whole(-b - sqrt))
			std::cout << x2 << std::endl;
		else
		{
			print_fraction(static_cast<int>(-b - sqrt), static_cast<int>(2 * a));
			std::cout << std::endl;
		}
	}
	else if (delta == 0)
	{
		if (b == 0)
			x1 = 0;
		else
			x1 = -b / (2 * a);
		std::cout << "Discriminant is strictly null: X = -b / 2a" << std::endl;

		std::cout << "The solution is:" << std::endl;
		if (is_whole(x1) || !is_whole(a) || !is_whole(b))
			std::cout << x1 << std::endl;
		else
		{
			print_fraction(static_cast<int>(-b), static_cast<int>(a));
			std::cout << std::endl;
		}
	}
	else
	{
		sqrt = static_cast<float>(ft_sqrt(static_cast<double>(-delta)));
		std::cout << "sqrt(delta) = " << sqrt << "i" << std::endl;
		std::cout << "Discriminant is strictly negative, the two complex solutions are:" << std::endl;
		if (b != 0)
			print_complex(a, -b, sqrt);
		else
			print_complex(a, b, sqrt);
	}
}

int	main(int ac, char **av)
{
	std::string	equation;
	std::string	left_side;
	std::string	right_side;
	Liste	*left;
	Liste	*right;
	
	if (ac < 2)
	{
		std::cout << "Error: no argument given.." << std::endl;
		return (1);
	}
	equation = av[1];
	prepare_equation(equation);
	if (!valid_chars(equation.c_str()))
		return 1;
	left_side = equation.substr(0, equation.find("="));
	right_side = equation.substr(equation.find("=") + 1, equation.length() - equation.find("=") - 1);
	if (right_side.find(" ") == 0)
		right_side = right_side.substr(1, right_side.length() - 1);
	if (!check_sides(left_side, right_side))
		return 1;
	left = create_liste(left_side);
	if (left == NULL)
		return 1;
	right = create_liste(right_side);
	if (right == NULL)
	{
		delete_liste(left);
		return 1;
	}
	simplify_equation(left, right);

	switch (reduce_form(left))
	{
	case 0:
		solve_X0(left);
		break;
	case 1:
		solve_X1(left);
		break;
	case 2:
		solve_X2(left);
		break;
	default:
		break;
	}
	delete_liste(left);

	return 0;
}
