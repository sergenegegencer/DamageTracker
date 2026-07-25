#include "DamageTracker.hpp"
#include <iostream>

void DamageTracker::initQueue()
{
    queue.head = nullptr;
    queue.tail = nullptr;
    queue.size = 0;
}

void DamageTracker::enqueue(int damage, double time)
{
    Hit* newHit { new Hit(damage, time) };
    if(newHit == nullptr) return;

    if(queue.tail == nullptr)
    {
        queue.head = newHit;
        queue.tail = newHit;
    }

    else{
        queue.tail->next = newHit;
        queue.tail = newHit;
    }

    ++queue.size;
}

bool DamageTracker::dequeue()
{
    if(queue.head == nullptr) return false;

    Hit* temp { queue.head };
    queue.head = queue.head->next;
    delete temp;

    if(queue.head == nullptr) queue.tail = nullptr;

    --queue.size;
    return true;
}

void DamageTracker::copyQueue(const DamageTracker& other)
{
    for(Hit* curr { other.queue.head }; curr != nullptr; curr = curr->next)
    {
        enqueue(curr->damage, curr->time);
    }
}

void DamageTracker::clearQueue()
{
    while(dequeue()) {}
}

DamageTracker::DamageTracker()
{
    initQueue();
}

DamageTracker::DamageTracker(const DamageTracker& other)
{
    initQueue();
    copyQueue(other);
}

DamageTracker& DamageTracker::operator=(const DamageTracker& other)
{
    if(this != &other)
    {
        clearQueue();
        copyQueue(other);
    }

    return *this;
}

DamageTracker::~DamageTracker()
{
    clearQueue();
}

void DamageTracker::addHit(int damage, double time, bool critical)
{
    Hit* newHit { new Hit(critical ? damage * 2 : damage, time) };
    if(newHit == nullptr) return;

    if(queue.head == nullptr) queue.head = newHit;
    else queue.tail->next = newHit;

    queue.tail = newHit;
    queue.size++;
}

int DamageTracker::totalDamage() const
{
    if(queue.head == nullptr) return 0;

    Hit* temp { queue.head };
    int damage { };

    while(temp != nullptr)
    {
        damage += temp->damage;
        temp = temp->next;
    }

    return damage;
}

double DamageTracker::avgDamage() const
{
    return static_cast<double>(totalDamage()) / static_cast<double>(queue.size);
}

int DamageTracker::highestDamage() const
{
    if(queue.head == nullptr) return 0;

    Hit* temp { queue.head->next };
    int max { queue.head->damage };

    while(temp != nullptr)
    {
        if(max < temp->damage) max = temp->damage;
        temp = temp->next;
    }

    return max;
}

int DamageTracker::comboDamage(double currentTime, double comboWindow) const
{
    int combo {};

    Hit* curr { queue.head };

    while(curr != nullptr)
    {
        if(curr->time >= currentTime - comboWindow && curr->time <= 10.0) combo += curr->damage;
        curr = curr->next;
    }

    return combo;
}

void DamageTracker::printTotalDamage() const
{
    std::cout << "Total Damage: " << totalDamage() << '\n';
}

void DamageTracker::printAvgDamage() const
{
    std::cout << "Average Damage: " << avgDamage() << '\n';
}

void DamageTracker::printHighestDamage() const
{
    std::cout << "Highest Damage: " << highestDamage() << '\n';
}

void DamageTracker::printComboDamage(double currentTime, double comboWindow) const
{
    std::cout << "Combo Damage: " << comboDamage(currentTime, comboWindow) << '\n';
}