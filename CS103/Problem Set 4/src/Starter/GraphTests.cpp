#include "GUI/SimpleTest.h"
#include "GraphEditor/Utilities/JSON.h"
#include "Grabbag/GrabbagTester.h"
#include <set>
#include <string>
#include <utility>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

namespace {
    /* Local versus Gradescope configuration. */
    #define UH_OH(x)   UH_OH_2(x)
    #define UH_OH_2(x) SHOW_ERROR(x)
    const string kBaseDir = "res/";

    using Graph = pair<set<string>, set<pair<string, string>>>;

    Graph decodeGraph(const string& filename) {
        ifstream input(filename);
        if (!input) UH_OH("Cannot open file " + filename);

        /* Raw JSON data. */
        JSON j = JSON::parse(input);

        Graph result;

        /* Map from index to name. */
        map<size_t, string> toName;
        for (JSON node: j["nodes"]) {
            toName[node["index"].asInteger()] = node["label"].asString();
            result.first.insert(node["label"].asString());
        }

        /* Load edges, bidirectionally. */
        for (JSON edge: j["edges"]) {
            auto e = make_pair(toName.at(edge["from"].asInteger()), toName.at(edge["to"].asInteger()));
            if (e.first == e.second) UH_OH("Undirected graphs cannot have self-loops.");

            result.second.insert(e);
            result.second.insert(make_pair(e.second, e.first));
        }

        return result;
    }

    /* Rabin rolling hash code. Our implementation works by checking your answers against
     * a series of hash codes for the correct answer. This gives high confidence that your
     * answer is correct without actually revealing what the answer is. :-)
     */
    uint32_t rollingHash(const string& str, uint64_t base, uint64_t multiplier) {
        const uint64_t modulus = 0x7FFFFFFF;
        uint64_t result = base;
        for (char ch: str) {
            result = (((result * multiplier) % modulus) + uint8_t(ch)) % modulus;
        }
        return result % modulus;
    }

    /* Given a list of seven answers, produces a key for those answers. */
    string keyFor(const Graph& graph) {
        ostringstream builder;
        builder << "{";
        for (const auto& node: graph.first) {
            builder << quotedVersionOf(node) << ",";
        }
        for (const auto& edge: graph.second) {
            builder << quotedVersionOf(edge.first) << "-" << quotedVersionOf(edge.second) << ",";
        }
        builder << "}";
        return builder.str();
    }

    Graph reencode(const Graph& source, const vector<string>& ordering) {
        map<string, string> remap;

        /* Convert names to indices. */
        int i = 0;
        for (const auto& key: ordering) {
            remap[key] = to_string(i++);
        }

        /* Now transform the graph. */
        Graph result;

        /* Convert nodes. */
        for (const auto& node: source.first) {
            result.first.insert(remap[node]);
        }

        /* Convert edges. */
        for (const auto& edge: source.second) {
            result.second.insert(make_pair(remap[edge.first], remap[edge.second]));
        }

        return result;
    }

    bool checkCorrectness(const string& part, bool checkPermutations = true) {
        auto graph = decodeGraph(kBaseDir + part + ".graph");
        if (graph.first.size() >= 9) {
            UH_OH("Graph is too large to be the correct solution.");
        }

        /* Try all permutations and see if any of them work. Begin by
         * listing all the nodes in sorted order.
         */
        vector<string> nodes(graph.first.begin(), graph.first.end());
        do {
            /* Get the hash for this graph. */
            auto key = keyFor(reencode(graph, nodes));
            bool correct = true;
            runPrivateTest(part + "_Solution", [&](istream& input) {
                for (uint64_t base, multiplier, result; input >> base >> multiplier >> result; ) {
                    /* Hash must agree; if not, we are definitely wrong. */
                    if (rollingHash(key, base, multiplier) != result) {
                        correct = false;
                        break;
                    }
                }
            });
            if (correct) return true;

        } while (checkPermutations && next_permutation(nodes.begin(), nodes.end()));

        /* No permutations work, so the graph must be wrong. */
        return false;
    }
}

PROVIDED_TEST("Part1.graph") {
    if (!checkCorrectness("Part1", false)) {
        UH_OH("Answer is incorrect.");
    }
}

PROVIDED_TEST("Part2.graph") {
    if (!checkCorrectness("Part2")) {
        UH_OH("Answer is incorrect.");
    }
}

PROVIDED_TEST("Part3.graph") {
    if (!checkCorrectness("Part3")) {
        UH_OH("Answer is incorrect.");
    }
}

PROVIDED_TEST("Part4.graph") {
    if (!checkCorrectness("Part4")) {
        UH_OH("Answer is incorrect.");
    }
}

