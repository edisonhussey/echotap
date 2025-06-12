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

        Beatmap create_map(
            float difficulty,  // 0.0 to 1.0
            float sensitivity, // 0.0 to 1.0 
            
            const std::string& backgroundImage, 
            const std::string& songFile,

            Quiz questionSet // quiz object containing questions and choices


        );
            




    };

// class next_position_generator {
//     public:
//         next_position_generator();//write a way to init 2 random starter 
//         ~next_position_generator();
//         std::vector<float> get_next_position();
//     private:

//         // float[4] previous_positions; class variable holds 2 prev positions continually updated
 
// };



#endif
