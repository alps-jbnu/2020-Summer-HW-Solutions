#include "train_color.h"

train_color_t* create_rgb_color_malloc(const uint8_t red, const uint8_t green, const uint8_t blue)
{
    train_color_t* color = (train_color_t*)malloc(sizeof(train_color_t));

    color->red = red;
    color->green = green;
    color->blue = blue;

    return color;
}