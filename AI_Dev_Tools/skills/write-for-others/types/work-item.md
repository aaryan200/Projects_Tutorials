# Issue-tracker story, task, or issue

**Job.** Make the work visible and trackable to people outside the session, and keep whatever
accounting the team runs on it correct.

## Settle before drafting

- **Item type** — story, task, bug, issue. It decides which fields are required.
- **Granularity.** A task is a unit of work someone could pick up and own — not an entry from
  the transcript. Mapping what happened onto items is a reduction, and how far to reduce is
  the author's call. Propose a count with reasoning.
- **Scope boundary.** Which parts belong to a later item instead. Rarely derivable.
- **Sizing.** Estimation scales are team-specific. Read sibling items in the same board area
  and calibrate against them; ask only if the siblings do not settle it.
- **State, assignee, parent, and where it lands** on the board.

Read one existing sibling item before asking anything. It usually answers item type, sizing,
required fields, and how acceptance criteria are formatted.

## Rules

- **Write for someone with no context of the conversation.** Describe the outcome and the
  requirement being met. A board reader is usually not in the repo, so class names, tool
  names, and paths are noise there — say what the thing does instead.
- **Keep the description high level.** What was done, not how the session got there.
- **Describe what actually happened.** Work that was ported, adapted or partly reused is
  described that way. Do not invent a deliverable to round out a list.
- Match the destination's house style — read a sibling item. Some boards run short
  problem/context prose rather than bullets. Where the siblings settle it, they win; where
  they do not, brief bullet points.
- Group by outcome. An item named after a single component is almost always too small.
- An acceptance criterion paired with how to verify it is stronger than one on its own.

## Required fields

Never leave a required field blank, and never silently guess one. Propose values with the
draft so a single approval covers them.

Which fields are required depends on the tracker and its process template — read a sibling
item rather than assuming.

**Azure DevOps**, the author's current tracker:

- Tasks carry both an estimate and completed work. For a new active task the estimate is the
  forecast and completed work is zero; for a closed task completed work is the actual time.
- Stories carry story points, commonly on a Fibonacci scale, but calibrate against siblings
  rather than trusting the default.
- A parent link is usually a separate call after creation, not a field on the create.

## Publishing

Draft the whole set, show it, and create only after approval.
