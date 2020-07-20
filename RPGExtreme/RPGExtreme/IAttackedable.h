#pragma once

#include "Character.h"

namespace rpg_extreme
{
    class IAttackedable
    {
    public:
        virtual bool IsAttackedable() const = 0;
        virtual void OnAttack(GameObject* gameObject, const int16_t damage) = 0;
    };
}