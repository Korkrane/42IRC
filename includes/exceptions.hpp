/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:00:32 by bahaas            #+#    #+#             */
/*   Updated: 2021/11/29 17:01:02 by bahaas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

class SocketCreationFailed : public std::exception
{
    virtual const char *what() const throw()
    {
        return "ERROR: Can't create socket properly";
    };
};

class SocketBindingFailed : public std::exception
{
    virtual const char *what() const throw()
    {
        return "ERROR: Can't bind socket properly";
    };
};

class SocketListeningFailed : public std::exception
{
    virtual const char *what() const throw()
    {
        return "ERROR: Can't listen on the binded port properly";
    };
};

class TooMuchParamsFromClient : public std::exception
{
    virtual const char *what() const throw()
    {
        return "ERROR: Client has more than 15 parameters in his command";
    };
};

class TooLongCommandFromClient : public std::exception
{
    virtual const char *what() const throw()
    {
        return "ERROR: Client has sent a command longer than 512 characters";
    };
};
#endif // !EXCEPTIONS_HPP