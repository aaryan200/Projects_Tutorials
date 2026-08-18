---
name: notes-keeper
description: Answer user questions by writing the answer to a markdown file under a notes/ directory rather than replying at length in chat. Use when the user wants their questions and conversations captured as a persistent, organized notes knowledge base — questions get routed into topic subdirectories and per-topic files, follow-ups refine those same files instead of spawning new ones, and chat stays short. Supports special modes when the user asks for a "notion note" (concept refresher), an external-facing "wiki"/document, or a "tutorial".
---

# Notes Keeper

Substantive answers live in markdown files under `notes/`, not in chat. Chat stays short: it reports what changed and, for follow-ups, carries the back-and-forth.

**Purpose of `notes/`:** it captures the user↔agent conversation in a meaningful, durable form. The acid test: a cold agent with zero prior context should be able to read these files and reconstruct the entire meaningful context of what was discussed and decided.

## Hard rules

- **`notes/` is for understanding/brainstorming only.** Files inside `notes/` must **never** be referenced from the codebase — not in comments, docstrings, READMEs, or any source file. Keep the two worlds separate.
- **Answer only what was asked.** The most common failure is not fluff — it is answering four questions when one was asked. Do not pre-empt follow-ups, add "related context", or document adjacent machinery. If an adjacent point matters, offer it in chat as one line; write it only if the user takes it up.
- **No fluff, ever** (all modes). Don't restate what the user already said. If they described a situation, do **not** write "a brief on the situation" — they already know it. No greetings, no adjectives, no preamble describing what the document is about to do.
- **Prefer editing over adding.** A new file and a new `## section` are both costs. Default to revising what already exists.

## Triage — file, chat, or both

| Situation | What to do |
|---|---|
| First substantive question on a new thread of work | **Write the file.** Report path + one-paragraph summary. Don't restate the answer in chat. |
| Follow-up inside an active thread — a "why", a "what about X", a challenge, a brainstorm | **Answer in chat, briefly.** Then fold the durable outcome into the file already in play. Report which sections changed. |
| Navigational — "what did we decide about X?", "which file covers Y?" | **Chat only. Write nothing.** |
| User explicitly asks for a wiki / tutorial / notion note | **Write the file** (clarify first — those modes require it). |

"Active thread" = the file this session most recently created or updated. Once a file is in play it stays in play until the user changes subject. Not every turn is a file-writing turn.

## Routing (when writing)

1. **Ensure `notes/` exists** in the current working directory; create it if absent.
2. **Pick the topic subdirectory.** List existing subdirectories. Reuse one if the question belongs to that body of work; otherwise create a new `kebab-case` subdirectory.
3. **Pick the file — bias hard toward an existing one.** The test is *"is this the same thread of work?"*, **not** *"does some file already answer this exact question?"* A follow-up is by definition a new question and still belongs in the existing file. Create a new file only when the question opens a genuinely separate sub-topic that a reader would go looking for under its own name.
4. **Write in the active mode**, within the length budget.
5. **Report in chat:** the path, whether it was created or updated, and which `## sections` changed — one paragraph. Do not restate the answer.

## Updating a file

- Revise the affected `## sections` in place. **Delete what the new answer supersedes** — a corrected conclusion replaces the wrong one, it does not sit beside it.
- Files are allowed to shrink. A file that only ever grows is a transcript, not a note.
- Add a new `## section` only for a genuinely new sub-question. Never append a section that restates or lightly extends an existing one — merge into that one instead.
- Keep headings stable and unique within the file; chat references them by name.

## Length budgets

Ceilings in lines — tripwires, not targets. Most notes should land well under them.

| Mode | Budget |
|---|---|
| Default answer | ~80 |
| Notion note | ~60 |
| Wiki / external doc | ~150 |
| Tutorial | ~300 |

**At the budget, stop and ask.** Say what is written, what is left, and let the user decide whether to continue. Never silently overrun. If the *existing* file is already at budget, that is a signal to prune superseded content — not to start a second file.

## Modes

Default applies unless the user explicitly says "notion note", "wiki"/external doc, or "tutorial". All shareable docs still live under `notes/`.

**Default — answer the question.** The answer, its reasoning, the decision, anything ruled out. Nothing beyond that.

**Notion note — concept refresher.** Triggered by "notion note" (a note about a *notion/concept* — a refresher for someone who once knew the thing). Explain it so they can recover it. A simple or real-world example/analogy **when it helps** — not mandatory.

**Wiki / external-facing document.** Triggered when the user wants something to **show to others** — to drive a meeting or share for reading. **Clarify first, in chat, before writing:** the document's purpose, its audience, and which concepts that audience already knows vs. doesn't. If they know [a, b, c] but maybe not [x, y, z], write only [x, y, z]. **Never link to any file in `notes/`** — the audience has no access, so the document must be self-contained. Skip trivial concepts; surface only what is un-intuitive, newly discovered, interesting, or a key insight. Build the document around that narrative.

**Tutorial.** Triggered by "tutorial". **Clarify first, in chat:** what the user already knows; then explain, in detail, what they don't. Simple words; explanatory tone is permitted here. **Prefer bullet points** over long paragraphs unless prose is genuinely needed. Add an example **or** an analogy **or** a code snippet where it aids understanding — not for everything. For codebase explanations two kinds of content help: real snippets quoted from the actual codebase, and — when the real thing is complex — a simpler toy version alongside it.

## Markdown conventions

These describe **how** to format something you have already decided to include. None of them is a reason to include it. Do not add a diagram, table, or example just to satisfy this list.

- **Math**: GitHub-flavored LaTeX. Inline `$x \in \mathbb{R}^{d}$`, display `$$\text{softmax}(QK^\top / \sqrt{d_k})$$`. Annotate tensor shapes inline (e.g. `$Q \in \mathbb{R}^{B \times T \times d_k}$`).
- **Code / pseudocode**: triple-backtick fenced blocks with language tags (` ```python `, ` ```c++ `, ` ```text ` for pseudocode).
- **Diagrams**: mermaid (` ```mermaid `) when a picture genuinely beats prose; ASCII when mermaid is awkward (e.g. tensor shapes).
- **Tables**: GitHub markdown tables.
- **Headings**: `## Heading` per major block — but a short answer may legitimately have no headings at all.
- **Cross-links**: relative paths between files, e.g. `[Method overview](03-method-overview.md#data-flow)`. Exception: wiki/external documents link to nothing in `notes/`.
- **External citations**: full URL plus a one-line note on why it's there.
