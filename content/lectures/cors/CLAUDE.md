# CORS

An extra deck (`lecture: false`), 25 slides, 5 vertical stacks. Sits between the
HTTP lecture and the security lecture.

Declared topics: Introduction · Policy · Usage · Example · Error · Middleware ·
Proxy.

## The claim the whole deck rests on

CORS **relaxes** the same-origin policy; it does not impose it. A server sending
`Access-Control-Allow-Origin` is _granting_ access that the browser would
otherwise deny. The deck previously stated this backwards, which inverts the
meaning of every slide after it — do not let it drift back.

Two corollaries also fixed and worth keeping:

- CORS headers appear on **responses** only. There is no request header that
  turns it on.
- CORS is enforced by the **browser**, for the browser. It is not a server-side
  access control. Lecture 11 restates this as "the same-origin policy and CORS
  protect the browser, not your server", and the two must agree.

The examples use `fetch`, not `XMLHttpRequest`.

## Open item

The middleware example is **Fiber v2** (`github.com/gofiber/fiber/v2`), and the
linked docs at `docs.gofiber.io` are for the current major version. Either
update the snippet to v3 or pin the link to the v2 docs — right now the slide
and the link can disagree.

Note this also sits awkwardly next to lecture 7, which now teaches `net/http`
with no external dependencies. A `net/http` CORS middleware would fit the course
better than a framework one.

## Note

**This deck declares seven topics but renders no TOC slides.** Either add the
divider pattern (see the root `CLAUDE.md`) or drop `topics` — as it stands the
title card advertises a structure the deck does not have.
