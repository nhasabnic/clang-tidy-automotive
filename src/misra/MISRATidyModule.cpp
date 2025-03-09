
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
#include "AvoidGotoCheck.h"
#include "AvoidLinesplicingWithinCommentCheck.h"
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
#include "CommentWithinCommentCheck.h"
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
#include "NoreturnvoidCheck.h"
#include "StaticInlineCheck.h"
#include "UncompleteFunctionPrototypeCheck.h"
#include "UniqueEnumValuesCheck.h"
#include "UnstructuredcaseCheck.h"
#include "UnterminatedEscapeSequenceCheck.h"
#include "UnusedLabelCheck.h"
#include "UnusedMacroCheck.h"
#include "UnusedObjectDefinitionCheck.h"
#include "UnusedTagCheck.h"
#include "UnusedTypeCheck.h"
#include "WrongBitfieldTypeCheck.h"
#include "WrongNullPointerValueCheck.h"
#include "WrongorderdefaultinswitchstatementCheck.h"

// using namespace clang::ast_matchers;

namespace clang::tidy {
namespace misra {

/* ----------------------------------------------------------------- */
/* MISRA Experimental support                                        */
/* ----------------------------------------------------------------- */
class MISRAExperimentalModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {

    /* TODO: Move this and name it properly. */
    CheckFactories.registerCheck<MissingStaticInternalLinkageCheck>(
        "misra-x-Missing-Static-Internal-Linkage");
  }
};

/* ----------------------------------------------------------------- */
/* MISRA C 2023                                                      */
/* ----------------------------------------------------------------- */
class MISRAC2023Module : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {

    /* Directive */
    /* ------------------------------------------------------------- */

    /* 1. Standard environment */
    /* ------------------------------------------------------------- */
    /* 1.2 */
    /* 1.3 */
    /* 1.4 */
    /* 1.5 */

    /* Unused code */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<UnusedTypeCheck>("misra-c2023-adv-2.3");
    CheckFactories.registerCheck<UnusedTagCheck>("misra-c2023-adv-2.4");
    CheckFactories.registerCheck<UnusedMacroCheck>("misra-c2023-adv-2.5");
    CheckFactories.registerCheck<UnusedLabelCheck>("misra-c2023-adv-2.6");
    CheckFactories.registerCheck<misc::UnusedParametersCheck>(
        "misra-c2023-adv-2.7");
    CheckFactories.registerCheck<UnusedObjectDefinitionCheck>(
        "misra-c2023-adv-2.8");

    /* 3. Comments */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<CommentWithinCommentCheck>(
        "misra-c2023-req-3.1");
    CheckFactories.registerCheck<AvoidLinesplicingWithinCommentCheck>(
        "misra-c2023-req-3.2");

    /* 4. Character sets and lexical conventions */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<UnterminatedEscapeSequenceCheck>(
        "misra-c2023-req-4.1");
    /* req-4.2: -Wtrigraphs */

    /* 5. Identifiers */
    /* ------------------------------------------------------------- */

    /* 6. Types */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<WrongBitfieldTypeCheck>("misra-c2023-req-6.1");
    CheckFactories.registerCheck<AvoidSignedSingleBitFieldsCheck>(
        "misra-c2023-req-6.2");
    CheckFactories.registerCheck<AvoidBitfieldsInUnionsCheck>(
        "misra-c2023-req-6.3");

    /* 7. Literals and constants */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidOctalNumberCheck>("misra-c2023-req-7.1");

    /* 8. Declarations and definitions */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<ImplicitIntCheck>("misra-c2023-req-8.1");
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

    /* 9. Initialization */
    /* ------------------------------------------------------------- */

    /* 10. The essential type model */
    /* ------------------------------------------------------------- */

    /* 11. Pointer type conversions */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<MissingBreakInSwitchCheck>(
        "misra-c2023-req-11.2");
    CheckFactories.registerCheck<WrongNullPointerValueCheck>(
        "misra-c2023-req-11.9");

