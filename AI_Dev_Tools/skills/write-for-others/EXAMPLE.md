# One worked pass

This shows the shape of the exchange, not what a good artifact looks like.

**Request:** after a long debugging session, *"write this up for the team wiki"*.

**Derived without asking** — channel (the wiki linked in the README, four pages to match);
genre (result summary — the cause is settled, so this is not an analysis of options); size
(the existing pages run 100–200 lines).

**Seven things were open, four could be asked.** Asked: who reads it; whether they already
know the caching layer exists; whether the fix is agreed or still proposed; whether the
unrelated capacity problem found on the way belongs here. Stated as assumptions instead, for
correction: that the page is new rather than replacing an existing one; that no runbook change
is wanted; that the incident timeline can be a table.

Each question carried a recommendation. Two lines came back. The brief went to
`notes/service-restarts/oom-root-cause.brief.md`, the draft to
`notes/service-restarts/oom-root-cause.md`.

**What the passes caught**

- *Vocabulary* — the session had been calling one failure mode by an invented shorthand for
  two days; replaced with a description of what happens. Two run ids were kept, because the
  reader can open them. Three file paths were cut, because the reader is not in the repo.
- *Reader test* — a fresh agent could not tell which of two services the recommendation
  applied to, and found a pronoun with no antecedent.
- *Against the brief* — a paragraph explained the caching layer, which question two had
  established the audience owns. Cut.

**Handed over** — both paths, one line on what the draft contains, and a note that the wiki
page had not been created. It was published two days later, on a separate instruction.
