#include "main.h"

main_type char_to_number(char& symbol) {
    if (symbol >= 48 && symbol <= 57)
        return symbol - 48;
    if (symbol >= 65 && symbol <= 90)
        return symbol - 55;
    if (symbol >= 97 && symbol <= 122)
        return symbol - 61;
    if (symbol == 32)
        return 62;
    if (symbol == 46)
        return 63;
    return 64;
}

main_type fast_degree(const main_type& num, const main_type& deg, const main_type& module) {
    if (deg == 0) {
        return 1;
    }
    if (deg % 2 == 1) {
        return (fast_degree(num, deg - 1, module) * num) % module;
    }
    main_type ans = fast_degree(num, deg >> 1,  module);
    return (ans * ans) % module;
}

void numeral_system_plus(std::vector<main_type>& number, const main_type& new_base) {
    main_type temp = 0;
    for (index_type i = 0; i < number.size() || temp; ++i) {
        if (i == number.size()) {
            number.push_back(0);
        }
        number[i] += temp;
        temp = number[i] / new_base;
        number[i] -= temp * new_base;
    }
}

void numeral_system_mult(std::vector<main_type>& number, const main_type& new_base, const main_type base) {
    main_type temp = 0;
    main_type num;
    for (index_type i = 0; i < number.size() || temp; ++i) {
        if (i == number.size()) {
            number.push_back(0);
        }
        num = temp + number[i] * base;
        temp = num / new_base;
        number[i] = num - new_base * temp;
    }
}

std::vector<main_type> input_message(const main_type& mod, const main_type& base) {
    std::string input;
    std::getline(std::cin, input);
    std::getline(std::cin, input);
    std::vector<main_type> message(1, 0);
    for (index_type i = input.size(); i >= 1; --i) {
        numeral_system_mult(message, mod, base);
        message[0] += char_to_number(input[i - 1]);
        numeral_system_plus(message, mod);
    }
    return message;
}

void output_cipher(const main_type& public_key, const main_type& mod, const main_type& generator,
                   const std::vector<main_type>& message) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> random_number(1.0, (double)mod - 2);
    for (main_type i : message) {
        main_type private_key = (main_type)random_number(mt);
        std::cout << fast_degree(generator, private_key, mod) << ' '
                  << (fast_degree(public_key, private_key, mod) * i) % mod << '\n';
    }
}

int main() {
    main_type mod;
    main_type generator;
    main_type public_key;
    main_type base = 64;
    std::cin >> mod >> generator >> public_key;
    std::vector<main_type> message = input_message(mod, base);
    output_cipher(public_key, mod, generator, message);
    return 0;
}
