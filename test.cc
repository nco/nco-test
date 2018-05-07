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
//arguments: 
//'cmd' NCO executable full path 
//'arg' arguments for NCO executable
//'expected': expected output as an array of strings (each element is 1 line of output)
/////////////////////////////////////////////////////////////////////////////////////////////////////

test_t::test_t(std::string cmd, const std::string &arg, const char **expected, int verbose)
{
  std::vector<std::string> out;

  cmd += " ";
  cmd += arg;
  out = exec(cmd);
  std::cout << "TESTING " << cmd << "... ";
  if (compare(out, expected) > 0)  //returns number of lines of output that differ
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
//'cmd' NCO executable full path concatenated with argumants (including data file full path)
//function returns the output of 'cmd' to stdout as a vector of strings 
/////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::string> test_t::exec(const std::string &cmd)
{
  std::vector<std::string> vec;
  const int PATH_MAX = 1024;
  char buf[PATH_MAX];

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
//returns number of lines of output that differ
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
