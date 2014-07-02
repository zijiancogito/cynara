/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
/*
 * @file        bucketrecordcorrupted.cpp
 * @author      Aleksander Zdyb <a.zdyb@partner.samsung.com>
 * @version     1.0
 * @brief       Tests for Cynara::BucketRecordCorruptedException
 */


#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exceptions/BucketRecordCorruptedException.h"

using namespace Cynara;

TEST(BucketRecordCorruptedException, line) {
    BucketRecordCorruptedException ex("line");
    auto expected = "Bucket record corrupted at line: <line>";
    ASSERT_STREQ(expected, ex.what());
    ASSERT_EQ("line", ex.line());
    ASSERT_EQ("", ex.filename());
    ASSERT_EQ(0, ex.lineNumber());
}

TEST(BucketRecordCorruptedException, line_lineno) {
    auto ex = BucketRecordCorruptedException("line").withLineNumber(10);
    auto expected = "Bucket record corrupted at line 10: <line>";
    ASSERT_STREQ(expected, ex.what());
    ASSERT_EQ("line", ex.line());
    ASSERT_EQ("", ex.filename());
    ASSERT_EQ(10, ex.lineNumber());
}

TEST(BucketRecordCorruptedException, line_lineno_filename) {
    auto ex = BucketRecordCorruptedException("line").withLineNumber(10).withFilename("bucket.bkt");
    auto expected = "Bucket record corrupted at bucket.bkt:10: <line>";
    ASSERT_STREQ(expected, ex.what());
    ASSERT_EQ("line", ex.line());
    ASSERT_EQ("bucket.bkt", ex.filename());
    ASSERT_EQ(10, ex.lineNumber());
}

TEST(BucketRecordCorruptedException, line_filename) {
    auto ex = BucketRecordCorruptedException("line").withFilename("bucket.bkt");
    auto expected = "Bucket record corrupted at bucket.bkt: <line>";
    ASSERT_STREQ(expected, ex.what());
    ASSERT_EQ("line", ex.line());
    ASSERT_EQ("bucket.bkt", ex.filename());
    ASSERT_EQ(0, ex.lineNumber());
}

TEST(BucketRecordCorruptedException, line_sliced) {
    std::string line = "A very long line placed here just to check,"
                       " if slicing works as expected (83 chars)";
    auto ex = BucketRecordCorruptedException(line);
    auto expected = "Bucket record corrupted at line:"
            " <A very long line placed here just to check, if sli...>";
    ASSERT_STREQ(expected, ex.what());
    ASSERT_EQ(line, ex.line());
    ASSERT_EQ("", ex.filename());
    ASSERT_EQ(0, ex.lineNumber());
}
