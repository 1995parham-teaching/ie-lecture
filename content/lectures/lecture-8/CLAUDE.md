# Lecture 8 — CGI

25 slides after the generated title, 2 vertical stacks. The historical bridge
between "static documents" and "web application frameworks": how the first
dynamic web worked, why it did not scale, and what replaced it.

Arc: typical web application → CGI → a C example (server config, source,
compile, test) → the same thing in bash → reading parameters from the client →
the CGI environment variables → pros and cons → what solved the problems →
server-side scripting → embedded vs external → client-side vs server-side.

## Facts worth not re-deriving

- `PATH_INFO` is the part of the URL path **after** the script name; it is not
  the filesystem `PATH`. That was wrong in the deck and is now right.
- CGI's cost is **one process per request** — that is the whole reason the
  pros/cons slide exists, and the reason FastCGI, mod_php and application
  servers followed. "Solving CGI Problems" is a three-row table of exactly
  those (server module, FastCGI, application server); keep it about keeping
  the program alive between requests.
- A CGI header ends with **one** empty line. The C sample used to print
  `"\r\n \r\n"`; under Apache that space-line leaked into the body as a
  stray `" \r\n"`. It now prints `"\r\n"`. It also no longer sends
  `Connection: close` — RFC 3875 §6.3 forbids a script from sending header
  fields about the client connection.

## C example transcripts

The "Compile" and "Through the Server" slides are one real session in
`debian:bookworm` (Docker) with Apache 2.4.68, `mod_cgid`, and the
`ScriptAlias` config from the "Server Config" slide; gcc 12.2.0. The source on
the slide is the one compiled (`gcc -Wall`, no warnings). Prompts are real
(`PS1='> \w# '`). If you change the source, re-capture both slides.

## Notes

- Code samples are apache config, bash, C and HTML.
- **This deck declares one topic but renders no TOC slides.** Either add the
  divider pattern (see the root `CLAUDE.md`) or drop `topics` from the front
  matter — as it stands the title card advertises a structure the deck does not
  have.
- The deck is not on lecture 1's syllabus slide. If CGI is being taught again,
  that slide needs updating too.

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They are their own source; the deck has no draw.io files:

| File                | Slide                                                        |
| ------------------- | ------------------------------------------------------------ |
| `web-app-flow.svg`  | Typical Web based Application — login, cookie, fetch, logout |
| `cgi-flow.svg`      | One CGI Request — env vars and stdin in, stdout out          |
| `cgi-url-env.svg`   | CGI Environment Variables — SCRIPT_NAME, PATH_INFO, query    |
| `cgi-vs-module.svg` | CGI vs. Server Module — a process per request vs a worker    |
| `sss.svg`           | Overview of Server-Side Scripting — the five numbered steps  |

- `web-app-flow.svg` is a real run of a small Go `net/http` app (an in-memory
  map stands in for the database) driven by `curl` with a cookie jar. Status
  lines and headers are as captured: `302 Found` + `Location: /login` with no
  cookie, `303 See Other` + `Set-Cookie: session=7f3a9c; HttpOnly` after the
  login POST, `200` JSON `[{"id":12,"total":40}]` from `/api/orders`, and
  `Set-Cookie: session=; Max-Age=0` on logout. The database arrows are the
  mechanism, not a captured query. It replaces the old hand-sketched
  `typical-server.png`.
- `sss.svg` replaces `sss.png` and the two numbered-list slides that repeated
  it; steps 1–5 are on the drawing. The `hello.php` line and its output
  `<p>Hello, ali</p>` were checked with PHP 8.5 (`php -S`, then
  `curl '/hello.php?name=ali'`). The sample uses `htmlspecialchars` on
  purpose — the deck warns about client input two slides later.
- The three `cgi-*.svg` come from a real run: a bash CGI script that prints its
  environment and stdin, hosted by Go's `net/http/cgi` (an RFC 3875 host) and
  called with `curl`. `GET /cgi-bin/hello.cgi/a/b?x=1&y=2` gave
  `SCRIPT_NAME=/cgi-bin/hello.cgi`, `PATH_INFO=/a/b`, `QUERY_STRING=x=1&y=2`;
  the POST gave `CONTENT_LENGTH=15` and the body on stdin; the response had
  `Content-Length: 279` added by the server.
- The pids in `cgi-vs-module.svg` (1671, 1678, 1681) are from three
  consecutive requests in that run. If you redraw, capture again.
- `cgi-vs-module.svg` says "process or thread" for the module worker on
  purpose: mod_php is normally run under the prefork MPM (processes), so
  "each request = a thread" is not true in general. The benefits slide was
  changed to match.
