#include "MutantStack.hpp"

int main() {
    MutantStack<int> mstack;//lifo
    
    mstack.push(5);
    mstack.push(17);
    std::cout << "mstack top value: " << mstack.top() << std::endl;
    std::cout << "mstack size before pop: " << mstack.size() << std::endl;
    mstack.pop();
    std::cout << "mstack size after pop: " << mstack.size() << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();
    ++it;
	std::cout << *it << " | ";
    --it;
	std::cout << *it << std::endl;
    while (it != ite) {
        std::cout << *it << std::endl;
        ++it;
    }
    std::cout << std::string(70, '-') << std::endl;

    std::stack<int> s(mstack);
    std::cout << "Top s value: " << s.top() << std::endl;
    std::cout << "S size: " << s.size() << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    std::list<int> l;//double chainee
    
    l.push_back(5);
    l.push_back(17);
    std::cout << "Top value: " << l.back() << std::endl;
    std::cout << "Size before pop: " << l.size() << std::endl;
    l.pop_back();
    std::cout << "Size after pop: " << l.size() << std::endl;
    l.push_back(3);
    l.push_back(5);
    l.push_back(737);
    l.push_back(0);
    std::list<int>::iterator i = l.begin();
    std::list<int>::iterator j = l.end();
    ++i;
	std::cout << *i << " | ";
    --i;
	std::cout << *i << std::endl;
    while (i != j) {
        std::cout << *i << std::endl;
        ++i;
    }
    std::cout << std::string(70, '-') << std::endl;

    return 0;
}
