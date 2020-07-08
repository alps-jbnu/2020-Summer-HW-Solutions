/*

#include <assert.h>
#include <stdio.h>

#include "train.h"
#include "train_size.h"

void print_train_information(const train_t* const train);

int main()
{
    train_t* train_jubin = create_train_malloc("jubin", SMALL, create_rgb_color_malloc(255, 0, 0));
    train_t* train_kiwan = create_train_malloc("kiwan", SMALL, create_rgb_color_malloc(0, 255, 0));
    train_t* train_jongbum = create_train_malloc("jongbum", MEDIUM, create_rgb_color_malloc(255, 128, 128));
    train_t* train_younghoon = create_train_malloc("younghoon", MEDIUM, create_rgb_color_malloc(0, 0, 0));
    train_t* train_seungwoo = create_train_malloc("seungwoo", LARGE, create_rgb_color_malloc(255, 255, 255));

    print_train_information(train_jubin);
    print_train_information(train_kiwan);
    print_train_information(train_jongbum);
    print_train_information(train_younghoon);
    print_train_information(train_seungwoo);

    retrieve_train_to_box(train_jubin);
    retrieve_train_to_box(train_kiwan);
    retrieve_train_to_box(train_jongbum);
    retrieve_train_to_box(train_younghoon);
    retrieve_train_to_box(train_seungwoo);

    return 0;
}

void print_train_information(const train_t* const train)
{
    const char* SIZE_NAME[] = { "Small", "Medium", "Large" };
    printf("name: %s\tsize = %s\tRGB Color=(%hhu, %hhu, %hhu)", train->name, SIZE_NAME[train->size], train->color->red, train->color->green, train->color->blue);
    putchar('\n');
}

*/