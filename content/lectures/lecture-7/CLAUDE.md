# Lecture 7 — Go Programming

139 slides, 25 vertical stacks, **12 hands-on sections** — the most hands-on
deck in the repo. Spans four sessions plus the two HTTP-server sessions. Topics
(TOC indices): `0` History · `1` Advantages · `2` Say Hello ·
`3` Programming Elements · `4` Analytic geometry · `5` Packages and Modules ·
`6` HTTP Server · `7` Concurrency.

The companion repo is
[`1995parham-teaching/go-lecture`](https://github.com/1995parham-teaching/go-lecture).

## The HTTP Server section is standard library only

This is a deliberate teaching decision, and it matches go-lecture, which has
**zero external dependencies** and a `just deps` target that fails the build if
that ever changes. The section used to teach Echo; it now teaches `net/http`:

`http.NewServeMux` → the handler interface → Go 1.22 pattern routing
(`GET /hello/{username}`, `r.PathValue`) → reading the request → writing the
response → methods on a struct as handlers → middleware as a plain function →
`http.Server` timeouts → graceful shutdown (`signal.NotifyContext`,
`context.Cause`, `srv.Shutdown`).

**Do not reintroduce a web framework here**, and do not add an import that is
not in the standard library.

## Every snippet compiles

The samples in this deck were run through `go build` and `go vet`. Two of them
did not compile before and were rewritten — both were "declared and not used":

- **Casting Types** — now `fmt.Println(f)` after `var f float32 = float32(one)`.
- **Type Assertion** — now uses `k` in both the direct assertion and the
  comma-ok form.

Do not add a snippet you have not built.

## Facts worth not re-deriving

- **Ken Thompson**, not "Ken Thomson".
- The package clause is `package main` — unquoted.
- `const third = 1 / 3` is **0** (integer division). The slide makes that trap
  explicit on purpose; do not "correct" it to `1.0 / 3`.
- Use `any`, not `interface{}` — the alias has existed since Go 1.18.
- The hands-on transcripts are real captured output, including
  `DELETE /hello` → **405**. Re-capture if you change a command.

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They have no draw.io source. Every Go fact in them was run with
`go run` (Go 1.27) and `go vet`:

| File                     | Slide                                    |
| ------------------------ | ---------------------------------------- |
| `string-bytes.svg`       | Strings hands-on: What Happened?         |
| `slice.svg`              | Slices — header and backing array        |
| `slice-append.svg`       | Slices: `append` and the Backing Array   |
| `interface-value.svg`    | Interfaces hands-on: What Is Inside `p`? |
| `module-path.svg`        | Module Path (second slide of the stack)  |
| `http-request-flow.svg`  | HTTP: One Request, End to End            |
| `graceful-shutdown.svg`  | HTTP: Shutdown, Measured                 |
| `goroutines-channel.svg` | Concurrency: Who Sends When              |

- `string-bytes.svg` uses go-lecture `05-strings`; bytes and `range` indices
  match the captured Result slide.
- `slice.svg` replaced the old `slice.png` screenshot. `slice.svg` and
  `slice-append.svg` use `a := [6]int{10, …, 60}`, `s := a[1:4]`,
  `t := a[3:5]`. The cap of 10 after `append(u, 8, 9)` is the runtime's growth
  rule, not the spec; the diagram says so.
- `interface-value.svg` follows go-lecture `11-interfaces`. The panic text and
  the `p.Hello undefined (type Printer has no field or method Hello)` compile
  error are real.
- `http-request-flow.svg` statuses were captured with `curl` against a
  standard-library server with the deck's three patterns and a logging
  middleware: 200, 204, 405 with `Allow: GET, HEAD, POST`, and 404.
- `graceful-shutdown.svg` timings are one measured run of the deck's shutdown
  code with a 2-second handler and `kill -INT` at 0.8 s. A new connection got
  curl exit 7 (connection refused).
- `goroutines-channel.svg` is a timed run of the Communicating goroutines code.
  The order of the three receives at 0 s changes between runs.
- `module-path.svg` examples and the `gopls/v0.4.0` tag are from go.dev/ref/mod.
  The tag was checked with `git ls-remote`.
- `echo.png` and `starwars.png` (left over from the Echo-based HTTP section)
  were deleted after a `grep -rn` across content, layouts, static and data
  found no reference.

## Open item

**Generics are not taught.** The history slide notes that "lack of support for
generic programming … in Go 1.x had drawn considerable criticism" — historically
accurate, but generics landed in Go 1.18 and the deck never gets there. This
needs a section, not a bullet.
