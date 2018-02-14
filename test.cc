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
const int PATH_MAX = 256;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//exec()
//uses the popen() function, that creates a bidirectional pipe, 
//forking, and invoking the shell;
//popen() returns a pointer to a stream that can be used to either read from or write to the pipe
//'arg' is a string with arguments for 'cmd'
//function returns the output of 'cmd' to stdout as a vector of strings 
/////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::string> exec(std::string cmd, const std::string &arg)
{
  std::vector<std::string> vec;
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

int compare(const std::vector<std::string> &out, const char **exps)
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
