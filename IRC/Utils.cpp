#include <vector>
#include <string>

// Split str into words seperated by delim. Put words inside results
void	StrSplit
	(std::vector<std::string> &results, std::string const &str, std::string const &delim)
{
	size_t	i(0);

	while (i < str.size())
	{
		size_t delimIdx(str.find(delim, i));
		if (delimIdx == std::string::npos)
			delimIdx = str.size();
		if ((delimIdx - i) > 0)
			results.push_back(str.substr(i, delimIdx - i));
		i = delimIdx + delim.size();
	}
}

// Return true if a mask (may contains wildcard character *) matches
// str's pattern. This function assumes mask doesn't contain multiple
// consecutive wildcard characters
bool	StrMatch(char const *mask, char const *str)
{
	if (*mask == '\0' && *str == '\0')
		return true;
	if (*mask == '*' && *(mask+1) != '\0' && *str == '\0')
		return false;
	if (*mask == *str)
		return StrMatch(mask+1, str+1);
	if (*mask == '*')
		return StrMatch(mask+1, str) || StrMatch(mask, str+1);
	return false;
}
