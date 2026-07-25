#ifndef DAMAGE_TRACKER_HPP
#define DAMAGE_TRACKER_HPP

#include <string>
#include "DamageType.hpp"

class DamageTracker
{
    private:
        struct Hit
        {
            DamageType type;
            int damage;
            double time;
            bool critical;
            Hit* next;
            Hit(DamageType _type, int _damage, double _time, bool _critical) : 
                type(_type), damage(_damage), time(_time), critical(_critical) , next(nullptr) {}
        };
        
        struct HitQueue
        {
            Hit* head;
            Hit* tail;
            int size;
        };

        HitQueue queue;

        void initQueue();
        void enqueue(DamageType type, int damage, double time, bool critical);
        bool dequeue();
        void copyQueue(const DamageTracker& other);
        void clearQueue();

    public:    
        DamageTracker();
        DamageTracker(const DamageTracker& other);
        DamageTracker& operator=(const DamageTracker& other);
        ~DamageTracker();

        void addHit(DamageType type, int damage, double time, bool critical); //kritik vuruslarin gercek hasari damage * 2
        void removeHitsBefore(double time); //belirli sureden onceki vuruslar iptal
        
        int actualDamage(const Hit& d) const; //critical => damage * 2
        int totalDamage() const; //tum gercek hasarlarin toplamini dondursun
        double avgDamage() const; //gercek hasar ortalamasini dondursun
        int highestDamage() const; //en yuksek gercek hasari dondursun
        int comboDamage(double currentTime, double comboWindow) const;
        //currentTime - comboWindow <= hitTime <= currentTime
        int damageByType(DamageType type) const; //bir vurulma tipine ait total degeri dondurur
        double criticalRate() const;
        int highestCombo(double window) const;

        std::string damageTypeToString(DamageType t) const;

        void printAllHits() const;
        void printTotalDamage() const;
        void printAvgDamage() const;
        void printHighestDamage() const;
        void printComboDamage(double currentTime, double comboWindow) const;
        void printDamageByType(DamageType t) const;
};

#endif