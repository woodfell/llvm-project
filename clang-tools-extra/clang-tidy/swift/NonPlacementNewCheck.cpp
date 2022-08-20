//===--- NonPlacementNewCheck.cpp - clang-tidy ----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NonPlacementNewCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace swift {

void NonPlacementNewCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(cxxNewExpr(unless(isExpansionInSystemHeader()),
                                unless(hasAnyPlacementArg(expr())))
                         .bind("expr"),
                     this);
}

void NonPlacementNewCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *expr = Result.Nodes.getNodeAs<CXXNewExpr>("expr");
  diag(expr->getExprLoc(),
       "Starling Core forbids the use of non-placement new expressions. Use "
       "swift::mem_alloc() or, preferably, swift::make_unique<T>() instead");
}

} // namespace swift
} // namespace tidy
} // namespace clang
