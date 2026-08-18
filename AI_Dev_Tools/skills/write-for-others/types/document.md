# Wiki page, analysis report, ADR

**Job.** Get a decision or a review from people who were not in the room. The reader should
finish able to act. A decision is wanted, not a knowledge transfer.

## Settle before drafting

- **Analysis or proposal.** An analysis presents the options and lets the reader form a view;
  a proposal argues for one. Ask which.
- **Audience familiarity with this subject**, not with the field. Someone fluent in the area
  can still be new to this system.
- **Scope boundary** — what is deliberately not covered, and whether open questions are raised
  here or taken elsewhere.
- **Where it will be committed or published.**
- **How assertive the headings should be.** Where the finding is established and the reader
  needs the conclusion, headings can state it. Where the work is exploratory, or where
  appearing to over-claim would cost the author credibility, headings name what was examined
  and the claims are gathered at the end. Both are right in the right place.
- **For an architecture decision record** — is it about the target design or about what was
  built this iteration? They admit different levels of detail.

## Rules

- **Assume the reader has the project context.** Do not explain things this audience already
  knows. Skip "does X exist?" sections when writing for a lead engineer.
- **No references to internal artefacts** — file names from the working tree, section numbers,
  scratch paths, or "as we discussed earlier in the doc". The reader has none of them.
- **Do not widen scope the reader already narrowed.** If the document is about one service,
  write "in this service", not "anywhere" or "in general". Broad phrasing reads as evasive.
- **No forward-looking hedges aimed at the author** — lines like "revisit only if X changes"
  read as scratch notes. Present what is true today and stop.
- **Evidence before claims**, and mark how strong each claim is: confirmed, observed once,
  not supported, method-limited.
- Give the reader a way back to the evidence — a number, a figure, a link, a named source.
- Long sentences only where there is no alternative.

## Structure for analysing an option

When the document evaluates one approach against others, in this order:

1. What the option is
2. How it works
3. How it compares to the alternatives — presented neutrally, with no "recommended" framing yet
4. What adopting it would entail
5. Pros and cons of each approach
6. **Recommendation** — here, at the end, not in the opening and not repeated throughout
7. Caveats
8. Sources

## Channel constraints

- A platform wiki supplies the page title; omit a top-level heading in the body.
- An architecture decision record repo almost always has a house template. Read two existing
  ones and match their section names exactly.
