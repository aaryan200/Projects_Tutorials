---
name: write-for-others
description: Draft or revise anything that will be read by someone who was not in this conversation — wiki page, analysis report, design doc, RFC, one-pager, ADR, MS Teams or Slack message, PR description or PR comment, issue-tracker story or task, status or standup update, release notes, email, or a document shown on a call. Use when the user says any of - draft a message, what should I say to X, write this up for the team, summarise what we did for X, create a wiki page or report or design doc or ADR, turn this into a ticket, create a story or tasks or an issue, add a PR comment, update the PR description, reply to a review comment, post an update in the channel, write my status update, something I can show on a call, make a deck. Use it for revising one of these that already exists, not only for new ones. Do not use it for code, code comments, docstrings, commit messages, a snippet the user is pasting into a terminal or config file, or anything the user is writing only for themselves.
---

# Write for others

Two things are true of every reader and are never worth recording about one of them:
**they were not in this conversation**, and **they will not decode a term you have not
explained**.

This file holds the procedure and the author's standing preferences, which travel across
projects. **Project-specific rules are not here** — banned words, local naming, one repo's
conventions — those stay in that project's `CLAUDE.md` or memory.

**Precedence**, highest first: project `CLAUDE.md` or memory → the type file → `context/map.md`
→ this file → the user-level `CLAUDE.md`. `map.md` is observation and can be stale; a type file
is a rule. Where this file and the user-level `CLAUDE.md` say the same thing, they are meant to;
flag the duplicate so one can be removed.

**Always attach your recommended answer to a question.** Never hand back a question you could
have answered, and never present a choice without saying which you would take and why. This
holds on every path, including when a check finds something that conflicts with the brief.

## Before you start

1. Read `context/map.md`, which sits **in this skill's own directory**, next to this file —
   not in the project being worked on. It holds who the audiences are, what they already know,
   and the house shape of each destination, so the same questions are not asked twice. If it
   is missing, say so once and gather as you go. Treat any entry marked unconfirmed as a lead,
   not a fact.
2. Classify the artifact and open its file from the table at the end.
3. Pick the path and say which one you are on and why, in one line.

Calibrate on **how much of the brief you can already establish**, not on how long the artifact
will be.

| Path | When | What runs |
|---|---|---|
| **Direct** | Almost everything is derivable — you have the session, the map covers the reader, a sibling shows the shape | State the brief in three lines, get a yes, draft, self-check |
| **Standard** | Real gaps: unfamiliar reader, unclear purpose, contested content, or granularity that is the user's call | Everything below |
| **Rush** | The user says there is no time, or "just draft it" | Type file and map still apply. Draft from what is known, list every assumption made, self-check. No grill, no plan, no reader test. |

A short artifact is not automatically Direct. A six-line reply that takes a position on a
contested point has more open than a long write-up of work just finished.

## 1. Settle the brief

The brief:

- **Reader** — who, and what they already know about *this subject*
- **Job** — what they should decide, do, or believe after reading
- **Channel** — where it lands; also decides whether it gets committed or published
- **Genre** — analysis, proposal, result summary, status, request, or decision record
- **Out of scope** — what not to raise here
- **Size** — target length, in whatever unit the channel uses

**Fill in everything you can before asking anything.** The map, the session, the repo, and a
sibling artifact at the destination answer most of it. A type file's "settle" list is things
to establish, not things to ask.

**Then invoke `grill-me` on what is left**, passing it a frame in the arguments, because its
own wording assumes a code plan. The frame must state: that this is an artifact for a named
reader, not a design; that the branches below and the type file's settle list are the tree;
that the answers live in the map, the transcript, the destination and its siblings, **not** in
the codebase; what is already settled; and that it should stop once the open items are
resolved rather than continuing indefinitely.

Branches. The first three always apply. The last two only when their trigger holds — say which
you skipped and why. **Add every unresolved item from the type file's settle list**; those are
usually the ones nothing else can answer.

- **Reader** *(always)* — who exactly; what they know about this subject; **what they
  currently believe that is wrong**; their history with this topic; who else will see it
- **Purpose** *(always)* — what they decide or do afterwards; what happens if they do nothing
- **Shape** *(always)* — read alone or talked through; what is out of scope
- **Ownership** *(when the artifact describes, credits, or reports on work — skip for a pure
  question or request)* — whose work this touches; anything that would read as overselling
- **Evidence** *(when it makes a claim the reader might act on or challenge — skip for a
  request, a scheduling note, or a question)* — which claims need backing; how strong each is;
  what cannot be supported yet

For a persuasive or contested artifact, also resolve what the reader will object to and the
first question they will ask. Skip both for routine or administrative ones.

**Show the filled brief and get a yes before planning.** Six lines. This is the last cheap
moment to correct the reader or the genre.

**Where things are saved.** If the artifact is a file, write the brief to
`notes/<topic>/<name>.brief.md` and the draft to `notes/<topic>/<name>.md`, both **under the
current working directory** — the project being worked on, not the skill directory — and
report both paths. If it is text to be pasted elsewhere (a message, a comment, most work
items), keep both in the conversation and write nothing to disk.

**Keep the map current.** When an answer corrects or adds to `context/map.md`, offer to update
it. Record what people know and need, never an opinion of them.

## 2. Plan

Show the shape and get a yes.

