// Keanu Aloua
// CS 302 - Use of Hashmaps
// March 24, 2022

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <cctype>
#include <vector>
#include <string>
#include <sstream>

std::string lowerCase(std::string);

int main() 
{
    std::string filename;
    std::fstream infile;
    int testCases, catAmount;

    // Key: Word            / Value: Category Name
    std::unordered_map<std::string, std::string> categories;

    // Key: Category Name   / Value: Valid words needed
    std::unordered_map<std::string, int> wordsValidMap;

    // Key: Category name   / Value: Word Count
    std::unordered_map<std::string, int> catCounters;

    // Key: Word            / Value: Bool for duplicates
    std::unordered_map<std::string, bool> found;

    // ------------------------------- //
    // ---- READING IN CATEGORIES ---- //
    // ------------------------------- //

    std::cout << "Enter filename: ";
    std::cin >> filename;

    // Open file for reading
    infile.open(filename);

    infile >> testCases; // Amount of test cases

    // Loops the amount of test cases
    for (int t = 0; t < testCases; t++) {
        std::vector<std::string> topics; // Vector for having cat names

        infile >> catAmount; // Amount of categories
        std::cout << "Test case " << t + 1 << std::endl;

        // Loops the amount of categories
        for (int i = 0; i < catAmount; i++) {
            std::string catName;
            int wordsTotal, wordsValid;

            infile >> catName >> wordsTotal >> wordsValid;

            // Making a vector of category names
            topics.push_back(catName);

            // Adds counter to counter hashmap
            catCounters[catName] = 0;

            // Adds words valid to hashmap
            wordsValidMap[catName] = wordsValid;

            // Loops the amount of words
            for (int j = 0; j < wordsTotal; j++) {
                std::string word;

                infile >> word;

                word = lowerCase(word); // Puts string into lowercase

                // Adds word to the category hashmap
                categories[word] = catName;

                // Sets words found to false
                found[word] = false;
            }
        }

        infile.ignore(); // Get rid of new line

        // ------------------------------- //
        // ----------- READ TEXT --------- //
        // ------------------------------- //
        std::string text;

        // Gets line until reaches an empty line
        do {
            std::string extracted;

            getline(infile, text);

            std::stringstream ss(text); // Stringstream to parse string into substrings

            while (ss >> extracted) {
                extracted = lowerCase(extracted); // Puts string into lowercase

                if (categories.count(extracted) > 0 && !found[extracted]) {
                    // Increments counter
                    catCounters[categories[extracted]]++;
                    found[extracted] = true; // Sets word found to true
                }
            }
        } while (!text.empty());

        // ------------------------------- //
        // ------ COMPARING COUNTS ------- //
        // ------------------------------- //
        bool sqfProblem = true;

        for (int i = 0; i < topics.size(); i++) {
            if (catCounters[topics[i]] == wordsValidMap[topics[i]]) {
                std::cout << topics[i] << std::endl;
                sqfProblem = false;
            }
        }

        if (sqfProblem) {
            std::cout << "SQF Problem" << std::endl;
        }
    }

    infile.close();

    return 0;
}

std::string lowerCase(std::string word) {
    // This function makes a string into all lower case

    std::string lowered = word;

    for (int i = 0; i < word.length(); i++) {
        lowered[i] = tolower(word[i]);
    }

    return lowered;
}