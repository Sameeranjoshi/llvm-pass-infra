#include "commonheaders.h"

using namespace llvm;

namespace  {
  // Real stuff functions
  void visitor(Function &F){
    errs() << "\n Function name is = " << F.getName();
    errs() << "\n Function takes " << F.arg_size() << " arguments";
  }
  
  // pass main class/ kind of old pass way?
  struct NewPMHelloWorld : public PassInfoMixin<NewPMHelloWorld> {
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
      visitor(F);
      return PreservedAnalyses::all();
    }
  };

} // end anaonymous namespace

// give call to pass
llvm::PassPluginLibraryInfo getHelloWorldPluginLibraryInfo(){
  return {LLVM_PLUGIN_API_VERSION, "NewPMHelloWorld", "11.22"/*pass version*/, [](PassBuilder &PB) {
                PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "new-pm-hello-world") {
                    FPM.addPass(NewPMHelloWorld());
                    return true;
                  }
                  return false;
                });
      }
  };
}
// register pass

extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK
llvmGetPassPluginInfo(){
  return getHelloWorldPluginLibraryInfo();
}