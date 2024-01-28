#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <sstream>

using index_type = size_t;
using main_type = int64_t;

char number_to_char(const main_type& symbol);

main_type fast_degree(const main_type& number, const main_type& degree, const main_type& mod);

void add_up_numeral_system(std::vector<main_type>& number, const main_type& base, main_type& plus);

void multiply_numeral_system(std::vector<main_type>& number, const main_type& new_base, const main_type& base);

std::vector<main_type> string_to_polynomial(std::string& input);

void normalise_polynomial(std::vector<main_type>& number, const main_type& base,
                          const std::vector<main_type>& polynomial);

std::vector<main_type> multiply_polynomials(const std::vector<main_type>& left, const std::vector<main_type>& right,
                                            const main_type& base, const std::vector<main_type>& polynomial);

std::vector<main_type> polynomial_fast_degree(const std::vector<main_type>& number, const main_type& degree,
                                              const main_type& mod, const std::vector<main_type>& polynomial);

std::vector<main_type> input_cipher(const std::vector<main_type>& polynomial, const main_type& mod,
                                    const main_type& private_key);

std::vector<main_type> translation_numeral_system(std::vector<main_type>& message, const main_type& base,
                                                  const main_type& mod);

void output_message(const std::vector<main_type>& encrypted);
