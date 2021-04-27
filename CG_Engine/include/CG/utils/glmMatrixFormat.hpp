#pragma once

#include <iomanip>
#include <sstream>

// credits: Andgel

template<glm::length_t C, glm::length_t R, typename T, glm::qualifier Q = glm::defaultp>
std::ostream &operator<<(std::ostream &stream, const glm::mat<C, R, T, Q> &mat)
{
    std::array<size_t, R> biggest;
    std::stringstream s;

    biggest.fill(0);
    for (unsigned i = 0; i < C; i++) {
        for (unsigned j = 0; j < R; j++) {
            s << mat[j][i];
            biggest[j] = std::max(biggest[j], s.str().size());
            s.str("");
        }
    }

    for (unsigned i = 0; i < C; i++) {
        stream << "|";
        for (unsigned j = 0; j < R; j++) {
            if (j)
                stream << ", ";
            stream << std::setfill(' ') << std::setw(biggest[j]) << mat[j][i];
        }
        stream << "|" << '\n';
    }
    return stream;
}