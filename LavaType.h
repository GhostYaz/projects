#ifndef LAVATYPE_H
#define LAVATYPE_H

#include "FireType.h"  // LavaType is a specialized form of FireType Pokémon

// LavaType.h
// Defines the LavaType Pokémon class, which inherits from the FireType class

class LavaType : public FireType {
public:
    // Constructor to initialize LavaType Pokémon with a name
    LavaType(const std::string& name) : FireType(name) {}

    // LavaType's special ultimate attack message
    // Note: This does not override the FireType's ultimate because the function signature is different
    void ultimate() {
        std::cout << name << " summons a blazing Lava Eruption!\n";
    }
};

#endif
