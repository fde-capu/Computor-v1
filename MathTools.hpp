/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MathTools.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-capu <fde-capu@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:25:31 by fde-capu          #+#    #+#             */
/*   Updated: 2024/02/05 16:25:32 by fde-capu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHTOOLS_HPP
# define MATHTOOLS_HPP

# include "StringTools.hpp"
# include <iostream>

typedef struct Complex {
    double real;
    double imag;
} complex_t;

double sqrt(double);
void noMinusZero(double&);

#endif
