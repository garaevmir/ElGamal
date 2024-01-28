#pragma once

#include <iostream>
#include <vector>
#include <random>

using main_type = uint64_t;

using index_type = size_t;

main_type char_to_number(char& symbol);

main_type fast_degree(const main_type& num, const main_type& deg, const main_type& module);

void numeral_system_plus(std::vector<main_type>& number, const main_type& new_base);

void numeral_system_mult(std::vector<main_type>& number, const main_type& new_base, const main_type base);

std::vector<main_type> input_message(const main_type& mod, const main_type& base);

void output_cipher(const main_type& public_key, const main_type& mod, const main_type& generator,
                   const std::vector<main_type>& message);