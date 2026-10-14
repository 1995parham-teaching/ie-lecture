# CORS

An extra deck (`lecture: false`), 23 slides after the generated title, 6
vertical stacks. Sits between the HTTP lecture and the security lecture.

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

The middleware example is **Fiber v3** (`github.com/gofiber/fiber/v3`), which
matches the linked `docs.gofiber.io`. It sits awkwardly next to lecture 7, which
now teaches `net/http` with no external dependencies. A `net/http` CORS middleware would fit the course
better than a framework one.

## Note

**This deck declares seven topics but renders no TOC slides.** Either add the
divider pattern (see the root `CLAUDE.md`) or drop `topics` — as it stands the
title card advertises a structure the deck does not have.

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They have no draw.io source. They replace four old PNGs
(`cors_principle.png`, `simple-req.png`, `cors-frontend.png`,
`cors-error.png`), which were deleted:

| File                 | Slide                                                           |
| -------------------- | --------------------------------------------------------------- |
| `origin.svg`         | What is an Origin? — scheme + host + port, five examples        |
| `preflight.svg`      | Preflight — OPTIONS, then the real PUT                          |
| `cross-origin.svg`   | Example — same-origin vs cross-origin fetch                     |
| `simple-request.svg` | Another Example — `Origin` and `Access-Control-Allow-Origin: *` |
| `blocked.svg`        | CORS Error — the request arrives, the response is withheld      |
| `dev-proxy.svg`      | Proxy Server — Flow                                             |

- `origin.svg`: every row is `new URL(u).origin` in Node compared with
  `https://domain-a.com`.
- `preflight.svg` and `blocked.svg` are captured from headless Chrome 155: a
  page on `localhost:8081` calling `fetch` against a Node server on
  `localhost:8082` that logged every request. The `OPTIONS` really carried
  `Access-Control-Request-Headers: content-type` (lower case), the blocked
  `GET` really reached the server, and the console text is Chrome's own. Only
  the CORS-relevant headers are drawn.
- `simple-request.svg` keeps the deck's `foo.example` / `bar.other` names;
  the header behaviour is the same as in the Chrome capture.
- `dev-proxy.svg` is from Vite 6 with the `vite.config.js` shown on the slide:
  the back-end received `GET /api/users` with no `Origin` header (the browser
  saw a same-origin request), and the path was forwarded unchanged.

## Captured transcripts

The two HTTP transcripts on the "Another Example" stack (request and response)
are a real run, not MDN's Firefox sample: headless Chrome 155 loaded a page
from `https://foo.example` that called the `fetch` on the slide, and a Node
HTTPS server for `https://bar.other` logged the raw request (`rawHeaders`, in
order) and the raw response header it sent (`res._header`). Both names were
mapped to `127.0.0.1` with `--host-resolver-rules` and a self-signed cert
(`--ignore-certificate-errors`). The request slide omits `User-Agent` and the
`sec-ch-ua*` client hints, and says so; everything else is verbatim. The body
`{"users":42}` is what the server sent. If you change the code on the slide,
re-capture.

The "Proxy Server (Frontend)" text matches `dev-proxy.svg`: the browser sees a
same-origin request and response, and no CORS is involved at any step.
