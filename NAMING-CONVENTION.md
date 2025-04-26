# Naming Convention for Check Classes

This project follows a clear and descriptive naming convention for `clang-tidy` check classes.  
Each check is implemented in a C++ class whose name indicates **what the check detects**, rather than its MISRA rule ID. This makes the code easier to navigate, understand, and maintain.

## Prefixes Used

We use the following prefixes to categorize the nature of the issue:

- **Avoid**: Something that should not be done  
  _Example_: `AvoidCommentWithinCommentCheck`
- **Missing**: Something important is absent  
  _Example_: `MissingDefaultCaseCheck`
- **Wrong**: Something is incorrect or violates a specific constraint  
  _Example_: `Wrong TBD`
- **Unstructured**: Formatting, layout or structure is unclear or inconsistent  
  _Example_: `Unstructured TBD`

These prefixes help contributors quickly grasp the intent of each check.

## Separation of Rule ID and Class Name

Although each check maps to one or more **MISRA rule IDs**, the class name does **not** include that ID.  
Instead, the rule ID is used when registering the check:

``cpp
CheckFactories.registerCheck<AvoidCommentWithinCommentCheck>("misra-c2023-req-3.1");


## Benefits of This Approach

* Clarity in Code: Developers don't need to memorize rule IDs to understand the code.
* Clarity in Configuration: Users can configure .clang-tidy using the official rule IDs.
* Compliance-Friendly: Keeps configuration and tooling consistent with regulatory guidelines.
* Scalability: Encourages modularity and reuse across different MISRA versions.

## When Adding a New Check

1. Name the class descriptively using one of the prefixes above.
2. Keep the filename identical to the class name (e.g. AvoidSomethingCheck.{h,cpp}).
3. Register the check with the appropriate MISRA rule ID(s).
4. Add it to the appropriate module (comments, unused-code, etc).

