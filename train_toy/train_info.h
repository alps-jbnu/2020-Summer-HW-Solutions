#pragma once

#include "train_size.h"
#include "train_color.h"

typedef struct train_info {
    char* const name;
    train_size_t size;
    train_color_t color;
};