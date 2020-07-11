#pragma once

#include <string>

#include "Character.h"

namespace rpg_extreme
{
    class Monster : public Character
    {
    public:
        Monster(const int8_t x, const int8_t y, const std::string& name, const int32_t attack, const int32_t defense, const int32_t hp, const int32_t exp);
        
        virtual char GetSymbol() const override;
        const std::string& GetName() const;

    protected:
        std::string mName;
    };
}