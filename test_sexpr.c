#include <math.h>
#include <assert.h>
#include <stdlib.h>

#define SEXPR_IMPLEMENTATION
#include "sexpr.h"

int main(int argc, char** argv)
{
    char s[] = "(10 -20.05 \"hello\" What (ok-alright 1 2 3 ()))";

    SExprResult result = ParseSExpr(s, sizeof(s), NULL);

    assert(result.type == SE_COUNT);

    SExpr* data = malloc(sizeof(SExpr) * result.count);

    SExprPool pool = { result.count, data };

    result = ParseSExpr(s, sizeof(s), &pool);

    assert(result.type == SE_SUCCESS);

    assert(result.expr->type == SE_LIST);

    assert(result.expr->head->type == SE_INT);
    assert(result.expr->head->i == 10);

    assert(result.expr->head->next->type == SE_FLOAT);
    assert(fabsf(result.expr->head->next->f - -20.05f) < 0.001f);
    
    assert(result.expr->head->next->next->type == SE_STRING);
    assert(SExprStringEqual(s, &result.expr->head->next->next->s, "hello"));

    assert(result.expr->head->next->next->next->type == SE_ID);
    assert(SExprStringEqual(s, &result.expr->head->next->next->next->s, "What"));

    assert(result.expr->head->next->next->next->next->type == SE_LIST); 

    assert(result.expr->head->next->next->next->next->head->type == SE_ID);
    assert(SExprStringEqual(s, &result.expr->head->next->next->next->next->head->s, "ok-alright"));

    assert(result.expr->head->next->next->next->next->head->next->type == SE_INT);
    assert(result.expr->head->next->next->next->next->head->next->i == 1);

    assert(result.expr->head->next->next->next->next->head->next->next->type == SE_INT);
    assert(result.expr->head->next->next->next->next->head->next->next->i == 2);

    assert(result.expr->head->next->next->next->next->head->next->next->next->type == SE_INT);
    assert(result.expr->head->next->next->next->next->head->next->next->next->i == 3);

    assert(result.expr->head->next->next->next->next->head->next->next->next->next->type == SE_NIL);

    return 0;
}
