//===--- NoexceptCorrectnessCheck.cpp - clang-tidy ------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NoexceptCorrectnessCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace swift {

void NoexceptCorrectnessCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(
      functionDecl(
        unless(
          isExpansionInSystemHeader()
        ),
        isNoThrow(),
        forEachDescendant(
          stmt(
          anyOf(
            callExpr(
              callee(
                functionDecl(
                  unless(
                    anyOf(
                      isNoThrow(),
                      isExternC(),
                      isExpansionInSystemHeader()
                    )
                  )
                )
              )
            ).bind("call-expr"),
            cxxConstructExpr(
              unless(
                anyOf(
                  isExpansionInSystemHeader(),
                  hasDeclaration(
                    functionDecl(
                      isNoThrow()
                    )
                  )
                )
              )
            ).bind("construct")
            )
            )
          )
        ).bind("func"), this);
}

void NoexceptCorrectnessCheck::check(const MatchFinder::MatchResult &Result) {
  // FIXME: Add callback implementation.
  const auto *func = Result.Nodes.getNodeAs<FunctionDecl>("func");
  const auto *call = Result.Nodes.getNodeAs<CallExpr>("call-expr");
  const auto *construct = Result.Nodes.getNodeAs<CXXConstructExpr>("construct");

  if (call)
  diag(call->getExprLoc(), "noexcept functions can only call functions which are also noexcept or have C linkage");
  else
  diag(construct->getExprLoc(), "noexcept functions can only call functions which are also noexcept or have C linkage");
}

} // namespace swift
} // namespace tidy
} // namespace clang
