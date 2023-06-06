#ifndef MAGICAL_CONTAINER_H
#define MAGICAL_CONTAINER_H

#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

namespace ariel
{
    class MagicalContainer
    {
    private:
        vector<int> elements; // vector of elements

    public:
        MagicalContainer();
        void addElement(int element);
        void removeElement(int element);
        size_t size();
        vector<int> &getElements();
        void setElements(vector<int> new_elements);

        class AscendingIterator
        {
        private:
            MagicalContainer *container; // pointer to MagicalContainer
            size_t currentIndex;         // current index

        public:
            AscendingIterator(MagicalContainer &container);
            AscendingIterator(const AscendingIterator &other);
            AscendingIterator(AscendingIterator &&other) = default; // Move constructor
            ~AscendingIterator() = default;
            AscendingIterator &operator=(const AscendingIterator &other);
            AscendingIterator &operator=(AscendingIterator &&other) = default; // Move assignment operator
            AscendingIterator &operator++();
            int operator*() const;
            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;
            bool operator>(const AscendingIterator &other) const;
            AscendingIterator begin();
            AscendingIterator end();
        };

        class SideCrossIterator
        {
        private:
            MagicalContainer *container; // pointer to MagicalContainer
            bool isForward;              // true if forward, false if backward
            size_t low, high;            // low and high indexes

        public:
            SideCrossIterator(MagicalContainer &container);
            SideCrossIterator(SideCrossIterator &other);
            SideCrossIterator(SideCrossIterator &&other) = default; // Move constructor
            ~SideCrossIterator() = default;
            SideCrossIterator &operator=(const SideCrossIterator &other);
            SideCrossIterator &operator=(SideCrossIterator &&other) = default; // Move assignment operator
            SideCrossIterator &operator++();
            int operator*() const;
            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;
            bool operator>(const SideCrossIterator &other) const;
            SideCrossIterator begin();
            SideCrossIterator end();
        };

        class PrimeIterator
        {
        private:
            MagicalContainer *container; // pointer to MagicalContainer
            size_t currentIndex;         // current index

        public:
            PrimeIterator(MagicalContainer &container);
            PrimeIterator(PrimeIterator &other);
            PrimeIterator(PrimeIterator &&other) = default; // Move constructor
            ~PrimeIterator() = default;
            PrimeIterator &operator=(const PrimeIterator &other);
            PrimeIterator &operator=(PrimeIterator &&other) = default; // Move assignment operator
            PrimeIterator &operator++();
            int operator*() const;
            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;
            bool operator>(const PrimeIterator &other) const;
            PrimeIterator begin();
            PrimeIterator end();
            size_t findNextPrime(size_t index) const;
            bool static prime(int number);
        };
    };

}

#endif