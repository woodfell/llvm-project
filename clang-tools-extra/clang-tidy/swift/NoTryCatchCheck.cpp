//===--- NoTryCatchCheck.cpp - clang-tidy ---------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// See https://llvm.org/LICENSE.txt for license information.
//
//===----------------------------------------------------------------------===//

#include "NoTryCatchCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace swift {

void NoTryCatchCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
    cxxTryStmt(
      unless(
          isExpansionInSystemHeader())).bind("expr"), this);
}

void NoTryCatchCheck::check(const MatchFinder::MatchResult &Result) {
    const auto *Expr = Result.Nodes.getNodeAs<CXXTryStmt>("expr");
    diag(Expr->getTryLoc(), "Starling Core does not permit the use of try/catch statements");
}

} // namespace swift
} // namespace tidy
} // namespace clang