    /* 11.10: Diagnostic error */

    /* 12. Expressions */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidCommaOperatorCheck>(
        "misra-c2023-adv-12.3");

    /* 13. Side effects */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidAssignmentInExpressionCheck>(
        "misra-c2023-adv-13.4");

    /* 14. Control statement expressions */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<cert::FloatLoopCounter>(
        "misra-c2023-req-14.1");
    CheckFactories.registerCheck<InvariantControlCheck>("misra-c2023-req-14.3");
    CheckFactories.registerCheck<AvoidNonBooleanInConditionCheck>(
        "misra-c2023-req-14.4");

    /* 15. Control Flow */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidGotoCheck>("misra-c2023-adv-15.1");
    CheckFactories.registerCheck<ForwardGotoLabelCheck>("misra-c2023-req-15.2");
    CheckFactories.registerCheck<MultipleReturnStmtCheck>(
        "misra-c2023-adv-15.5");
    CheckFactories.registerCheck<MissingCompoundCheck>("misra-c2023-req-15.6");
    CheckFactories.registerCheck<MissingElseCheck>("misra-c2023-req-15.7");

    /* 16. Switch Statements */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<UnstructuredcaseCheck>("misra-c2023-req-16.2");
    CheckFactories.registerCheck<MissingDefaultInSwitchStatementCheck>(
        "misra-c2023-req-16.4");
    CheckFactories.registerCheck<WrongorderdefaultinswitchstatementCheck>(
        "misra-c2023-req-16.5");
    CheckFactories.registerCheck<AvoidBooleanInSwitchCheck>(
        "misra-c2023-req-16.7");

    /* 16.2 Inspiration: m
     * caseStmt(unless(hasParent(compoundStmt(hasParent(switchStmt()))))) */

    /* 17. Functions */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidStdargHeaderCheck>(
        "misra-c2023-req-17.1");
    CheckFactories.registerCheck<misc::NoRecursionCheck>(
        "misra-c2023-req-17.2");
    CheckFactories.registerCheck<ImplicitFunctionDeclCheck>(
        "misra-c2023-man-17.3");
    CheckFactories.registerCheck<MissingReturnValueHandlingCheck>(
        "misra-c2023-req-17.7");
    CheckFactories.registerCheck<NoreturnvoidCheck>("misra-c2023-req-17.10");
    /* 18. Pointers and arrays */
    /* ------------------------------------------------------------- */
    /* 18.7 m Inspiration:
       varDecl(allOf(hasType(arrayType(incompleteArrayType())))) 18.8 m
       Inspiration:  varDecl(allOf(hasType(arrayType(incompleteArrayType()))))
*/

    /* 19. Overlapping Storage */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidUnionCheck>("misra-c2023-adv-19.2");

    /* 20. Preprocessing directives */
    /* ------------------------------------------------------------- */
    /* 20.3 clang-native: clang-diagnostic-error */
    CheckFactories.registerCheck<AvoidUndefCheck>("misra-c2023-adv-20.5");

    /* 21. Standard libraries */
    /* ------------------------------------------------------------- */
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
  }
};

/* ----------------------------------------------------------------- */
/* MISRA C 2012                                                      */
/* ----------------------------------------------------------------- */
class MISRAC2012Module : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {

    /* 1. Standard environment */
    /* ------------------------------------------------------------- */
    /* 1.1 */
    /* 1.2 */
    /* 1.3 */
    /* 1.4 */
    /* 1.5 */

    /* Unused code */
    /* ------------------------------------------------------------- */
    /* 2.1 */
    /* 2.2 */
    /* 2.3 */
    /* 2.4 */
    /* 2.5 */
    CheckFactories.registerCheck<UnusedLabelCheck>("misra-c2012-adv-2.6");
    CheckFactories.registerCheck<misc::UnusedParametersCheck>(
        "misra-c2012-adv-2.7");
    /* 2.8 */

