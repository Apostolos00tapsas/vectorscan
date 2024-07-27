/*
 * Copyright (c) 2018-2019, Intel Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of Intel Corporation nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

#include "gtest/gtest.h"
#include "hs.h"
#include "config.h"
#include "test_util.h"


#include <fstream>
#include <sstream>
#include <string>

using namespace std;

TEST(rebar, leipzig_math_symbols_count) {
    hs_database_t *db = nullptr;
    hs_compile_error_t *compile_err = nullptr;
    CallBackContext c;
    const char *expr = "\\p{Sm}";
    const unsigned flag = HS_FLAG_UCP | HS_FLAG_UTF8;
    const unsigned id= 1;
    hs_error_t err = hs_compile(expr, flag, HS_MODE_BLOCK,nullptr, &db, &compile_err);

    ASSERT_EQ(HS_SUCCESS, err);
    ASSERT_TRUE(db != nullptr);

    hs_scratch_t *scratch = nullptr;
    err = hs_alloc_scratch(db, &scratch);
    ASSERT_EQ(HS_SUCCESS, err);
    ASSERT_TRUE(scratch != nullptr);


    std::ifstream file("../source/unit/hyperscan/datafiles/leipzig-3200.txt");
    std::stringstream buffer;
    buffer << file.rdbuf(); // Read the file into the buffer
    std::string data = buffer.str(); // Convert the buffer into a std::string

    c.halt = 0;
    err = hs_scan(db, data.c_str(), data.size(), 0, scratch, record_cb,
                  reinterpret_cast<void *>(&c));
    ASSERT_EQ(HS_SUCCESS, err);
    ASSERT_EQ(69, c.matches.size());

    hs_free_database(db);
    err = hs_free_scratch(scratch);
    ASSERT_EQ(HS_SUCCESS, err);
}

TEST(rebar, lh3lh3_reb_uri_or_email_grep) {
    hs_database_t *db = nullptr;
    hs_compile_error_t *compile_err = nullptr;
    CallBackContext c;
    const char *expr = "([a-zA-Z][a-zA-Z0-9]*)://([^ /]+)(/[^ ]*)?|([^ @]+)@([^ @]+)";
    const unsigned flag = 0;
    const unsigned id= 1;
    hs_error_t err = hs_compile(expr, flag, HS_MODE_BLOCK,nullptr, &db, &compile_err);

    ASSERT_EQ(HS_SUCCESS, err);
    ASSERT_TRUE(db != nullptr);

    hs_scratch_t *scratch = nullptr;
    err = hs_alloc_scratch(db, &scratch);
    ASSERT_EQ(HS_SUCCESS, err);
    ASSERT_TRUE(scratch != nullptr);


    std::ifstream file("../source/unit/hyperscan/datafiles/lh3lh3-reb-howto.txt");
    std::stringstream buffer;
    buffer << file.rdbuf(); // Read the file into the buffer
    std::string data = buffer.str(); // Convert the buffer into a std::string

    c.halt = 0;
    err = hs_scan(db, data.c_str(), data.size(), 0, scratch, record_cb,
                  reinterpret_cast<void *>(&c));
    ASSERT_EQ(HS_SUCCESS, err);
    ASSERT_EQ(888987, c.matches.size());

    hs_free_database(db);
    err = hs_free_scratch(scratch);
    ASSERT_EQ(HS_SUCCESS, err);
}

TEST(rebar, lh3lh3_reb_email_grep) {
    hs_database_t *db = nullptr;
    hs_compile_error_t *compile_err = nullptr;
    CallBackContext c;
    const char *expr = "([^ @]+)@([^ @]+)";
    const unsigned flag = 0;
    const unsigned id= 1;
    hs_error_t err = hs_compile(expr, flag, HS_MODE_BLOCK,nullptr, &db, &compile_err);

    ASSERT_EQ(HS_SUCCESS, err);
    ASSERT_TRUE(db != nullptr);

    hs_scratch_t *scratch = nullptr;
    err = hs_alloc_scratch(db, &scratch);
    ASSERT_EQ(HS_SUCCESS, err);
    ASSERT_TRUE(scratch != nullptr);


    std::ifstream file("../source/unit/hyperscan/datafiles/lh3lh3-reb-howto.txt");
    std::stringstream buffer;
    buffer << file.rdbuf(); // Read the file into the buffer
    std::string data = buffer.str(); // Convert the buffer into a std::string

    c.halt = 0;
    err = hs_scan(db, data.c_str(), data.size(), 0, scratch, record_cb,
                  reinterpret_cast<void *>(&c));
    ASSERT_EQ(HS_SUCCESS, err);
    ASSERT_EQ(232354, c.matches.size());

    hs_free_database(db);
    err = hs_free_scratch(scratch);
    ASSERT_EQ(HS_SUCCESS, err);
}


TEST(rebar, lh3lh3_reb_date_grep) {
    hs_database_t *db = nullptr;
    hs_compile_error_t *compile_err = nullptr;
    CallBackContext c;
    const char *expr = "([0-9][0-9]?)/([0-9][0-9]?)/([0-9][0-9]([0-9][0-9])?)";
    const unsigned flag = 0;
    const unsigned id= 1;
    hs_error_t err = hs_compile(expr, flag, HS_MODE_BLOCK,nullptr, &db, &compile_err);

    ASSERT_EQ(HS_SUCCESS, err);
    ASSERT_TRUE(db != nullptr);

    hs_scratch_t *scratch = nullptr;
    err = hs_alloc_scratch(db, &scratch);
    ASSERT_EQ(HS_SUCCESS, err);
    ASSERT_TRUE(scratch != nullptr);


    std::ifstream file("../source/unit/hyperscan/datafiles/lh3lh3-reb-howto.txt");
    std::stringstream buffer;
    buffer << file.rdbuf(); // Read the file into the buffer
    std::string data = buffer.str(); // Convert the buffer into a std::string

    c.halt = 0;
    err = hs_scan(db, data.c_str(), data.size(), 0, scratch, record_cb,
                  reinterpret_cast<void *>(&c));
    ASSERT_EQ(HS_SUCCESS, err);
    ASSERT_EQ(819, c.matches.size());

    hs_free_database(db);
    err = hs_free_scratch(scratch);
    ASSERT_EQ(HS_SUCCESS, err);
}