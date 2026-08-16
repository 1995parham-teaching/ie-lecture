# Lecture 5 — JavaScript

214 slides, 44 vertical stacks — the deck with the most slides. Topics (TOC
indices): `0` Introduction · `1` JavaScript Basic · `2` JavaScript & DOM & CSS ·
`3` Event Handling · `4` Web Applications · `5` Summary.

The middle of the deck is a full run through the concurrency model: event loop →
zero delays → never blocking → Promise → `async`/`await` → the same chain →
errors → waiting in parallel. Then optional chaining, nullish coalescing and
modules. That run is the modern core of the lecture; the OOP/prototype material
before it is the legacy half.

## Facts worth not re-deriving

- **Five snippets used to be `SyntaxError`s** — `let a` declared three times and
  `let m` twice in the same scope. Any sample that redeclares a `let` in one
  scope does not run. Paste new samples into a console before adding them.
- `const` is introduced alongside `let`, not after. Do not reorder those.
- `document.getElementsByTagName` and friends return an **`HTMLCollection`**,
  which is _live_ — not an array, not a `NodeList`.
- `Event.type` values are **case-sensitive** and lowercase (`"click"`, not
  `"Click"`).
- Private class fields (`#x`) are **ES2022**.
- `document.applets` was removed from the DOM; it is gone from the deck.
- The library-graveyard slide (jQuery, Prototype, MooTools…) is deliberate
  historical framing, not a recommendation.

## Cautions

- `innerHTML` was replaced with `textContent` wherever the sample was only
  setting text. Keep it that way — lecture 11 teaches that `innerHTML` with
  untrusted input is the XSS vector.
- A `document.write` demo was removed. `document.write` after page load wipes the
  document; do not reintroduce it, even as a joke.
- HTML samples inside this deck still need `&lt;` / `&gt;` escaping.
