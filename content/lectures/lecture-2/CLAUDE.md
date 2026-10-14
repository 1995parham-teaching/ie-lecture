# Lecture 2 — HTTP

The largest deck in the repo: 167 slides, 34 vertical stacks, 9 hands-on
slides. Spans four sessions. Topics (TOC indices): `0` Introduction ·
`1` Cookie · `2` Proxy & Cache · `3` Authentication.

## Standards this deck follows

Cite the RFC when you change a claim here — the deck was corrected against them:

- **RFC 9110** — HTTP semantics, including the safe/idempotent table.
- **RFC 6265** — cookies. Browser limits on the slides are 4096 bytes per
  cookie, 50 cookies per domain, 3000 total.
- **RFC 7231 §6.4** — method rewriting on 3xx.
- **RFC 10008** — the `QUERY` method.

## Sections with history

**Cookies** (19 slides) was rewritten end to end. The order is deliberate:
the stateless problem → two kinds (the only difference is _lifetime_) → what
goes in a cookie and why not the data itself → limits → who controls a cookie →
attributes → domain & path → hands-on → prefixes (`__Host-`, `__Secure-`) →
third-party cookies → CSRF (one slide, pointing at lecture 11) → SSO. Do not
reorder without reading the whole run; each slide sets up the next.

Two claims that were wrong and are now right, so do not "restore" them: the
leading-dot `Domain` rule (superseded — the Public Suffix List is what matters),
and HttpOnly (it blocks _script access_, not transport).

**3xx** (7 slides) and **1xx** (7 slides) were both written from captured
traffic against a purpose-built local server. Two things were learned the hard
way and are documented on the slides:

- `curl -X POST -L` **forces** the method on the redirect follow-up, so it hides
  the very conversion the slide is about. Use `-d` alone.
- curl 8.7.1 only adds `Expect: 100-continue` automatically **above 1 MB**
  (verified at 1024, 1025, 65536 and 1048577 bytes).

Server Push is marked dead (removed from Chrome); 103 Early Hints is what
replaced it.

**Session Authentication** (5 slides, between "In the Wild" and Bearer) closes
the loop the "In the Wild" slide opens — it asks for a way to not re-authenticate
every request, and this is the cookie answer, before Bearer offers the stateless
one. The transcripts are captured against a purpose-built Go server on
`127.0.0.1:8211` (`POST /login` → 303 + `Set-Cookie`, `GET /me` reading a
server-side store, `POST /logout` deleting from it). The point the slides build
to is that logout is the **store delete**, not the `Max-Age=0` cookie.

**HTTPS on the wire** (4 slides, closing the Security stack) is issue #17. The
hexdumps are real, captured with a byte-level TCP relay between curl and
`example.com` — curl's own `--trace` shows plaintext on both ports because it
traces above TLS, so it cannot make this point. Port 80 shows a readable
`GET / HTTP/1.1`; port 443 shows the same request as a
`17 03 03 00 6e` application-data record; the last slide shows the SNI hostname
in the plaintext ClientHello. If you re-capture, keep all three from **one** pair
of runs or the story stops lining up.

**Base64** (2 slides, inside Authentication) is two hand-written SVGs in
`img/` — `base64.svg` (`Man` → 24 bits → `TWFu`) and `base64-padding.svg`
(`Man`/`Ma`/`M` → `TWFu`/`TWE=`/`TQ==`). They replaced three paragraphs of
prose; keep the explanation in the drawing. The bit values were checked with
`base64`; if you change the example, re-check every cell. Render with
`rsvg-convert -b '#2b2b2b'` before and after an edit.

**QUERY** (8 slides, right after the `HTTP Methods (Cont.)` run) is the RFC
10008 method, published June 2026 — the first new method since `PATCH` (2010).
The order is deliberate: the problem (`GET` puts the query in the URL, `POST`
throws away safe/idempotent/cacheable) → why `GET`-with-a-body is not the answer
(RFC 9110 §9.3.1 gives it no semantics, and it is not in the cache key) → what
`QUERY` is → the wire → `Content-Location` / `Accept-Query` → hands-on → result.

The transcript is captured against a purpose-built Go server on
`127.0.0.1:8241`: `QUERY /students` filters a fixed three-student slice on the
JSON body and answers with `Content-Location` and `Cache-Control: max-age=60`;
any other method gets 405 plus `Accept-Query: application/json`, which is the
point of the last slide. `Content-Length: 44` on the wire slide is the real
length of the JSON body next to it — re-count if you change the filter.

`curl -X QUERY` works on 8.7.1, but `-d` alone would send `POST`, so the `-X` is
load-bearing here — the opposite of the 3xx slides, where `-X` hides the effect.

**HTTP Tools** was a flat slide until Noodle was added; it is now a 4-slide
stack: the tool list → what Noodle is → a real `example.yml` with the transcript
of `noodle collection run demo` → the upstream screenshot. The YAML and the
transcript are a captured run of noodle v0.7.7 against a collection made with
`noodle collection create demo`, so re-capture both together if either changes.
`img/noodle.png` is upstream's own screenshot (Apache-2.0, and it shows v0.6.1,
not the version in the transcript).

**Modernised in October 2026** (cookies, proxy and cache). Additions were put
at the **end of existing vertical stacks**, or made by turning a flat slide into
a stack, so that no horizontal index moved — the session notes in the vault
cite slides by `#/N/M`. Keep it that way: a new horizontal slide shifts every
later reference. What was added:

- `The Standard Today: RFC 6265bis` (end of the Cookie stack): SameSite,
  prefixes, the 400-day lifetime cap, 4096 bytes for name + value.
- `Partitioned Cookies (CHIPS)` under `Third-Party Cookies`, which now says
  Chrome **kept** third-party cookies (plan dropped in 2024, most of Privacy
  Sandbox retired October 2025). FedCM on the SSO slide.
