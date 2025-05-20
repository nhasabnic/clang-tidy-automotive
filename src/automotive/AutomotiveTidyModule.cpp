//===--- AutomotiveTidyModule.cpp - clang-tidy ----------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "../cert/FloatLoopCounter.h"
#include "../misc/NoRecursionCheck.h"
#include "../misc/UnusedParametersCheck.h"

#include "AvoidAssignmentInExpressionCheck.h"
#include "AvoidFunctionParameterModificationCheck.h"
#include "AvoidNonBooleanInConditionCheck.h"
#include "AvoidUnionCheck.h"
#include "ImplicitFunctionDeclCheck.h"
#include "ImplicitIntCheck.h"
#include "InvariantControlCheck.h"
#include "MissingCompoundCheck.h"
#include "MissingElseCheck.h"
#include "MissingStaticInternalLinkageCheck.h"

#include "array/ArrayComponent.h"
#include "bitfield/BitfieldComponent.h"
#include "comment/CommentComponent.h"
#include "literal/LiteralComponent.h"
#include "operator/OperatorComponent.h"
#include "preprocessor/PreprocessorComponent.h"
#include "stdlib/StdlibComponent.h"
#include "switch-stmt/SwitchStmtComponent.h"

#include "char-sets-and-lexical-convs/CharSetsAndLexicalConvsModule.h"
#include "declarations-and-definitions/DeclarationsAndDefinitionsModule.h"
#include "pointer-type-conversions/PointerTypeConversionsModule.h"
#include "unused-code/UnusedCodeModule.h"

// using namespace clang::ast_matchers;

namespace clang::tidy {
namespace automotive {

class AutomotiveModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {

    /* TODO: Move this and name it properly. */
    CheckFactories.registerCheck<MissingStaticInternalLinkageCheck>(
        "automotive-x-Missing-Static-Internal-Linkage");
    CheckFactories.registerCheck<ImplicitIntCheck>("automotive-x-req-8.1");

    ArrayComponent::addCheckFactories(CheckFactories);
    BitfieldComponent::addCheckFactories(CheckFactories);
    CommentComponent::addCheckFactories(CheckFactories);
    LiteralComponent::addCheckFactories(CheckFactories);
    PreprocessorComponent::addCheckFactories(CheckFactories);
    OperatorComponent::addCheckFactories(CheckFactories);
    StdlibComponent::addCheckFactories(CheckFactories);
    SwitchStmtComponent::addCheckFactories(CheckFactories);

    /* C 2023
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<cert::FloatLoopCounter>(
        "automotive-c23-req-14.1");
    CheckFactories.registerCheck<misc::NoRecursionCheck>(
        "automotive-c23-req-17.2");

    /* C 2012
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<cert::FloatLoopCounter>(
        "automotive-c12-req-14.1");

    /* 2. Unused code
    ---------------------------------------------------------------- */
    UnusedCodeModule::addCheckFactories(CheckFactories);

    /* 4. Character sets and lexical conversations
    ---------------------------------------------------------------- */
    CharSetsAndLexicalConvsModule::addCheckFactories(CheckFactories);

    /* 8. Declarations and defintions
    ---------------------------------------------------------------- */
    DeclarationsAndDefinitionsModule::addCheckFactories(CheckFactories);

    /* 11. Pointer type conversions
    ---------------------------------------------------------------- */
    PointerTypeConversionsModule::addCheckFactories(CheckFactories);

    /* 13.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidAssignmentInExpressionCheck>(
        "automotive-c23-adv-13.4");

    /* 14.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<InvariantControlCheck>(
        "automotive-c23-req-14.3");
    CheckFactories.registerCheck<AvoidNonBooleanInConditionCheck>(
        "automotive-c23-req-14.4");

    /* 15.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<MissingCompoundCheck>(
        "automotive-c23-req-15.6");
    CheckFactories.registerCheck<MissingElseCheck>("automotive-c23-req-15.7");

    /* 17.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<ImplicitFunctionDeclCheck>(
        "automotive-c23-man-17.3");
    CheckFactories.registerCheck<AvoidFunctionParameterModificationCheck>(
        "automotive-c23-adv-17.8");

    /* 19.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidUnionCheck>("automotive-c23-adv-19.2");

    /* 21.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidAssignmentInExpressionCheck>(
        "automotive-c12-adv-13.4");

    /* 14.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidNonBooleanInConditionCheck>(
        "automotive-c12-req-14.4");

    /* 15.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<MissingCompoundCheck>(
        "automotive-c12-req-15.6");
    CheckFactories.registerCheck<MissingElseCheck>("automotive-c12-req-15.7");

    /* 16.
    ---------------------------------------------------------------- */
  }
};

} // namespace automotive

// Register the Automotive Module using this statically initialized variable.
static ClangTidyModuleRegistry::Add<automotive::AutomotiveModule>
    X("automotive-module", "Adds automotive lint checks.");

// This anchor is used to force the linker to link in the generated object file
// and thus register the AutomotiveModule.
volatile int AutomotiveModuleAnchorSource = 0;

} // namespace clang::tidy
