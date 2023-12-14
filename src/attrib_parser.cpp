#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// n-ary tree for the tags
struct Tag {
  string tagName;
  unordered_map<string, string> attribs;
  unordered_map<string, shared_ptr<Tag>> nestedTags;
};

// A atring split function for tags
vector<string> split_tag(const string &hrmlLine, char delimiter) {
  vector<string> tokens;
  string token;
  istringstream hmrlStream(hrmlLine);

  while (getline(hmrlStream, token, delimiter)) {
    if (token != "=") {
      tokens.push_back(token);
    }
  }

  return tokens;
};

// A string split function for queries
vector<string> split_querie(const string &query, char firstDelim,
                            char secondDelim) {
  vector<string> tokens;
  string token, subtoken;
  istringstream querieStream(query);

  while (getline(querieStream, token, firstDelim)) {
    istringstream subqueryStream(token);
    while (getline(subqueryStream, subtoken, secondDelim)) {
      tokens.push_back(subtoken);
    }
  }
  return tokens;
};

// Set the tags and values in a hash map
unordered_map<string, string> set_attrmap(const vector<string> &tags) {
  unordered_map<string, string> tagsHmap;
  for (size_t i = 1; i < tags.size(); i += 2) {
    string value = tags[i + 1];
    value.erase(std::remove(value.begin(), value.end(), '\"'), value.end());
    tagsHmap[tags[i]] = value;
  }
  return tagsHmap;
};

// Parse current line and set node values
void process_tag(const string &hrmlLine, shared_ptr<Tag> hrml) {
  string tmpLine;
  vector<string> tokenizedHrml;

  tmpLine = hrmlLine.substr(1, hrmlLine.size() - 2);
  tokenizedHrml = split_tag(tmpLine, ' ');
  hrml->tagName = tokenizedHrml[0];
  if (tokenizedHrml.size() > 1) {
    hrml->attribs = set_attrmap(tokenizedHrml);
  }
};

// Parse query
void parse_query(const vector<string> &queryTokens,
                 const shared_ptr<Tag> hrml) {
  string answer, attribute;
  answer = "Not Found!";
  shared_ptr<Tag> currentNode = hrml;

  for (size_t i = 0; i < queryTokens.size() - 1; i++) {
    string tagNameCurrent = queryTokens[i];
    if (currentNode->nestedTags.count(tagNameCurrent) == 0) {
      cout << answer << endl;
      return;
    }
    currentNode = currentNode->nestedTags[tagNameCurrent];
  }

  attribute = queryTokens[queryTokens.size() - 1];

  if (currentNode->attribs.count(attribute) != 0) {
    answer = currentNode->attribs[attribute];
  }

  cout << answer << endl;
};

int main() {
  // Auxiliary variables
  string hrmlLine, queryLine;
  vector<string> oneQuery;
  vector<vector<string>> allQueries;
  stack<shared_ptr<Tag>> stackedTags;

  // Input parameters
  int n, q;
  cin >> n >> q;
  cin.ignore();

  // Instantiate data structure
  shared_ptr<Tag> rootHrml = make_shared<Tag>();

  // Create a root entry for the HRML program
  stackedTags.push(rootHrml);

  // Read HRML source
  for (size_t i = 0; i < n; i++) {
    getline(cin, hrmlLine);
    if (hrmlLine.find("/") == string::npos) {
      shared_ptr<Tag> nodeHrml = make_shared<Tag>();
      process_tag(hrmlLine, nodeHrml);
      stackedTags.top()->nestedTags[nodeHrml->tagName] = nodeHrml;
      stackedTags.push(nodeHrml);
    } else {
      stackedTags.pop();
    }
  }

  // Read queries
  for (size_t i = 0; i < q; i++) {
    getline(cin, queryLine);
    oneQuery = split_querie(queryLine, '.', '~');
    allQueries.push_back(oneQuery);
  }

  // Print results
  for (size_t i = 0; i < q; i++) {
    oneQuery = allQueries[i];
    parse_query(oneQuery, rootHrml);
  }

  return 0;
}