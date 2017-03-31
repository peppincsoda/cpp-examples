
#include <memory>
#include <stdio.h>
#include "callable.h"

// This is the native function we would register into the VM.
static int test(int i, const char* s)
{
    printf("test(%d,%s)\n", i, s);
    return i;
}

int main()
{
    // This variable would be stored in the symbol table when the VM is initialized.
    std::unique_ptr<Callable> function(NewCallableFunction(test));

    RuntimeStack stack;
    function->Call(stack);  // The VM code would call this when encountering
                            // a CALL instruction in the bytecode.

    return 0;
}
