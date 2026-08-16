# Lecture 2 — HTTP

The largest deck in the repo: 164 slides, 27 vertical stacks, 5 hands-on
sections. Spans four sessions. Topics (TOC indices): `0` Introduction ·
`1` Cookie · `2` Proxy & Cache · `3` Authentication.

## Standards this deck follows

Cite the RFC when you change a claim here — the deck was corrected against them:

- **RFC 9110** — HTTP semantics, including the safe/idempotent table.
- **RFC 6265** — cookies. Browser limits on the slides are 4096 bytes per
  cookie, 50 cookies per domain, 3000 total.
- **RFC 7231 §6.4** — method rewriting on 3xx.

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

## Cautions

- The capture on the URL slide states `length 85`, which depends on the path in
  it. The path was changed from `/~bakhshis/` to `/~students/` **because both
  are 11 characters** — keep any replacement the same length or re-capture.
- Three `height="500px"` / `height="400px"` attributes remain; dimension
  attributes take a bare integer.
- `diag/reverse-proxy.drawio` is the source for the proxy diagram.
