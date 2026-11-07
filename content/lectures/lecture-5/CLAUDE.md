# Lecture 5 — JavaScript

124 slides in 66 horizontal positions. It was cut from 216 on 2026-11-06,
when the user asked for the deck to be "short and useful" and to cover the
newest JavaScript features. On 2026-11-07 the user said "short" meant
removing duplicates, not depth, and asked for more: 16 vertical slides were
added (engines and runtimes, `<script>` head/body, `defer`/`async`, boxing in
Java vs JavaScript, `reduce`, and the event loop). Add new material as
vertical slides so the session ranges below stay valid. Topics (TOC indices): `0` Introduction · `1`
JavaScript Basic · `2` Modern JavaScript · `3` JavaScript & DOM & CSS · `4`
Event Handling · `5` Web Applications · `6` Summary. It is taught in four
sessions (IE S11–S14): `#/2`–`#/15`, `#/16`–`#/31`, `#/32`–`#/45`,
`#/46`–`#/66`.

The middle of the deck is a full run through the concurrency model: event loop →
zero delays → non-blocking I/O → Promise → `async`/`await` → errors → waiting in
parallel → modules. Topic 2 then tours the editions ES2020–ES2027 (`?.`, `??`,
`toSorted`, `Object.groupBy`, `Set` methods, iterator helpers, the ES2026
additions, Temporal and `using`).

## What the cut removed, and why

Do not bring these back without a reason; each was a duplicate, legacy, or
wrong:

- Slides that repeated the next slide in prose (wrapper disposal, "Events &
  their handling in more details", "DOM & JavaScript", the `var` scope
  one-liner, "JavaScript Programming Language" checklist).
- Legacy APIs: `new Object()`, `new String()`, form access by `name`
  (`document.nametest.output`), typed arrays, the 19-row `on*` event table
  (it listed `onkeypress` and `onunload` and said `onabort` was page loading),
  `navigator.appCodeName/appName/appVersion/platform`, `window.stop/close/open`,
  `document.domain`, the `window.onresize` hack that rewrote a slide.
- The `changeMe`/`changePropertyInMe` sample, whose arrow `toString` read
  `this`, and the bullet "call by value for primitives, by reference for
  objects", which contradicted the pass-by-sharing slides.
- Demos that taught nothing new: the uppercase textarea, Find OS (repeated
  `FormData.getAll`), the Star Wars logo blob fetch, a second "What next".
- Errors fixed on the way: `element.getElementById` (it exists only on
  `document`), `(1.1).toExponential()` is `"1.1e+0"` not `'1.1e0'`,
  `input.value()` on the email slide, a `while(true)` scope sample that never
  ended, a setter that warned but still stored a negative price.

## Modern JavaScript (topic 2)

