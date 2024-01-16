//
// Created by stas on 16.01.2024.
//

#ifndef SNEK_IO_VECTOR_2F_HPP
#define SNEK_IO_VECTOR_2F_HPP

namespace snek {

    class vector_2f {

        float x;
        float y;

    public:
        vector_2f (float x, float y);

        vector_2f (int x, int y);

        void update (float x, float y);

        float get_x();

        float get_y();

    };
}


#endif //SNEK_IO_VECTOR_2F_HPP
