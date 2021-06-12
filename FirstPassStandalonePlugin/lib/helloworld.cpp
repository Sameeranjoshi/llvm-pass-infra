#include "helloworld.h"
//... haeder files
using namespace llvm;

static cl::opt<bool> someflag("someflag",
    cl::desc("Ok this does nothing, just waves in air"),
    cl::init(true)
    );

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv,
                              "outoftreetool - A command line flag tool, does nothing except prints this\n");

}
