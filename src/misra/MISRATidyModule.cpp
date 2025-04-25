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
#include "AvoidAtomicVoidPointerCheck.h"
#include "AvoidBitfieldsInUnionsCheck.h"
#include "AvoidBooleanInSwitchCheck.h"
#include "AvoidCommaOperatorCheck.h"
#include "comments/AvoidCommentWithinCommentCheck.h"
#include "AvoidFunctionParameterModificationCheck.h"
#include "AvoidGotoCheck.h"
#include "comments/AvoidLinesplicingWithinCommentCheck.h"
#include "AvoidLowercaseLiteralSuffixCheck.h"
#include "AvoidMacroNamedAsCkeywordCheck.h"
#include "AvoidNonBooleanInConditionCheck.h"
#include "AvoidOctalNumberCheck.h"
#include "AvoidRestrictTypeCheck.h"
#include "AvoidSetjmpHeaderCheck.h"
#include "AvoidSignalHeaderCheck.h"
#include "AvoidSignedSingleBitFieldsCheck.h"
#include "AvoidStdargHeaderCheck.h"
#include "AvoidStdlibMemoryCheck.h"
#include "AvoidStdlibRandCheck.h"
#include "AvoidUndefCheck.h"
#include "AvoidUnionCheck.h"
#include "AvoidstdlibsystemcallCheck.h"
#include "ExitCheck.h"
#include "ForwardGotoLabelCheck.h"
#include "FunctionDeclarationMismatchCheck.h"
#include "ImplicitFunctionDeclCheck.h"
#include "ImplicitIntCheck.h"
#include "InvariantControlCheck.h"
#include "MissingBreakInSwitchCheck.h"
#include "MissingCompoundCheck.h"
#include "MissingDefaultInSwitchStatementCheck.h"
#include "MissingElseCheck.h"
#include "MissingExternalArraySizeCheck.h"
#include "MissingReturnValueHandlingCheck.h"
#include "MissingStaticInternalLinkageCheck.h"
#include "MultipleReturnStmtCheck.h"
#include "NoReturnVoidCheck.h"
#include "PreprocessorFlowCheck.h"
#include "StaticInlineCheck.h"
#include "UncompleteFunctionPrototypeCheck.h"
#include "UniqueEnumValuesCheck.h"
#include "UnstructuredSwitchCaseCheck.h"
#include "UnterminatedEscapeSequenceCheck.h"
#include "WrongBitfieldTypeCheck.h"
#include "WrongNullPointerValueCheck.h"
#include "WrongOrderDefaultInSwitchStatementCheck.h"

#include "comments/CommentsModule.h"
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

    /* ------------------------------------------------------------- */
    /* MISRA C 2023                                                  */
    /* ------------------------------------------------------------- */

    /* Directive
    ================================================================ */

    /* Rules
    ================================================================ */

    /* 1.
    ---------------------------------------------------------------- */

    UnusedCodeModule::addCheckFactories(CheckFactories);
    CommentsModule::addCheckFactories(CheckFactories);

    /* 3.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidCommentWithinCommentCheck>(
        "misra-c2023-req-3.1");
    CheckFactories.registerCheck<AvoidLinesplicingWithinCommentCheck>(
        "misra-c2023-req-3.2");

    /* 4.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<UnterminatedEscapeSequenceCheck>(
        "misra-c2023-req-4.1");
    /* req-4.2: -Wtrigraphs */

    /* 5.
    ---------------------------------------------------------------- */

    /* 6.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<WrongBitfieldTypeCheck>("misra-c2023-req-6.1");
    CheckFactories.registerCheck<AvoidSignedSingleBitFieldsCheck>(
        "misra-c2023-req-6.2");
    CheckFactories.registerCheck<AvoidBitfieldsInUnionsCheck>(
        "misra-c2023-req-6.3");

    /* 7.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidOctalNumberCheck>("misra-c2023-req-7.1");
    CheckFactories.registerCheck<AvoidLowercaseLiteralSuffixCheck>(
        "misra-c2023-req-7.3");

    /* 8.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<UncompleteFunctionPrototypeCheck>(
        "misra-c2023-req-8.2");
    CheckFactories.registerCheck<FunctionDeclarationMismatchCheck>(
        "misra-c2023-req-8.3");
    CheckFactories.registerCheck<StaticInlineCheck>("misra-c2023-req-8.10");
    CheckFactories.registerCheck<MissingExternalArraySizeCheck>(
        "misra-c2023-adv-8.11");
    CheckFactories.registerCheck<UniqueEnumValuesCheck>("misra-c2023-req-8.12");
    CheckFactories.registerCheck<AvoidRestrictTypeCheck>(
        "misra-c2023-req-8.14");

    /* 9.
    ---------------------------------------------------------------- */

    /* 10.
    ---------------------------------------------------------------- */

    /* 11.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<MissingBreakInSwitchCheck>(
        "misra-c2023-req-11.2");
    CheckFactories.registerCheck<WrongNullPointerValueCheck>(
        "misra-c2023-req-11.9");

    /* 12.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidCommaOperatorCheck>(
        "misra-c2023-adv-12.3");

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

    /* 1.
    ---------------------------------------------------------------- */

    /* 2.
    ---------------------------------------------------------------- */


    /* 4.
    ---------------------------------------------------------------- */
    /* req-4.2: -Wtrigraphs */

    /* 5.
    ---------------------------------------------------------------- */

    /* 6.
    ---------------------------------------------------------------- */
    /* 6.1. TODO */
    CheckFactories.registerCheck<AvoidSignedSingleBitFieldsCheck>(
        "misra-c2012-req-6.2");

    /* 7.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidOctalNumberCheck>("misra-c2012-req-7.1");

    /* 8.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<StaticInlineCheck>("misra-c2012-req-8.10");
    /* 8.11 m varDecl(allOf(hasType(arrayType(incompleteArrayType())),
     * hasExternalFormalLinkage())) */
    CheckFactories.registerCheck<AvoidRestrictTypeCheck>(
        "misra-c2012-req-8.14");

    /* 9.
    ---------------------------------------------------------------- */

    /* 10.
    ---------------------------------------------------------------- */

    /* 11.
    ---------------------------------------------------------------- */
    /* 11.10: Diagnostic error */

    /* 12.
    ---------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidCommaOperatorCheck>(
        "misra-c2012-adv-12.3");

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
