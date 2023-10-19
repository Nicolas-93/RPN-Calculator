#include "stack.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int Stack_init(ValueStack* new) {
    Vector_init(&new->vec, sizeof(Value), 100, NULL);

    return 0;
}

int Stack_push_value(ValueStack* self, Value value) {

    Vector_append(&self->vec, &value);

    return 0;
}

Value Stack_get_head_value(const ValueStack* self) {
    Value t = * (Value*) Vector_get(&self->vec, -1);
    return t;
}

Value Stack_pop_head_value(ValueStack* self) {
    Value t = * (Value*) Vector_pop(&self->vec);
    return t;
}

int Stack_swap_head_value(ValueStack* self) {
    assert(Vector_get_length(&self->vec) >= 2);

    Value* entry1 = Vector_get(&self->vec, -1);
    Value* entry2 = Vector_get(&self->vec, -2);

    Value tmp = *entry2;
    *entry2 = *entry1;
    *entry1 = tmp;

    return 0;
}

int Stack_free(ValueStack* self) {
    Vector_free(&self->vec);

    return 0;
}

void Stack_clear(ValueStack* self) {
    Vector_clear(&self->vec);
}

void Stack_print(const ValueStack* self) {

    // Comment déclarer un pointeur comme tableau avec la syntaxe des VLAs ?
    // De sorte que la tableau soit correctement typé et ainsi facilement itérable,
    // et possède sa taille réelle ? (sizeof(array))

    // Value* values = (Value*) self->vec.arr;

    VECTOR_DECLARE_ARRAY(self->vec, Value, values);

    for (int i = 0; i < Vector_get_length(&self->vec); ++i) {
        printf("%d ", values[i]);
    }

    putchar('\n');
}

size_t Stack_get_length(const ValueStack* self) {
    return Vector_get_length(&self->vec);
}
