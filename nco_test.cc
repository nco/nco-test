#include <stdio.h>
#include <assert.h>
#include <cstdlib>
#include <iostream>
#include "test.hh"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//usage
/////////////////////////////////////////////////////////////////////////////////////////////////////

void usage()
{
  std::cout << "usage: ./nco_test -p <PATH> -f <FILE>" << std::endl;
  std::cout << "PATH: path of NCO executables" << std::endl;
  std::cout << "FILE: full path name of netCDF data file to read" << std::endl;
  exit(0);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//main
/////////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
  std::vector<std::string> exp;
  std::vector<std::string> out;
  std::string path_exe;
  std::string path_data;
  std::string ncks;
  std::vector<std::string> arg;

  if (argc != 5)
  {
    usage();
  }

  for (int idx = 1; idx < argc; idx++)
  {
    if (argv[idx][0] == '-')
    {
      switch (argv[idx][1])
      {
      case 'p':
        path_exe = argv[idx + 1];
        idx++;
        break;
      case 'f':
        path_data = argv[idx + 1];
        idx++;
        break;
      default:
        usage();
      }
    }
    else
    {
      usage();
    }
  }

  ncks = path_exe;
#ifdef _MSC_VER
  ncks += "\\";
  ncks += "ncks.exe";
#else
  ncks += "/";
  ncks += "ncks";
#endif

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  //ncks tests
  /////////////////////////////////////////////////////////////////////////////////////////////////////

  arg.push_back("-C --trd -g g6g1 -v area");
  arg.push_back(path_data);

  exp.push_back("/g6/g6g1/area");
  exp.push_back("area: type NC_FLOAT, 1 dimension, 0 attributes, compressed? no, chunked? no, packed? no");
  exp.push_back("area size (RAM) = 2*sizeof(NC_FLOAT) = 2*4 = 8 bytes");
  exp.push_back("area dimension 0: /lat, size = 2 NC_FLOAT (Coordinate is /lat)");
  exp.push_back("");
  exp.push_back("/g6/g6g1/area");
  exp.push_back("lat[0]=-90 area[0]=40 (no units)");
  exp.push_back("lat[1]=90 area[1]=50 (no units)");
  exp.push_back("");

  out = exec(ncks, arg);
  if (compare(out, exp))
  {
    std::cout << "test FAILURE" << std::endl;
  }
  else
  {
    std::cout << "test PASSED" << std::endl;
  }

  return 0;
}

