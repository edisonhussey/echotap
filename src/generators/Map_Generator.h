#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include <string>
#include <unordered_map>
#include "../logical/Quiz.h"
#include "../logical/Beatmap.h"
#include <vector>
class Map_Generator { 
    public:
        Map_Generator();
        ~Map_Generator();

        std::pair<std::vector<Tap>, std::vector<Prompt>> create_map(
            float difficulty,  // 0.0 to 1.0
            float sensitivity, // 0.0 to 1.0 
            
            const std::string& backgroundImage, 
            const std::string& songFile,

            Quiz questionSet // quiz object containing questions and choices


        );
            




    };


#endif
