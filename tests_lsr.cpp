#include <gtest/gtest.h>
#include "scanner.h"
#include <sstream>

/*
*/
class ScannerTest : public ::testing::Test {

  protected:
  void SetUp() override {
    /* Full lines */
    ssFullLines << "1\n2\n3\n4";

    /* Mixed lines */
    ssMixedLines << "1\n2\n\n\n5\n6\n";

    /* Empty Lines */
    ssEmptyLines << "\n\n\n\n\n";
  }

  // void TearDown() override {}
  std::stringstream ssEmpty;
  std::stringstream ssFullLines;
  std::stringstream ssEmptyLines;
  std::stringstream ssMixedLines;
};

/*  Scanner, line count Tests
*/
TEST_F(ScannerTest, lineCount_ZeroLinesInAnEmptyFile){
  Scanner scan;
  scan.scan(ssEmpty);
  EXPECT_EQ(scan.lineCount(), 0);
}

TEST_F(ScannerTest, lineCount_EveryNewLineCounts){
  Scanner scan;
  scan.scan(ssFullLines);
  EXPECT_EQ(scan.lineCount(), 4);
}

TEST_F(ScannerTest, lineCount_EmptyNewLineCounts){
  Scanner scan;
  scan.scan(ssEmptyLines);
  EXPECT_EQ(scan.lineCount(), 6);
}

TEST_F(ScannerTest, lineCount_MixedLinesAreCounted){
  Scanner scan;
  scan.scan(ssMixedLines);
  EXPECT_EQ(scan.lineCount(), 7);
}

/*  Scanner, empty line count Tests
*/
TEST_F(ScannerTest, emptyLineCount_ZeroLinesInAnEmptyFile){
  Scanner scan;
  scan.scan(ssEmpty);
  EXPECT_EQ(scan.emptyLineCount(), 0);
}

TEST_F(ScannerTest, emptyLineCount_ZeroLinesInAnFullLinesFile){
  Scanner scan;
  scan.scan(ssFullLines);
  EXPECT_EQ(scan.emptyLineCount(), 0);
}

TEST_F(ScannerTest, emptyLineCount_EmptyNewLineCounts){
  Scanner scan;
  scan.scan(ssEmptyLines);
  EXPECT_EQ(scan.emptyLineCount(), 6);
}

TEST_F(ScannerTest, emptyLineCount_OnlyEmptyLinesInMixedLinesFile){
  Scanner scan;
  scan.scan(ssMixedLines);
  EXPECT_EQ(scan.emptyLineCount(), 3);
}

/*  Scanner, non empty line count Tests
*/
TEST_F(ScannerTest, noEmptyLineCount_ZeroLinesInAnEmptyFile){
  Scanner scan;
  scan.scan(ssEmpty);
  EXPECT_EQ(scan.nonEmpytLineCount(), 0);
}

TEST_F(ScannerTest, emptyLineCount_CountEveryNonEmptyline){
  Scanner scan;
  scan.scan(ssFullLines);
  EXPECT_EQ(scan.nonEmpytLineCount(), 4);
}

TEST_F(ScannerTest, emptyLineCount_DontCountEmptyLines){
  Scanner scan;
  scan.scan(ssEmptyLines);
  EXPECT_EQ(scan.nonEmpytLineCount(), 0);
}

TEST_F(ScannerTest, emptyLineCount_OnlyNonEmptyLinesInMixedLinesFile){
  Scanner scan;
  scan.scan(ssMixedLines);
  EXPECT_EQ(scan.nonEmpytLineCount(), 4);
}
