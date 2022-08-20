//===--- AtomicFlagConstructorCheck.h - clang-tidy --------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_SWIFT_ATOMICFLAGCONSTRUCTORCHECK_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_SWIFT_ATOMICFLAGCONSTRUCTORCHECK_H

#include "../ClangTidyCheck.h"

namespace clang {
namespace tidy {
namespace swift {

/// FIXME: Write a short description.
///
/// For the user-facing documentation see:
/// http://clang.llvm.org/extra/clang-tidy/checks/swift-atomic-flag-constructor.html
class AtomicFlagConstructorCheck : public ClangTidyCheck {
public:
  AtomicFlagConstructorCheck(StringRef Name, ClangTidyContext *Context)
      : ClangTidyCheck(Name, Context) {}
  void registerMatchers(ast_matchers::MatchFinder *Finder) override;
  void check(const ast_matchers::MatchFinder::MatchResult &Result) override;
};

} // namespace swift
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_SWIFT_ATOMICFLAGCONSTRUCTORCHECK_H
