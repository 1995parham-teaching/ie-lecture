# Lecture 2 — HTTP

The largest deck in the repo: 156 slides, 31 vertical stacks, 8 hands-on
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

## Cautions

- The capture on the URL slide states `length 85`, which depends on the path in
  it. The path was changed from `/~bakhshis/` to `/~students/` **because both
  are 11 characters** — keep any replacement the same length or re-capture.
- Three `height="500px"` / `height="400px"` attributes remain; dimension
  attributes take a bare integer.
- `diag/reverse-proxy.drawio` is the source for the proxy diagram.
- The `QUERY` slides claim framework support is thin (Node.js parses it, OpenAPI
  3.2 documents it). That ages fast — re-check before teaching it.
