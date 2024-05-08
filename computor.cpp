#include "computor.hpp"

bool	valid_chars(const char *s)
{
	int	i = 0;
	bool	equal = false;

	while (s[i])
	{
		if ((s[i] < '0' || s[i] > '9') && s[i] != '^' && s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '.' && s[i] != '=' && s[i] != 'X' && s[i] != ' ')
		{
			std::cout << "Error: Invalid char '" << s[i] << "'" << std::endl;
			return (0);
		}
		else if (s[i] == '=' && equal == false)
			equal = true;
		else if (s[i] == '=' && equal == true)
		{
			std::cout << "Error: Invalid input, more than 1 '='" << std::endl;
			return (0);
		}
		i++;
	}
	if (equal == false)
	{
		std::cout << "Error: Invalid input, no '='" << std::endl;
		return (0);
	}
	return (1);
}

bool	valid_coeff(std::string coeff)
{
	if (coeff.find_first_of("0123456789") != std::string::npos)
		return true;
	return false;
}

void	replace_all(std::string &src, std::string from, std::string to)
{
	std::string	new_string;
	new_string.reserve(src.length());

	std::string::size_type	last_pos = 0;
	std::string::size_type	find_pos;

	while (std::string::npos != (find_pos = src.find(from, last_pos)))
	{
		new_string.append(src, last_pos, find_pos - last_pos);
		new_string += to;
		last_pos = find_pos + from.length();
	}
	new_string += src.substr(last_pos);

	src.swap(new_string);
}

void	prepare_equation(std::string &raw)
{
	std::string	equation;
	raw.erase(std::remove(raw.begin(), raw.end(), ' '), raw.end());
	replace_all(raw, "+", " +");
	replace_all(raw, "-", " -");
	if (raw.find(" ") == 0)
		raw.erase(std::remove(raw.begin(), raw.begin() + 1, ' '), raw.begin() + 1);
}

Liste	*init_liste()
{
	Liste	*liste = new Liste();
	Terme	*terme = NULL;

	if (liste == NULL)
	{
		std::cout << "EXIT: malloc problem" << std::endl;
		exit(EXIT_FAILURE);
	}
	liste->first = terme;

	return liste;
}

void	add_elem(Liste *liste, std::string elem)
{
	Terme	*new_terme = new Terme();
	std::string	exp = "0";
	std::string coeff = "0";

	if (liste == NULL || new_terme == NULL)
	{
		std::cout << "EXIT: malloc problem" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	new_terme->elem = elem;
	if (elem.find("X") != std::string::npos)
	{
		if (elem.find("^") != std::string::npos)
			exp = elem.substr(elem.find("^") + 1);
		else
			exp = "1";
		if (elem.find("*") != std::string::npos)
			coeff = elem.substr(0, elem.find("X") - 1);
		else if ((elem.substr(0, elem.find("X")) != "") && (elem.substr(0, elem.find("X")) != "+") && (elem.substr(0, elem.find("X")) != "-"))
			coeff = elem.substr(0, elem.find("X"));
		else if (elem.substr(0, elem.find("X")) == "-")
			coeff = "-1";
		else
			coeff = "1";
	}
	else
		coeff = elem.substr(0, elem.back());

	if (!valid_coeff(coeff))
	{
		std::cout << "EXIT: coeff [" << coeff << "] is invalid" << std::endl;
		exit(EXIT_FAILURE);
	}
	new_terme->exposant = std::stoi(exp);
	new_terme->coeff = std::stof(coeff);
	if (new_terme->coeff == 0)
		delete new_terme;
	else
	{
		new_terme->next = liste->first;
		liste->first = new_terme;
	}
}

void	move_elem(Liste *liste, Terme terme)
{
	Terme	*new_terme = new Terme();

	*new_terme = terme;
	new_terme->next  = liste->first;
	new_terme->coeff *= -1;
	liste->first = new_terme;
}

Liste	*create_liste(std::string str)
{
	Liste	*liste = init_liste();
	std::string	temp;

	while (str.find(" ") != std::string::npos)
	{
		temp = str.substr(0, str.find(" ", 1));
		str.erase(0, str.find(" ", 1) + 1);
		add_elem(liste, temp);
	}
	temp = str.substr(0, str.find(" ", 1));
	add_elem(liste, temp);
	return liste;
}

void	delete_liste(Liste *liste)
{
	Terme	*current = liste->first;
	Terme	*tmp;

	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		delete tmp;
	}
	delete liste;
}

void	print_liste(Liste *liste)
{
	if (liste == NULL)
	{
		std::cout << "EXIT: print liste NULL" << std::endl;
		exit(EXIT_FAILURE);
	}

	Terme *current = liste->first;

	while (current != NULL)
	{
		std::cout << current->coeff << "X^" << current->exposant << " (+)";
		current = current->next;
	}
	std::cout << "\nNULL" << std::endl;
}

bool	check_sides(std::string left, std::string right)
{
	if ((left.find("^") != std::string::npos && !isdigit(left[left.find("^") + 1])) || (right.find("^") != std::string::npos && !isdigit(right[right.find("^") + 1])))
	{
		std::cout << "Error: Invalid input, no exposant after '^'" << std::endl;
		return false;
	}
	return true;
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
	std::stringstream tmp;
	std::string temp;

	std::cout << "Reduced form: ";
	while (current != NULL)
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
			if (current->next->coeff > 0)
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
		current = current->next;
	}
	std::cout << " = 0" << std::endl << "Polynomial degree: " << max_exp << std::endl;
	if (max_exp > 2)
	{
		std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
		delete_liste(equation);
		exit(EXIT_SUCCESS);
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
	if (equation->first->coeff == 0)
		std::cout << "Each real number is a solution" << std::endl;
	else
		std::cout << "This polynomial equation is impossible" << std::endl;
}

void	solve_X1(Liste *equation)
{
	Terme	*current = equation->first;

	while (current != NULL)
	{

		current = current->next;
	}
}

void	solve_X2(Liste *equation)
{
	Terme	*current = equation->first;
	while (current != NULL)
	{
		
		current = current->next;
	}
}

//!!!!!!!!!!!   0=0 crash      !!!!!!!!!!!
//!!!!!!!!!!!   2X+3=2X+3 WRONG OUTPUT      !!!!!!!!!!
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
	right = create_liste(right_side);

	simplify_equation(left, right);

	switch (reduce_form(left))
	{
	case 0:
		solve_X0(left);
		break;
	case 1:
		solve_X1(left);
		break;
	default:
		solve_X2(left);
		break;
	}
	delete_liste(left);

	return 0;
}