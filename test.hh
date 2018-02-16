#ifndef NCO_TEST_HH
#define NCO_TEST_HH 1

#include <string>
#include <vector>

class test_t
{
public:
  test_t(std::string cmd, const std::string &arg, const char **exps, int verbose);
  std::vector<std::string> exec(std::string cmd, const std::string &arg);
  int compare(const std::vector<std::string> &out, const char **exps);
};



#endif
