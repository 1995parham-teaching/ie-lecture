# Lecture 3 — HTML

106 slides, 13 vertical stacks. Topics (TOC indices): `0` Introduction ·
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
- The 12 form `action` URLs were all switched from `http://` to `https://`.
  Keep new ones on https; a form demo posting over cleartext undercuts
  lecture 11.

## Cautions

- Every HTML sample is inside `<pre><code class="language-html">`, so `<` and `>`
  must be escaped as `&lt;` / `&gt;`. This deck is the easiest place in the repo
  to get that wrong, because the subject _is_ markup.
- Figures use `<figure>` / `<figcaption>` rather than a bare `<img>` plus a
  paragraph. Follow that when adding one.
- This deck teaches correct HTML while the deck itself nests `<ul>` directly
  inside `<ul>` in 79 places (see the repo-wide note in the root `CLAUDE.md`).
  If that ever gets fixed, fix it here first.
