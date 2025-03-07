#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Ismael Paredes"; // Changed name

// Function to get applicants from the file
std::set<std::string> get_applicants(std::string filename) {
    std::set<std::string> applicants; // Using an ordered set
    std::ifstream file(filename);    // Opening the file

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return applicants; // Return an empty set if there's an error
    }

    std::string name;
    while (std::getline(file, name)) { // Reading each line from the file
        applicants.insert(name);       // Inserting the name into the set
    }

    file.close(); // Closing the file
    return applicants;
}

// Helper function to get initials from a name
std::string get_initials(std::string name) {
    std::string initials;
    initials += name[0]; // First letter of the name
    for (size_t i = 0; i < name.length(); i++) {
        if (name[i] == ' ') {
            initials += name[i + 1]; // First letter of the last name
            break;
        }
    }
    return initials;
}

// Function to find matches
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
    std::queue<const std::string*> matches; // Queue of pointers to names
    std::string target_initials = get_initials(name); // Initials of the given name

    for (const auto& student : students) { // Iterating through the set of students
        std::string student_initials = get_initials(student);
        if (student_initials == target_initials) { // If the initials match
            matches.push(&student); // Add a pointer to the name to the queue
        }
    }

    return matches;
}

// Function to get the final "match"
std::string get_match(std::queue<const std::string*>& matches) {
    if (matches.empty()) {
        return "NO MATCHES FOUND."; // If there are no matches
    }

    // Simply return the first name in the queue
    const std::string* match = matches.front();
    return *match;
}

// Do not modify this line
#include "autograder/utils.hpp"
