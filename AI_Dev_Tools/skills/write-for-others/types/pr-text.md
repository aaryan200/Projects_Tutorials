# PR description or PR comment

**Job.**
*Comment* — get one specific change made, or one specific question answered, by the person who
wrote the code and has none of this session's context.
*Description* — tell a reviewer what changed and why, so they can review it.

## Settle before drafting

- **Comment or change.** If the fix is small, making it directly may be faster than asking.
  That is the author's call, not an assumption.
- **Who wrote the code**, and their seniority relative to the author. It sets the register.
- **Where each comment attaches** — file and line, or top-level.
- **How many comments.** A long list reads as an audit; say the count when proposing.

## Rules — comments

- Short — a line or two by default. What the change is, and why it matters. That is enough.
- **Phrase a change as a proposal, not an order** — "can we…" rather than an imperative.
- No top-level summary comment unless asked for one.
- Explain the change itself, not only its consequence. The reviewer has not read the analysis.
- File paths and function names belong here — they are the address the reader needs, not
  session jargon.

## Rules — descriptions

- Short, bullet points, no fluff. Not an essay.
- Scoped to what this PR changes. Nothing extra.
- Worth including when they apply: new dependencies, new environment variables, the changed
  contract shown in a fenced block with comments marking which fields changed, and the
  priority order of the changes.
- Leave placeholders for screenshots rather than describing them.
