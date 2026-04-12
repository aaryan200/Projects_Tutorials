---
name: prompt-writer
description: Guide users through writing well-structured AI prompts using the RISEN framework (Role, Instruction, Structure, Examples, Nuance). Use when users want to write, improve, or refine a prompt, craft system instructions, or need help getting better results from an AI. Trigger on prompt writing, prompt engineering, system prompts, "make a prompt for", or structuring LLM instructions.
---

# Prompt Writer (RISEN Framework)

Guide users through the RISEN framework to build well-structured prompts for any AI model. The final output uses XML tags — one per component — so the prompt is easy to read, edit, and maintain.

RISEN maps to six XML tags:

| Component       | XML Tag           | Purpose                            | Key Question                        |
|-----------------|-------------------|------------------------------------|-------------------------------------|
| **Role**        | `<role>`          | Set the AI's expertise and persona | "Who should the AI be?"             |
| **Instruction** | `<context>` + `<instructions>` | Define the task and its background | "What exactly should it do and why?" |
| **Structure**   | `<output_format>` | Specify the output schema          | "What should the result look like?" |
| **Examples**    | `<examples>`      | Demonstrate desired quality        | "What does good output look like?"  |
| **Nuance**      | `<rules>`         | Set constraints and guardrails     | "Any hard rules or preferences?"    |

## When to Offer This Workflow

Offer this skill when the user:
- Asks for help writing, improving, or refining an AI prompt
- Wants to create a system prompt or reusable prompt template
- Mentions prompt engineering, RISEN, or structured prompting
- Says something like "make a prompt for..." or "help me ask Claude to..."

## Stage 1: Discovery

Before building any RISEN components, understand what the user needs. Ask these questions (adapt based on what they have already shared):

1. **What task should the prompt accomplish?** Get specific about the deliverable.
2. **Which AI model is this for?** Claude, GPT, Gemini, a custom agent, or general-purpose? This affects how to frame the role and instructions.
3. **Starting fresh or improving an existing prompt?** If they have an existing prompt, ask to see it.
4. **What has gone wrong before?** If they have tried prompting for this task, find out what the AI got wrong — too verbose, off-topic, wrong format, wrong tone.
5. **How will the prompt be used?** One-off, reusable template, system prompt for an app, or part of a larger pipeline.

### Handling Existing Prompts

If the user provides an existing prompt, analyze it through the RISEN lens before starting the build process:

- Map the existing prompt against the six XML tags — identify which are present and which are missing or weak
- Point out the specific gaps so the user understands the diagnosis
- Use the existing prompt as a starting point rather than rebuilding from scratch

### Fast-Track Path

If the user wants a quick result ("just write me a prompt for X"), build all components in a single pass based on what they have shared. Still cover all RISEN tags, but do it without an extended interview — propose a complete prompt and let them react.

## Stage 2: Build the RISEN Components

Work through each component in order. For each, ask targeted questions, propose a draft, and get the user's reaction before moving on.

### Role

Define who the AI should be. The role shapes depth, vocabulary, and perspective for every other tag.

**Ask the user:**
- What expertise should the AI bring to this task?
- What perspective or persona fits best? (e.g., senior engineer, empathetic therapist, concise editor)
- Is there an audience the AI should tailor its output for?

**What good looks like:**
- Specific and relevant: "You are a senior backend engineer specializing in distributed systems" — not "You are a helpful assistant"
- Includes audience awareness when relevant: "...explaining concepts to a non-technical product manager"
- Matches the task: a creative writing task needs a different persona than a code review task

**Common pitfalls:**
- Roles that are too generic ("You are an expert") provide no useful constraint
- Roles that conflict with the instruction (e.g., "You are a comedian" for a formal legal document)
- Stacking too many roles dilutes focus — one clear persona is better than three blended ones

### Instruction (Context + Instructions)

This RISEN component maps to two XML tags: `<context>` (why the task exists) and `<instructions>` (what to do). Separating the "why" from the "what" prevents the AI from confusing background information with actionable steps.

