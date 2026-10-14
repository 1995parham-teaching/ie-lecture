# React

An extra deck (`lecture: false`), 61 slides, 8 vertical stacks. Originally by
**Amirhossein Nouri**. Declared topics: Introduction · Components · JSX · Props ·
State · Component Styling · Fetch External Data.

## This deck was rewritten end to end — read before editing

Roughly 730 lines changed. The things that were fixed are the things most likely
to be reintroduced:

- **Every JSX sample is escaped** as `&lt;` / `&gt;` inside `<pre><code>`. This
  is the only deck where every single code block is markup, so an unescaped `<`
  silently eats the rest of the slide.
- `onclick` → **`onClick`**. JSX event props are camelCase.
- Fragments `<>…</>` are used where a component returns siblings, and there is a
  dedicated "One Root Element" slide explaining why.
- The class component `extends React.Component`.
- A component called `Date` was renamed to **`Year`** — it shadowed the built-in.
- `<img />` is self-closed; JSX has no void elements.
- `<hl-green>` was being used as if it were a tag. It is a **class**:
  `<span class="hl-green">`.
- The `data-selected="2"` TOC divider was missing and is now present.
- A reference to a nonexistent `img/background.jpg` was removed.

## The State run has to stay in order

`State` → `First Attempt` → `Two Problems` → `Working Counter` →
`What a Click Does` → `Updating From the Previous Value`. It is a deliberate
broken-then-fixed narrative: the first attempt does not work, the next slide
says why, and only then does the working `useState` counter appear. Reordering or "fixing" the
first attempt destroys the lesson.

The last section does the same for `useEffect`: dependency array, then an
`AbortController` cleanup.

## Open item

**Class components are still taught** (marked ⚰️ on the slide). Hooks are the
modern API and the deck teaches them properly; whether the class-component
detour still earns its slides is a teaching call, not an editing one.

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They have no draw.io source:

| File                         | Slide                                                    |
| ---------------------------- | -------------------------------------------------------- |
| `declarative-imperative.svg` | Declarative — the same list written both ways            |
| `jsx-compile.svg`            | What the Build Step Makes — JSX → `jsx()` → object → DOM |
| `component-tree.svg`         | The same page as a tree (after Composing components)     |
| `props-down.svg`             | Pass props down to components                            |
| `render-cycle.svg`           | What a Click Does — set state, render, reconcile, commit |
| `state-queue.svg`            | Updating From the Previous Value                         |
| `effect-timeline.svg`        | Effect Timeline (after The Two Details That Matter)      |

Verified with React 19.3 and react-dom in jsdom, and esbuild 0.28:

- `jsx-compile.svg`: the `jsx("button", { className, children })` line is
  esbuild's `--jsx=automatic` output; the element object and the
  `<button class="primary">` come from rendering it.
- `render-cycle.svg`: a MutationObserver on the working counter records exactly
  one mutation per click (`characterData` on the text node); the `<p>`, the
  `<button>` and both text nodes are the same objects before and after.
- `state-queue.svg`: two `setA(v + 1)` give 1, two `setB((x) => x + 1)` give 2,
  and the four calls in one handler cause one re-render.
- `effect-timeline.svg`: the logged order is render 1, effect 1, render 1,
  render 2, cleanup 1, effect 2, cleanup 2 (no StrictMode). If a sample
  changes, re-run it before editing the drawing.
- `declarative-imperative.svg` replaced a black-on-white meme PNG that showed
  as a white rectangle on the dark slide. Both code boxes were run in jsdom: the JSX, compiled by
  esbuild and rendered by React, and the DOM loop each give
  `<ul><li>Buy milk</li><li>Learn React</li></ul>`, with no React key warning.
- `jsx.png` and the two `.jpg` files are memes and screenshots, kept as they
  were.
