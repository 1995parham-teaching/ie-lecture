# Introduction to Redux

An extra deck (`lecture: false`) and a **PDF wrapper**, not a real reveal.js
deck: 4 slides that frame `Slides.pdf`, which is embedded with
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
