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

**Code snippets**: Source files in `snippets/` are organized into topic subfolders (`snippets/<topic>/`) and imported into slides using Slidev's `<<< @/snippets/<topic>/file.ext lang` syntax (e.g., `<<< @/snippets/c-memory/malloc_basic.c c`). Each snippet is a self-contained C/C++ source file. When creating a new topic page, create a matching `snippets/<topic>/` folder and extract code blocks there rather than inlining them.

**Styling**: Uses UnoCSS (configured via `css: unocss` in headmatter). Utility classes are used directly in Vue template attributes.

**Deployment**: Configured for both Netlify (`netlify.toml`) and Vercel (`vercel.json`), both serving from the `dist/` directory with SPA rewrites.

## Slide Authoring Conventions

- `layout: two-cols` with `::right::` separator for two-column layouts (no shared header)
- `layout: two-cols-header` with `::left::` / `::right::` separators when a full-width header row is needed above the columns
- `layout: section` for chapter/topic dividers; `layout: cover` for chapter title slides within page files
- Images are stored in `images/` and referenced as `/images/<filename>` (absolute path from public root)
- Presenter notes go inside HTML comments `<!-- note here -->`
- MDC syntax is enabled (`mdc: true`), allowing component-style directives in markdown

## Coding Conventions

Rules are defined in `.claude/rules/coding-convention.md`. Key rules: pointer declarations must use `int* p;` style (type-attached), not `int *p;`; reference declarations must use `int& r;` style (type-attached), not `int &r;`. Both apply to all types and function parameters. Exception: intentional bad-style examples marked with 😖 must not be changed.

## Course Content

Pages imported by `slides.md` in order:

| 파일 | 주제 |
|------|------|
| `about-me`, `about-TA`, `about-course` | 강의 소개 |
| `cpp-history` | C++ 역사 |
| `dev-env` | 개발 환경 |
| `c-intro-01`, `c-intro-02` | C 기초 |
| `c-memory` | 동적 메모리 |
| `c-structure` | 구조체 |
| `c-to-cpp` | C → C++ 전환 |
| `cpp-reference` | 참조 |
| `cpp-class-intro` | 클래스 기초 |
| `cpp-enum` | 열거형 |
| `cpp-pointer` | 포인터 |
| `cpp-smart-pointer` | 스마트 포인터 |
| `std-streams` | 표준 스트림 |
| `io-buffers` | I/O 버퍼 |
| `cpp-class-advanced` | 특수 멤버 함수, 연산자 오버로딩 |
| `inheritance` | 상속 |
| `polymorphism` | 다형성, virtual 함수 |

새 주제 파일은 `pages/`에 추가하고 `slides.md`에 `src:` 항목을 등록한다. 코드가 긴 예제는 `snippets/<topic>/` 폴더에 별도 파일로 분리하고 `<<< @/snippets/<topic>/file.ext lang` 구문으로 임포트한다. 현재 스니펫 폴더: `c-memory`, `c-structure`, `std-streams`, `io-buffers`, `cpp-class`.
