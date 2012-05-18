#ifndef _GFF_FEATURE_H
#define _GFF_FEATURE_H

#include <string>
#include <map>
#include <vector>

#include "Attributes.h"

using std::string;
using std::vector;

namespace GFF
{
    class Feature
    {
        public:
            Feature(void);
            Feature(const char*);
            Feature(string&);

            string seqid;
            string source;
            string type;
            unsigned int start;
            unsigned int end;
            string score;
            char strand;
            char phase;
            string raw_attributes;
            Attributes attributes;

            vector<Feature> children;

            bool hasStrand(void);
            bool isRevStrand(void);
            bool hasScore(void);
            double getScore(void);
            int getLength(void);
            // TODO string toString( void );

            bool initFromGFF(string&);
    };

    struct PositionComparison
    {
        bool operator() (const Feature& a, const Feature& b) const
        {
            return (a.seqid < b.seqid)
                   || (a.seqid == b.seqid && a.start < b.start)
                   || (a.seqid == b.seqid && a.start == b.start
                       && a.end < b.end);
        }
    };

    bool spliceJunctions(vector<Feature>& exons, vector<Feature>& junctions);
}
#endif
