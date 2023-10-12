#ifndef INTERPRETOR_H
#define INTERPRETOR_H

typedef struct Action {
    char* short_name;
    char* name;
    void (*action)(void);
} Action;


/**
 * @brief 
 * 
 */
void interpretor(void);

#endif