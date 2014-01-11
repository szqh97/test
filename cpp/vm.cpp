#include <iostream>
using namespace std;

typedef enum {
    OBJ_INT, 
    OBJ_PAIR,
} ObjectType;

typedef struct sObject
{
    ObjectType type;

    union
    {
        // OBJ_INT
        int value;

        // OBJ_PAIR
        struct 
        {
            struct sObject* head;
            struct sObject* tail;
        };
    };

} Object;

#define STACK_MAX 256
typedef struct
{
    Object* stack[STACK_MAX];
    int stackSize;
}VM;

VM* newVM()
{
    VM* vm = malloc(sizeof(VM));
    vm->stackSize = 0;
    return vm;
}

void push(VM* vm, Object* value)
{
    assert(vm->stackSize < stackSize, "Stack overflow");
    vm->stack[vm->stackSize++] = value;
}

Object* pop(VM* vm)
{
    assert(vm->stackSize > 0, "Stack underflow!");
    return vm->stack[--vm->stackSize];
}

Object* newObject(VM* vm, ObjectType type)
{
    Object* object = malloc(sizeof(Object));
    object->type = type;
    return object;
}

void pushInt(VM* vm, int intValue)
{
    Object* object = newObject(vm, OBJ_INT);
    object->value = intValue;
    push(vm, object);
}

Objcet* pushPair(VM* vm)
{
    Object* object = newObject(vm, OBJ_PAIR);
    object->tail = pop(vm);
    object->head = pop(vm);

    push(vm, object);
    return object;
}

typedef struct sObjcet 
{
    unsigned char marked;
} Object;

void mark(Object* object);
void markAll(VM* vm)
{
    for (int i = 0; i < vm->stackSize; ++i)
    {
        mark(vm->stack[i]);
    }
}

void mark(Object* object)
{
    /* If already marked, we're done. Check this first
     * to avoid recursing on cycles in the object graph
     */
    if (object->marked) return;

    object->marked = 1;
    if (object->type == OBJ_PAIR)
    {
        mark(object->head);
        mark(object->tail);
    }
}
