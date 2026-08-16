# MongoDB

An extra deck (`lecture: false`), 29 slides, 5 vertical stacks. Originally
presented by **Ehsan Edalat** and **Parham Alvani**; `presentation.pptx` next to
`index.html` is the original source and is linked from the first slide.

Declared topics: NoSQL · Distribution · MongoDB · Documents · Operations.

Arc: why NoSQL → taxonomy → questions to ask → CAP → replica sets → sharding →
what MongoDB is → hierarchy → coming from SQL → processes → schema-free? →
embed or reference → CRUD → aggregation pipeline → transactions → Mongoose.

## Cross-lecture dependency

**CAP is introduced in lecture 9**, which also places MongoDB as CP and
Cassandra as AP. This deck repeats CAP; the two statements must agree.

## Facts worth not re-deriving

- The CRUD examples operate on `db.courses`. One slide said `db.students` for a
  collection that was `courses` everywhere else — a copy-paste slip, now fixed.
  Keep collection names consistent across the CRUD run.
- MongoDB has had multi-document transactions since 4.0, which is why the
  transactions slide exists at all — do not reduce it back to "NoSQL has no
  transactions".

## Notes

- Code samples are javascript (mongo shell) and json.
- If a slide changes materially, the `.pptx` becomes stale. Either update both
  or stop advertising the pptx as the source.
