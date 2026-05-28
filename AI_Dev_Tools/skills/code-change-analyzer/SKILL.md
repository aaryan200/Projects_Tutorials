---
name: code-change-analyzer
description: Thoroughly review recent code changes to identify logic changes, potential bugs, security issues, and edge cases. Use when the user explicitly asks to review changes, check commits, or verify they didn't break anything. Trigger on "review my changes", "check my commit", "did I break anything", "analyze my changes". Do NOT auto-trigger after coding tasks — instead, offer the user the option to run this skill.
---

# Code Change Analyzer

Perform exhaustive analysis of code changes — logic alterations, potential bugs, security vulnerabilities, and edge cases. Since this skill runs in the main conversation, leverage any context already gathered rather than re-reading files you have already seen.

## When to Use This Skill

- User explicitly asks to review changes, check a commit, or verify they didn't break something
- User says "review my changes", "analyze my changes", "check my commit", or similar

After completing a significant coding task, do not load this skill automatically. Instead, offer it: "Would you like me to review your changes using the code change analyzer?"

## Step 1: Determine Change Scope

1. Run `git status` to check for uncommitted changes
2. If uncommitted changes exist, run `git diff` (staged and unstaged) to examine them
3. If no uncommitted changes, run `git log -1 --name-only` to identify files in the latest commit, then `git show HEAD` to examine the diff
4. Document which files were modified, added, or deleted

## Step 2: Gather Context

For every changed file, read the full file to understand the surrounding implementation — not just the diff. Then:

- Identify functions, classes, and modules that interact with the changed code
- Trace the call chain: callers of modified functions, and functions called by modified code
- Check related test files to understand expected behavior
- Check configuration files that might affect changed code behavior

Skip files you have already read in this conversation — use that existing context instead.

## Step 3: Analyze

### Logic Changes

For each change, determine:

- **Previous behavior** vs. **new behavior** — understand both completely
- **Is this a fundamental logic change?** Flag changes to:
  - Control flow (conditions, loop logic, early returns)
  - Data transformations (calculations, mappings, filtering)
  - State management (how data is stored, updated, retrieved)
  - Business rules (validation, thresholds, decision criteria)
  - Workflow sequencing (order of operations, step dependencies)

### Bug Risk

Search for these red flags:

**Type mismatches**: parameters expecting different types than provided, return type changes callers don't handle, implicit conversions that could fail, null/None handling inconsistencies

**Infinite loops**: termination conditions that might never be met, recursive calls without proper base cases, while loops with conditions that could remain true indefinitely

**Edge cases**: empty collections/strings not handled, boundary conditions (zero, negative, max values), null inputs not validated, division by zero, index out of bounds, race conditions in async code

**Logic errors**: off-by-one errors, incorrect operator usage (== vs ===, and vs or), negation errors, short-circuit evaluation side effects, exception handling that swallows important errors

### Security

Examine changes for:
- Injection vulnerabilities (SQL, command, path traversal, SSRF)
- Improper input validation
- Authentication/authorization bypasses
- Sensitive data exposure (logging secrets, returning private data)
- Insecure cryptographic practices

## Output Format

Structure the analysis as:

```
### Changes Summary
[One-line description per changed file]

### Logic Changes
For each significant logic change:
- Location: file, function/method, line numbers
- Previous behavior → New behavior
- Impact: what parts of the system this affects
- Risk: Low/Medium/High with justification

### Potential Bugs
For each identified risk:
- Issue: clear description
- Location: exact file and line
- Scenario: how this bug could manifest
- Severity: Critical/High/Medium/Low
- Fix: specific recommendation

### Security Concerns
For each issue:
- Type: category of vulnerability
- Location: where in the code
- Exploit scenario: how it could be exploited
- Fix: specific remediation steps

### Positive Observations
[Improvements, good practices, or well-handled edge cases]

### Recommendations
[Prioritized actions to take before committing/deploying]
```

## Guidelines

**Analyze what matters.** Be thorough on real risks, don't pad with trivial observations. If changes look safe, say so clearly — do not manufacture issues.

**Verify against actual code.** Always read the full file, not just the diff. When uncertain about behavior, trace through the code path manually.

**Think adversarially.** Consider both the happy path and error paths. How could this code fail? How could it be misused?

**Be specific.** Every finding should include exact file locations, line numbers, and actionable fix suggestions.

Keywords: review changes, code review, check commit, analyze changes, verify changes, did I break, review my code, change analysis
