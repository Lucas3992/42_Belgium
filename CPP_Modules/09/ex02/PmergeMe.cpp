#include "PmergeMe.hpp"

Sort::Sort() {}
Sort::Sort(const Sort &o) : _v(o._v), _d(o._d) {}
Sort& Sort::operator=(const Sort &o) {
    if (this != &o) {
        _v = o._v;
        _d = o._d;
    }
    return *this;
}
Sort::~Sort() {}
Sort::SortException::SortException(const std::string msg) : _msg("Error: " + msg) {}
Sort::SortException::~SortException() throw() {}
const char* Sort::SortException::what() const throw() {return _msg.c_str();}

static bool isDuplicate(const std::vector<int>& v, int x) {
    for (std::vector<int>::const_iterator it = v.begin(); it != v.end(); ++it) {
        if (*it == x)
            return true;
    }
    return false;
}

void Sort::validateNb(const std::string& av) {
    if (av.empty() || av.find_first_not_of(" \t\n") == std::string::npos)//double negation
		throw SortException("only positive ints are allowed");
	char *end;
	long nb = strtol(av.c_str(), &end, 10);
	if (*end != '\0' || nb > INT_MAX || nb < 0)
		throw SortException("only positives int are allowed");
	if (isDuplicate(_v, (int)nb))
		throw SortException("no duplicates allowed");
	_v.push_back((int)nb);
	_d.push_back((int)nb);
}

void Sort::printBefore() {
	std::cout << "Before:";
	for (std::vector<int>::iterator it = _v.begin(); it != _v.end(); ++it)
		std::cout << " " << *it;
	std::cout << std::endl;
}

static void sortPair(std::vector<std::pair<int, int> >& pairs, const std::vector<int>& src, int i) {
	int a = src[i];
	int b = src[i +1];
	if (a > b)
		pairs.push_back(std::make_pair(a, b));
	else
		pairs.push_back(std::make_pair(b, a));
}

//etape 1: faire des paires et les trier
std::vector<std::pair<int, int> > Sort::makePairs(const std::vector<int>& src, int& alone) {
	std::vector<std::pair<int, int> > pairs;
	alone = -1;
	for (size_t i = 0; i +1 < src.size(); i += 2)
		sortPair(pairs, src, i);
	if (src.size() % 2 != 0)
		alone = src.back();
	return pairs;
}

//etape 3: construire index dinsertion;
static std::vector<int> buildJacobsthalOrder(size_t size) {
	std::vector<int> order;
	if (size == 0)
		return order;
	std::vector<int> j;
	j.push_back(1);
	j.push_back(1);
	while ((size_t)j.back() < size) { //on ajoute des nb de la suite tant que le nb en question est plus petit que pend.size();
		int n = j.size();
		j.push_back(j[n -1] + (2 * j[n -2]));
	}
	order.push_back(0);
	int previous = 1;
	for (size_t i = 2; i < j.size(); ++i) { //*
		int current = j[i];
		for (size_t d = current -1; d >= (size_t)previous; --d) {
			if (d < size)
				order.push_back(d);
		}
		previous = current;
	}
	return order;
}

//etape 2: diviser en deux piles et trier la main;
void Sort::fordJohnsonV(std::vector<int>& v) {
	if (v.size() < 2)
		return;
	int alone;
	std::vector<std::pair<int, int> > pairs = makePairs(v, alone);
	std::vector<int> main;
	std::vector<int> pend;
	for (std::vector<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
		main.push_back(it->first);
		pend.push_back(it->second);
	}
	fordJohnsonV(main);//appel recursif pour trier main;
	//jacobsthal (0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341…): deux nb de depart [0, 1] puis on commence a i = 2; J[n] = J[n -1] + 2 * J[n -2];
	//ou bien formule direkk : J[n] = (2*n -(-1)^n) / 3;
	//au lieu dinserer pend dans cet ordre : pend[1], 2, 3 etc.. 
	//on va inserer pend[1], 3 (qui est le prochain nb de la suite), puis revenir en arriere donc 2; *
	//puis de nouveau pend[5], 4, pend[11], 10 -> 6, pend[21]->12 etc...
	std::vector<int> order = buildJacobsthalOrder(pend.size());
	for (std::vector<int>::iterator oi = order.begin(); oi != order.end(); ++oi) {
		std::vector<int>::iterator pos = std::lower_bound(main.begin(), main.end(), pend[*oi]);//lowerbound return le premier element plus grand ou egal a la valeur cherchee
		main.insert(pos, pend[*oi]);
	}
	if (alone != -1) {
		std::vector<int>::iterator pos = std::lower_bound(main.begin(), main.end(), alone);
		main.insert(pos, alone);
	}
	v = main;
}

void Sort::fordJohnsonD(std::deque<int>& d) {
    if (d.size() < 2)
        return;
    int alone = -1;
    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i + 1 < d.size(); i += 2) {
        int a = d[i];
        int b = d[i + 1];
        if (a > b)
            pairs.push_back(std::make_pair(a, b));
        else
            pairs.push_back(std::make_pair(b, a));
    }
    if (d.size() % 2 != 0)
        alone = d.back();
    std::deque<int> main;
    std::deque<int> pend;
    for (std::deque<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it) {
        main.push_back(it->first);
        pend.push_back(it->second);
    }
    fordJohnsonD(main);
    std::vector<int> order;
    if (pend.size() != 0) {
        std::vector<int> j;
        j.push_back(1);
        j.push_back(1);
        while (j.back() < (int)pend.size()) {
            int n = j.size();
            j.push_back(j[n - 1] + (2 * j[n - 2]));
        }
        order.push_back(0);
        int previous = 1;
        for (size_t i = 2; i < j.size(); ++i) {
            int current = j[i];
            for (int k = current - 1; k >= previous; --k) {
                if (k < (int)pend.size())
                    order.push_back(k);
            }
            previous = current;
        }
    }
    for (std::vector<int>::iterator oi = order.begin(); oi != order.end(); ++oi) {
        std::deque<int>::iterator pos = std::lower_bound(main.begin(), main.end(), pend[*oi]);
        main.insert(pos, pend[*oi]);
    }
    if (alone != -1) {
        std::deque<int>::iterator pos = std::lower_bound(main.begin(), main.end(), alone);
        main.insert(pos, alone);
    }
    d = main;
}

void Sort::printAfter() {
	std::cout << "After:";
	for (std::vector<int>::iterator it = _v.begin(); it != _v.end(); ++it)
		std::cout << " " << *it;
	std::cout << "\nTime to process a range of " << _v.size() << " elements with std::vector: " << std::fixed << std::setprecision(5) << _timeV << " us";
	std::cout << "\nTime to process a range of " << _d.size() << " elements with std::deque: " << std::fixed << std::setprecision(5) << _timeD << " us\n";
}

void Sort::sort() {
	struct timespec start, stop;
	clock_gettime(CLOCK_MONOTONIC, &start);
	fordJohnsonV(_v);
	clock_gettime(CLOCK_MONOTONIC, &stop);
	_timeV = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) /1000.0;

	clock_gettime(CLOCK_MONOTONIC, &start);
	fordJohnsonD(_d);
	clock_gettime(CLOCK_MONOTONIC, &stop);
	_timeD = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) /1000.0;
}
