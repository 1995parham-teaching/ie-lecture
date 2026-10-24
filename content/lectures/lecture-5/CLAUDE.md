# Lecture 5 — JavaScript

216 slides, 44 vertical stacks — the deck with the most slides. Topics (TOC
indices): `0` Introduction · `1` JavaScript Basic · `2` JavaScript & DOM & CSS ·
`3` Event Handling · `4` Web Applications · `5` Summary.

The middle of the deck is a full run through the concurrency model: event loop →
zero delays → non-blocking I/O → Promise → `async`/`await` → the same chain →
errors → waiting in parallel. Then optional chaining, nullish coalescing and
modules. That run is the modern core of the lecture; the OOP/prototype material
before it is the legacy half.

## Facts worth not re-deriving

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
- `document.applets` was removed from the DOM; it is gone from the deck.
- Form reading was checked in headless Chrome: `select.value` with `multiple`
  is only the first selected option (`selectedOptions` has all);
  `FormData.getAll(name)` returns every checked box sharing a name, `get` only
  the first; for radios `form.elements[name].value` is the checked one (for
  checkboxes it is `""`). The "Reading Many Values" comments are that run.
- The HTML Validator demo and `findOS` were run from the built deck: an invalid
  submit fires no `submit` event; a valid one is stopped by
  `preventDefault()` and prints `age=20&email=a%40b.co`, so the deck stays.
- The library-graveyard slide (jQuery, Prototype, MooTools…) is deliberate
  historical framing, not a recommendation.

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They have no draw.io source:

| File                  | Slide                                                     |
| --------------------- | --------------------------------------------------------- |
| `prototype-chain.svg` | Prototype — `Object.create` and `new` chains, name lookup |
| `event-loop.svg`      | Concurrency model — stack, heap, Web APIs, both queues    |
| `zero-delay.svg`      | Zero Delays — timeline of the `setTimeout` sample         |
| `promise-states.svg`  | Promise — pending / fulfilled / rejected and chaining     |
| `await-parallel.svg`  | Waiting in Parallel — two `await`s vs `Promise.all`       |
| `dom-structure.svg`   | DOM — `window` holding the DOM tree and the BOM objects   |
| `event-flow.svg`      | Event Propagation — capture, target, bubble for the demo  |

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
