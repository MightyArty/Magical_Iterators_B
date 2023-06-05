#include "MagicalContainer.hpp"

using namespace std;
using namespace ariel;

MagicalContainer::MagicalContainer() {}

void MagicalContainer::addElement(int element)
{
    auto iter = lower_bound(this->elements.begin(), this->elements.end(), element);
    this->elements.insert(iter, element);
}

void MagicalContainer::removeElement(int element)
{
    auto iter = find(this->elements.begin(), this->elements.end(), element);
    if (iter != this->elements.end())
        this->elements.erase(iter);
    else
        throw runtime_error("The given element isn't located in the container!");
}

size_t MagicalContainer::size()
{
    return this->elements.size();
}

vector<int> &MagicalContainer::getElements()
{
    return this->elements;
}

void MagicalContainer::setElements(vector<int> new_elements)
{
    this->elements = move(new_elements);
}

// ------------------- Ascending Iterator -------------------

MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) : container(&container), currentIndex(0) {}

MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) : container(other.container), currentIndex(other.currentIndex) {}

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

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    if (this->currentIndex >= this->container->size())
    {
        throw runtime_error("Out of bounds");
    }
    ++currentIndex;
    return *this;
}

int MagicalContainer::AscendingIterator::operator*() const
{
    return this->container->getElements()[currentIndex];
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
{
    return (this->container == other.container) && (currentIndex == other.currentIndex);
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
{
    return !(*this == other);
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
{
    return currentIndex < other.currentIndex;
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
{
    return currentIndex > other.currentIndex;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
{
    return AscendingIterator(*container);
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
{
    AscendingIterator iter(*container);
    // point to the end of the container
    iter.currentIndex = container->elements.size();
    return iter;
}

// ------------------- SideCross Iterator -------------------

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container) : container(&container), currentIndex(0), isForward(true) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator &other) : container(other.container), currentIndex(other.currentIndex), isForward(other.isForward) {}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
{
    if (this != &other)
    {
        this->container = other.container;
        this->currentIndex = other.currentIndex;
        this->isForward = other.isForward;
    }

    return *this;
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    currentIndex++;
    return *this;
}

int MagicalContainer::SideCrossIterator::operator*() const
{
    return container->getElements()[currentIndex];
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
{
    return (this->container == other.container) && (currentIndex == other.currentIndex);
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
{
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
{
    return currentIndex < other.currentIndex;
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
{
    return currentIndex > other.currentIndex;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    SideCrossIterator iter(*container);
    iter.isForward = true;
    return iter;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    SideCrossIterator iter(*container);
    iter.isForward = true;
    iter.currentIndex = container->size();
    return iter;
}

// ------------------- Prime Iterator -------------------

MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container) : container(&container), currentIndex(0) {}

MagicalContainer::PrimeIterator::PrimeIterator(PrimeIterator &other) : container(other.container), currentIndex(other.currentIndex) {}

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

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    currentIndex++;
    while (currentIndex < container->size() && !prime(container->getElements()[currentIndex]))
    {
        currentIndex++;
    }
    return *this;
}

int MagicalContainer::PrimeIterator::operator*() const
{
    return this->container->getElements()[currentIndex];
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
{
    return (this->container == other.container) && (currentIndex == other.currentIndex);
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
{
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
{
    return currentIndex < other.currentIndex;
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
{
    return currentIndex > other.currentIndex;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    PrimeIterator iter(*container);
    iter.currentIndex = 0;
    if (!prime(container->getElements()[iter.currentIndex]))
    {
        ++iter;
    }
    return iter;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    PrimeIterator iter(*container);
    iter.currentIndex = container->elements.size();
    return iter;
}

bool MagicalContainer::PrimeIterator::prime(int number)
{
    if (number < 2)
        return false;
    for (int i = 2; i <= sqrt(number); i++)
        if (number % i == 0)
            return false;
    return true;
}