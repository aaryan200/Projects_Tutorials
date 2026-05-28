---
name: research-paper
description: Generate structured, GitHub-ready markdown notes that walk through a research paper phase-by-phase the way a human expert would explain it — pitch, contribution, method overview, method mechanics, experiments, critique, and connections. Creates a per-paper directory, saves the PDF alongside the notes, and writes one markdown file per phase or topic using LaTeX math, mermaid diagrams, and fenced code blocks. Output goes to files, not chat — the chat is only a navigation layer that tells the user which file was written/updated and where to look. Use when the user shares a paper (PDF path, arXiv link, URL), asks to "explain", "walk me through", "deep dive into", "break down", "study", or "deconstruct" a paper, or asks any substantive question about a paper they have already loaded.
---

# Research Paper Deep-Dive

## Operating principle

The artifact is a directory of markdown files the user can push to GitHub and re-read later. The chat window is a navigation interface only: every substantive response writes or updates a file, then tells the user which file and section to look at. Do not dump long explanations into chat.

## What the skill does, in order

1. **Read the paper.** Local PDF → Read tool. arXiv/URL → WebFetch (or `curl` to fetch the raw PDF if WebFetch only returns rendered text). If you cannot access it, stop and ask.
2. **Generate a slug** from the paper title (e.g., "Attention Is All You Need" → `attention-is-all-you-need`). Show it to the user, allow rename.
3. **Create the directory** under the current working directory. If it already exists, read its `README.md` and resume (do not overwrite).
4. **Save the PDF** into the directory as `paper.pdf`:
   - URL given → download (WebFetch / `curl -L -o paper.pdf <url>`).
   - Local file path given → **move** (not copy) into the directory.
5. **Ask calibration questions** (skip any that are obvious from context):
   - Familiarity with the subfield (new / comfortable / expert)
   - Goal (understanding / implementing / reviewing / building on)
   - Depth preference (full mechanics vs. conceptual only)
   - Time budget (one sitting / spread across sessions)
6. **Write `README.md`** — paper metadata, source link, calibration answers, and an index of phase files.
7. **Run phase-by-phase**, writing one file per phase. Pause for the user after each phase.

## Directory layout

```
<paper-slug>/
├── paper.pdf
├── README.md                  # Index, metadata, calibration answers
├── 01-pitch.md
├── 02-contribution.md
├── 03-method-overview.md
├── 04-method-mechanics.md     # Single file, or split into 04-components/
├── 04-components/             # Optional; one file per major sub-component
│   └── <component>.md
├── 05-experiments.md
├── 06-critique.md
├── 07-connections.md
├── background/                # Optional; primers on prerequisite concepts the paper assumes
│   └── <concept>.md
├── glossary.md                # Symbols, jargon, and defined terms used by the paper
└── questions.md               # Ad-hoc Q&A log for anything that doesn't fit a phase file
```

Skip phases or files that don't apply to this paper. Add component files when Phase 4 has multiple major pieces. Add background files when the paper assumes concepts the user hasn't met.

## The seven phases

| # | Phase | What it answers | File |
|---|---|---|---|
| 1 | **Pitch** | Problem, why it matters, core idea, headline result | `01-pitch.md` |
| 2 | **Contribution & positioning** | What's new vs prior work; named contributions; lineage | `02-contribution.md` |
| 3 | **Method overview** | Block-diagram-level data flow; no precise formalism | `03-method-overview.md` |
| 4 | **Method — detailed mechanics** | Precise details — *math, pseudocode, architecture, dimensions* — whichever the paper actually uses | `04-method-mechanics.md` |
| 5 | **Experiments** | Setup, baselines, ablations, what numbers actually show | `05-experiments.md` |
| 6 | **Critique** | Limitations, hand-waving, reproducibility, missing comparisons | `06-critique.md` |
| 7 | **Connections** | Prior work, follow-ups, implementation path, cost | `07-connections.md` |

**Phase 4 is not math-only.** Pick the right registers for the paper:
- ML / math-heavy → equations with shape annotations and per-operation intuition
- Algorithmic → pseudocode, complexity, data structures
- Systems → component decomposition, interfaces, interactions, sequence diagrams
- Empirical / measurement → methodology details, instruments, sampling design
- Theory → assumptions → lemmas → theorem → corollaries

Most papers blend several. Name what you're doing in the file's section headings.

## Chat response pattern

After writing or updating a file, your chat message should be three short lines:

> **Wrote** `<paper-slug>/<file>.md` (or **Updated** `…` — section `<heading>`).
> **Look at**: `## <section heading>` (or `paragraph 2`, `Table 1`, etc.).
> **Next**: continue to `<next phase>.md`, drill into `<component>`, or ask a follow-up.

That's it. No re-explaining the content. The file is the artifact.

For meta / workflow questions ("what phase are we on?", "should I read experiments first?"), answer in chat directly without writing a file.

## Handling user questions

Every substantive question (about the paper, a component, a concept, an experiment) must result in a file write or update:

- **Clarification on an existing phase** → update the phase file in place. Insert or append; never overwrite prior content.
- **Side topic or new component of the paper** → new file (component file under `04-components/`, or a topic file at the root). Link it from `README.md`.
- **New term or symbol used in the paper** → add to `glossary.md` and link from the place it first appeared.
- **Prerequisite concept the paper assumes but doesn't explain** (e.g., the user asks "what is contrastive learning?" while reading a paper that builds on it) → create `background/<concept>.md` with a self-contained primer. Link it from `README.md` under a `## Background primers` section and from the first place in a phase file where the concept appears. This keeps the paper notes clean while making the prerequisite material reachable.
- **Move forward** → write the next phase file.

