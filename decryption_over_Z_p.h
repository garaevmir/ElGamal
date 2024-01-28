#pragma once

#include <cstdint>
#include <iostream>
#include <vector>
#include <sstream>

using main_type = uint64_t;

using index_type = size_t;

char number_to_char(main_type symbol);

main_type fast_degree(const main_type& num, const main_type& deg, const main_type& module);

void numeral_system_plus(std::vector<main_type>& number, const main_type& base, main_type plus);

void numeral_system_mult(std::vector<main_type>& number, const main_type& new_base, const main_type base);

std::vector<main_type> input_cipher(const main_type& private_key, const main_type& mod);

void output_message(const main_type& base, const main_type& mod, const std::vector<main_type>& message);