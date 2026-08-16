# ie-lecture

Slide decks for the **Internet Engineering** course at Amirkabir University of
Technology. Hugo builds the site; each deck is a [reveal.js](https://revealjs.com)
presentation written as raw HTML.

Per-deck notes live in `content/lectures/<slug>/CLAUDE.md`.

## Build and check

```bash
npm install          # or: just install
hugo server          # or: just dev
```

Requires **Hugo 0.165.0 extended** (pinned in `.github/workflows/github-pages.yml`)
and Node. The macOS extended build ships only as a `.pkg` — there is no tarball,
so `xar`/`cpio` it open if you need a throwaway copy rather than a system install.

Two CI gates, both on every push and PR:

| Workflow           | Command                              |
| ------------------ | ------------------------------------ |
| `format.yml`       | `npx prettier --check .`             |
| `github-pages.yml` | `hugo --minify` then deploy to Pages |

**Always run `npx prettier --write <file>` after editing a deck.** Prettier
rewraps HTML, which means any exact string you matched on before the run will
have moved afterwards — re-read the file before making a second edit.

## Layout

```
config.toml                       site params: semester, university, instructor
content/lectures/<slug>/index.html  one deck
layouts/lectures/single.html      deck shell + the generated title slide
layouts/home.html                 the index page (Bootstrap, dark-mode toggle)
assets/scss/lecture.scss          all deck styling
assets/js/index.js                reveal.js bootstrap
assets/js/toc.ts                  TOC builder — a Hugo template, see below
data/references.yml               the References section on the home page
```

Decks are raw HTML, which Hugo refuses by default since v0.16x; `[security]
allowContent` in `config.toml` is what permits it. Do not remove it.

## Front matter

```yaml
---
index: 7 # numbered course lecture; drives home-page order and the "07" on the card
title: Go Programming
topics: # feeds both the title card and the TOC slides
  - History
  - Advantages
lecture: false # guest/extra deck: no number, listed in the second home-page table
---
```

A deck has **either** `index` (a numbered lecture) **or** `lecture: false` (an
extra deck). The home page selects on exactly that.

## Deck conventions

**Never hand-write a title slide.** `layouts/lectures/single.html` generates one
from front matter for every deck, so a hand-written one is a duplicate.

**Slides** are `<section>`. A `<section>` containing `<section>`s is a vertical
stack (down-arrow navigation).

**TOC dividers** — the deck opens with the full list, then a highlighted divider
before each topic:

```html
<section><div class="toc"></div></section>
<section><div class="toc" data-selected="0"></div></section>
...
<section><div class="toc" data-selected="1"></div></section>
```

`data-selected` is a **0-based index into `topics`**. `assets/js/toc.ts` is run
through `resources.ExecuteAsTemplate` with the page's params, so it contains Go
template actions and cannot be parsed by Prettier — it is in `.prettierignore`.

**Highlight colours** come from the `$highlights` map in `assets/scss/lecture.scss`:
`hl-orange`, `hl-green`, `hl-cyan`, `hl-red`, `hl-material`, `hl-violet`,
`hl-yellow`, `hl-pink`. Any other `hl-*` class renders **silently unstyled** —
past bugs were `hl-volet` and `hl-json`. Check the map before inventing one.

**Hands-on slides** carry `class="hands-on"` on the `<section>` itself, which
paints the marker via `section.hands-on:not(:has(> section))::after`. Putting it
on a child `<ul>` breaks any slide that ends with a code block.

**Code blocks** are `<pre><code class="language-go">`. Both the `language-` and
the older `lang-` prefix are in use and both work with highlight.js; match the
deck you are editing. Escape `<`, `>` and `&` inside them — JSX and HTML samples
are where this bites.

**Diagrams.** A deck's `img/` holds the exported SVG/PNG; the matching `diag/`
holds the editable draw.io source. Edit the `.drawio` and re-export — never
hand-patch the exported file, or the two drift apart.

## Things that fail silently

- **Overflow.** The slide is 960×700 logical px at `--r-main-font-size: 24px`.
  Content past that is simply cut off; nothing warns you.
- **Code blocks.** `.reveal pre code` is `overflow: hidden !important`
  (reveal.css) with `max-height: 400px` (league). A long line or a tall block is
  clipped with no scrollbar. Roughly 25 lines is the ceiling.
- **Live demos.** Several decks fetch from the public internet during the
  lecture. Always give them a `.catch` that prints the failure, or a blocked
  classroom network leaves a slide stuck on "Waiting…".

## Content rules

This material is taught from, so correctness beats speed:

- **Run the code.** Go samples must `go build` and `go vet` clean; YAML, JSON and
  JSON Schema must parse; JS must not throw. Do not put a snippet on a slide you
  have not executed.
- **Captured output must be real.** The transcripts on hands-on slides are actual
  captured runs. If you change the command, re-capture the output — do not edit
  the transcript to match.
- **Check external links resolve.** Note that requests to `.ir` hosts may need
  the proxy stripped (`--noproxy '*'`), and that hosts behind CloudFront may be
  reachable from a dev machine but not from the classroom.

## Known repo-wide issues

Do not fix these in one deck in isolation — they are systematic, and a partial
fix makes the decks inconsistent. Raise them first.

- **`<ul>` nested directly inside `<ul>`**, ~511 places across 15 decks. Invalid
  HTML (a `ul` may contain only `li`), but every browser renders it. Notable
  because lecture 3 teaches HTML.
- **Dimension attributes with units**, e.g. `height="250px"`. `width`/`height`
  take a bare integer; browsers salvage the rest. Remaining in `lecture-2` (3)
  and `lecture-4` (3).
- **`cors` and `lecture-8`** declare `topics` but render no TOC slides.
