#include "encryption_over_F_q.h"

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

main_type fast_degree(const main_type& number, const main_type& degree, const main_type& mod) {
    if (degree == 0) {
        return 1;
    }
    if (degree % 2 == 1) {
        return (fast_degree(number, degree - 1, mod) * number) % mod;
    }
    main_type root = fast_degree(number, degree >> 1, mod);
    return (root * root) % mod;
}

void numeral_system_plus(std::vector<main_type>& number, const main_type & new_base) {
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

void multiply_numeral_system(std::vector<main_type>& number, const main_type& new_base, const main_type& base) {
    main_type temp = 0;
    main_type memory;
    for (index_type i = 0; i < number.size() || temp; ++i) {
        if (i == number.size()) {
            number.push_back(0);
        }
        memory = temp + number[i] * base;
        temp = memory / new_base;
        number[i] = memory - new_base * temp;
    }
}


std::vector<main_type> string_to_polynomial(std::string& input) {
    std::stringstream text(input);
    std::string number;
    std::vector<main_type> output;
    while (std::getline(text, number, ' ')) {
        output.push_back(std::stoi(number));
    }
    return output;
}

void normalise_polynomial(std::vector<main_type>& number, const main_type& base,
                          const std::vector<main_type>& polynomial) {
    while (number.size() >= polynomial.size()) {
        main_type multiplier = number.back();
        index_type number_size = number.size();
        index_type polynomial_size = polynomial.size();
        for (index_type i = 1; i <= polynomial_size; ++i) {
            number[number_size - i] = (number[number_size - i] - polynomial[polynomial_size - i] * multiplier) % base;
            if (number[number_size - i] < 0) {
                number[number_size - i] += base;
            }
        }
        while (number.size() > 1 && number.back() == 0) {
            number.pop_back();
        }
    }
}

std::vector<main_type> multiply_polynomials(const std::vector<main_type>& left, const std::vector<main_type>& right,
                                            const main_type& base, const std::vector<main_type>& polynomial) {
    std::vector<main_type> result(left.size() + right.size());
    for (index_type i = 0; i < left.size(); ++i) {
        for (index_type j = 0; j < right.size(); ++j) {
            result[i + j] = (result[i + j] + left[i] * right[j]) % base;
        }
    }
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    normalise_polynomial(result, base, polynomial);
    return result;
}

std::vector<main_type> polynomial_fast_degree(const std::vector<main_type>& number, const main_type& degree,
                                              const main_type& mod, const std::vector<main_type>& polynomial) {
    if (degree == 0) {
        return {1};
    }
    if (degree % 2 == 1) {
        std::vector<main_type> temp = polynomial_fast_degree(number, degree - 1, mod, polynomial);
        return multiply_polynomials(temp, number, mod, polynomial);
    }
    std::vector<main_type> root = polynomial_fast_degree(number, degree >> 1, mod, polynomial);
    return multiply_polynomials(root, root, mod, polynomial);
}

std::vector<main_type> input_message(const main_type& mod, const main_type& base) {
    std::string input;
    std::getline(std::cin, input);
    std::vector<main_type> message(1, 0);
    for (index_type i = input.size(); i >= 1; --i) {
        multiply_numeral_system(message, mod, base);
        message[0] += char_to_number(input[i - 1]);
        numeral_system_plus(message, mod);
    }
    return message;
}

void output_cipher(const std::vector<main_type>& public_key, const main_type& mod, std::vector<main_type>& message,
                   const std::vector<main_type>& generator, const std::vector<main_type>& poly) {
    main_type n = poly.size() - 1;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> random_number(1.0, (double)mod - 2);
    for (main_type i = 0; i < message.size(); i += n) {
        main_type private_key = (main_type)random_number(mt);
        std::vector<main_type> temp = polynomial_fast_degree(generator, private_key, mod, poly);
        polynom_out(temp);
        temp.clear();
        for (main_type j = i; j < message.size() && j < i + n; ++j) {
            temp.push_back(message[j]);
        }
        std::vector<main_type> mem = polynomial_fast_degree(public_key, private_key, mod, poly);
        temp = multiply_polynomials(mem, temp, mod, poly);
        polynom_out(temp);
    }
}

void polynom_out(const std::vector<main_type>& poly) {
    for (main_type i : poly) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

int main() {
    const main_type base = 64;
    std::string input;

    std::getline(std::cin, input);
    main_type mod = std::stoi(input);

    std::getline(std::cin, input);
    std::vector<main_type> poly = string_to_polynomial(input);

    std::getline(std::cin, input);
    std::vector<main_type> generator = string_to_polynomial(input);

    std::getline(std::cin, input);
    std::vector<main_type> public_key = string_to_polynomial(input);

    std::vector<main_type> message = input_message(mod, base);

    output_cipher(public_key, mod, message, generator, poly);
    
    return 0;
}
