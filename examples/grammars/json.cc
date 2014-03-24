#include "tree_sitter/compiler.h"

namespace tree_sitter {
    namespace examples {
        using namespace tree_sitter::rules;

        static rule_ptr comma_sep(const rule_ptr &rule) {
            return choice({
                seq({
                    rule,
                    repeat(seq({ _sym("comma"), rule })),
                }),
                blank(),
            });
        }

        Grammar json() {
            return Grammar({
                { "value", choice({
                    sym("object"),
                    sym("array"),
                    sym("string"),
                    sym("number"),
                    sym("true"),
                    sym("false"),
                    sym("null"), }) },
                { "object", seq({
                    _sym("left_brace"),
                    comma_sep(err(seq({
                        sym("string"),
                        _sym("colon"),
                        sym("value") }))),
                    _sym("right_brace"), }) },
                { "array", seq({
                    _sym("left_bracket"),
                    comma_sep(err(sym("value"))),
                    _sym("right_bracket"), }) },
                { "string", pattern("\"([^\"]|\\\\\")+\"") },
                { "number", pattern("\\d+(.\\d+)?") },
                { "comma", str(",") },
                { "colon", str(":") },
                { "left_bracket", str("[") },
                { "right_bracket", str("]") },
                { "left_brace", str("{") },
                { "right_brace", str("}") },
                { "null", str("null") },
                { "true", str("true") },
                { "false", str("false") },
            });
        }
    }
}
