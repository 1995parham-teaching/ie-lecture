# Lecture 11 — Web Security

36 slides, 5 vertical stacks, no images. Two sessions. Topics (TOC indices):
`0` Introduction · `1` Injection · `2` Cross-Site Scripting ·
`3` Cross-Site Request Forgery · `4` Authentication & Authorization ·
`5` Transport & Headers.

## The organising idea

The deck is built around one thesis, stated on **The Golden Rule** slide:
_never mix data with code_. SQL injection, XSS and command injection are then
presented as the same bug with three different interpreters, and every defence
is framed as "keep them separate" rather than "sanitize harder".

If you add a vulnerability here, fit it to that frame or the deck loses its
spine.

## Cross-lecture dependencies

This deck is the payoff for claims made earlier, and they must stay consistent:

- **Lecture 2 (HTTP)** — the cookie section ends with one CSRF slide that points
  here; `SameSite`, `HttpOnly` and `Secure` are defined there and used here. The
  "a GET must never change state" rule is introduced there as safe/idempotent
  (RFC 9110) and re-used here as a security rule.
- **Lecture 5 (JavaScript)** — `innerHTML` vs `textContent`. The XSS defence
  slide depends on lecture 5 having already used `textContent`.
- **cors deck** — "the same-origin policy and CORS protect the browser, not your
  server" is the hinge of the first slide, and the CSRF section restates it as
  "the call is coming from inside the house".

## Facts worth not re-deriving

- `SameSite=Lax` **is** the default in current Chrome, Firefox and Edge.
- A JWT is **signed, not encrypted** — the payload is readable base64url. The
  `header.payload.signature` sample is correct.
- The prepared-statement point is protocol-level parameter binding, _not_
  quoting. Do not weaken that slide into "escape your quotes".
- The SQL sample uses `$1`, which is PostgreSQL placeholder syntax (MySQL uses
  `?`). Keep the dialect consistent if you extend it.

## Notes

- Code samples: go, sql, javascript, html, http, plaintext. The HTML and
  JavaScript ones contain markup and are escaped as `&lt;` / `&gt;` — check that
  before editing.
- References are OWASP Top 10, the OWASP Cheat Sheets, MDN, RFC 6749 and the
  OIDC overview. Prefer those over blog posts.
