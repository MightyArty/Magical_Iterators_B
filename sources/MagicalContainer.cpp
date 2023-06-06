#include "MagicalContainer.hpp"

using namespace std;
using namespace ariel;

/**
 * @brief Default constructor
 */
MagicalContainer::MagicalContainer() {}

/**
 * @brief Adds the given element to the container
 * @param element the element to add
 */
void MagicalContainer::addElement(int element)
{
    auto iter = lower_bound(this->elements.begin(), this->elements.end(), element);
    this->elements.insert(iter, element);
}

/**
 * @brief Removes the given element from the container
 * @param element the element to remove
 */
void MagicalContainer::removeElement(int element)
{
    auto iter = find(this->elements.begin(), this->elements.end(), element);
    if (iter != this->elements.end())
        this->elements.erase(iter);
    else
        throw runtime_error("The given element isn't located in the container!");
}

/**
 * @brief Returns the size of the container
 */
size_t MagicalContainer::size()
{
    return this->elements.size();
}

/**
 * @brief Returns the elements of the container
 */
vector<int> &MagicalContainer::getElements()
{
    return this->elements;
}

/**
 * @brief Sets the elements of the container
 * @param new_elements the new elements
 */
void MagicalContainer::setElements(vector<int> new_elements)
{
    this->elements = move(new_elements);
}

// ------------------- Ascending Iterator -------------------

/**
 * @brief Default constructor
 */
MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) : container(&container), currentIndex(0) {}

/**
 * @brief Copy constructor
 */
MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : container(other.container), currentIndex(other.currentIndex) {}

/**
 * @brief Copy assignment operator
 */
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
{
    if (this->container != other.container)
    {
        throw runtime_error("The given iterator is in another location in memory!");
    }

    if (this != &other)
    {
        this->container = other.container;
        this->currentIndex = other.currentIndex;
    }

    return *this;
}

/**
 * @brief Moving the iterator to the next element
 */
MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    if (this->currentIndex >= this->container->size())
    {
        throw runtime_error("Out of bounds");
    }
    ++currentIndex;
    return *this;
}

/**
 * @brief Returns the current element of the iterator
 */
int MagicalContainer::AscendingIterator::operator*() const
{
    return this->container->getElements()[currentIndex];
}

/**
 * @brief Returns true if the iterator is equal to the other iterator
 * @return true if the iterator is equal to the other iterator
 */
bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
{
    return (this->container == other.container) && (currentIndex == other.currentIndex);
}

/**
 * @brief Returns true if the iterator is not equal to the other iterator
 * @return true if the iterator is not equal to the other iterator
 */
bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
{
    return !(*this == other);
}

/**
 * @brief Returns true if the iterator is less than the other iterator
 * @return true if the iterator is less than the other iterator
 */
bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
{
    return currentIndex < other.currentIndex;
}

/**
 * @brief Returns true if the iterator is greater than the other iterator
 * @return true if the iterator is greater than the other iterator
 */
bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
{
    return currentIndex > other.currentIndex;
}

/**
 * @brief Returns the iterator to the beginning of the container
 */
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
{
    return AscendingIterator(*container);
}

/**
 * @brief Returns the iterator to the end of the container
 */
MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
{
    AscendingIterator iter(*container);
    iter.currentIndex = container->elements.size();
    return iter;
}

// ------------------- SideCross Iterator -------------------

/**
 * @brief Default constructor
 */
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container) : container(&container), isForward(true), low(0), high(container.size() - 1)
{
    if (container.size() == 0)
    {
        high = 0;
    }
}

/**
 * @brief Copy constructor
 */
MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator &other) : container(other.container), isForward(other.isForward), low(other.low), high(other.high) {}

/**
 * @brief Assignment operator
 */
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
{
    if (container != other.container)
    {
        throw runtime_error("The given iterator is in another location in memory!");
    }

    if (this != &other)
    {
        this->container = other.container;
        this->isForward = other.isForward;
        this->low = other.low;
        this->high = other.high;
    }

    return *this;
}

/**
 * @brief Returns the iterator to the beginning of the container
 */
MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    if (*this == end())
    {
        throw runtime_error("Out of bounds");
    }

    if (isForward)
    {
        low++;
        if (low > high)
        {
            low = 0;
            high = container->size();
        }
    }
    else
    {
        high--;
        if (high < low)
        {
            high = container->size();
            low = 0;
        }
    }
    isForward = !isForward;
    return *this;
}

/**
 * @brief Returns the current element in the iterator
 * @return The current element in the iterator
 */
int MagicalContainer::SideCrossIterator::operator*() const
{
    if (!isForward)
        return container->getElements()[high];
    return container->getElements()[low];
}

