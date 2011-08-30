#include <stdexcept>

#include <gtest/gtest.h>

#include "Parser.h"

using namespace ccs;

TEST(ParserTest, BasicPhrases) {
  Parser parser;
  EXPECT_TRUE(parser.parseString(""));
  EXPECT_TRUE(parser.parseString("@import 'file'"));
  EXPECT_TRUE(parser.parseString("prop = 'val'"));
  EXPECT_TRUE(parser.parseString("elem#id {prop = 'val'}"));
  EXPECT_TRUE(parser.parseString(".class.class :root > elem#id {prop=43}"));
  EXPECT_FALSE(parser.parseString(".class.class :root > elem# id {prop=2.3}"));
  EXPECT_FALSE(parser.parseString(".class. class :root > elem#id {prop=\"val\"}"));
  EXPECT_FALSE(parser.parseString(".class.class : root > elem#id {prop=0xab12}"));
  EXPECT_FALSE(parser.parseString("blah"));
  EXPECT_TRUE(parser.parseString("elem#id { prop = 'val'; prop2 = 31337 }"));
}

TEST(ParserTest, Comments) {
  Parser parser;
  EXPECT_TRUE(parser.parseString("// single line comment\n"));
  EXPECT_TRUE(parser.parseString("// single line comment nonl"));
  EXPECT_TRUE(parser.parseString("/* multi-line comment */"));
  EXPECT_TRUE(parser.parseString("prop = /* comment */ 'val'"));
  EXPECT_TRUE(parser.parseString("prop = /* comment /*nest*/ more */ 'val'"));
  EXPECT_TRUE(parser.parseString("elem#id /* comment */ {prop = 'val'}"));
  EXPECT_TRUE(parser.parseString("// comment\nelem { prop = 'val' prop = 'val' }"));
}

