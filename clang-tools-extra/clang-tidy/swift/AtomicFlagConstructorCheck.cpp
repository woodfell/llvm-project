//===--- AtomicFlagConstructorCheck.cpp - clang-tidy ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AtomicFlagConstructorCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace swift {

void AtomicFlagConstructorCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(
      cxxConstructExpr(
      unless(
  isExpansionInSystemHeader()),
  hasType(namedDecl(hasName("::std::atomic_flag"))),
  hasDescendant(expr())).bind("flag"), this);
}

void AtomicFlagConstructorCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *Expr = Result.Nodes.getNodeAs<CXXConstructExpr>("flag");
  diag(Expr->getExprLoc(), 
       "According to the language spec std::atomic_flag only has a default constructor which leaves the object in an undefined state. Passing arguments to the constructor is a compiler extension. On GCC/Clang this is accepted even when using -pedantic which is a clear violation of the language spec. Remove the constructor argument(s) and explicitly assign a value in some other place, or assign ATOMIC_FLAG_INIT");
}

} // namespace swift
} // namespace tidy
} // namespace clang
