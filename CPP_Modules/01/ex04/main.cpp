#include <iostream>
#include <fstream>
#include <string>

static int	print_error(const std::string &msg)
{
	std::cerr << "Error\n" << msg << "\n";
	return 1;
}

static std::string	replace_in_line(const std::string &line,
									const std::string &s1,
									const std::string &s2)
{
	std::string result;
	std::size_t pos = 0;
	std::size_t found;

	found = line.find(s1, pos);
	while (found != std::string::npos)
	{
		result.append(line.substr(pos, found - pos));
		result.append(s2);
		pos = found + s1.length();
		found = line.find(s1, pos);
	}
	result.append(line.substr(pos));
	return result;
}

static void	copy_with_replace  (std::ifstream &infile,
								std::ofstream &outfile,
								const std::string &s1,
								const std::string &s2)
{
	std::string line;

	while (std::getline(infile, line))
		outfile << replace_in_line(line, s1, s2) << '\n';
}

int	main(int ac, char **av)
{
	std::string s1;
	std::string s2;
	std::string outname;

	if (ac != 4)
		return print_error("Usage: ./ex04 <filename> <s1> <s2>");
	s1 = av[2];
	s2 = av[3];
	if (s1.empty())
		return print_error("S1 must not be empty");
	std::ifstream infile(av[1]);
	if (!infile)
		return print_error("Cannot open input file");
	outname = std::string(av[1]) + ".replace";
	std::ofstream outfile(outname.c_str());
	if (!outfile)
		return print_error("Cannot create output file");
	copy_with_replace(infile, outfile, s1, s2);
	return 0;
}