**Ask the user:**
- What is the specific deliverable? (a list, an analysis, a code snippet, a rewrite)
- Why does this task exist? What system or workflow invokes it? What has already been determined?
- Are there steps the AI should follow?
- What should it not do? (Sometimes exclusions are as important as inclusions)

**What good `<context>` looks like:**
- Explains the situation the AI is entering: "The user has uploaded a CSV of quarterly sales data. The marketing team needs a summary for the board meeting."
- States what is already known or decided, so the AI does not re-derive it

**What good `<instructions>` looks like:**
- Verb-driven and specific: "Write a 500-word blog post titled '5 Productivity Hacks for Remote Workers'" — not "Write about productivity"
- Numbered steps for multi-step reasoning: "1. Identify the top 3 trends. 2. For each trend, provide one supporting data point. 3. Write a one-paragraph executive summary."
- Includes explicit exclusions when relevant: "Do not include pricing comparisons"

**Common pitfalls:**
- Mixing context and instructions together — the AI may treat background facts as tasks to perform
- Vague verbs: "Discuss" and "talk about" produce rambling output — prefer "List", "Compare", "Analyze", "Write", "Summarize"
- Trying to do too much in one prompt — if the task is complex, suggest breaking it into multiple prompts

### Structure (Output Format)

Maps to `<output_format>`. Define the exact schema of the output — field by field if structured, section by section if prose. This tag eliminates ambiguity about what the AI should produce.

**Ask the user:**
- What format works best for their use case? (JSON, markdown sections, bullet points, table, code block)
- Are there specific fields or sections the output should include? What does each field mean?
- Is there a length constraint?
- If structured output (JSON, YAML): what are the valid values for each field?

**What good looks like:**
- Field-by-field schema: "Return JSON with fields: `summary` (string, 1-2 sentences), `key_findings` (array of strings, max 5), `confidence` (float 0-1)"
- For prose: "Format as markdown with these sections: Executive Summary (2-3 sentences), Key Findings (bullet points), Recommendations (numbered list)"
- Include a reasoning scratchpad when the task involves judgment: "Use the `analysis` field as your reasoning scratchpad BEFORE setting other fields"
- Length boundaries: "Keep the total response under 300 words"

**Common pitfalls:**
- No structure at all — the AI defaults to prose paragraphs, which may not be what the user wants
- Over-specifying structure for creative tasks where flexibility matters
- Forgetting to specify valid values or types for structured output fields

### Examples

Provide input/output demonstrations. The AI pattern-matches against examples, making this the most effective way to control output quality and consistency.

**Ask the user:**
- Can they provide a sample of good output for this task? Even a rough sketch helps.
- Can they describe what a perfect response would contain?
- Are there examples of bad output they want to avoid?

**What good looks like:**
- 1-2 concrete input/output pairs showing the desired transformation
- Examples that demonstrate tone, depth, and format simultaneously
- Both positive examples ("like this") and negative examples ("not like this") when the distinction is subtle

**What to do when the user has no examples:**
- Propose a brief example based on the role and instruction, then ask if it matches their expectations
- Use a simplified version of the actual task as the example input

**Common pitfalls:**
- Skipping examples entirely — this is the most commonly omitted component and the one that causes the most output variance
- Examples that contradict the `<instructions>` or `<output_format>` tags
- Too many examples (3+) that over-constrain the AI and produce rigid outputs

### Nuance (Rules)

Maps to `<rules>`. These are the hard constraints and guardrails — stated as a flat list of dos, don'ts, and fallback behaviors. The `<rules>` tag keeps constraints scannable and separated from the instructions themselves.

**Ask the user:**
- What should the AI always do? (positive rules)
- What should the AI never do? (hard constraints)
- What should it do when uncertain? (explicit fallbacks)
- Any tone, vocabulary, or audience constraints?

