---
name: solution-explorer
description: Works through a technical or design problem by first figuring out what general type of problem it is, then listing a few different ways to solve it with the pros, cons, and practical costs of each, so the user can choose instead of just taking the first idea that works. Use when the user asks "how do I solve / build / design this", is comparing approaches, or wants the best way to build something.
---

# Solution Explorer

## Quick start
When someone asks "how do I solve / build X", don't just give the first idea that works. Work through the steps below and give back a short summary: what general type of problem this is, two or three different ways to solve it, the main trade-off between them, and which one you'd pick and why. Leave the final choice to the user.

## Steps
1. **Say the problem in general terms.** Drop the project-specific words and describe what's really being asked. Example: instead of "remember a user's past tax decisions", say "save useful patterns from past records and reuse them on new ones". This makes it easier to research and reason about.
2. **Figure out what type of problem it is.** Most problems are a version of a known one (caching, search, recommendations, keeping a saved result up to date, and so on). This step matters most: if you get the type wrong, every solution after it is wrong too. Say the type out loud and check that it really fits.
3. **List the known ways to solve that type.** Once you know the type, the common solutions are already well known. List them instead of inventing from scratch.
4. **Pick two or three that are actually different.** Not small variations, but options on opposite sides of the main trade-off. Say what that trade-off is (for example: do the work fresh every time, vs. do it once and save the result, trading freshness for speed).
5. **For each option, cover the practical side.** Where it runs, what stores the data, what it costs, what breaks when things get big, and who needs to agree to it. This is usually where a "simple" option turns out to be not so simple.
6. **Summarize and recommend.** Give the trade-off, the options with their pros and cons, and the one you'd pick with a reason. Also give the best argument against your pick, so the user can defend the choice.

## Example
Problem: "remember a user's past decisions so we can reuse them on new cases".
- Type: keeping a saved result up to date instead of recalculating it.
- Trade-off: work it out fresh each time, vs. work it out once and save it.
  - Fresh each time: simple, always current, no extra storage, but slow and expensive as data grows.
  - Save it (a small job that updates the saved patterns now and then): fast and scales, but needs storage, something to run the job, an owner, and team agreement.
- Which one wins depends on how often it's read and how fresh it needs to be, not on which is quickest to build.

## Avoid
- Taking the first idea that works before looking at others.
- Choosing an option just to dodge its hard practical questions.
- Dumping everything you found instead of naming two or three real options.
- Giving one answer with no trade-off, which can't be defended or adjusted later.
