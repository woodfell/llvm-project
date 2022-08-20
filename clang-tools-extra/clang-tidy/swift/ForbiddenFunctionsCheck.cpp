//===--- ForbiddenFunctionsCheck.cpp - clang-tidy -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ForbiddenFunctionsCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace swift {

static auto forbidden_function_list() {
  return functionDecl(hasAnyName(
        "::abort",
        "std::abort",
        "std::terminate",
        "::malloc",
        "::free",
        "::calloc",
        "::realloc",
        "::strcmp",
        "::strcat",
        "::printf",
        "::fprintf",
        "::scanf",
        "::fscanf",
        "::fgets",
        "::fgetc",
        "::gets",
        "::getch",
        "::getchar",
        "::signal",
        "::kill",
        "std::make_unique",
        "std::make_shared"
  ));
}

void ForbiddenFunctionsCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(callExpr(unless(isExpansionInSystemHeader()),
                     anyOf(
                     callee(
                     forbidden_function_list() .bind("resolved-call")
                     ),
                     callee(
                     unresolvedLookupExpr(
                     hasAnyDeclaration(
                     forbidden_function_list().bind("unresolved-callee")))))).bind("expr"), this);
}

void ForbiddenFunctionsCheck::check(const MatchFinder::MatchResult &Result) {
  auto *expr = Result.Nodes.getNodeAs<CallExpr>("expr");
  auto *resolved = Result.Nodes.getNodeAs<FunctionDecl>("resolved-callee");
  auto *unresolved = Result.Nodes.getNodeAs<FunctionDecl>("unresolved-callee");

  diag(expr->getExprLoc(), "Starling Core does not permit the use of function");
}

} // namespace swift
} // namespace tidy
} // namespace clang
