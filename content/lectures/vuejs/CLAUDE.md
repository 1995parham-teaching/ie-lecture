# VueJS

An extra deck (`lecture: false`), 24 slides, 4 vertical stacks. Originally
presented by **Pooya** and **Parsa**; `presentation.pptx` is their original
deck and is linked from the first slide.

Declared topics: Introduction · Reactivity · Template Syntax · Components ·
Tooling.

Arc: what Vue is → declarative rendering → creating an application →
`ref` and `reactive` → computed properties → interpolation and binding →
conditionals and lists → events and input → single-file components →
props and events → getting started.

## This deck is Vue 3, Composition API

Stated explicitly on an early slide and carried through every sample:
`createApp` with `setup()`, then `<script setup>` in the SFC section. Tooling is
`npm create vue@latest` (Vite), with Vue Router and **Pinia** — not Vuex.

**Do not mix in Options API samples.** The whole deck's coherence depends on one
API being shown; a `data()`/`methods` example dropped into the middle would
contradict the `ref`/`reactive` slides that precede it.

## Notes

- Code samples are html, javascript and shell.
- The SFC slides contain `<script setup>` and `<template>` markup inside
  `<pre><code>`, so `&lt;` / `&gt;` escaping matters here.
- **Vue is not on the syllabus** — this is a student presentation deck, parallel
  to `react`. The course teaches React in the TA sessions. Keep the two decks
  independent; neither should assume the other was shown.
- **`presentation.pptx` is not the source of this deck and is not kept in
  step with it.** It is the 40-slide Spring 2020 original: Vue 2, Options API
  (`new Vue({ el, data, methods })`), with Vue 2 lifecycle and reactivity
  pictures. This deck was rewritten for Vue 3 and the Composition API, so the
  two differ on almost every code slide. The first slide says so ("written for
  Vue 2 and the Options API ... this deck is Vue 3"). Do not edit the pptx to
  match: adding Vue 3 material would put both APIs in one file.

## Diagrams

Hand-written SVGs in `img/`, no draw.io source. They are deliberately **not**
in `presentation.pptx`: both show Vue 3 APIs (`ref`, `count.value`, `emit`)
that the Vue 2 pptx never uses, so inserting them would contradict the slides
around them (its slide 5 "Reactivity" is the Vue 2 docs' Watcher and
getter/setter picture). Checked by dumping the pptx text and slide 5's image
with python-pptx 1.0.

| File               | Slide                                        |
| ------------------ | -------------------------------------------- |
| `reactivity.svg`   | What count.value++ Does (after ref/reactive) |
| `props-events.svg` | Props and Events                             |

Verified with Vue 3.5 in jsdom:

- `reactivity.svg`: after three `count.value++` the DOM still shows `0`; after
  `await nextTick()` it shows `3`, with one extra render. Changing a ref the
  render never read causes no render.
- `props-events.svg`: a `StudentCard` emitting `selected` with `student.id`
  sets the parent's `selectedId`. Assigning to a prop in the child warns
  `Set operation on key "title" failed: target is readonly` and leaves it
  unchanged.
