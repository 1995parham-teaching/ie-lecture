# MongoDB

An extra deck (`lecture: false`), 30 slides, 5 vertical stacks. Originally
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

- The CRUD slide runs on `db.students` throughout; the aggregation slide and
  its diagram run on `db.courses`. Keep collection names consistent within each
  run. (The CRUD sample was executed in `mongosh` against MongoDB 8.3.)
- MongoDB has had multi-document transactions since 4.0, which is why the
  transactions slide exists at all — do not reduce it back to "NoSQL has no
  transactions".

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They have no draw.io source:

| File                       | Slide                                         |
| -------------------------- | --------------------------------------------- |
| `replica-set.svg`          | Replica Sets — primary, oplog, failover       |
| `sharded-cluster.svg`      | Sharding — mongos, config servers, key ranges |
| `document-vs-tables.svg`   | Embed or Reference? — three tables vs one doc |
| `aggregation-pipeline.svg` | Aggregation Pipeline (Cont.) — data per stage |

- `replica-set.svg`: checked on a three-member `mongo:8` (8.3) replica set in
  Docker. `rs.conf()` gives `heartbeatIntervalMillis: 2000` and
  `electionTimeoutMillis: 10000`; an insert on a secondary failed with
  `NotWritablePrimary`; stopping the primary elected a secondary.
- `aggregation-pipeline.svg`: the eight courses and every stage's output come
  from running the slide's exact pipeline in `mongosh`. `$group` output order
  is not defined, which is why that column is labelled "any order". The data
  is chosen so `$sort` has no ties; if you change it, run it again.
- `sharded-cluster.svg` was not run on a sharded cluster. The ranges are
  illustrative; the targeted vs scatter-gather behaviour and config servers as
  a replica set are from the manual's sharding pages.
- `document-vs-tables.svg` draws the JSON document that used to be on that
  slide as a code block.

## Notes

- Code samples are javascript (mongo shell) and json.
- If a slide changes materially, the `.pptx` becomes stale. Either update both
  or stop advertising the pptx as the source.
