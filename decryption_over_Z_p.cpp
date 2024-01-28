#include "main.h"

char number_to_char(main_type symbol) {
    if (symbol <= 9)
        return (char)(symbol + 48);
    if (symbol <= 35)
        return (char)(symbol + 55);
    if (symbol <= 61)
        return (char)(symbol + 61);
    if (symbol == 62)
        return 32;
    if (symbol == 63)
        return 46;
    return '\n';
}

main_type fast_degree(const main_type& num, const main_type& deg, const main_type& module) {
    if (deg == 0) {
        return 1;
    }
    if (deg % 2 == 1) {
        return (fast_degree(num, deg - 1, module) * num) % module;
    }
    main_type ans = fast_degree(num, deg >> 1, module);
    return (ans * ans) % module;
}

void numeral_system_plus(std::vector<main_type>& number, const main_type& base, main_type plus) {
    std::vector<main_type> mem;
    main_type temp = 0;
    while (plus > 0) {
        mem.push_back(plus % base);
        plus = plus / base;
    }
    for (index_type i = 0; i < std::max(number.size(), mem.size()) || temp; ++i) {
        if (i == number.size()) {
            number.push_back(0);
        }
        number[i] += temp + (i < mem.size() ? mem[i] : 0);
        temp = number[i] >= base;
        if (temp)  {
            number[i] -= base;
        }
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

std::vector<main_type> input_cipher(const main_type& private_key, const main_type& mod) {
    main_type inp_1;
    main_type inp_2;
    std::string input;
    std::getline(std::cin, input);
    std::vector<main_type> message;
    while (std::getline(std::cin, input, '\n') && !input.empty()) {
        std::istringstream in(input);
        in >> inp_1 >> inp_2;
        inp_1 = fast_degree(inp_1, private_key, mod);
        main_type cnt = fast_degree(inp_1, mod - 2, mod);
        message.push_back((cnt * inp_2) % mod);
    }
    return message;
}

void output_message(const main_type& base, const main_type& mod, const std::vector<main_type>& message) {
    std::vector<main_type> encrypted(1, 0);
    for (main_type i = message.size(); i >= 1; --i) {
        numeral_system_mult(encrypted, base, mod);
        numeral_system_plus(encrypted, base, message[i - 1]);
    }
    for (main_type i : encrypted) {
        std::cout << number_to_char(i);
    }
}

int main() {
    main_type mod;
    main_type private_key;
    const main_type base = 64;
    std::cin >> mod >> private_key;
    std::vector<main_type> message = input_cipher(private_key, mod);
    output_message(base, mod, message);
    return 0;
}
