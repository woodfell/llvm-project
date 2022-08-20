//===--- NostdlibassertCheck.cpp - clang-tidy -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NostdlibassertCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace swift {

void NostdlibassertCheck::registerMatchers(MatchFinder *Finder) {
        Finder->addMatcher(
            callExpr(
              unless(
                isExpansionInSystemHeader()
              ),
              anyOf(
                callee(
                  functionDecl(
                    hasName("::__assert_fail")
                  ).bind("resolved-callee")
                ),
                callee(
                  unresolvedLookupExpr(
                    hasAnyDeclaration(
                      functionDecl(
                        hasName("::__assert_fail")
                      ).bind("unresolved-callee")
                    )
                  )
                )
              )
            ).bind("call"), this);
}

void NostdlibassertCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *Expr = Result.Nodes.getNodeAs<CallExpr>("call");
  const auto *ResolvedCallee = Result.Nodes.getNodeAs<FunctionDecl>("resolve-callee");
  const auto *UnresolvedCallee = Result.Nodes.getNodeAs<FunctionDecl>("unresolved-callee");

  diag(Expr->getExprLoc(), "Do not call standard library assert(), use SWIFT_ASSERT() instead");
}

} // namespace swift
} // namespace tidy
} // namespace clang
