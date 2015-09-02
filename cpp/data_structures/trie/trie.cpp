#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

// Implementation of a Trie data structure.
//
// A trie is an ordered data structure that is used to store
// a dynamic set. The keys in a trie are usually strings.
// 
// Tries allow for O(length) queries for words, and are perfectly
// suited for dictionaries as they do not depend on the size of the
// word list.
//
// For more information: https://en.wikipedia.org/wiki/Trie
class Trie {
public:
    Trie(): 
        word_end(false)
    {};

    void insert(std::string word);
    int count(std::string word);

    template <class ForwardIterator>
    void insert(ForwardIterator begin, ForwardIterator end);
    template <class ForwardIterator>
    int count(ForwardIterator begin, ForwardIterator end);

    std::vector<std::string> words();

private:
    void traversal(std::string current, std::vector<std::string>& words);

    bool word_end;
    std::unordered_map<char, std::unique_ptr<Trie>> children; 
};

void Trie::traversal(std::string current, std::vector<std::string>& words) {
    if (word_end) {
        words.push_back(current);
    }

    for (auto& kv : children) {
        current.push_back(kv.first);
        kv.second->traversal(current, words);
        current.pop_back();
    }
}

// Insert a word into the Trie
//
// Args:
//      word: string to be inserted
void Trie::insert(std::string word) {
    insert(word.begin(), word.end());
}

// Count the number of appearances of the word.
// Will return 1 if the trie contains word and 0 otherwise.
//
// Args:
//      word: string to search for
int Trie::count(std::string word) {
    return count(word.begin(), word.end());
}

template <class ForwardIterator>
void Trie::insert(ForwardIterator begin, ForwardIterator end) {
    if (begin == end) {
        word_end = true;
        return;
    }

    if (children.find(*begin) == children.end()) {
        children[*begin] = std::unique_ptr<Trie>(new Trie());
    }
    children[*begin]->insert(std::next(begin), end);
}

template <class ForwardIterator>
int Trie::count(ForwardIterator begin, ForwardIterator end) {
    if (begin == end)
        return word_end;
    if (children.find(*begin) == children.end())
        return 0;

    return children[*begin]->count(std::next(begin), end);
}

// Return a vector of the words stored in the trie.
std::vector<std::string> Trie::words() {
    std::vector<std::string> result;
    traversal("", result);

    return result;
}

int main() 
{
    Trie t;
    t.insert("banana");
    t.insert("band");

    std::cout << t.count("ban") << std::endl;
    std::cout << t.count("band") << std::endl;

    std::vector<std::string> words = t.words();
    for (auto s : words)
        std::cout << s << std::endl;

    return 0;
}