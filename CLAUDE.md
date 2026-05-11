# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Overview

C++ 프로그래밍 강의 슬라이드 (국민대학교, Junho Kim). The repository contains a [Slidev](https://sli.dev/) presentation project under `slides/`, course assignments under `assignments/`, and pre-built HTML under `docs/`.

## Commands

All commands run from the `slides/` directory:

```bash
pnpm install        # Install dependencies
pnpm dev            # Dev server at http://localhost:3030
pnpm build          # Production build → dist/ (base path: /slidev-cpp)
pnpm export         # Export slides to PDF
```

## Architecture

### Repository layout

- `slides/` — the Slidev project (main working area; see `slides/CLAUDE.md` for full detail)
- `assignments/` — homework and exam files (`hw-io.md`, `midterm.md`, `midterm-rubric.md`)
- `docs/` — pre-built static HTML for GitHub Pages

### Slidev project structure (`slides/`)

**Entry point**: `slides.md` — global YAML frontmatter (theme, transitions, Shiki highlighting) and `src:` directives that import all 22 page files in order.

**Slide pages**: `pages/<topic>.md` — one file per lecture topic, each containing one or more slides separated by `---`. New topics go here and must be registered in `slides.md`.

**Code snippets**: `snippets/<topic>/` — self-contained C/C++ source files imported into slides with `<<< @/snippets/<topic>/file.ext lang`. Existing topic folders: `c-memory`, `c-structure`, `std-streams`, `io-buffers`, `cpp-class`. Inline long code blocks should be extracted to snippet files instead.

**Vue components**: `components/` — auto-imported into any slide markdown.

**Deployment**: Netlify (`netlify.toml`) and Vercel (`vercel.json`) both serve from `dist/` with SPA rewrites.

## Coding Conventions

Pointer and reference declarations attach the declarator to the **type**, not the variable name:

```cpp
int* p;          // correct — not int *p;
int& r;          // correct — not int &r;
void f(int* a, const std::string& s);  // correct
```

Exception: intentional bad-style pedagogical examples (marked with 😖) must not be changed.

## Slide Authoring Conventions

- `layout: two-cols` + `::right::` — two-column layout without shared header
- `layout: two-cols-header` + `::left::` / `::right::` — two-column with full-width header
- `layout: section` — chapter/topic divider; `layout: cover` — chapter title within a page file
- Images: stored in `images/`, referenced as `/images/<filename>` (absolute from public root)
- Presenter notes: inside HTML comments `<!-- note here -->`
- MDC syntax enabled (`mdc: true`)
