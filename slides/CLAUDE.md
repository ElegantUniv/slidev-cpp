# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Commands

```bash
pnpm install        # Install dependencies
pnpm dev            # Start dev server at http://localhost:3030
pnpm build          # Build for production (outputs to dist/, base path: /slidev-cpp)
pnpm export         # Export slides to PDF
```

## Architecture

This is a [Slidev](https://sli.dev/) presentation project for a C/C++ programming course (국민대학교 C++ 프로그래밍, Junho Kim).

**Entry point**: `slides.md` — the root slide deck. It uses YAML frontmatter to configure global settings (theme, transitions, syntax highlighting) and imports individual page files via `src:` directives.

**Slide organization**: Content is split across `pages/` as separate markdown files, each imported by `slides.md` with `src: ./pages/<file>.md`. Each page file contains one or more slides separated by `---`, with per-slide frontmatter for layout.

**Custom components**: Vue components in `components/` are auto-imported and usable directly in any slide's markdown (e.g., `<Counter />`).

**Code snippets**: TypeScript files in `snippets/` can be imported into slides using Slidev's `<<< @/snippets/file.ts#region` syntax for code blocks.

**Styling**: Uses UnoCSS (configured via `css: unocss` in headmatter). Utility classes are used directly in Vue template attributes.

**Deployment**: Configured for both Netlify (`netlify.toml`) and Vercel (`vercel.json`), both serving from the `dist/` directory with SPA rewrites.

## Slide Authoring Conventions

- `layout: two-cols` with `::right::` separator for two-column layouts
- `layout: two-cols-header` with `::left::` / `::right::` separators when a full-width header row is needed above the columns
- `layout: section` for chapter/topic dividers; `layout: cover` for chapter title slides within page files
- Images are stored in `images/` and referenced as `/images/<filename>` (absolute path from public root)
- Presenter notes go inside HTML comments `<!-- note here -->`
- MDC syntax is enabled (`mdc: true`), allowing component-style directives in markdown

## Coding Conventions

Rules are defined in `.claude/rules/coding-convention.md`. Key rules: pointer declarations must use `int* p;` style (type-attached), not `int *p;`; reference declarations must use `int& r;` style (type-attached), not `int &r;`. Both apply to all types and function parameters. Exception: intentional bad-style examples marked with 😖 must not be changed.

## Course Content

Pages imported by `slides.md` in order: `about-me`, `about-TA`, `about-course`, `cpp-history`, `dev-env`, `c-intro-01`, `c-intro-02`, `c-memory`, `c-structure`, `c-to-cpp`, `cpp-reference`, `cpp-class-intro`, `cpp-enum`, `cpp-pointer`, `cpp-smart-pointer`, `cpp-std-streams`. Add new topic files under `pages/` and register them in `slides.md` with a `src:` directive.
