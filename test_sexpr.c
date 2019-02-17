#include <assert.h>
#include <stdlib.h>

#define SEXPR_IMPLEMENTATION
#include "sexpr.h"

int main(int argc, char** argv)
{
    char s[] = "(10 -20.05 \"hello\" What )";

    SExprResult result = ParseSExpr(s, sizeof(s), NULL);

    assert(result.type == SE_COUNT);

    SExpr* data = malloc(sizeof(SExpr) * result.count);

    SExprPool pool = { result.count, data };

    result = ParseSExpr(s, sizeof(s), pool);

    assert(result.type == SE_SUCCESS);

    return 0;
}
