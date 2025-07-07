#ifndef TSUNAMIWATERTYPE_H
#define TSUNAMIWATERTYPE_H

#include "WaterType.h"

// TsunamiWaterType class inherits from WaterType and adds a special ultimate move
class TsunamiWaterType : public WaterType {
public:
    // Constructor: forwards name to base WaterType constructor
    TsunamiWaterType(const std::string& name) : WaterType(name) {}

    // Special ultimate move unique to TsunamiWaterType
    void ultimate()  {
        std::cout << name << " unleashes a massive Tsunami wave!\n";
    }
};

#endif
