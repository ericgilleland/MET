// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
// ** Copyright UCAR (c) 1992 - 2021
// ** University Corporation for Atmospheric Research (UCAR)
// ** National Center for Atmospheric Research (NCAR)
// ** Research Applications Lab (RAL)
// ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA
// *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
////////////////////////////////////////////////////////////////////////

using namespace std;

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <cmath>
#include <vector>

#include "vx_util.h"
#include "vx_tc_util.h"

////////////////////////////////////////////////////////////////////////

static ConcatString program_name;

////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {

   program_name = get_short_name(argv[0]);

   if(argc != 2) {
      mlog << Error
           << "\nusage: " << program_name
           << " track_filename\n\n";
      exit(1);
   }

   ConcatString input_filename = (string)argv[1];
   LineDataFile f;
   ATCFProbLine p_line;
   ProbInfoArray probs;
   int count;

   if(!f.open(input_filename.c_str())) {
      mlog << Error
           << "\n" << program_name
           << ": unable to open input file \"" << input_filename << "\"\n\n";
      exit(1);
   }

   count = 0;
   while(f >> p_line) {

      // Add the current line to the array of probs
      probs.add(p_line);

      // Increment the line count
      count++;

      mlog << Debug(1)
           << "\nLine " << count << "...\n";
      p_line.dump(cout);
   }

   // Dump out summary info
   mlog << Debug(1)
        << "Read " << count << " lines from input file \""
        << input_filename << "\"\n";

   // Dump out summary info
   mlog << Debug(1) << probs.serialize_r() << "\n";

   // Clean up
   f.close();

   return(0);

}

////////////////////////////////////////////////////////////////////////
