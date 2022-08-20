//===--- SwiftTidyModule.cpp - clang-tidy
//----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "../google/UnnamedNamespaceInHeaderCheck.h"
#include "../misc/NewDeleteOverloadsCheck.h"
#include "../misc/NonCopyableObjects.h"
#include "../misc/StaticAssertCheck.h"
#include "../misc/ThrowByValueCatchByReferenceCheck.h"
#include "../performance/MoveConstructorInitCheck.h"
#include "AtomicFlagConstructorCheck.h"
#include "ForbiddenFunctionsCheck.h"
#include "ForbiddenTypesCheck.h"
#include "NoTryCatchCheck.h"
#include "NoexceptCorrectnessCheck.h"
#include "NonPlacementNewCheck.h"
#include "NostdlibassertCheck.h"

namespace clang {
namespace tidy {
namespace swift {

class SwiftModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    // C++ checkers
    // DCL
    CheckFactories.registerCheck<AtomicFlagConstructorCheck>(
        "swift-atomic-flag-constructor");
    CheckFactories.registerCheck<ForbiddenFunctionsCheck>(
        "swift-forbidden-functions");
    CheckFactories.registerCheck<ForbiddenTypesCheck>(
        "swift-forbidden-types");
    CheckFactories.registerCheck<NostdlibassertCheck>(
        "swift-no-stdlib-assert");
    CheckFactories.registerCheck<NoTryCatchCheck>(
        "swift-no-try-catch");
    CheckFactories.registerCheck<NoexceptCorrectnessCheck>(
        "swift-noexcept-correctness");
    CheckFactories.registerCheck<NonPlacementNewCheck>(
        "swift-non-placement-new");
  }
};

} // namespace swift

// Register the MiscTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<swift::SwiftModule>
    X("swift-module",
      "Adds lint checks corresponding to Swift secure coding guidelines.");

// This anchor is used to force the linker to link in the generated object file
// and thus register the SwiftModule.
volatile int SwiftModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang
