# Lecture 3 — HTML

109 slides (plus the generated title slide), 15 vertical stacks. Topics (TOC indices): `0` Introduction ·
`1` HTML · `2` Body · `3` Semantic Tags · `4` Head · `5` HTML in Practice.

The element tour ("Main root", "Content sectioning", "Text content", "Inline
text semantics", …) follows the MDN element-reference grouping. Keep that
correspondence — it is what makes the slides usable next to MDN.

## Facts worth not re-deriving

- HTML is a **Living Standard** (WHATWG). The deck used to say "HTML5" as if it
  were the current numbered version; it is not.
- The `id` attribute rule was corrected: in HTML5 an id must be non-empty and
  contain no whitespace. The "must start with a letter A–Z or a–z" rule is
  **XHTML/HTML 4**, not HTML5.
- `<meta>` is a void element — no closing tag.
- Parser behaviour on the slides was checked in headless Chrome, not taken
  from memory: `<p>Hello <div>World</div></p>` becomes
  `<p>Hello </p><div>World</div><p></p>`; `<div />` does not close; an unknown
  tag (`<blink>`) is an `HTMLUnknownElement` and its content shows; a
  `<button>` in a form defaults to `type="submit"`; a form defaults to `get`.
- History dates: HTML Tags 1991 (not 1989, that is the WWW proposal), HTML 2.0
  is RFC 1866 of 1995, HTML 3.2 and 4.0 are both 1997.
- The 12 form `action` URLs were all switched from `http://` to `https://`.
  Keep new ones on https; a form demo posting over cleartext undercuts
  lecture 11.

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They have no draw.io source:

| File                  | Slide                                          |
| --------------------- | ---------------------------------------------- |
| `html-timeline.svg`   | Introduction (Cont.) — 1991 to Living Standard |
| `element-anatomy.svg` | Tag & Attribute & Element, plus void elements  |
| `block-inline.svg`    | Rendering — block vs inline, `ltr` vs `rtl`    |
| `dom-tree.svg`        | Nested Tags — the Hello World page as a tree   |
| `url-resolution.svg`  | `<a>` — how each `href` resolves               |
| `form-get-post.svg`   | Forms — the same fields sent by GET and POST   |
| `form-same-name.svg`  | Forms — checkboxes sharing a name, `multiple`  |
| `semantic-layout.svg` | Semantic Tags Example                          |

- `dom-tree.svg` matches what Chrome builds for the Hello World sample: the
  leading comment is a child of `Document`, not of `html`. If the sample
  changes, re-check the tree.
- `url-resolution.svg` results come from `new URL(href, page)` in Node.
- `form-get-post.svg` shows a real request captured from headless Chrome
  submitting to a local socket server (other headers left out). If the
  fields change, capture again.
- `form-same-name.svg` is captured the same way: `skills=html&skills=js&skills=go`
  (GET and POST bodies alike), `colors=r&colors=b` for `<select multiple>`,
  and a form whose only filled field is `q=x` sends just `?q=x` (an unchecked
  box and an empty multiple select add nothing). The server slide's Go output
  is from `go run`; the PHP claim is from `parse_str` (last value wins without
  `[]`).
- `example.png` and `summary.png` are still the old screenshots.

## Cautions

- Every HTML sample is inside `<pre><code class="lang-html">` (this deck uses the `lang-` prefix throughout; keep to it), so `<` and `>`
  must be escaped as `&lt;` / `&gt;`. This deck is the easiest place in the repo
  to get that wrong, because the subject _is_ markup.
- Figures use `<figure>` / `<figcaption>` rather than a bare `<img>` plus a
  paragraph. Follow that when adding one.
- This deck teaches correct HTML while the deck itself nests `<ul>` directly
  inside `<ul>` in 89 places (see the repo-wide note in the root `CLAUDE.md`).
  If that ever gets fixed, fix it here first.
