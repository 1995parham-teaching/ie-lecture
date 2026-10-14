# Introduction to WebAssembly

An extra deck (`lecture: false`) and mostly a **PDF wrapper**: 5 slides framing
`slides.pdf` (embedded with `data-background-iframe`), plus three slides on the
`wabt` toolchain and `wat2wasm` and two diagram slides.

By **Mohammad Hashemi** and **Narges N.**, originally presented at Shahid
Beheshti University.

## Directory contents

```
slides.pdf     the actual presentation — no source in this repo
wat2wasm/      hand-written .wat examples that go with the tool slides
snake-game/    an emscripten-generated bundle
```

**`snake-game/` is generated output, not hand-written**, and is listed in
`.prettierignore` for that reason. Do not reformat it, and do not treat its
HTML as an example of the conventions used elsewhere in this repo — it has its
own `width="296px"`-style attributes and other artifacts of the generator.

## Notes

- No `topics` in the front matter, so the title card shows no topics line. That
  is correct for a wrapper deck.
- The directory name is capitalised (`WebAssembly/`), giving
  `/lectures/WebAssembly/`. Leave it.
- The prose links to Shahid Beheshti University, where this was first given; the
  course now runs at Amirkabir. The attribution is historical and correct as
  written.
- WebAssembly is also on lecture 42's suggested-presentation list. If a student
  picks it, this deck is the existing baseline.

## The wat2wasm demo

`wat2wasm/index.html` loads `hello-WebAssembly.js`, which fetches
`addTwoNum.wasm` and prints `add(14, 5)`. `fetch()` refuses `file://` URLs, so
the folder has to be served over HTTP; the "Run It in the Browser" slide says
so and shows a captured `python3 -m http.server` run (Python 3.11, headless
Chrome as the client). Hugo does not publish `wat2wasm/index.html` (it treats
the `.html` as content), so the slide links to the folder on GitHub rather than
to the deployed site.

The fetch chain checks `response.ok` and ends in a `.catch` that prints the
failure on the page. Verified in headless Chrome: over HTTP the page reads
`Addition result: 19`; from `file://` it prints `TypeError: Failed to fetch`
plus the hint to serve the folder; with the `.wasm` missing it prints
`Error: 404 File not found.`

## Diagrams

Hand-written SVGs in `img/`, no draw.io source, for the files in `wat2wasm/`:

| File                | Slide                 |
| ------------------- | --------------------- |
| `wasm-pipeline.svg` | From .wat to the Page |
| `wasm-bytes.svg`    | Inside addTwoNum.wasm |

- `wasm-bytes.svg` is the `wat2wasm -v` byte log for `addTwoNum.wat` (wabt
  1.0.39, npm `wabt`). Its output is byte-identical to the committed
  `addTwoNum.wasm`, 41 bytes.
- `wasm-pipeline.svg` follows `hello-WebAssembly.js`. Node 20's
  `WebAssembly.instantiate` on the committed file returns `{ module, instance }`
  and `instance.exports.add(14, 5)` returns 19.
- If `addTwoNum.wat` changes, rebuild it and redraw both.
