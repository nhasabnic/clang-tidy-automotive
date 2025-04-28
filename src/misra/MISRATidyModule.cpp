//===--- MISRATidyModule.cpp - clang-tidy --------------------------------===//
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
#include "AtoXCheck.h"
#include "AvoidAssignmentInExpressionCheck.h"
#include "AvoidBooleanInSwitchCheck.h"
#include "AvoidFunctionParameterModificationCheck.h"
#include "AvoidGotoCheck.h"
#include "AvoidMacroNamedAsCkeywordCheck.h"
#include "AvoidNonBooleanInConditionCheck.h"
#include "AvoidSetjmpHeaderCheck.h"
#include "AvoidSignalHeaderCheck.h"
#include "AvoidStdargHeaderCheck.h"
#include "AvoidStdlibMemoryCheck.h"
#include "AvoidStdlibRandCheck.h"
#include "AvoidUndefCheck.h"
#include "AvoidUnionCheck.h"
#include "AvoidstdlibsystemcallCheck.h"
#include "ExitCheck.h"
#include "ForwardGotoLabelCheck.h"
#include "ImplicitFunctionDeclCheck.h"
#include "ImplicitIntCheck.h"
#include "InvariantControlCheck.h"
#include "MissingBreakInSwitchCheck.h"
#include "MissingCompoundCheck.h"
#include "MissingDefaultInSwitchStatementCheck.h"
#include "MissingElseCheck.h"
#include "MissingReturnValueHandlingCheck.h"
#include "MissingStaticInternalLinkageCheck.h"
#include "MultipleReturnStmtCheck.h"
#include "NoReturnVoidCheck.h"
#include "PreprocessorFlowCheck.h"
#include "UnstructuredSwitchCaseCheck.h"
#include "WrongOrderDefaultInSwitchStatementCheck.h"

#include "char-sets-and-lexical-convs/CharSetsAndLexicalConvsModule.h"
#include "comments/CommentsModule.h"
#include "expressions/ExpressionsModule.h"
#include "declarations-and-definitions/DeclarationsAndDefinitionsModule.h"
#include "literals-and-constants/LiteralsAndConstantsModule.h"
#include "pointer-type-conversions/PointerTypeConversionsModule.h"
#include "types/TypesModule.h"
#include "unused-code/UnusedCodeModule.h"

// using namespace clang::ast_matchers;

namespace clang::tidy {
namespace misra {

class MISRAModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {

    /* TODO: Move this and name it properly. */
    CheckFactories.registerCheck<MissingStaticInternalLinkageCheck>(
        "misra-x-Missing-Static-Internal-Linkage");
    CheckFactories.registerCheck<PreprocessorFlowCheck>("misra-x-req-20.14");

    CheckFactories.registerCheck<ImplicitIntCheck>("misra-x-req-8.1");
    CheckFactories.registerCheck<UnstructuredSwitchCaseCheck>(
        "misra-x-req-16.2");
    CheckFactories.registerCheck<AvoidMacroNamedAsCkeywordCheck>(
        "misra-x-req-20.4");

    /* 2. Unused code
    ---------------------------------------------------------------- */
    UnusedCodeModule::addCheckFactories(CheckFactories);

    /* 3. Comments
    ---------------------------------------------------------------- */
    CommentsModule::addCheckFactories(CheckFactories);

    /* 4. Character sets and lexical conversations
    ---------------------------------------------------------------- */
    CharSetsAndLexicalConvsModule::addCheckFactories(CheckFactories);

    /* 6. Types
    ---------------------------------------------------------------- */
    TypesModule::addCheckFactories(CheckFactories);

    /* 7. Literals and constants
    ---------------------------------------------------------------- */
    LiteralsAndConstantsModule::addCheckFactories(CheckFactories);

    /* 8. Declarations and defintions
    ---------------------------------------------------------------- */
    DeclarationsAndDefinitionsModule::addCheckFactories(CheckFactories);

    /* 11. Pointer type conversions
    ---------------------------------------------------------------- */
    PointerTypeConversionsModule::addCheckFactories(CheckFactories);







