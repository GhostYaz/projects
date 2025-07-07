#ifndef TYPE_EFFECTIVENESS_H
#define TYPE_EFFECTIVENESS_H

#include <string>
#include <map>

using namespace std;

// Class to manage type effectiveness multipliers between Pokémon types
class TypeEffectiveness {
private:
    // Nested map: attacker type -> (defender type -> damage multiplier)
    map<string, map<string, float>> multiplier;

public:
    // Constructor initializes the effectiveness multipliers
    TypeEffectiveness() {
        multiplier = {
            {"Fire",        {{"Water", 0.8}, {"Earth", 0.8}, {"Ice", 1.5}, {"Grass", 1.2}}}, // Fire attacks
            {"Water",       {{"Fire", 1.2}, {"Earth", 0.8}, {"Electric", 0.7}}},             // Water attacks
            {"Earth",       {{"Fire", 1.2}, {"Water", 1.2}, {"Electric", 1.2}}},             // Earth attacks
            {"Magic",       {{"Earth", 1.2}, {"Cyberpunk", 0.8}}},                          // Magic attacks
            {"Cyberpunk",   {{"Magic", 1.2}, {"Fire", 0.8}}},                              // Cyberpunk attacks
            {"Scorpion",    {{"Magic", 1.2}, {"Water", 0.8}}},                             // Scorpion attacks
            {"Shadow",      {{"Fire", 1.2}, {"Earth", 0.8}}},                              // Shadow attacks
            {"Air",         {{"Earth", 1.2}, {"Scorpion", 0.8}}},                          // Air attacks
            {"Ice",         {{"Air", 1.2}, {"Fire", 0.7}}},                               // Ice attacks
            {"Electric",    {{"Water", 1.2}, {"Earth", 0.7}}},                            // Electric attacks
            {"Tsunami",     {{"Fire", 1.5}, {"Lava", 1.3}, {"Electric", 0.7}, {"Earth", 1.2}}},  // Tsunami (water) attacks stronger against fire and lava
            {"Lava",        {{"Ice", 1.7}, {"Grass", 1.5}, {"Water", 0.7}, {"Tsunami", 0.7}}}     // Lava (fire) attacks stronger against ice and grass
        };
    }

    // Get the damage multiplier for attacker attacking defender type
    float getMultiplier(const string& attacker, const string& defender) {
        if (multiplier.count(attacker) && multiplier[attacker].count(defender)) {
            return multiplier[attacker][defender];
        }
        return 1.0f; // Neutral damage if no specific multiplier found
    }
};

#endif
