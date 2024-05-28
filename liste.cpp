#include "computor.hpp"

Liste	*init_liste()
{
	Liste	*liste = new Liste();

	if (liste == NULL)
	{
		std::cout << "ERROR: malloc problem" << std::endl;
		exit(EXIT_FAILURE);
	}
	liste->first = NULL;

	return liste;
}

void	delete_liste(Liste *liste)
{
	if (liste == NULL)
		return;
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

int	add_elem(Liste *liste, std::string elem)
{
	Terme	*new_terme = new Terme();
	std::string	exp = "0";
	std::string coeff = "0";

	if (liste == NULL || new_terme == NULL)
	{
		std::cout << "ERROR: malloc problem" << std::endl;
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
		std::cout << "ERROR: coeff [" << coeff << "] is invalid" << std::endl;
		delete new_terme;
		delete_liste(liste);
		return 1;
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
	return 0;
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
		if (add_elem(liste, temp))
			return NULL;
	}
	temp = str.substr(0, str.find(" ", 1));
	if (add_elem(liste, temp))
		return NULL;
	return liste;
}

// void	print_liste(Liste *liste)
// {
// 	if (liste == NULL)
// 	{
// 		std::cout << "ERROR: print liste NULL" << std::endl;
// 		exit(EXIT_FAILURE);
// 	}
// 	Terme *current = liste->first;
// 	while (current != NULL)
// 	{
// 		std::cout << current->coeff << "X^" << current->exposant << " (+)";
// 		current = current->next;
// 	}
// 	std::cout << "\nNULL" << std::endl;
// }