Preserve everything the user has accumulated. When in doubt, append.

If calibration revealed low familiarity with the subfield, proactively offer to write background primers before or during each phase rather than dropping unfamiliar jargon into phase files.

## Markdown conventions for files

- **Math**: GitHub-flavored LaTeX. Inline `$x \in \mathbb{R}^{d}$`, display `$$\text{softmax}(QK^\top / \sqrt{d_k})$$`. Always annotate tensor shapes inline (e.g., `$Q \in \mathbb{R}^{B \times T \times d_k}$`).
- **Code / pseudocode**: triple-backtick fenced blocks with language tags (` ```python `, ` ```c++ `, ` ```text ` for pseudocode).
- **Diagrams**: prefer mermaid (` ```mermaid `) for flowcharts, sequence diagrams, component graphs. Fall back to ASCII when mermaid is awkward (e.g., a tensor-shape diagram).
- **Tables**: GitHub markdown tables for ablations and comparisons.
- **Section headings**: `## Heading` for every major block. Chat messages reference these by name, so headings must be stable and unique within a file.
- **Cross-links**: link between files with relative paths (e.g., `[Method overview](03-method-overview.md#data-flow)`).
- **Citations to the paper**: cite section/figure/table (`§3.2`, `Figure 4`, `Table 2`).
- **External citations**: full URL plus a one-line note on why it's there.

## Component drill-down

When the user asks about a specific component (e.g., "explain multi-head attention"):

- If the component is a major sub-system → create `04-components/<slug>.md`
- Use the canonical internal template (see REFERENCE.md): **intuition → purpose → data flow with shapes → mechanics → worked numeric/concrete example → caveats and variants**
- For numeric/shape examples in ML papers: plug in concrete numbers (e.g., `B=2, T=128, d=512, d_k=64`) and trace shapes through every operation.

## Critique mode and external research

**Default Phase 6** uses only the paper. Surface, with citations to the paper:
- Claims that outrun the visible evidence
- Conspicuously missing baselines or ablations
- Hand-waving in derivations or experimental design
- Hyperparameter / compute / data asymmetries
- Headline numbers within noise on a single seed
- Disclosure gaps (no code, no hyperparameters, no compute info)

**Deep critique** (triggered by "critique mode", "be a tough reviewer", "search externally", "what are people saying", "play devil's advocate", "is this actually true", "what would a reviewer reject this for"): go outside the paper. The user invoking critique mode **is** the permission — do not re-ask.

1. Announce in chat what you're searching and why (one short line). Typical targets:
   - `"<paper title>" criticism` / `"<paper title>" reproducibility` / `"<paper title>" failed to replicate`
   - OpenReview entry if the venue is OpenReview-based (ICLR / NeurIPS / TMLR / COLM)
   - Papers With Code for replication numbers and community-reported gaps
   - Follow-up papers that revise, extend, or challenge the claims
   - The authors' subsequent work — did they walk back any claim?
   - Retraction databases for medical / social-science papers
   - Discussions on Twitter/X, AlphaXiv, Hacker News (treat as low-trust signal pointing at sources to verify, never as evidence on their own)
2. Use WebSearch / WebFetch. Be thorough — don't stop after one query. Triangulate.
3. Cite every external source with URL in the file.
4. Update `06-critique.md` with two clearly separated sections: `## From the paper alone` and `## From external sources` — never blend them.

The goal: if the authors buried or excluded unflattering details, this file should still give the user the truthful picture. Be evidence-first. Never assert "overhyped" without a cited basis. If a claim cannot be checked externally, say so explicitly.

For non-critique phases, only go external when the user explicitly asks ("look up the related work", "what is X" where X is a prerequisite concept outside the paper). Announce the search in one line, then run it.

## Resuming prior sessions

Before doing anything else, check whether `<slug>/` already exists in the working directory:
- Read its `README.md` for calibration answers and metadata
- Scan the existing phase files to see what's been written
- Tell the user in chat what's already in place and offer to continue, redo, or branch

Never overwrite without explicit confirmation.

## What not to do

- Don't dump long explanations in chat. Files are the artifact; chat is the navigation layer. If you find yourself writing more than ~3 lines of paper content in chat, stop and move it to a file.
- Don't overwrite existing notes. Append, insert, or create a sibling file.
- Don't pull external sources silently. Announce in one line what you're searching and why, then run; always cite the URL in the file.
- Don't recommend the paper as "great" or otherwise vouch for it. Present evidence; let the user judge.
- Don't write notes the user didn't ask for. After each phase or question, stop and offer the next action.
- Don't paste long verbatim chunks of the paper. Paraphrase; quote only when wording matters (definitions, exact claims).
- Don't invent details the paper doesn't have. If the paper is silent on something, say so in the file and (if relevant) flag it as a disclosure gap in the critique.

See [REFERENCE.md](REFERENCE.md) for: per-phase file templates, math notation conventions, the full critique checklist, paper-type adaptations (theory / systems / empirical / survey / position), slug generation rules, and starter file skeletons.
