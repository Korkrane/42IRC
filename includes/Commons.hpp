#ifndef COMMONS_HPP
#define COMMONS_HPP

#define CMD_DELIM	"\r\n"
#define LEN_DELIM	2

using	std::string;
using	std::stringstream;

class	Server;
class	Client;
class	IRC;
class	Channel;
class	User;
class	Command;

void	splitStr(std::vector<string> &results, string const &str, string const &delim);
bool	maskMatchesStr(string const &mask, string const &str);

#endif
