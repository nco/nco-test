#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include "test.hh"

#ifdef _MSC_VER
#define popen _popen
#define pclose _pclose
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////
//test_t
/////////////////////////////////////////////////////////////////////////////////////////////////////

test_t::test_t(std::string cmd, const std::string &arg, const char **exps, int verbose)
{
  std::vector<std::string> out;
  out = exec(cmd, arg);
  std::cout << "TESTING " << cmd << " " << arg << " ... ";
  if (compare(out, exps))
  {
    std::cout << "FAILURE" << std::endl;
  }
  else
  {
    std::cout << "PASSED" << std::endl;
  }
  if (!verbose) return;
  std::cout << "OUTPUT" << std::endl;
  for (int idx = 0; idx < out.size(); idx++)
  {
    std::cout << out.at(idx);
  }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//exec()
//uses the popen() function, that creates a bidirectional pipe, 
//forking, and invoking the shell;
//popen() returns a pointer to a stream that can be used to either read from or write to the pipe
//'arg' is a string with arguments for 'cmd'
//function returns the output of 'cmd' to stdout as a vector of strings 
/////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::string> test_t::exec(std::string cmd, const std::string &arg)
{
  std::vector<std::string> vec;
  const int PATH_MAX = 256;
  char buf[PATH_MAX];

  cmd += " ";
  cmd += arg;
  FILE* fp = popen(cmd.c_str(), "r");
  if (fp == NULL)
  {
    assert(0);
  }
  while (fgets(buf, PATH_MAX, fp) != NULL)
  {
    std::string str(buf);
    vec.push_back(str);
  }
  pclose(fp);
  return vec;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//compare()
//compares an expected vector of strings with another vector of strings (output)
/////////////////////////////////////////////////////////////////////////////////////////////////////

int test_t::compare(const std::vector<std::string> &out, const char **exps)
{
  int nbr = 0;
  std::vector<std::string> exp;
  while (*exps != 0)
  {
    std::string str(*exps);
    exp.push_back(str);
    exps++;
  }
  assert(exp.size() == out.size());
  for (int idx = 0; idx < out.size(); idx++)
  {
    std::string outs = out.at(idx);
    std::string exps = exp.at(idx);
    //remove '\n' from output (last character)
    assert(outs.at(outs.size() - 1) == '\n');
    outs = outs.substr(0, outs.size() - 1);
    if (outs.compare(exps) != 0)
    {
      std::cout << "EXPECTED ";
      std::cout << exps << "\n";
      std::cout << "RESULT ";
      std::cout << outs << "\n";;
      nbr++;
    }
  }
  return nbr;
}
