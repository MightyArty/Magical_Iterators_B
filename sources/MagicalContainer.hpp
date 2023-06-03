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
        vector<int> elements;

    public:
        /**
         * @brief Default constructor
         */
        MagicalContainer();

        /**
         * @brief Adding element to the container
         * @param element the mistic element to add
         */
        void addElement(int element);

        /**
         * @brief Removing element from the container
         * @param element the mistic element to remove
         */
        void removeElement(int element);

        /**
         * @brief Returning the size of the container
         * @return the size of the container
         */
        int size();

        /**
         * @return The elements of the container
         */
        vector<int> &getElements();

        /**
         * @brief Setting new elements of the container
         * @param new_elements the new elements to set in the container
         */
        void setElements(vector<int> new_elements);

        class AscendingIterator
        {
        private:
            MagicalContainer *container;
            size_t currentIndex;

        public:
            /**
             * @brief Default constructor
             */
            AscendingIterator(MagicalContainer &container);

            /**
             * @brief Copy constructor
             */
            AscendingIterator(const AscendingIterator &other);

            /**
             * @brief Destructor
             */
            ~AscendingIterator() = default;

            /**
             * @brief Assignment operator
             */
            AscendingIterator &operator=(const AscendingIterator &other);

            /**
             * @brief Pre-increment operator
             */
            AscendingIterator &operator++();

            /**
             * @brief Dereference operator
             */
            int operator*() const;

            /**
             * @brief Equality comparison operator
             */
            bool operator==(const AscendingIterator &other) const;

            /**
             * @brief Inequality comparison operator
             */
            bool operator!=(const AscendingIterator &other) const;

            /**
             * @brief Small comparison operator
             */
            bool operator<(const AscendingIterator &other) const;

            /**
             * @brief Great comparison operator
             */
            bool operator>(const AscendingIterator &other) const;

            /**
             * @brief Returns the appropriate iterator pointing
             * to the first element of the container
             * based on the specified type
             */
            AscendingIterator begin();

            /**
             * @brief Returns the appropriate iterator pointing
             * to the one position past the last element
             * of the container based on the specified type
             */
            AscendingIterator end();
        };

        class SideCrossIterator
        {
        private:
            MagicalContainer *container;
            size_t currentIndex;
            bool isForward;

        public:
            /**
             * @brief Default constructor
             */
            SideCrossIterator(MagicalContainer &container);

            /**
             * @brief Copy constructor
             */
            SideCrossIterator(SideCrossIterator &other);

            /**
             * @brief Destructor
             */
            ~SideCrossIterator() = default;

            /**
             * @brief Assignment operator
             */
            SideCrossIterator &operator=(const SideCrossIterator &other);

            /**
             * @brief Pre-increment operator
             */
            SideCrossIterator &operator++();

            /**
             * @brief Dereference operator
             */
            int operator*() const;

            /**
             * @brief Equality comparison operator
             */
            bool operator==(const SideCrossIterator &other) const;

            /**
             * @brief Inequality comparison operator
             */
            bool operator!=(const SideCrossIterator &other) const;

            /**
             * @brief Small comparison operator
             */
            bool operator<(const SideCrossIterator &other) const;

            /**
             * @brief Great comparison operator
             */
            bool operator>(const SideCrossIterator &other) const;

            /**
             * @brief Returns the appropriate iterator pointing
             * to the first element of the container
             * based on the specified type
             */
            SideCrossIterator begin();

            /**
             * @brief Returns the appropriate iterator pointing
             * to the one position past the last element
             * of the container based on the specified type
             */
            SideCrossIterator end();
        };

        class PrimeIterator
        {
        private:
            MagicalContainer *container;
            size_t currentIndex;

        public:
            /**
             * @brief Default constructor
             */
            PrimeIterator(MagicalContainer &container);

            /**
             * @brief Copy constructor
             */
            PrimeIterator(PrimeIterator &other);

            /**
             * @brief Destructor
             */
            ~PrimeIterator() = default;

            /**
             * @brief Assignment operator
             */
            PrimeIterator &operator=(const PrimeIterator &other);

            /**
             * @brief Pre-increment operator
             */
            PrimeIterator &operator++();

            /**
             * @brief Dereference operator
             */
            int operator*() const;

            /**
             * @brief Equality comparison operator
             */
            bool operator==(const PrimeIterator &other) const;

            /**
             * @brief Inequality comparison operator
             */
            bool operator!=(const PrimeIterator &other) const;

            /**
             * @brief Small comparison operator
             */
            bool operator<(const PrimeIterator &other) const;

            /**
             * @brief Great comparison operator
             */
            bool operator>(const PrimeIterator &other) const;

            /**
             * @brief Returns the appropriate iterator pointing
             * to the first element of the container
             * based on the specified type
             */
            PrimeIterator begin();

            /**
             * @brief Returns the appropriate iterator pointing
             * to the one position past the last element
             * of the container based on the specified type
             */
            PrimeIterator end();

            /**
             * @brief Function to check if the number is prime
             * @return true if the given number is prime, otherwise false
             * @param number the given number to check
             */
            bool static prime(int number);
        };
    };

}

#endif