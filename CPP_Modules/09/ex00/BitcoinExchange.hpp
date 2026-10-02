#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <map>
# include <cstdlib>
# include <fstream>

class btc {
	private:
		std::map<std::string, float>	_map;

		bool isValidDate(const std::string &date) const;
		bool isValidValue(const std::string &valueSTR, double& value) const;
        float getRateForDate(const std::string& date) const;
	public:
		btc();
		btc(const btc& o);
		btc& operator=(const btc& o);
		~btc();

		bool isValidRate(const std::string& rateSTR, double& rate) const;
		void checkDate(const std::string& year, const std::string& month, const std::string& day) const;
		void expectPipe(std::string& line, size_t& pipePos);
		void loadDatabase(const std::string &file);
		void processInput(const std::string& file);
		class btcException : public std::exception {
			private:
				std::string _msg;
			public:
				btcException(const std::string& msg);
				virtual ~btcException() throw();
				virtual const char* what() const throw();
		};
};

#endif