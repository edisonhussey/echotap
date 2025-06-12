#ifndef NEXT_POSITION_H
#define NEXT_POSITION_H

#include <vector>
#include <cstdlib>
#include <ctime>

class next_position {
    public:
        next_position(); // initializes with 2 random positions
        ~next_position();

        std::vector<float> get_next_position(); // returns {x, y}

    private:
        float previous_positions[4]; // [x1, y1, x2, y2]
        int mode = 0; // 0 attempts same direction 1 random direction 2 opposite direction
    

        std::vector<float> calculate_direction() const;
        void update_previous(const std::vector<float>& new_pos);
    };

#endif
