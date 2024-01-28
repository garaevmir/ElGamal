#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <random>
#include <sstream>

using index_type = size_t;
using main_type = int64_t;

main_type char_to_number(char& symbol);

main_type fast_degree(const main_type& number, const main_type& degree, const main_type& mod);

void numeral_system_plus(std::vector<main_type>& number, const main_type & new_base);

void multiply_numeral_system(std::vector<main_type>& number, const main_type& new_base, const main_type& base);

std::vector<main_type> string_to_polynomial(std::string& input);

void normalise_polynomial(std::vector<main_type>& number, const main_type& base,
                          const std::vector<main_type>& polynomial);

std::vector<main_type> multiply_polynomials(const std::vector<main_type>& left, const std::vector<main_type>& right,
                                            const main_type& base, const std::vector<main_type>& polynomial);

std::vector<main_type> polynomial_fast_degree(const std::vector<main_type>& number, const main_type& degree,
                                              const main_type& mod, const std::vector<main_type>& polynomial);

void output_cipher(const std::vector<main_type>& public_key, const main_type& mod, std::vector<main_type>& message,
                   const std::vector<main_type>& generator, const std::vector<main_type>& poly);

void polynom_out(const std::vector<main_type>& poly);