    /* 13.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidAssignmentInExpressionCheck>(
        "misra-c2023-adv-13.4");

    /* 14.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<cert::FloatLoopCounter>(
        "misra-c2023-req-14.1");
    CheckFactories.registerCheck<InvariantControlCheck>("misra-c2023-req-14.3");
    CheckFactories.registerCheck<AvoidNonBooleanInConditionCheck>(
        "misra-c2023-req-14.4");

    /* 15.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidGotoCheck>("misra-c2023-adv-15.1");
    CheckFactories.registerCheck<ForwardGotoLabelCheck>("misra-c2023-req-15.2");
    CheckFactories.registerCheck<MultipleReturnStmtCheck>(
        "misra-c2023-adv-15.5");
    CheckFactories.registerCheck<MissingCompoundCheck>("misra-c2023-req-15.6");
    CheckFactories.registerCheck<MissingElseCheck>("misra-c2023-req-15.7");

    /* 16.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<MissingBreakInSwitchCheck>(
        "misra-c2023-req-16.3");
    CheckFactories.registerCheck<MissingDefaultInSwitchStatementCheck>(
        "misra-c2023-req-16.4");
    CheckFactories.registerCheck<WrongOrderDefaultInSwitchStatementCheck>(
        "misra-c2023-req-16.5");
    CheckFactories.registerCheck<AvoidBooleanInSwitchCheck>(
        "misra-c2023-req-16.7");

    /* 16.2 Inspiration: m
     * caseStmt(unless(hasParent(compoundStmt(hasParent(switchStmt()))))) */

    /* 17.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidStdargHeaderCheck>(
        "misra-c2023-req-17.1");
    CheckFactories.registerCheck<misc::NoRecursionCheck>(
        "misra-c2023-req-17.2");
    CheckFactories.registerCheck<ImplicitFunctionDeclCheck>(
        "misra-c2023-man-17.3");
    CheckFactories.registerCheck<MissingReturnValueHandlingCheck>(
        "misra-c2023-req-17.7");
    CheckFactories.registerCheck<AvoidFunctionParameterModificationCheck>(
        "misra-c2023-adv-17.8");
    CheckFactories.registerCheck<NoReturnVoidCheck>("misra-c2023-req-17.10");

    /* 18.
    ---------------------------------------------------------------- */
    /* 18.7 m Inspiration:
       varDecl(allOf(hasType(arrayType(incompleteArrayType())))) 18.8 m
       Inspiration:  varDecl(allOf(hasType(arrayType(incompleteArrayType()))))
*/

    /* 19.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidUnionCheck>("misra-c2023-adv-19.2");

    /* 20.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidUndefCheck>("misra-c2023-adv-20.5");

    /* 21.
    ---------------------------------------------------------------- */
    // CheckFactories.registerCheck<AvoidStdlibMemoryCheck>(
    //     "misra-c2023-req-21.3");
    CheckFactories.registerCheck<AvoidSetjmpHeaderCheck>(
        "misra-c2023-req-21.4");
    CheckFactories.registerCheck<AvoidSignalHeaderCheck>(
        "misra-c2023-req-21.5");
    CheckFactories.registerCheck<AtoXCheck>("misra-c2023-req-21.7");
    CheckFactories.registerCheck<ExitCheck>("misra-c2023-req-21.8");

    CheckFactories.registerCheck<AvoidstdlibsystemcallCheck>(
        "misra-c2023-req-21.21");
    CheckFactories.registerCheck<AvoidStdlibRandCheck>("misra-c2023-req-21.24");

    /* ------------------------------------------------------------- */
    /* MISRA C 2012                                                  */
    /* ------------------------------------------------------------- */

    /* Directive
    ================================================================ */

    /* Rules
    ================================================================ */

    /* 13.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidAssignmentInExpressionCheck>(
        "misra-c2012-adv-13.4");

    /* 14.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<cert::FloatLoopCounter>(
        "misra-c2012-req-14.1");
    CheckFactories.registerCheck<AvoidNonBooleanInConditionCheck>(
        "misra-c2012-req-14.4");

    /* 15.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidGotoCheck>("misra-c2012-adv-15.1");
    CheckFactories.registerCheck<ForwardGotoLabelCheck>("misra-c2012-req-15.2");
    CheckFactories.registerCheck<MultipleReturnStmtCheck>(
        "misra-c2012-adv-15.5");
    CheckFactories.registerCheck<MissingCompoundCheck>("misra-c2012-req-15.6");
    CheckFactories.registerCheck<MissingElseCheck>("misra-c2012-req-15.7");

    /* 16.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<MissingDefaultInSwitchStatementCheck>(
        "misra-c2012-req-16.4");
    CheckFactories.registerCheck<WrongOrderDefaultInSwitchStatementCheck>(
        "misra-c2012-req-16.5");
  }
};

} // namespace misra

// Register the MISRA Module using this statically initialized variable.
static ClangTidyModuleRegistry::Add<misra::MISRAModule>
    X("misra-module", "Adds MISRA lint checks.");

// This anchor is used to force the linker to link in the generated object file
// and thus register the MisraModule.
volatile int MISRAModuleAnchorSource = 0;

} // namespace clang::tidy
