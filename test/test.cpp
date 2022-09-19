#define CATCH_CONFIG_MAIN
#include <fstream>
#include "catch.hpp"
#include "../src/gui.cpp"
#include "../src/trie.cpp"

TEST_CASE("GUI TEST 1", "[gui]") 
{
    REQUIRE(0 == 1); // REQUIRE( TEST == CASE)
}

TEST_CASE("Insertion Test", "[trie][insert]") 
{
    Trie dict;
    std::string test = "word";

    dict.insert(test);

    REQUIRE(dict.search(test)); // REQUIRE( TEST == CASE)
}

TEST_CASE("Search Test", "[trie][search]") 
{
    Trie dict;
    std::string test[10] = {"gator", "Civium",  "in",  "moribus", "rei", "publicae", "salus" };

    for(auto iter : test)
        dict.insert(iter);

    mt19937 mt(time(0));
    uniform_int_distribution<int> dist(0, 9); // total words in txt file
    int index = dist(mt);

    // REQUIRE(dict.search("test")); // REQUIRE( TEST == CASE)
    REQUIRE(dict.search(test[index])); // REQUIRE( TEST == CASE)
}

TEST_CASE("Random Search Test", "[trie][search]") 
{
    Trie dict;
    std::string word = "";
    std::ifstream file("../dataset/words.txt");

    /// Insert All Words ///
    while (file>>word) {
        dict.insert(word);
    }
    file.close();

    /// Select Random Word ///
    file.open("../dataset/words.txt");

    // Generates random number, goes to that line in the file
    mt19937 mt(time(0));
    uniform_int_distribution<int> dist(1, 370105); // total words in txt file
    int wordNumber = dist(mt);

    for (int i = 0; i < wordNumber; ++i) {
        file >> word;
    }

    file.close();

    // REQUIRE(dict.search("tezt")); // REQUIRE( TEST == CASE)
    REQUIRE(dict.search(word)); // REQUIRE( TEST == CASE)
} // Refactored test code from Woosungj

// TODO: Figure a way to check if the trie is empty
TEST_CASE("Deletion Test", "[trie][delete]") 
{
    Trie dict;
    std::string words[10] = {"gator", "Civium",  "in",  "moribus", "rei", "publicae", "salus" };

    for(auto iter : words)
        dict.insert(iter);

    dict.~Trie();

    // Generates random number, goes to that line in the file
    mt19937 mt(time(0));
    uniform_int_distribution<int> dist(0, 9); // total words in txt file
    int index = dist(mt);

    REQUIRE(dict.search(words[index])); // REQUIRE( TEST == CASE)
}

TEST_CASE("MAP TEST 1", "[map]") 
{
    REQUIRE(0 == 1); // REQUIRE( TEST == CASE)
}

TEST_CASE("Word Size Test", "[input]") 
{
    Trie dict;
    std::string word = "";
    std::ifstream file("../dataset/words.txt");

    /// Insert All Words ///
    while (file>>word) {
        dict.insert(word);
    }
    file.close();

    /// Select Random Word ///
    file.open("../dataset/words.txt");

    // Generates random number, goes to that line in the file
    mt19937 mt(time(0));
    uniform_int_distribution<int> dist(1, 370105); // total words in txt file
    int wordNumber = dist(mt);

    for (int i = 0; i < wordNumber; ++i) {
        file >> word;
    }

    int length = 5;

    //If word at that line is not the length user specified, go to next word in list until correct length found
    //Similar to "open addressing", except we are pulling words, not hashing
    while (word.size() != length) {
        if (!(file>>word)) {
            file.clear();
            file.seekg(0);
        }
    }

    file.close();

    // REQUIRE(word.size() == 3); // REQUIRE( TEST == CASE)
    REQUIRE(word.size() == length); // REQUIRE( TEST == CASE)
} // Refactored test code from Woosungj