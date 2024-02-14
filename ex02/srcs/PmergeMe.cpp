#include "PmergeMe.hpp"

const int K = 5; // Define your constant K value

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(std::list<int> _list, std::deque<int> _deque) : mList(_list), mDeque(_deque) {}

PmergeMe::PmergeMe(const PmergeMe &other) {
    *this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    mList = other.mList;
    mDeque = other.mDeque;
    return (*this);
}

void PmergeMe::printTime(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end, const std::string& label) {
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << label << " duration: " << duration.count() << " microseconds" << std::endl;
}

void PmergeMe::mergeMe(int argc, char **argv) {
    takeArgs(argc, argv);

    auto start_list = std::chrono::high_resolution_clock::now();
    insertionSort<std::list<int>>(mList.begin(), mList.end());
    auto end_list = std::chrono::high_resolution_clock::now();
    printTime(start_list, end_list, "std::list");

    auto start_deque = std::chrono::high_resolution_clock::now();
    insertionSort<std::deque<int>>(mDeque.begin(), mDeque.end());
    auto end_deque = std::chrono::high_resolution_clock::now();
    printTime(start_deque, end_deque, "std::deque");
}

size_t PmergeMe::isStringOnlyDigits(const char *s) {
    size_t len = strlen(s);
    for (size_t i = 0; i < len; i++) {
        if (!isdigit(s[i])) {
            return (0);
        }
    }
    return (1);
}

void PmergeMe::takeArgs(int argc, char **argv) {
    int n;
    int i = 1;
    while (i < argc) {
        n = atoi(argv[i]);
        if (!isStringOnlyDigits(argv[i]) || n < 0) {
            std::cerr << "Error" << std::endl;
            exit(1);
        }
        mList.push_back(n);
        mDeque.push_back(n);
        i++;
    }

    std::cout << "Before: ";
    int count = 0;
    for (int j = 1; j < argc; ++j) {
        std::cout << argv[j] << " ";
        ++count;
    }
    std::cout << std::endl;

    // Call mergeInsert to sort the elements using the Ford-Johnson algorithm
    std::cout << "Sorting using mergeInsert algorithm...\n";
    mergeInsert<std::list<int>>(mList.begin(), mList.end());
    mergeInsert<std::deque<int>>(mDeque.begin(), mDeque.end());

    std::cout << "After sorting:  ";
    printSortedInput(mList);
    std::cout << std::endl;

    size = argc - 1;
}

template <typename T>
void PmergeMe::mergeInsert(typename T::iterator p, typename T::iterator r) {
    int n = std::distance(p, r);
    if (n <= K) {
        insertionSort<T>(p, r);
    } else {
        typename T::iterator q = p;
        std::advance(q, n / 2);
        mergeInsert<T>(p, q);
        mergeInsert<T>(q, r);
        std::cout << "Splitting range: [" << *p << ", " << *(std::prev(r)) << "] into two subranges...\n";
        merge<T>(p, q, r);
    }
}


template <typename T>
void PmergeMe::insertionSort(typename T::iterator p, typename T::iterator r) {
    typename T::iterator it = p;
    while (it != r) {
        typename T::iterator current = it;
        int temp = *it;
        typename T::iterator prev = it;
        typename T::iterator next = prev;
        next++;
        while (prev != p && *(--prev) > temp) {
            *current = *prev;
            current = prev;
        }
        *current = temp;
        current = next;
        it++;
    }
    std::cout << "After insertion sorting: ";
    printSortedRange<T>(p, r);
}

template <typename T>
void PmergeMe::merge(typename T::iterator p, typename T::iterator q, typename T::iterator r) {
    std::vector<int> L;
    std::vector<int> R;

    for (typename T::iterator it = p; it != q; ++it) {
        L.push_back(*it);
    }
    for (typename T::iterator it = q; it != r; ++it) {
        R.push_back(*it);
    }

    typename std::vector<int>::iterator itL = L.begin();
    typename std::vector<int>::iterator itR = R.begin();
    typename T::iterator itA = p;

    while (itL != L.end() && itR != R.end()) {
        if (*itL <= *itR) {
            *itA = *itL;
            ++itL;
        } else {
            *itA = *itR;
            ++itR;
        }
        ++itA;
    }

    while (itL != L.end()) {
        *itA = *itL;
        ++itL;
        ++itA;
    }

    while (itR != R.end()) {
        *itA = *itR;
        ++itR;
        ++itA;
    }
    std::cout << "After merging: ";
    printSortedRange<T>(p, r);
}

void PmergeMe::printSortedInput(const std::list<int>& sortedList) {
    for (const auto& item : sortedList) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void PmergeMe::printSortedRange(typename T::iterator p, typename T::iterator r) {
    for (auto it = p; it != r; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
