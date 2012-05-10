#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Feature.h"

using testing::ElementsAre;
using std::vector;
using namespace GFF;

// TODO features can have URL escaped characters

TEST(FeatureTest, isRevStrand)
{
    Feature f;
    f.strand = '+';
    EXPECT_FALSE(f.isRevStrand());

    f.strand = '.';
    EXPECT_FALSE(f.isRevStrand());

    f.strand = '-';
    EXPECT_TRUE(f.isRevStrand());
}

TEST(FeatureTest, hasStrand)
{
    Feature f;
    f.strand = '+';
    EXPECT_FALSE(f.isRevStrand());

    f.strand = '-';
    EXPECT_TRUE(f.isRevStrand());

    f.strand = '.';
    EXPECT_FALSE(f.isRevStrand());

    f.strand = '?';
    EXPECT_FALSE(f.isRevStrand());
}

TEST(FeatureTest, getLength)
{
    Feature f;
    f.start = 20;
    f.end = 30;
    EXPECT_EQ(11, f.getLength());
}

TEST(FeatureTest, from_GFF)
{
    Feature f("Chr\ttest\ttestgene\t20\t30\t0\t+\t0\tName=foo");
    EXPECT_EQ("Chr", f.seqid);
    EXPECT_EQ("test", f.source);
    EXPECT_EQ("testgene", f.type);
    EXPECT_EQ(20, f.start);
    EXPECT_EQ(30, f.end);
    EXPECT_EQ("0", f.score);
    EXPECT_EQ('+', f.strand);
    EXPECT_EQ('0', f.phase);
    EXPECT_EQ("Name=foo", f.raw_attributes);
    string s;
    f.attributes.get("Name", s);
    EXPECT_EQ("foo", s);
}

TEST(FeatureTest, from_GFF_invalid_number_of_columns)
{
    // TODO more specific exception class
    EXPECT_ANY_THROW(Feature f("Chr\ttest\ttestgene\t20\t30\t0\t+\t"));
}

TEST(FeatureTest, children_init_empty)
{
    Feature f;
    EXPECT_EQ(0, f.children.size());
}

TEST(FeatureTest, spliceJunctions)
{
    Feature a;
    Feature b;
    Feature c;
    Feature d;

    b.type = "exon";
    b.start = 10;
    b.end = 20;

    c.type = "exon";
    c.start = 30;
    c.end = 40;

    d.type = "exon";
    d.start = 60;
    d.end = 65;

    a.children.push_back(b);
    a.children.push_back(c);
    a.children.push_back(d);

    vector<Feature> ret;
    EXPECT_TRUE(a.spliceJunctions(ret));

    EXPECT_EQ("splice_junction", ret.at(0).type);
    EXPECT_EQ("splice_junction", ret.at(1).type);
    EXPECT_EQ(20, ret.at(0).start);
    EXPECT_EQ(30, ret.at(0).end);
    EXPECT_EQ(40, ret.at(1).start);
    EXPECT_EQ(60, ret.at(1).end);

    EXPECT_EQ(2, ret.size());
}

/*
TEST( FeatureTest, toString ){

    Feature f;
    f.seqid = "Chr";
    f.source = "test";
    f.type = "testgene";
    f.start = 20;
    f.end = 30;
    f.score = "0";
    f.strand = '+';
    f.phase = '0';

    EXPECT_EQ("Chr\ttest\ttestgene\t20\t30\t0\t+\t0\t", f.toString());

    f.score = ".";
    EXPECT_EQ("Chr\ttest\ttestgene\t20\t30\t.\t+\t0\t", f.toString());

    f.phase = '.';
    EXPECT_EQ("Chr\ttest\ttestgene\t20\t30\t.\t+\t.\t", f.toString());

    f.strand = '.';
    EXPECT_EQ("Chr\ttest\ttestgene\t20\t30\t.\t.\t.\t", f.toString());
}
*/
