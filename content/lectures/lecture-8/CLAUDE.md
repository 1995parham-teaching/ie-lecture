# Lecture 8 — CGI

25 slides, 2 vertical stacks. The historical bridge between "static documents"
and "web application frameworks": how the first dynamic web worked, why it did
not scale, and what replaced it.

Arc: typical web application → CGI → a C example (server config, source,
compile, test) → the same thing in bash → reading parameters from the client →
the CGI environment variables → pros and cons → what solved the problems →
server-side scripting → embedded vs external → client-side vs server-side.

## Facts worth not re-deriving

- `PATH_INFO` is the part of the URL path **after** the script name; it is not
  the filesystem `PATH`. That was wrong in the deck and is now right.
- CGI's cost is **one process per request** — that is the whole reason the
  pros/cons slide exists, and the reason FastCGI, mod_php and application
  servers followed.

## Notes

- Code samples are apache config, bash, C and HTML.
- `diag/typical-server.drawio` and `diag/sss.drawio` are the diagram sources.
- **This deck declares one topic but renders no TOC slides.** Either add the
  divider pattern (see the root `CLAUDE.md`) or drop `topics` from the front
  matter — as it stands the title card advertises a structure the deck does not
  have.
- The deck is not on lecture 1's syllabus slide. If CGI is being taught again,
  that slide needs updating too.
