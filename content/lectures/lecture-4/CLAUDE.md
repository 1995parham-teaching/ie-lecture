# Lecture 4 — CSS

211 slides, 36 vertical stacks — the second-largest deck. Topics (TOC indices):
`0` Introduction · `1` Style Types · `2` Selectors · `3` Cascading ·
`4` Box-Model · `5` Layout Design · `6` Miscellaneous · `7` CSS Tools.

## Facts worth not re-deriving

- CSS came out of **CERN**, not MIT. (Håkon Wium Lie, 1994.)
- `:first-child` is a **pseudo-class**, not a pseudo-element — the deck used to
  file it under the wrong heading.
- The property value is `white-space: nowrap`, not `no-wrap`.
- The colour function is `hsl()`, not `usl()`.
- CSS has **no `//` comments**. Every sample uses `/* … */`. If a snippet here
  contains `//` it is a bug, not SCSS.
- The closing slide is about what is current — `:has()`, `@container`, native
  nesting, `@layer`, subgrid. It deliberately does _not_ say "CSS3/CSS4"; CSS is
  versioned per-module and has been since CSS 2.1.

## Open item

**Two slides cover the same ground**: "Custom Properties" (~line 2769) and
"CSS Variables" (~line 3321). They are the same feature under two names. They
should be merged, but which one survives and where it sits in the flow is a
teaching call.

## Cautions

- Three `width="650px"` / `width="350px"` / `width="850px"` attributes remain;
  dimension attributes take a bare integer.
- `diag/cascading.drawio` is the source for the cascade diagram.
- The one hands-on section here uses `class="hands-on"` on the `<section>`.
