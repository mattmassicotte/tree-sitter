This grammar resolves the conflict shown in the `precedence_on_single_child_missing` grammar by giving `function_call` a positive precedence. This causes shifting the `{` token as part of `function_call` to be preferred over reducing the `bar` variable to an expression.