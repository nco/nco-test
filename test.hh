#ifndef NCO_TEST_HH
#define NCO_TEST_HH 1

#include <string>
#include <vector>

std::vector<std::string> exec(std::string &cmd, const std::vector<std::string> &arg);
int compare(const std::vector<std::string> &out, const std::vector<std::string> &exp);

#endif
