# React

An extra deck (`lecture: false`), 57 slides, 8 vertical stacks. Originally by
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
`Updating From the Previous Value`. It is a deliberate broken-then-fixed
narrative: the first attempt does not work, the next slide says why, and only
then does the working `useState` counter appear. Reordering or "fixing" the
first attempt destroys the lesson.

The last section does the same for `useEffect`: dependency array, then an
`AbortController` cleanup.

## Open item

**Class components are still taught** (marked ⚰️ on the slide). Hooks are the
modern API and the deck teaches them properly; whether the class-component
detour still earns its slides is a teaching call, not an editing one.
