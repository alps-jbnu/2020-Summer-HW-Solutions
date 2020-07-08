#include "train.h"

train_t* create_train_malloc(const char* const name, const train_size_t size, const train_color_t* color)
{
    train_t* train = (train_t*)malloc(sizeof(train_t));
    
    train->name = name;
    train->size = size;
    train->color = (train_color_t*)color;
    train->prev = NULL;
    train->next = NULL;

    return train;
}

train_t* get_train_head(const train_t* trains)
{
    assert(trains != NULL);

    while (trains->prev != NULL) {
        trains = trains->prev;
    }
    return (train_t*)trains;
}

train_t* get_train_tail(const train_t* trains)
{
    assert(trains != NULL);

    while (trains->next != NULL) {
        trains = trains->next;
    }
    return (train_t*)trains;
}

void merge_train(const train_t* left_trains, const train_t* right_trains)
{
    assert(left_trains != NULL);
    assert(right_trains != NULL);
    assert(left_trains != right_trains);

    interleave_train(get_train_tail(left_trains), right_trains);
}

void interleave_train(train_t* const target_train, const train_t* const new_trains)
{
    assert(target_train != NULL);
    assert(new_trains != NULL);
    assert(target_train != new_trains);

    train_t* const new_train_head = get_train_head(new_trains);
    train_t* const new_train_tail = get_train_tail(new_trains);

    if (target_train->next != NULL) {
        target_train->next->prev = new_train_tail;
        new_train_tail->next = target_train->next;
    }
    new_train_head->prev = target_train;
    target_train->next = new_train_head;
}

int pop_train(train_t* trains, train_t* const target_train)
{
    assert(trains != NULL);
    assert(target_train != NULL);

    trains = get_train_head(trains);
    
    while (trains->next != NULL) {
        if (trains != target_train) {
            trains = trains->next;
            continue;
        }

        if (trains->next != NULL) {
            if (trains->prev != NULL) {
                trains->next->prev = trains->prev;
                trains->prev->next = trains->next;
            }
            else {
                trains->next->prev = NULL;
            }
        }

        trains->prev = NULL;
        trains->next = NULL;

        return 1;
    }

    if (trains == target_train) {
        if (trains->prev != NULL) {
            trains->prev->next = NULL;
            trains->prev = NULL;
            trains->next = NULL;
        }
        return 1;
    }

    return 0;
}

void retrieve_train_to_box(train_t* const train)
{
    assert(train != NULL);

    pop_train(train, train);

    free(train->color);
    free(train);
}