The edition of each feature comes from TC39's
[finished proposals](https://github.com/tc39/proposals/blob/main/finished-proposals.md)
(read 2026-11-06), not from blog posts — several blogs wrongly put Temporal in
ES2026. ES2026: Upsert (`getOrInsert`), `Iterator.concat`, `Uint8Array`
Base64/hex, `Math.sumPrecise`, `Error.isError`, `Array.fromAsync`, JSON.parse
source text. Temporal and Explicit Resource Management (`using`) are stage 4
with edition 2027, so the slide says "Coming in ES2027".

Every sample in topic 2, and every changed sample elsewhere, was run in
headless Chrome 157 (Node 20 lacks most of these). Notable outputs:
`Math.sumPrecise([0.1, 0.2])` is still `0.30000000000000004` (it is exact for
the doubles, so it is a bad demo); the slide uses `[1e20, 0.1, -1e20]` →
`0.1` vs `reduce` → `0`. `Temporal.PlainDate.from("2026-11-07").dayOfWeek` is
`6` (Monday is 1); `until("2027-01-01").days` is `55`. 07:45 Tehran is
`2026-11-07T05:15:00+01:00[Europe/Berlin]`. When a new edition ships each June,
update the table on `#/26`.

## Facts worth not re-deriving

- **Script loading** was measured in headless Chrome 157 with a local server
  that delays each file: two `async` files (600 ms, then 100 ms in HTML order)
  ran fast-first; two `defer` files ran in HTML order, before
  `DOMContentLoaded`, after the end-of-body inline script; an inline module ran
  after the `defer` files; `defer` on an inline classic script is ignored (it
  ran in `<head>` with `document.body` null); a head script got `null` from
  `getElementById("para")` and an end-of-body script got the element.
- **Boxing slide**: the Java sample was run in OpenJDK 27 (Homebrew,
  `/opt/homebrew/opt/openjdk/bin/java Box.java`): `6`, `1000 == 1000` `false`,
  `equals` `true`, `100 == 100` `true` (the −128..127 cache), unboxing `null`
  throws `NullPointerException`. The JS lines were run in Node.
- **Event-loop quiz** (`1 4 7 3 5 6 2`) and the walkthrough order (`A D C B`)
  were run in Node and in Chrome 157. The "Block the Loop" demo was run in
  Chrome: during the 2 s busy loop no frame rendered (longest
  `requestAnimationFrame` gap 1983 ms).
- **`reduce` slides** were run in Node: `35`, `35` without an initial value,
  `TypeError: Reduce of empty array with no initial value`, `0`, and
  `{ js: 3, css: 1, html: 1 }`.

- **Five snippets used to be `SyntaxError`s** — `let a` declared three times and
  `let m` twice in the same scope. Any sample that redeclares a `let` in one
  scope does not run. Paste new samples into a console before adding them.
- `const` is introduced alongside `let`, not after. Do not reorder those.
- `document.getElementsByTagName` and friends return an **`HTMLCollection`**,
  which is _live_ — not an array, not a `NodeList`.
- `Event.type` values are **case-sensitive** and lowercase (`"click"`, not
  `"Click"`).
- Private class fields (`#x`) are **ES2022**.
- The Event Loop slides say **task queue** and **task**, not "message queue",
  to match `event-loop.svg` and the HTML spec.
- The "Non-blocking I/O" slide (it was "Never Blocking") says that the event
  loop does not block on I/O, but that synchronous code (a busy loop,
  `alert()`) does. Both samples were run in Node 20: a 10 ms interval ticked
  21 times while `loadUsers()` fetched from jsonplaceholder (~250 ms), and a
  0 ms timer queued before the 3 s busy loop fired after 3000 ms.
- The `new Person(...)` sample's constructor sets `this.name = { first, last }`
  and the other fields, so `farewell()` works. Run in Node with a stub
  `alert`: it prints "Tammi has left the building. Bye for now!".
- The live demos were clicked in headless Chrome after the cut: the fetch
  error slide prints `Failed: Error: HTTP status 403`, a UUID, and
  `Failed: TypeError: Failed to fetch` (unsplash, CORS); SWAPI returns Luke
  Skywalker; `preventDefault` keeps the checkbox unchecked. They all write with
  `append`/`textContent` now.
- `document.applets` was removed from the DOM; it is gone from the deck.
- Form reading was checked in headless Chrome: `select.value` with `multiple`
  is only the first selected option (`selectedOptions` has all);
  `FormData.getAll(name)` returns every checked box sharing a name, `get` only
  the first; for radios `form.elements[name].value` is the checked one (for
  checkboxes it is `""`). The "Reading Many Values" comments are that run.
- The HTML Validator demo was run from the built deck: an invalid submit fires
  no `submit` event; a valid one is stopped by `preventDefault()` and prints
  `age=20&email=a%40b.co`, so the deck stays.

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They have no draw.io source:

| File                    | Slide                                                     |
| ----------------------- | --------------------------------------------------------- |
| `prototype-chain.svg`   | Prototype — `Object.create` and `new` chains, name lookup |
| `event-loop.svg`        | Concurrency model — stack, heap, Web APIs, both queues    |
| `zero-delay.svg`        | Zero Delays — timeline of the `setTimeout` sample         |
| `promise-states.svg`    | Promise — pending / fulfilled / rejected and chaining     |
| `await-parallel.svg`    | Waiting in Parallel — two `await`s vs `Promise.all`       |
| `dom-structure.svg`     | DOM — `window` holding the DOM tree and the BOM objects   |
| `event-flow.svg`        | Event Propagation — capture, target, bubble for the demo  |
| `runtime.svg`           | Engine and Runtime — same V8 in Chrome and Node.js        |
| `script-loading.svg`    | defer and async — four loading timelines                  |
| `reduce.svg`            | How reduce Works — `[5, 10, 20]` to `35`                  |
| `event-loop-turn.svg`   | One Turn of the Loop — task, microtasks, render           |
| `event-loop-step-*.svg` | Step by Step — five snapshots of the A/B/C/D sample       |

The five step diagrams, `event-loop-turn.svg`, `script-loading.svg`,
`reduce.svg` and `runtime.svg` were written by a Python script, but each SVG is
its own source: edit the SVG. Their facts: the step order is the Node/Chrome
run above; `script-loading.svg` is a schematic of the HTML standard (the bar
lengths are not measurements), and its order claims are the Chrome run above;
16.7 ms is one frame at 60 Hz and 50 ms is the Long Tasks API threshold;
`runtime.svg` was checked with `typeof document` (`"undefined"`) in Node.

- `prototype-chain.svg`: every link was checked with `Object.getPrototypeOf`
  in Node, for both the `Object.create(Person)` and the `new Person` samples.
  `p1`'s own keys after the setters are `_name` / `_family`.
- `event-loop.svg`: the microtask-before-task order was run in Node
  (`sync, sync, then, setTimeout`).
- `zero-delay.svg`: the output order is the deck's own sample, run in Node.
- `promise-states.svg`: settle-once, `then` returning a new pending promise, a
  throwing handler rejecting it and `catch` recovering were all run in Node.
- `await-parallel.svg`: the timings are a real Node run with `timeout = 300`
  (603 ms and 301 ms). If the timeout changes, re-measure.
- `event-flow.svg`: the order of phases, `eventPhase`, `this` and
  `event.target` come from headless Chrome clicking the deck's own
  `#parent` / `#click-btn-1` markup with a capture and a bubble listener on
  every ancestor; `stopPropagation()` at the button stopped every listener
  above it.
- `dom-structure.svg` replaced an OmniGraffle export (no source in the repo).
  `prototype-chain.svg`, `promise-states.svg` and `event-flow.svg` replaced
  `prototype.png`, `promises.png` and `eventflow.png`.

## Cautions

- `innerHTML` was replaced with `textContent` wherever the sample was only
  setting text. The Zero Delays live demo uses `el.append(text, <br>)` (text
  nodes); headless Chrome renders the same five lines in the same order as the
  old `innerHTML +=` version. Keep it that way — lecture 11 teaches that `innerHTML` with
  untrusted input is the XSS vector.
- A `document.write` demo was removed. `document.write` after page load wipes the
  document; do not reintroduce it, even as a joke.
- HTML samples inside this deck still need `&lt;` / `&gt;` escaping.
