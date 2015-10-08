/*
 * Copyright (C) 2015 BIO-DIKU.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 *
 * http://www.gnu.org/copyleft/gpl.html
 */

#include "../catch.hpp"
#include <string>

#include "../../src/modules/levenshtein.cc"

TEST_CASE("Levenshtein returns a correct result after comparison", "[levenshtein]") {
  SeqEntry t1, t2;
  LevenshteinDistance compare;
  compare.setIdentity(0.05f);

  SECTION("Compare two equal strings") {
    t1.set_seq("acgtagcgcggctatagcgcataaatcgctctagcgctatcttcgggttagca");
    t2.set_seq("acgtagcgcggctatagcgcataaatcgctctagcgctatcttcgggttagca");

    REQUIRE(compare.compare(&t1, &t2) == true);
  }

  SECTION("Compare two very different strings") {
    t1.set_seq("acgtagcgcggctatagcgcataaatcgctctagcgctatcttcgggttagca");
    t2.set_seq("ggatcctcatagcggctattgcgaaaagctatttcgcggccctagcga");

    REQUIRE(compare.compare(&t1, &t2) == false);
  }

  SECTION("compare two similar strings of differing length") {
    t1.set_seq("acgtagcgcggctatagcgcataaatcgctctagcgctatcttcgggttagca");
    t2.set_seq("acgtagcgcggctatagcgcataaatcctctagcgctatcttcgggttagca");

    REQUIRE(compare.compare(&t1, &t2));
  }

  SECTION("compare two similar strings of same length") {
    t1.set_seq("acgtagcgcggctatagcgcataaatcgctctagcgctatcttcgggttagca");
    t2.set_seq("acgtagcgcggctatagcgcataaatcgctctagcgctatcttcgggttagca");

    REQUIRE(compare.compare(&t1, &t2));
  }
}

TEST_CASE("Levenshtein properly handles empty sequences", "[levenshtein]") {
  SeqEntry t1, t2;
  LevenshteinDistance compare;
  compare.setIdentity(0.05f);

  SECTION("First sequence is empty") {
    t1.set_seq("");
    t2.set_seq("a");

    REQUIRE(!compare.compare(&t1, &t2));
  }

  SECTION("Second Sequence is empty") {
    t1.set_seq("a");
    t2.set_seq("");

    REQUIRE(!compare.compare(&t1, &t2));
  }
}

TEST_CASE("Levenshtein properly handles same sequence", "[levenshtein]") {
  SeqEntry t1;
  LevenshteinDistance compare;
  t1.set_seq("acgt");

  SECTION("identity is 0.05f") {
    compare.setIdentity(0.05f);

    REQUIRE(compare.compare(&t1, &t1));
  }

  SECTION("identity is 0.00f") {
    compare.setIdentity(0.00f);

    REQUIRE(compare.compare(&t1, &t1));
  }

  SECTION("identity is 1.00f") {
    compare.setIdentity(1.00f);

    REQUIRE(compare.compare(&t1, &t1));
  }
}