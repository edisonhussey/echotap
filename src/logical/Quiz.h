// #ifndef QUIZ_H
// #define QUIZ_H

// #include <string>
// #include <vector>  // need this for std::vector

// struct question {
//     std::string prompt;
//     std::vector<std::string> choices;
// };

// class quiz {
// public:
//     quiz();

//     void add_question(const std::string& prompt, const std::vector<std::string>& choices);

//     int length() const;
//     const std::vector<question>& get_questions() const;

// private:
//     std::vector<question> questionSet;
// };

// #endif // QUIZ_H


#ifndef QUIZ_H
#define QUIZ_H

#include <string>
#include <vector>

struct question {
    std::string prompt;
    std::vector<std::string> choices;
};

class Quiz {
public:
    Quiz();  // constructor

    void add_question(const std::string& prompt, const std::vector<std::string>& choices);
    int length() const;
    question get_next();
    const std::vector<question>& get_questions() const;

private:
    std::vector<question> question_set;
    int index = 0;  // keeps track for get_next()
};

#endif
