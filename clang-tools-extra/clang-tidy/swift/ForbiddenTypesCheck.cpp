//===--- ForbiddenTypesCheck.cpp - clang-tidy -----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "ForbiddenTypesCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace swift {

void ForbiddenTypesCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      varDecl(
          unless(isExpansionInSystemHeader()),
          hasType(namedDecl(hasAnyName(
              "::std::vector", "::std::deque", "::std::forward_list",
              "::std::list", "::std::set", "::std::map", "::std::multiset",
              "::std::multimap", "::std::unordered_set", "::std::unordered_map",
              "::std::unordered_multiset", "::std::unordered_multimap",
              "::std::stack", "::std::queue", "::std::priority_queue",
              "::std::string", "::std::unique_ptr", "::std::shared_ptr")).bind("type")))
          .bind("decl"),
      this);
}

void ForbiddenTypesCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *decl = Result.Nodes.getNodeAs<VarDecl>("decl");
  const auto *type = Result.Nodes.getNodeAs<NamedDecl>("type");
  diag(decl->getLocation(), "Starling Core forbids the use of type");
}

} // namespace swift
} // namespace tidy
} // namespace clang