**What good looks like:**
- Positive rules first: "Always cite the source document when making a claim"
- Hard constraints with NEVER prefix: "NEVER: include personal opinions or speculation"
- Explicit fallback for uncertainty: "If uncertain: state the ambiguity and ask for clarification rather than guessing"
- Specific, measurable: "Under 150 words", "Use 8th-grade reading level"
- Tone anchored to a reference: "Professional but approachable — like a senior colleague, not a textbook"

**Common pitfalls:**
- Vague constraints: "Keep it short" (how short?) or "Be professional" (what does that mean here?)
- Over-constraining: too many rules can confuse the AI and produce awkward, stilted output
- Contradictory rules: "Be concise" + "Provide thorough explanations" without clarifying which takes priority
- All negative rules, no positive ones — tell the AI what to do, not just what to avoid

## Stage 3: Assembly

Assemble the components into a single prompt using this XML structure:

```xml
<role>
You are a [specific expert role]. [One sentence on domain and purpose].
</role>

<context>
[Why this task exists. What system or workflow invokes it. What has already been determined.]
</context>

<instructions>
[The specific task to perform. Use numbered steps for multi-step reasoning.]
</instructions>

<rules>
- [Positive rule: do X]
- [Positive rule: always Y]
- NEVER: [hard constraint]
- If uncertain: [explicit fallback]
</rules>

<output_format>
[Exact schema field-by-field, or section-by-section for prose. What each field means. What values are valid.]
</output_format>

<examples>
<example>
<input>...</input>
<output>...</output>
</example>
</examples>
```

### Tag Ordering

The order above is deliberate: `<role>` and `<context>` prime the AI's perspective before it reads the task. `<instructions>` comes next so the AI knows what to do. `<rules>` constrain how to do it. `<output_format>` defines the shape of the result. `<examples>` come last so the AI can pattern-match against them with full context.

### Presenting the Output

Present the finished prompt in a code block (with `xml` syntax highlighting) so the user can copy it directly. The XML tags are self-documenting — no separate breakdown is needed.

### When to Omit Tags

Not every prompt needs all six tags. Omit a tag when it adds no value:
- `<context>` can be skipped for simple, self-contained tasks
- `<examples>` can be skipped if the task is straightforward and the output format is clear
- `<rules>` can be minimal for creative tasks where flexibility matters
- Always include `<role>`, `<instructions>`, and `<output_format>` at minimum

## Stage 4: Refinement

After presenting the assembled prompt, help the user iterate:

1. Ask if the prompt captures their intent — is anything missing or off?
2. If they have access to the target AI model, suggest they test the prompt and share the result
3. Based on feedback or test results, adjust specific XML tags rather than rewriting from scratch — the tag structure makes surgical edits easy
4. When refining, identify which tag is causing the issue — this teaches the user to diagnose prompt problems independently (e.g., "The tone is off — let's update `<rules>`" or "The output is unstructured — let's tighten `<output_format>`")

### When to Stop

The prompt is ready when:
- The user confirms it captures their intent
- A test run produces output that meets their expectations
- Or the user is satisfied with the draft and wants to iterate on their own

## Guidelines

**Calibrate complexity to the task.** A simple question does not need all six tags. For straightforward tasks, `<role>` + `<instructions>` + `<output_format>` may be enough.

**Stay model-agnostic.** RISEN works across all major LLMs. If the user specifies a target model, adjust guidance accordingly — some models respond better to explicit role-setting than others, and system prompt formatting varies by platform.

**Teach as you build.** Explain why each component matters as you build it, so the user can write better prompts independently.

**Common mistakes to watch for:**
- Putting everything in `<instructions>` and neglecting other tags
- Writing prompts that are too long — verbosity dilutes the signal
- Confusing `<examples>` (demonstrations of desired output) with `<instructions>` (what to do)
- Omitting `<output_format>` — the easiest tag to add and often the highest-impact on output quality

Keywords: prompt writing, prompt engineering, RISEN, system prompt, prompt template, prompt improvement, LLM prompting, structured prompts
