#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(const std::string& source) {
    // All token limits found using find_all
    auto space_iters = find_all(source.begin(), source.end(), ::isspace);

    // tokens are generated between consecutive iterators
    Corpus tokens;
    std::transform(
        space_iters.begin(), std::prev(space_iters.end()), 
        std::next(space_iters.begin()),                    
        std::inserter(tokens, tokens.end()),               
        [&source](auto start, auto end) {                  
            return Token(source, start, end);
        }
    );

    // Eliminate all the empty tokens
    std::erase_if(tokens, [](const Token& t) {
        return t.content.empty();
    });

    return tokens;
}

std::set<Mispelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
    namespace rv = std::ranges::views;

    // Pipeline of ranges
    auto results = source
        // Filtering words not present in the dictionary
        | rv::filter([&dictionary](const Token& t) {
            return !dictionary.contains(t.content);
        })
    
        
        | rv::transform([&dictionary](const Token& token) {
            auto suggestions = dictionary
                | rv::filter([&token](const std::string& word) {
                    return levenshtein(token.content, word) == 1;
                })
                | rv::common; // Convert to common range to build the set

            return Mispelling{
                token,
                std::set<std::string>(suggestions.begin(), suggestions.end())
            };
        })
        // Filtrate words without suggestions
        | rv::filter([](const Mispelling& m) {
            return !m.suggestions.empty();
        });

    return std::set<Mispelling>(results.begin(), results.end());
}

/* Helper methods */
#include "utils.cpp"