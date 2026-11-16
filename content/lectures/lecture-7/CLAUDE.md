# Lecture 7 — Go Programming

124 slides (123 in `index.html` plus the generated title), 28 vertical stacks,
**12 hands-on slides** — the most hands-on deck in the repo. Counted from the
source on 16 November 2026: a slide is a `<section>` with no `<section>`
inside it. Spans four sessions plus the two HTTP-server sessions. Topics
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
`srv.Shutdown`) → testing a handler with `httptest`. The shutdown slide does
not show `context.Cause`; only go-lecture's `main.go` logs it, and the Server
Side slide points at that log line.

**Do not reintroduce a web framework here**, and do not add an import that is
not in the standard library.

## Every snippet compiles

Checked with **go1.27.4** (darwin/arm64) on 16 November 2026. Fragments were
wrapped in a `main` package and run through `go build`, `go vet` and `go run`;
the outputs in comments are from those runs. Fixed in that pass:

- **Calculation** used an undefined `f` and declared `x` and `y` twice. It is
  now one program (`f := 212.0` prints `100`) and the five bit patterns were
  re-checked.
- **Variables** declared `x` and `s` in both blocks; the second block now uses
  `x2`, `s2`, `t2`, `y`, `u`, `b`.
- **Communication via channels** keeps `var ch` and `ch :=` on adjacent lines,
  marked "either" / "or": they are alternatives and do not compile together.
- **Analytic geometry** used pointer receivers and never used `Point`. The
  methods now have value receivers and `main` ranges over a `[]Point`. With
  pointer receivers the slice fails with `Cartesian does not implement Point
(method Distance has pointer receiver)` (the Result slide shows that tail of
  the real message, marked with `…:`).
- **Methods** was 31 lines and clipped; it is two slides now.
- Earlier: **Casting Types** and **Type Assertion** were "declared and not
  used"; both were rewritten.

Do not add a snippet you have not built.

## Facts worth not re-deriving

- **Ken Thompson**, not "Ken Thomson".
- The package clause is `package main` — unquoted.
- `const third = 1 / 3` is **0** (integer division). The slide makes that trap
  explicit on purpose; do not "correct" it to `1.0 / 3`.
- Use `any`, not `interface{}` — the alias has existed since Go 1.18.
- The hands-on transcripts are real captured output, including
  `DELETE /hello` → **405**. Re-capture if you change a command.
- **HTTP hands-on** (`#/62`) was re-captured on 16 November 2026 after
  go-lecture's `Get` handler was given `w.Header().Set("Content-Type",
"application/json")` — before that the live run answered a sniffed
  `text/plain; charset=utf-8`. curl ran on a pty, so no progress meter; the
  `DELETE` line uses `-s` because `-o /dev/null` otherwise prints the meter.
  The only change to the captures is the bold ANSI on curl's header names. The
  Server Side slide shows the five `slog` lines whole, `time=` included, in a
  `font-size: 0.5em` block so the 115-character line fits.
- **07-slices** prints its `range` line as `range s1: 0:10 1:20 …` (changed in
  go-lecture so the Result slide can show it whole) and the slide is the
  unedited run.
- `fmt.Println(s[0], s[7])` prints **`104 119`**, the bytes.
- `[2]int == [3]int` fails with `invalid operation: a == d (mismatched types
[2]int and [3]int)`.
- The Fibonacci slide and go-lecture `03-conditions` use F(0) = F(1) = 1, so
  F(10) is **89**; the slide says so and names the textbook 55.
- A type assertion is a **run-time** check: `k.(int)` on an `example` panics
  with `interface conversion: interface {} is main.example, not int`; the
  comma-ok form gives `0 false`.
- `new(42)` compiles since Go 1.26 and is a `*int`; the JSON slide uses
  `new(3)` for the optional `Count`.
- Predeclared names in Go 1.27 (`go doc builtin`) include `any`,
  `comparable`, `clear`, `min`, `max`, `print` and `println`.
- Static linking: `GOOS=linux CGO_ENABLED=0 go build` gives `file` output
  "statically linked"; a macOS build links `/usr/lib/libSystem.B.dylib` and
  `/usr/lib/libresolv.9.dylib` (`otool -L`).
- `sync.WaitGroup.Go` is Go 1.25. The Simple Example now prints five lines per
  goroutine and exits when all three return (5.5 s measured), instead of
  `time.Sleep(20 * time.Second)`.
- The `select` slide prints `fast`, `timeout`, `slow` (three runs, same order:
  100 ms, the 500 ms timer, then 1 s).
- The `httptest` slide's test was run in a scratch copy of go-lecture with the
  file at `httpserver/handler/hello_test.go`: `ok` with the fixed `Get`, and
  `Content-Type = ""` against the old one. The file is **not** in go-lecture.

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
| `response-writer.svg`    | HTTP: The Life of a `ResponseWriter`     |

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
- `response-writer.svg` was captured with `curl -i` against two scratch
  servers on Go 1.27.4: `Header().Set` → `WriteHeader(201)` → two `Write`s
  gave `201 Created`, `Content-Type: application/json`, `Content-Length: 6`,
  body `"a""b"`, and a header set after `WriteHeader` was absent. Writing
  first, then setting `Content-Type`, then `WriteHeader(418)` gave `200 OK`
  with a sniffed `text/plain; charset=utf-8`, and the server logged the exact
  line in the diagram (`… superfluous response.WriteHeader call from
main.main.func1 (main.go:14)`). Rendered with `rsvg-convert -b '#2b2b2b'`.
- `module-path.svg` examples and the `gopls/v0.4.0` tag are from go.dev/ref/mod.
  The tag was checked with `git ls-remote`.
- `echo.png` and `starwars.png` (left over from the Echo-based HTTP section)
  were deleted after a `grep -rn` across content, layouts, static and data
  found no reference.

## Open item

**Generics are not taught.** The history slide now says they were added in Go
1.18 (2022), but the deck never teaches them. This needs a section, not a
bullet.