/**
 * @brief Checks if the current iterator is equal to the given iterator
 * @return True if the current iterator is equal to the given iterator, false otherwise
 */
bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
{
    if (container != other.container)
        throw runtime_error("Trying to compare between to different containers!");
    return (low == other.low) && (high == other.high);
}

/**
 * @brief Checks if the current iterator is different than the given iterator
 * @return True if the current iterator is different than the given iterator, false otherwise
 */
bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
{
    return !(*this == other);
}

/**
 * @brief Checks if the current iterator is smaller than the given iterator
 * @return True if the current iterator is smaller than the given iterator, false otherwise
 */
bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
{
    if (container != other.container)
        throw runtime_error("Trying to compare between to different containers!");
    return (high < other.high) || (low < other.low);
}

/**
 * @brief Checks if the current iterator is bigger than the given iterator
 * @return True if the current iterator is bigger than the given iterator, false otherwise
 */
bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
{
    if (container != other.container)
        throw runtime_error("Trying to compare between to different containers!");
    return (high > other.high) || (low > other.low);
}

/**
 * @brief Returns an iterator to the beginning of the container
 */
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    return SideCrossIterator(*container);
}

/**
 * @brief Returns an iterator to the end of the container
 */
MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    SideCrossIterator iter(*container);
    iter.low = 0;
    iter.high = container->size();
    iter.isForward = true;
    return iter;
}

// ------------------- Prime Iterator -------------------

/**
 * @brief Main constructor
 */
MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container) : container(&container), currentIndex(findNextPrime(0)) {}

/**
 * @brief Copy constructor
 */
MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator &other) : container(other.container), currentIndex(other.currentIndex) {}

/**
 * @brief Function to assign one iterator to another
 */
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    if (this->container != other.container)
    {
        throw runtime_error("The given iterator is in another location in memory!");
    }

    if (this != &other)
    {
        this->container = other.container;
        this->currentIndex = other.currentIndex;
    }

    return *this;
}

/**
 * @brief Function to get the next prime number in the container
 * @return The next prime number in the container
 */
MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    if (*this == end())
    {
        throw runtime_error("Out of bounds");
    }
    currentIndex = findNextPrime(currentIndex + 1);

    if (currentIndex >= container->size())
    {
        currentIndex = container->size();
    }
    return *this;
}

/**
 * @brief Function to get the current element of the iterator
 * @return The current element of the iterator
 */
int MagicalContainer::PrimeIterator::operator*() const
{
    return this->container->getElements()[currentIndex];
}

/**
 * @brief Function to check if the current iterator is equal to the given iterator
 * @return True if the current iterator is equal to the given iterator, false otherwise
 */
bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
{
    if (container != other.container)
        throw runtime_error("Trying to compare between to different containers!");
    return (currentIndex == other.currentIndex);
}

/**
 * @brief Function to check if the current iterator is not equal to the given iterator
 * @return True if the current iterator is not equal to the given iterator, false otherwise
 */
bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
{
    return !(*this == other);
}

/**
 * @brief Function to check if the current iterator is smaller than the given iterator
 * @return True if the current iterator is smaller than the given iterator, false otherwise
 */
bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
{
    if (container != other.container)
        throw runtime_error("Trying to compare between to different containers!");
    return currentIndex < other.currentIndex;
}

/**
 * @brief Function to check if the current iterator is bigger than the given iterator
 * @return True if the current iterator is bigger than the given iterator, false otherwise
 */
bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
{
    if (container != other.container)
        throw runtime_error("Trying to compare between to different containers!");
    return currentIndex > other.currentIndex;
}

/**
 * @brief Function to get the begining of the container
 * @return An iterator to the begining of the container
 */
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    return PrimeIterator(*container);
}

/**
 * @brief Function to get the end of the container
 * @return An iterator to the end of the container
 */
MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    PrimeIterator iter(*container);
    iter.currentIndex = container->size();
    return iter;
}

/**
 * @brief Helper function to check if a number is prime
 * @param number The number to check
 * @return True if the number is prime, false otherwise
 */
bool MagicalContainer::PrimeIterator::prime(int number)
{
    if (number < 2)
        return false;
    for (int i = 2; i <= sqrt(number); i++)
        if (number % i == 0)
            return false;
    return true;
}

/**
 * @brief Helper function fo find the next prime number in the container
 * @param index The index to start searching from
 * @return The index of the next prime number in the container
 */
size_t MagicalContainer::PrimeIterator::findNextPrime(size_t index) const
{
    for (size_t i = index; i < container->size(); i++)
    {
        if (prime(container->getElements()[i]))
        {
            return i;
        }
    }
    return container->size();
}