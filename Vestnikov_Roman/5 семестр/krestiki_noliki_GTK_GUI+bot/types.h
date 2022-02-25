#ifndef GTK_TEST_TYPES_H
#define GTK_TEST_TYPES_H

typedef enum {
    NOTHING,
    CROSS_WIN,
    ZERO_WIN,
    DRAW,
} Victory_result;

typedef enum {
    CROSS,
    ZERO,
    EMPTY,
} Cell;

typedef enum {
    YES,
    NO,
} Trigger;

#endif //GTK_TEST_TYPES_H
