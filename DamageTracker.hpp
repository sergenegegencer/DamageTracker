#ifndef DAMAGE_TRACKER_HPP
#define DAMAGE_TRACKER_HPP

class DamageTracker
{
    private:
        struct Hit
        {
            int damage;
            double time;
            Hit* next;
            Hit(int _damage, double _time) : damage(_damage), time(_time), next(nullptr) {}
        };
        
        struct HitQueue
        {
            Hit* head;
            Hit* tail;
            int size;
        };

        HitQueue queue;

        void initQueue();
        void enqueue(int damage, double time);
        bool dequeue();
        void copyQueue(const DamageTracker& other);
        void clearQueue();

    public:    
        DamageTracker();
        DamageTracker(const DamageTracker& other);
        DamageTracker& operator=(const DamageTracker& other);
        ~DamageTracker();

        void addHit(int damage, double time, bool critical); //kritik vuruslarin gercek hasari damage * 2
        int totalDamage() const; //tum gercek hasarlarin toplamini dondursun
        double avgDamage() const; //gercek hasar ortalamasini dondursun
        int highestDamage() const; //en yuksek gercek hasari dondursun
        int comboDamage(double currentTime, double comboWindow) const;
        //currentTime - comboWindow <= hitTime <= currentTime

        void printTotalDamage() const;
        void printAvgDamage() const;
        void printHighestDamage() const;
        void printComboDamage(double currentTime, double comboWindow) const;
};

#endif