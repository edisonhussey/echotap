

#include "Quiz.h"
#include <vector>
#include <string>
#include <stdexcept>

Quiz::Quiz() : index(0) {
    // Initialize empty question_set vector and index
    question_set = std::vector<question>();
}

void Quiz::add_question(const std::string& prompt, const std::vector<std::string>& choices) {
    question q;
    q.prompt = prompt;
    q.choices = choices;
    question_set.push_back(q);  // was questionSet, changed to question_set
}

int Quiz::length() const {
    return static_cast<int>(question_set.size());
}

question Quiz::get_next() {
    if (index < question_set.size()) {
        return question_set[index++];
    } else {
        throw std::out_of_range("No more questions available");
    }
}

const std::vector<question>& Quiz::get_questions() const {
    return question_set;
}
