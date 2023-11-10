#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {

struct CoolPass : PassInfoMixin<CoolPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
    errs() << F.getName() << " has " << F.getInstructionCount() << " instrs\n";
    return PreservedAnalyses::all();
  }
};

}

llvm::PassPluginLibraryInfo getCoolPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "MyCoolPass", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "cool-pass") {
                    FPM.addPass(CoolPass());
                    return true;
                  }
                  return false;
                });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getCoolPassPluginInfo();
}
