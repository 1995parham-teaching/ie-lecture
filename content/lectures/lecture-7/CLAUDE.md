# Lecture 7 — Go Programming

134 slides, 24 vertical stacks, **12 hands-on sections** — the most hands-on
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

## Open item

**Generics are not taught.** The history slide notes that "lack of support for
generic programming … in Go 1.x had drawn considerable criticism" — historically
accurate, but generics landed in Go 1.18 and the deck never gets there. This
needs a section, not a bullet.
