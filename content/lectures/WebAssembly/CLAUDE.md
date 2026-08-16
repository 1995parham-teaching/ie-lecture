# Introduction to WebAssembly

An extra deck (`lecture: false`) and mostly a **PDF wrapper**: 5 slides framing
`slides.pdf` (embedded with `data-background-iframe`), plus three slides on the
`wabt` toolchain and `wat2wasm`.

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