- **Document** — the headings, one line each on what goes under them
- **Work items** — the full set as titles, one line each. Granularity is settled here
- **Presentation** — the points, each marked with where it goes
- **Message, short comment** — no plan stage

Structural rework is cheap here and expensive later.

## 3. Draft

**One batch at a time, with a hard stop between batches.** A batch is self-contained,
reviewable in one pass, and a coherent step — a section or two of a document, a slide group.
A small complete set, such as four work items, is one batch.

Before showing a batch, run the self-checks in step 4 on it. What you show is finished, so
nothing you have already approved gets rewritten later.

After each batch: show it, say what it covers, and **end the turn**. Do not start the next
batch until the user says to continue. This holds even when the plan was approved upfront,
even when the next batch looks small, and even when the skill was invoked from a workflow that
otherwise runs continuously. Skipping the stop produces exactly the big unreviewable draft
this procedure exists to prevent.

If the user says up front to write the whole thing without stopping, confirm that reading
before starting rather than assuming it.

### How it reads

Defaults for every type; a type file may override any of them.

- **Plain, everyday English.** Common words, short sentences. The author is a non-native
  speaker and uncommon or ornamental words slow them and their readers down.
- **Bullets, not paragraphs.** One idea per bullet, about two lines.
- **Crisp is about words, not content.** Cutting words is right; cutting the explanation that
  makes a point land is not. If a reader could not follow it, it is too short.
- **Do not oversell.** No enthusiasm the evidence does not support. An observation is not a
  proof — say which it is. Describe what was actually done, including work that was adapted or
  ported rather than built.
- **Plain headings.** Modest and descriptive, not slogans.

## 4. Self-check — every batch, before showing it

No subagent. You reading your own text against three rules.

**Vocabulary.**

- *Terms coined in this conversation do not survive.* Invented names, and labels that only
  index this session — numbered options, case ids, section shorthand. Replace each with what
  it means. Run this every time: the set differs in every session, so a remembered list is
  worthless. Two exceptions: a coined term that is becoming the real name of a thing may stay
  if defined on first use, and a term the reader introduced always stays.
- *Identifiers survive only if this reader can use them.* A file path, function name, run id
  or metric is worth keeping when the reader can open it, check it, or act on it. It is noise
  when they cannot — say what the thing does instead. Any number needs enough context to know
  what was measured and against what.

Expanding a term makes the text longer. That is right, and the size target gives way to it.

**Sensitivity.** Drafting pulls material out of the transcript, so check the written text, not
just the plan: credentials, tokens, customer data, internal identifiers, names of people who
are not party to the artifact. Raise anything questionable rather than deciding alone.

**Against the brief.** Does this batch move the reader toward the job? Is anything present
that they already know, or outside the stated scope? Is every claim traceable to this session
or the repo — nothing carried in from memory, from inference, or from another project and
stated as established?

Verify the property the user asked for, not a proxy for it. "Bullets" means one idea per
bullet; a page of dash-prefixed paragraphs passes the proxy and fails the request.

## 5. Reader test — once, when the artifact is complete

Skip on Direct and Rush, and for anything under roughly twenty lines.

Start a fresh subagent — not a fork, which inherits this conversation. Give it **the draft
alone** and ask what it assumes the reader already knows, what has no antecedent or reads two
ways, and what contradicts itself. Then give it the brief's job line and ask whether a reader
could do that job from the artifact. Keeping the brief out of the first question is what makes
it a cold read.

Report what it found with your recommended fix for each. Where a finding conflicts with the
agreed brief, say so, say which you would follow and why, and let the user decide.

## 6. Hand over

Report the paths, or the text, and what it contains.

**Creating the thing** — the wiki page, the work item, the PR comment — happens only when the
user asked for it to be created, and only after they have seen the draft and said yes. A
request to write something *for* a destination is an instruction to draft; a request to
create, post, or file it is an instruction to publish, still gated on approval of the draft.
Never create anything that was not asked for.

## Revising

**A draft from this session.** Apply the change, rerun the self-checks on what changed, show
it. Do not re-establish the brief and do not ask which artifact is meant.

**Something already published.** Fetch the current version; if you cannot reach it, ask for
the text or a link. There is usually no brief and building one is not worth it — ask what is
wrong with the part named, if the request does not say. Change only that. Skip the plan stage
and the sibling read. Rerun the self-checks on what changed; rerun the reader test only if the
change alters what the artifact argues. Hand over the new text, what changed, and what you
left alone.

## Artifact types

| Artifact | File |
|---|---|
| Wiki page, report, design doc, RFC, ADR | [types/document.md](types/document.md) |
| Team chat message | [types/chat-message.md](types/chat-message.md) |
| Issue-tracker story, task, or issue | [types/work-item.md](types/work-item.md) |
| PR description or PR comment | [types/pr-text.md](types/pr-text.md) |
| Slide plan, or a document talked through on a call | [types/presentation.md](types/presentation.md) |

A document that will also be presented is both. Settle and structure it as a document; apply
`presentation.md` only to what goes on screen and how it is delivered.

Type not listed — email, release notes, an onboarding page, a status update, anything else:
run this same procedure, ask what shape the reader expects, and find a sibling artifact to
match. Do not force it into the nearest row.

See [EXAMPLE.md](EXAMPLE.md) for one worked pass.
