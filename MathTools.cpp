/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MathTools.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:19:54 by fde-capu          #+#    #+#             */
/*   Updated: 2024/02/05 16:24:22 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MathTools.hpp"

double sqrt(double number)
{
    double error = 0.000001;
    double guess = number;

    while (guess - (number / guess) > error)
        guess = (guess + (number / guess)) / 2;
    return guess;
}

void noMinusZero(double& d)
{
	std::string noMinus = dtoa(d);
	if (noMinus.at(0) == '-')
		noMinus = noMinus.substr(1);
	d = std::stod(noMinus.c_str());
}
