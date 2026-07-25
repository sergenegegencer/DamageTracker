#include "DamageTracker.hpp"
#include <iostream>

void DamageTracker::initQueue()
{
    queue.head = nullptr;
    queue.tail = nullptr;
    queue.size = 0;
}

void DamageTracker::enqueue(DamageType type, int damage, double time, bool critical)
{
    Hit* newHit { new Hit(type, damage, time, critical) };
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
        enqueue(curr->type, curr->damage, curr->time, curr->critical);
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

void DamageTracker::addHit(DamageType type, int damage, double time, bool critical)
{
    Hit* newHit { new Hit(type, damage, time, critical) };
    if(newHit == nullptr) return;

    if(queue.head == nullptr) queue.head = newHit;
    else queue.tail->next = newHit;

    queue.tail = newHit;
    queue.size++;
}

void DamageTracker::removeHitsBefore(double time)
{
    if(queue.head == nullptr) return;

    Hit* curr { queue.head };

    while(curr != nullptr && curr->next != nullptr)
    {
        if(curr->time < time) //head durumu icin
        {
            dequeue();
        }

        else if(curr->next->time < time)
        {
            Hit* willBeDeleted { curr->next };
            curr->next = willBeDeleted->next;
            delete willBeDeleted;
            --queue.size;
        }

        curr = curr->next;

    }
}

int DamageTracker::actualDamage(const Hit& h) const
{
    return h.critical ? h.damage * 2 : h.damage; 
}

int DamageTracker::totalDamage() const
{
    if(queue.head == nullptr) return 0;

    Hit* curr { queue.head };
    int damage { };

    while(curr != nullptr)
    {
        damage += actualDamage(*curr);
        curr = curr->next;
    }

    return damage;
}

double DamageTracker::avgDamage() const
{
    if(queue.size == 0) return 0.0;

    return static_cast<double>(totalDamage()) / queue.size;
}

int DamageTracker::highestDamage() const
{
    if(queue.head == nullptr) return 0;

    Hit* curr { queue.head->next };
    int max { queue.head->damage };

    while(curr != nullptr)
    {
        int damage { actualDamage(*curr) };
        if(max < damage) max = damage;
        curr = curr->next;
    }

    return max;
}

int DamageTracker::comboDamage(double currentTime, double comboWindow) const
{
    int combo {};

    Hit* curr { queue.head };

    while(curr != nullptr)
    {
        if(curr->time >= currentTime - comboWindow && curr->time <= 10.0) combo += actualDamage(*curr);
        curr = curr->next;
    }

    return combo;
}

int DamageTracker::damageByType(DamageType type) const
{
    Hit* curr { queue.head };
    int total {};

    while(curr != nullptr)
    {
        if(curr->type == type) total += actualDamage(*curr);
        curr = curr->next;
    }

    return total;
}

double DamageTracker::criticalRate() const
{
    Hit* curr { queue.head };

    double criticalCount {};

    while(curr != nullptr)
    {
        if(curr->critical) ++criticalCount;
        curr = curr->next;
    }

    return criticalCount / static_cast<double>(queue.size);
}

/*
int DamageTracker::highestCombo(double window) const
{

}
*/

std::string DamageTracker::damageTypeToString(DamageType t) const
{
    switch(t)
    {
        case DamageType::PHYSICAL: return "Physical";
        case DamageType::FIRE: return "Fire";
        case DamageType::ICE: return "Ice";
        case DamageType::POISON: return "Poison";
    }
    
    return "";
}

void DamageTracker::printAllHits() const
{
    Hit* curr { queue.head };

    int i {};

    while(curr != nullptr)
    {
        std::cout << "HIT " << ++i << '\n'; 
        std::cout << "Damage Type: " << damageTypeToString(curr->type) << '\n';
        std::cout << "Pure Damage: " << curr->damage << '\n';
        std::cout << "Time: " << curr->time << '\n';
        std::cout << "Is Critical: " << (curr->critical ? "Yes" : "No") << '\n';
        std::cout << "Actual Damage: " << actualDamage(*curr) << "\n\n";
        
        curr = curr->next;
    }
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

void DamageTracker::printDamageByType(DamageType t) const
{
    std::cout << damageTypeToString(t) << " Damage Type: " << damageByType(t) << '\n';
}