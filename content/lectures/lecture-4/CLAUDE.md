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

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They have no draw.io source:

| File                  | Slide                                                 |
| --------------------- | ----------------------------------------------------- |
| `specificity.svg`     | Overriding — Priority 1, scored on the deck's example |
| `cascade-order.svg`   | Overriding: the Full Order (replaced Priority 2 text) |
| `box-model.svg`       | CSS Box Model (replaced `box-model.png`)              |
| `margin-collapse.svg` | Vertical Margin Collapse (replaced the book scan)     |
| `positioning.svg`     | Specified Positioning — static, relative, absolute    |
| `float-clear.svg`     | Clearing around Float Elements                        |
| `flex-axes.svg`       | FlexBox Axises (replaced `flex-axises.png`)           |
| `justify-content.svg` | justify-content (replaced the two `flex-justify-*`)   |
| `grid-lines.svg`      | Grid Lines — new sub-slide after Placing Items        |

Every number in them was measured in headless Chrome, not drawn from memory.
If you change one, measure again:

- `specificity.svg` / `cascade-order.svg`: computed colours for `p`, `p.c`,
  `p#i`, `style=""`, `!important` against `style=""`, two equal rules in source
  order, and an inherited `!important` losing to a direct rule. One ID beats 11
  classes; one class beats 11 type selectors.
- `box-model.svg`: `width: 200px; padding: 20px; border: 5px; margin: 30px`
  renders 250 × 150; with `box-sizing: border-box`, 200 × 100.
- `margin-collapse.svg`: 40px bottom + 20px top margin leave a 40px gap; 40px
  right + 20px left on inline-blocks leave 60px.
- `positioning.svg`: four `<p>` (24px tall, `margin: 0 0 16px`) in an 800px
  `position: relative` parent; #2 gets `top: 150px; left: 50%`. Relative lands at
  (400, 190) and keeps its slot; absolute lands at (400, 150), 3 and 4 move up,
  and the parent shrinks from 144 to 104px. Drawn at 0.34× horizontally only.
- `float-clear.svg`: a 150 × 120 left float in a 400px parent. Without clear
  the `<p>` and footer boxes start at x = 0 (text at x = 150) and the parent is
  60px tall; with `clear: both` the footer starts at y = 120.
- `justify-content.svg`: items 120/80/160px in a 600px row; every x position is
  taken from `getBoundingClientRect`. The column case (`justify-content` moves
  items vertically, `align-items` horizontally) was checked for `flex-axes.svg`.
- `grid-lines.svg`: `200px 1fr 1fr`, `gap: 16px`, 760px wide → tracks 200, 264,
  264; `.hero { grid-column: 1 / 3 }` spans 0–480 and item 2 auto-places into
  the third track of row 1.

The generator scripts were throwaway; edit the SVG directly and re-render it.

## Cautions

- Two `width="350px"` / `width="850px"` attributes remain; dimension attributes
  take a bare integer.
- `img/cascading.png` (from `diag/cascading.drawio`) puts **User** after
  Inline as the strongest layer. That is wrong: normal user styles lose to
  author styles; only user `!important` beats them. Fix it in the `.drawio`.
- "Absolute Positioning" says that with no positioned ancestor the containing
  block is `<html>`. It is the _initial containing block_ (a viewport-sized
  rectangle), not the `html` element.
- `diag/cascading.drawio` is the source for the cascade diagram.
- The one hands-on section here uses `class="hands-on"` on the `<section>`.
