#include <cstddef>
#include <cstdlib>
#include <string>
#include <chrono>
#include <iostream>

#include "TreeMap.h"
#include "HashMap.h"

using namespace std::chrono;

namespace{

    template <typename T>
    using HashCollection = aisdi::HashMap<T>;

    void perfomTest(size_t argc){
		high_resolution_clock::time_point time1;
		high_resolution_clock::time_point time2;

        aisdi::HashMap<std::string> hashysz( {"Litwo"});//, "Ojczyzno", "moja", "Ty", "jestes", "jak", "zdrowie", "Ile", "Cie", "trzeba", "cenic", "ten", "tylko", "sie", "dowie", "kto", "Cie", "stracil", "Dzis", "pieknosc", "twa", "w", "calej", "ozdobie", "widze", "i", "opisuje", "bo", "tesknie", "po", "Tobie", "Panno", "Swieta", "co", "jasnej", "bronisz", "Czestochowy", "i", "w", "Ostrej", "swiecisz", "Bramie", "Ty", "co", "grod", "zamkowy", "Nowogrodzki", "ochraniasz", "z", "jego", "wiernym", "ludem"});
        aisdi::TreeMap<std::string> tree( {"Litwo"});//, "Ojczyzno", "moja"});//, "Ty", "jestes", "jak", "zdrowie", "Ile", "Cie", "trzeba", "cenic", "ten", "tylko", "sie", "dowie", "kto", "Cie", "stracil", "Dzis", "pieknosc", "twa", "w", "calej", "ozdobie", "widze", "i", "opisuje", "bo", "tesknie", "po", "Tobie", "Panno", "Swieta", "co", "jasnej", "bronisz", "Czestochowy", "i", "w", "Ostrej", "swiecisz", "Bramie", "Ty", "co", "grod", "zamkowy", "Nowogrodzki", "ochraniasz", "z", "jego", "wiernym", "ludem"});

		time1 = high_resolution_clock::now();
		for (std::size_t i = 0; i < argc; ++i)
			hashysz.append("Pan Tadeusz");
        time2 = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(time2 - time1).count();
        std::cout << "Hash append time: " << duration << " microseconds" << std::endl;

        time1 = high_resolution_clock::now();
        for (std::size_t i = 0; i < argc; ++i)
			tree.append("Pan Tadeusz");
        time2 = high_resolution_clock::now();
        duration = duration_cast<microseconds>(time2 - time1).count();
        std::cout << "Tree append time: " << duration << " microseconds" << std::endl;

        time1 = high_resolution_clock::now();
        for (std::size_t i = 0; i < argc; ++i)
			hashysz.prepend("Pan Tadeusz");
        time2 = high_resolution_clock::now();
        duration = duration_cast<microseconds>(time2 - time1).count();
        std::cout << "Hash prepend time: " << duration << " microseconds" << std::endl;

        time1 = high_resolution_clock::now();
        for (std::size_t i = 0; i < argc; ++i)
			tree.prepend("Pan Tadeusz");
        time2 = high_resolution_clock::now();
        duration = duration_cast<microseconds>(time2 - time1).count();
        std::cout << "Tree prepend time: " << duration << " microseconds" << std::endl;

        time1 = high_resolution_clock::now();
        for (std::size_t i = 0; i < argc; ++i)
			hashysz.popLast();
        time2 = high_resolution_clock::now();
        duration = duration_cast<microseconds>(time2 - time1).count();
        std::cout << "Hash popLast time: " << duration << " microseconds" << std::endl;

        time1 = high_resolution_clock::now();
        for (std::size_t i = 0; i < argc; ++i)
			tree.popLast();
        time2 = high_resolution_clock::now();
        duration = duration_cast<microseconds>(time2 - time1).count();
        std::cout << "Tree popLast time: " << duration << " microseconds" << std::endl;
    }

} // namespace

int main(int argc, char** argv){
    const std::size_t repeatCount = argc > 1 ? std::atoll(argv[1]) : 10000;
    perfomTest(repeatCount);
    return 0;
}
