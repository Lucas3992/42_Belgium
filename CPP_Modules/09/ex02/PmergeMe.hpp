#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <deque>
# include <vector>
# include <cstdlib>
# include <climits>
# include <algorithm>
# include <time.h>
# include <iomanip>

class Sort {
    private:
        std::vector<int>    _v;
        std::deque<int>     _d;
        double              _timeV;
        double              _timeD;
    public:
        Sort();
        Sort(const Sort& o);
        Sort& operator=(const Sort& o);
        ~Sort();

        void validateNb(const std::string& av);
        void printBefore();

        std::vector<std::pair<int, int> > makePairs(const std::vector<int>& src, int& alone);
        void fordJohnsonV(std::vector<int>& v);
        void fordJohnsonD(std::deque<int>& d);
        void sort();
        void printAfter();

    class SortException : public std::exception {
        private:
            std::string _msg;
        public:
            SortException(const std::string msg);
            virtual ~SortException() throw();
            virtual const char* what() const throw();
    };
};

#endif