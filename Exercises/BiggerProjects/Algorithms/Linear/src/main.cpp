#include <cstddef>
#include <cstdlib>
#include <string>
#include <chrono>
#include <iostream>

#include "Vector.h"
#include "LinkedList.h"

using namespace std::chrono;

namespace{

    template <typename T>
    using LinearCollection = aisdi::LinkedList<T>;

    void perfomTest(){
        aisdi::LinkedList<std::string> list( {"Litwo", "Ojczyzno", "moja", "Ty", "jestes", "jak", "zdrowie", "Ile", "Cie", "trzeba", "cenic", "ten", "tylko", "sie", "dowie", "kto", "Cie", "stracil", "Dzis", "pieknosc", "twa", "w", "calej", "ozdobie", "widze", "i", "opisuje", "bo", "tesknie", "po", "Tobie", "Panno", "Swieta", "co", "jasnej", "bronisz", "Czestochowy", "i", "w", "Ostrej", "swiecisz", "Bramie", "Ty", "co", "grod", "zamkowy", "Nowogrodzki", "ochraniasz", "z", "jego", "wiernym", "ludem"});
        aisdi::Vector<std::string> vectr( {"Litwo", "Ojczyzno", "moja", "Ty", "jestes", "jak", "zdrowie", "Ile", "Cie", "trzeba", "cenic", "ten", "tylko", "sie", "dowie", "kto", "Cie", "stracil", "Dzis", "pieknosc", "twa", "w", "calej", "ozdobie", "widze", "i", "opisuje", "bo", "tesknie", "po", "Tobie", "Panno", "Swieta", "co", "jasnej", "bronisz", "Czestochowy", "i", "w", "Ostrej", "swiecisz", "Bramie", "Ty", "co", "grod", "zamkowy", "Nowogrodzki", "ochraniasz", "z", "jego", "wiernym", "ludem"});

        high_resolution_clock::time_point time1 = high_resolution_clock::now();
        list.append("Pan Tadeusz");
        high_resolution_clock::time_point time2 = high_resolution_clock::now();
        auto duration1 = duration_cast<microseconds>(time2 - time1).count();
        std::cout << "List append time: " << duration1 << std::endl;

        high_resolution_clock::time_point time3 = high_resolution_clock::now();
        vectr.append("Pan Tadeusz");
        high_resolution_clock::time_point time4 = high_resolution_clock::now();
        auto duration2 = duration_cast<microseconds>(time4 - time3).count();
        std::cout << "Vector append time: " << duration2 << std::endl;

        high_resolution_clock::time_point time5 = high_resolution_clock::now();
        list.prepend("Pan Tadeusz");
        high_resolution_clock::time_point time6 = high_resolution_clock::now();
        auto duration3 = duration_cast<microseconds>(time6 - time5).count();
        std::cout << "List prepend time: " << duration3 << std::endl;

        high_resolution_clock::time_point time7 = high_resolution_clock::now();
        vectr.prepend("Pan Tadeusz");
        high_resolution_clock::time_point time8 = high_resolution_clock::now();
        auto duration4 = duration_cast<microseconds>(time8 - time7).count();
        std::cout << "Vector prepend time: " << duration4 << std::endl;

        high_resolution_clock::time_point time9 = high_resolution_clock::now();
        list.popLast();
        high_resolution_clock::time_point time10 = high_resolution_clock::now();
        auto duration5 = duration_cast<microseconds>(time10 - time9).count();
        std::cout << "List popLast time: " << duration5 << std::endl;

        high_resolution_clock::time_point time11 = high_resolution_clock::now();
        vectr.popLast();
        high_resolution_clock::time_point time12 = high_resolution_clock::now();
        auto duration6 = duration_cast<microseconds>(time12 - time11).count();
        std::cout << "Vector popLast time: " << duration6 << std::endl;
    }

} // namespace

int main(int argc, char** argv){
    const std::size_t repeatCount = argc > 1 ? std::atoll(argv[1]) : 10000;
    for (std::size_t i = 0; i < repeatCount; ++i)
        perfomTest();
    return 0;
}
