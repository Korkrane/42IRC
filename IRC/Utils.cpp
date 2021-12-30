#include <vector>
#include <string>

// Split str into words seperated by delim. Put words inside results
void	splitStr
	(std::vector<std::string> &results, std::string const &str, std::string const &delim)
{
	std::size_t	i(0);

	while (i < str.size())
	{
		std::size_t delimIdx(str.find(delim, i));
		if (delimIdx == std::string::npos)
			delimIdx = str.size();
		if ((delimIdx - i) > 0)
			results.push_back(str.substr(i, delimIdx - i));
		i = delimIdx + delim.size();
	}
}

// Return true if a mask (may contains wildcard character *) matches str
bool	maskMatchesStr(std::string const &mask, std::string const &str)
{

}
