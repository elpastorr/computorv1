#include "computor.hpp"

double	ft_abs(double nb)
{
	if (nb < 0)
		return (-nb);
	return nb;
}

double	ft_sqrt(double number)
{
	double	precision = 0.00001;
	double	estimation = number;
	double	sqrt = (estimation + number / estimation) / 2;

	while (ft_abs(estimation - sqrt) >= precision)
	{
		estimation = sqrt;
		sqrt = (estimation + number / estimation) / 2;
	}
	return sqrt;
}

bool	is_whole(float num)
{
	std::string	number = std::to_string(num);
	bool	after_point = false;
	for (std::string::iterator it = number.begin(); it != number.end(); it++)
	{
		if (*it == '.')
			after_point = true;
		else if (after_point == true && *it != '0')
			return 0;
	}
	return 1;
}

int	ft_pgcd(int a, int b)
{
	int	i = 2;

	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;
	while (i <= a && i <= b)
	{
		if (a % i == 0 && b % i == 0)
			return (ft_pgcd(a / i, b / i) * i);
		i++;
	}
	return 1;
}

void	print_fraction(int b, int a)
{
	if (b == 0)
		b = -1;
	int	pgcd = ft_pgcd(b, a);
	if (a < 0)
	{
		if (b < 0)
			std::cout << -b / pgcd << " / " << -a / pgcd;
		else
			std::cout << "-" << b / pgcd << " / " << -a / pgcd;
	}
	else
		std::cout << b / pgcd << " / " << a / pgcd;
}

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
	raw.erase(std::remove(raw.begin(), raw.end(), ' '), raw.end());
	replace_all(raw, "+", " +");
	replace_all(raw, "-", " -");
	if (raw.find(" ") == 0)
		raw.erase(std::remove(raw.begin(), raw.begin() + 1, ' '), raw.begin() + 1);
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