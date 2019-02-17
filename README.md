# SExpr

A fast single-header library for parsing s-expressions. Performs no allocations and has no dependencies other than the C standard library.

## Usage

Simply include `sexpr.h` as many times
as you want, but make sure you `#define SEXPR_IMPLEMENTATION` in exactly one
source file.

Here's how one would use the API:

```c
const char* s = "(equal? 5 6)";

// By passing in NULL for the 'pool' parameter, we're asking the function to
// count how many SExpr's we will need to allocate to parse the given string.
SExprResult result = ParseSExpr(s, strlen(s), NULL);

if(result.type == SE_SYNTAX_ERROR) {
    fprintf(stderr, "Error(%d): %s.\n", result.syntaxError.lineNumber, result.syntaxError.message);
    // ... 
} else {
    // result.count stores how many expressions are needed
    SExpr* data = malloc(sizeof(SExpr) * result.count);

    // This time we supply the pool
    SExprPool pool = { result.count, data }; 

    result = ParseSExpr(s, strlen(s), &pool);

    // result.expr contains the successfully parsed SExpr
}
```

You might be wondering how it stores the `equal?` in the identifier above. Instead of storing a copy, it uses this structure:

```c
typedef struct SExprString {
    int start, len;
} SExprString;
```

`start` is an index into the source string. As such, the source string must remain valid if you want to examine the contents of identifiers and strings.
There is a small helper function for comparing `SExprString` with other strings:

```c
// Returns true if a == b (reading a from source)
bool SExprStringEqual(const char* source, const SExprString* a, const char* b);
```