- `CONNECT` tunnelling and TLS inspection on Forward Proxies; TLS termination
  and CDNs on the reverse-proxy uses; `Who Is the Real Client?` (`Forwarded`,
  RFC 7239, and `X-Forwarded-For`).
- RFC 9111 in place of the RFC 2616 "general-header" wording; then, after the
  staleness diagram: `private` / `public` / `s-maxage` / `Vary`, a recipes table
  (`immutable`, `stale-while-revalidate`), a cdnjs capture, and an httpbin
  caching hands-on.

The cdnjs and httpbin transcripts are real captures from 9 October 2026 with
**selected headers**, and the slides say so. httpbin still runs
`gunicorn/19.9.0` and sends `ETag: abc` unquoted, which is invalid; the slide
points that out. GitHub Pages for this site now sits behind Cloudflare, which
strips the `ETag`, so it cannot be used for a 304 demo.

## Cautions

- These claims age fast; re-check them each term: 6265bis had **no RFC number**
  yet (RFC Editor queue, October 2026); Chrome's third-party cookie policy;
  `Partitioned` support (Chrome 114, Firefox 141, Safari 26.2).

- The capture on the URL slide states `length 85`, which depends on the path in
  it. The path was changed from `/~bakhshis/` to `/~students/` **because both
  are 11 characters** — keep any replacement the same length or re-capture.
- Three `height="500px"` / `height="400px"` attributes remain; dimension
  attributes take a bare integer.
- `diag/reverse-proxy.drawio` is the source for `img/reverse-proxy.png`.
- The `QUERY` slides claim framework support is thin (Node.js parses it, OpenAPI
  3.2 documents it). That ages fast — re-check before teaching it.

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). Only `reverse-proxy.png` has a draw.io source. No slide was added
for any of them — each replaced an image or a list in place, so every `#/N/M`
stayed where it was.

| File                        | Slide                                                     |
| --------------------------- | --------------------------------------------------------- |
| `url-anatomy.svg`           | URL — the parts, and what reaches the server              |
| `url-in-action.svg`         | URL in Action (2nd) — DNS, handshake, request, close      |
| `message-structure.svg`     | HTTP Messages — start line, headers, empty line, body     |
| `redirect-codes.svg`        | The Shape of It — 301/302/303/307/308 on two axes         |
| `cookie-flow.svg`           | Solution of Stateless Problem — Set-Cookie then Cookie    |
| `forward-reverse-proxy.svg` | Reverse Proxies — who each kind works for                 |
| `cache-types.svg`           | Caching (2nd) — no cache, shared, private: 4 / 1 / 2 hits |
| `cache-staleness.svg`       | Caching Algorithm (Cont.) — fresh, stale, 304             |
| `auth-challenge.svg`        | HTTP Authentication — 401, prompt, Authorization          |
| `jwt-anatomy.svg`           | JWT — header, payload, signature                          |
| `tls13-handshake.svg`       | Security (2nd) — the TLS 1.3 handshake                    |

How the facts were checked:

- `url-anatomy.svg`: the parts come from `new URL()` in Node. The request box
  is what curl sent to a local server for the same URL (`user:pass` became
  `Authorization: Basic dXNlcjpwYXNz`); Chrome sent the same request line
  without it. Neither sent `#intro`.
- `url-in-action.svg` and `message-structure.svg` are drawn from the tcpdump
  capture on the URL in Action slides: the packet numbers, 85 and 224 bytes, the
  283 ms between packets 5 and 6, and the 98-byte body. The 85 is 26 + 20 + 24 +
  13 + 2. If that capture is redone, redraw both.
- `cookie-flow.svg` is a fresh capture of the httpbin exchange (October 2026,
  same headers as the Cookies in Action slide). The `Cookie` order
  `name=parham; family=alvani` is what headless Chrome sent; curl sends them
  the other way round.
- `redirect-codes.svg` follows RFC 9110 §15.4. It replaced `3xx.png`, which put
  301 under "do a GET? yes" and left 302 out.
- `cache-staleness.svg` redraws the old MDN `staleness.png` (max-age 100, ages
  0 / 10 / 110), with an explicit `ETag` so the `If-None-Match` has something to
  match.
- `auth-challenge.svg` is a fresh httpbin capture: `401` with
  `WWW-Authenticate: Basic realm="Fake Realm"`, and `base64 admin:admin` is
  `YWRtaW46YWRtaW4=`.
- `jwt-anatomy.svg` decodes the Sample Token slide in Node; its HS256 signature
  verifies with the secret `your-256-bit-secret`. Change the token and redo both.
- `tls13-handshake.svg` lists the messages `openssl s_client -tls1_3 -msg`
  logged against `example.com` (key exchange `X25519MLKEM768`). It replaced
  `ssl.jpg`, which drew RSA key transport — the client encrypting a session key
  with the server's public key — and TLS 1.3 no longer has that.

Removed with the redraw: `message-structure.jpg`, `3xx.png`,
`http-cache-types.png` (its shared-cache box was labelled "Browser 1"),
`staleness.png`, `ssl.jpg`. Still screenshots or third-party images:
`http-transactions.png`, `http2-transactions.png`, `proxy.png`, `cookies.png`,
`sub-domain-cookies.png`, `csrf-attack.png`, `basic-auth-in-action.png`, the
three `moodle-*.png`, `noodle.png`.

The Digest slide's formula was `MD5(HA1:nonce:HA2)`, which is the form
**without** `qop`; the header under it has `qop=auth`, and its `response` value
`6629fae4…` is `MD5(HA1:nonce:nc:cnonce:qop:HA2)` (checked in Node with the RFC
2617 password `Circle Of Life`). The formula now says so.
