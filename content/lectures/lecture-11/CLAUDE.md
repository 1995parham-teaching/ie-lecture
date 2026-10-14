# Lecture 11 — Web Security

37 slides (plus the generated title), 6 vertical stacks. Two sessions.
Topics (TOC indices): `0` Introduction · `1` Injection · `2` Cross-Site Scripting ·
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

- `SameSite=Lax` **is** the default in current Chrome and Edge. Chrome 155
  still sends a cookie that has **no** `SameSite` attribute on a top-level
  cross-site `POST` if it was set moments before (its two-minute "Lax+POST"
  exception) — seen in the CSRF test below. Firefox's default was not
  confirmed: its third-party cookie blocking hides the answer.
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

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They have no draw.io source:

| File                   | Slide                                 |
| ---------------------- | ------------------------------------- |
| `origin-site.svg`      | Origin and Site (under Why Security?) |
| `sql-injection.svg`    | Prepared Statements                   |
| `xss-stored.svg`       | Stored XSS, Step by Step              |
| `csrf.svg`             | The Forged Request                    |
| `password-hashing.svg` | Storing Passwords                     |
| `jwt.svg`              | Inside a JWT                          |
| `oauth-code-flow.svg`  | Authorization Code Flow               |
| `tls13-handshake.svg`  | The TLS 1.3 Handshake                 |
| `clickjacking.svg`     | Clickjacking                          |

How each was checked:

- `origin-site.svg`: origins from `new URL(u).origin` in Node; `github.io` is
  on the Public Suffix List; `example` is not, so `bank.example` is the
  registrable domain. "Same site" is the schemeful definition.
- `sql-injection.svg`: both queries run against `postgres:17` with
  `log_statement=all`. Concatenation returns 2 rows; `\bind` (extended
  protocol) returns 0 and the log shows the query with `$1` and the parameter
  in a separate `DETAIL` line.
- `xss-stored.svg`: headless Chrome — `innerHTML` with the `<img onerror>`
  payload runs it, a `<script>` inserted the same way does not, and
  `textContent` creates no elements.
- `csrf.svg`: a local Node server on `bank.localhost` / `evil.localhost` and
  headless Chrome 155. The auto-submitted cross-site `POST` carried the
  `SameSite=None` cookie (and a fresh no-attribute cookie), not the `Lax` or
  `Strict` ones; `Origin` and `Sec-Fetch-Site: cross-site` were sent.
- `password-hashing.svg`: the two PHC strings are real output of
  `golang.org/x/crypto/argon2` (`IDKey`, m=19456 KiB, t=2, p=1, OWASP's
  minimum) for `hunter2`; the guesses-per-second figures were timed on the
  dev laptop, one core.
- `jwt.svg`: the token is real — HS256 with the secret `s3cret`, made and
  decoded in Node. `exp` is 2027-01-15.
- `oauth-code-flow.svg`: parameters from RFC 6749 §4.1 and RFC 7636. The
  code is RFC 6749's example; the verifier and challenge are RFC 7636
  Appendix B's, and the challenge was recomputed in Node.
- `tls13-handshake.svg`: message order from RFC 8446 §2 (Figure 1) and a
  captured `openssl s_client -msg` run against a local `s_server` (OpenSSL
  3.6.5). The compatibility `ChangeCipherSpec` is left out on purpose.
- `clickjacking.svg`: headless Chrome — a page with `frame-ancestors 'none'`
  did not render inside a cross-site iframe, and a framed page received only
  the `SameSite=None` cookie, which is why the footnote says so.
