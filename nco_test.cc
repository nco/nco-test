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
  std::vector<std::string> out;
  std::string path_exe;
  std::string path_data;
  std::string ncks;
  std::string arg;

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

  arg = "-C --trd -g g6g1 -v area ";
  arg += path_data;

  const char* ncks_tst_01[] =
  {
    "/g6/g6g1/area",
    "area: type NC_FLOAT, 1 dimension, 0 attributes, compressed? no, chunked? no, packed? no",
    "area size (RAM) = 2*sizeof(NC_FLOAT) = 2*4 = 8 bytes",
    "area dimension 0: /lat, size = 2 NC_FLOAT (Coordinate is /lat)",
    "",
    "/g6/g6g1/area",
    "lat[0]=-90 area[0]=40 (no units)",
    "lat[1]=90 area[1]=50 (no units)",
    "",
    0
  };

  out = exec(ncks, arg);
  std::cout << "TESTING " << ncks << " " << arg << " ... ";
  if (compare(out, ncks_tst_01))
  {
    std::cout << "FAILURE" << std::endl;
  }
  else
  {
    std::cout << "PASSED" << std::endl;
  }

  std::cout << "OUTPUT" << std::endl;
  for (int idx = 0; idx < out.size(); idx++)
  {
    std::cout << out.at(idx);
  }

  return 0;
}