    /* 3. Comments */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<CommentWithinCommentCheck>(
        "misra-c2012-req-3.1");
    CheckFactories.registerCheck<AvoidLinesplicingWithinCommentCheck>(
        "misra-c2012-req-3.2");

    /* 4. Character sets and lexical conventions */
    /* ------------------------------------------------------------- */
    /* req-4.2: -Wtrigraphs */

    /* 5. Identifiers */
    /* ------------------------------------------------------------- */

    /* 6. Types */
    /* ------------------------------------------------------------- */
    /* 6.1. TODO */
    CheckFactories.registerCheck<AvoidSignedSingleBitFieldsCheck>(
        "misra-c2012-req-6.2");

    /* 7. Literals and constants */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidOctalNumberCheck>("misra-c2012-req-7.1");

    /* 8. Declarations and definitions */
    /* ------------------------------------------------------------- */
    // CheckFactories.registerCheck<ImplicitIntCheck>("misra-c2012-req-8.1");
    CheckFactories.registerCheck<StaticInlineCheck>("misra-c2012-req-8.10");
    /* 8.11 m varDecl(allOf(hasType(arrayType(incompleteArrayType())),
     * hasExternalFormalLinkage())) */
    CheckFactories.registerCheck<AvoidRestrictTypeCheck>(
        "misra-c2012-req-8.14");

    /* 9. Initialization */
    /* ------------------------------------------------------------- */

    /* 10. The essential type model */
    /* ------------------------------------------------------------- */

    /* 11. Pointer type conversions */
    /* ------------------------------------------------------------- */
    /* 11.10: Diagnostic error */

    /* 12. Expressions */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidCommaOperatorCheck>(
        "misra-c2012-adv-12.3");

    /* 13. Side effects */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidAssignmentInExpressionCheck>(
        "misra-c2012-adv-13.4");

    /* 14. Control statement expressions */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<cert::FloatLoopCounter>(
        "misra-c2012-req-14.1");
    CheckFactories.registerCheck<AvoidNonBooleanInConditionCheck>(
        "misra-c2012-req-14.4");

    /* 15. Control Flow */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<AvoidGotoCheck>("misra-c2012-adv-15.1");
    CheckFactories.registerCheck<ForwardGotoLabelCheck>("misra-c2012-req-15.2");
    CheckFactories.registerCheck<MultipleReturnStmtCheck>(
        "misra-c2012-adv-15.5");
    CheckFactories.registerCheck<MissingCompoundCheck>("misra-c2012-req-15.6");
    CheckFactories.registerCheck<MissingElseCheck>("misra-c2012-req-15.7");

    /* 16. Switch Statements */
    /* ------------------------------------------------------------- */
    CheckFactories.registerCheck<UnstructuredcaseCheck>("misra-c2012-req-16.2");
    CheckFactories.registerCheck<MissingDefaultInSwitchStatementCheck>(
        "misra-c2012-req-16.4");
    CheckFactories.registerCheck<WrongorderdefaultinswitchstatementCheck>(
        "misra-c2012-req-16.5");
  }
};

} // namespace misra

// Register the MISRA Experimental Module using this statically initialized
// variable.
static ClangTidyModuleRegistry::Add<misra::MISRAExperimentalModule>
    X("misra-x-module", "Adds MISRA experimental lint checks.");

// Register the MISRA C2023 Module using this statically initialized variable.
static ClangTidyModuleRegistry::Add<misra::MISRAC2023Module>
    Y("misra-c2023-module", "Adds MISRA C 2023 lint checks.");

// Register the MISRA C2023 Module using this statically initialized variable.
static ClangTidyModuleRegistry::Add<misra::MISRAC2012Module>
    Z("misra-c2012-module", "Adds MISRA C 2012 lint checks.");

// This anchor is used to force the linker to link in the generated object file
// and thus register the MisraModule.
volatile int MISRAModuleAnchorSource = 0;

} // namespace clang::tidy
