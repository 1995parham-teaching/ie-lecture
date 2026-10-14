# Introduction to Redux

An extra deck (`lecture: false`) and a **PDF wrapper**, not a real reveal.js
deck: 5 slides that frame `Slides.pdf`, which is embedded with
`data-background-iframe` and `data-background-interactive` so it can be scrolled
in place.

By **SeyedEhsan Sajadi** and **Kian Jalilian**, from a student presentation.

## Notes

- `Slides.pdf` and `Slides.pptx` are the real content and have **no source in
  this repo**. Nothing you change in `index.html` affects them. Do not "fix" a
  claim from the PDF by editing the wrapper — the two would then disagree.
- No `topics` in the front matter, so the generated title card shows no topics
  line. That is correct for a wrapper deck; do not invent topics to fill it.
- The one live command is the Redux + Vite template via `npx degit`. If that
  template path moves, the command breaks silently — it is the only thing here
  worth re-checking each term.
- The directory name is capitalised (`Redux/`), which makes the URL
  `/lectures/Redux/`. Leave it; renaming breaks any link already handed out.

## Related

The **react** deck is the prerequisite and is a full reveal.js deck. If Redux is
ever rewritten as real slides rather than a PDF, match that deck's conventions
(escaped JSX, `language-jsx`, TOC dividers).

## Diagrams

`img/redux-loop.svg` (hand-written, no draw.io source) is on **The Redux Loop**
slide, before the PDF. It follows one click of the template's **Add Amount**
button. The action type, the `payload: 2` (the template's default amount), the
`{ value, status: "idle" }` slice shape and `useAppSelector` all come from
`vite-template-redux` on GitHub; the "…" in the root state stands for the
template's `quotesApi` slice. Dispatching the same action through RTK 2.13 in
Node gives `{ value: 2, status: "idle" }` and a new `counter` object, with the
old one unchanged. If the template changes, re-check it.

This slide is new; the PDF does not contain it, so it cannot disagree with it.
