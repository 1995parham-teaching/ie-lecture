# Lecture 9 — Web Application Architectures

61 slides after the generated title, in 33 horizontal positions (`#/0`–`#/32`) with 10 vertical stacks. 24 diagrams, all hand-written SVGs, and 4 code blocks (three Go, one curl transcript). Topics (TOC indices): `0` MVC & MVVM Design Patterns · `1` Multilayer Design · `2` Microservices Architecture.

Arc: MVC (four interaction diagrams) → MVVM → MVC across browser and server → patterns in modern apps → layering (presentation, business logic, data) → the lecture 7 server, layered, with code and a run → traditional vs modern multi-layer → SOA and the ESB → monolith problems → microservices and their four tiers → what makes them hard, and when not to use them → ACID on a bank transfer → the real story, what went wrong, and the fix (outbox + idempotent consumers, saga) → CAP → MongoDB (CP) vs Cassandra (AP) → messaging patterns (RPC vs shared resources, sync vs async, orchestration vs choreography) → brokers and QoS → REST → north-south vs east-west traffic.

This is the deck that sets up **mongodb** and **nats101**, and it is where CAP is introduced — mongodb repeats it, so keep the two statements consistent. Both now state CAP as a choice made during a partition, not "pick 2 of 3".

## Facts worth not re-deriving

- **AngularJS is end-of-life** (and Angular is a different framework). The deck
  used to present it as current.
- The Go frameworks named here were corrected; check any framework claim against
  its current docs before adding one.
- **React and Vue are not "MVVM".** React is a view library with one-way data flow. The Vue 2 guide (`v2.vuejs.org/v2/guide/instance.html`) says Vue is "not strictly associated with the MVVM pattern" but its design was "partly inspired by it". The deck quotes that.
- **CAP**: Brewer, "CAP Twelve Years Later" (InfoQ, 30 May 2012): "The '2 of 3' formulation was always misleading". The deck states CAP as "during a partition, choose consistency or availability".
- **MongoDB**: a replica set has exactly one primary; data is BSON documents in WiredTiger. The implicit default write concern is `w: "majority"` since 5.0 (5.0 compatibility notes and the write-concern reference), except with arbiters when the data-bearing voting members do not exceed the voting majority, where it is `w: 1`. CP holds only with majority writes and primary reads. Heartbeats every 2 s (the mongodb deck measured `heartbeatIntervalMillis: 2000` on 8.3).
- **Cassandra**: consistency level is chosen per operation (Apache Cassandra docs, Dynamo page); `QUORUM` is n/2 + 1 replicas, and W + R > RF makes the read and write sets overlap.
- **Brokers and licences** (checked 16 November 2026): EMQX moved to the Business Source License 1.1 from 5.9, announced 7 May 2025 (emqx.com blog), merging the community and enterprise editions. VerneMQ's downloads page: "Free to test; a paid subscription is required for production use" for the binary packages; building from source has no such note. Kafka and NATS were added to the list.
- **MQTT QoS** 0/1/2 are at-most-once / at-least-once / exactly-once, and QoS 2 is per hop (client to broker, broker to client), not end to end.
- **Example repos**: TMail (`9231058/TMail`) is PHP/Laravel, last pushed July 2016, not formally archived. say-hello is a Go Fiber API that embeds a React 17 build made with `react-scripts` (Create React App); React deprecated CRA on 14 February 2025. Both slides say so.
- **Fowler, Monolith First** (3 June 2015), Lewis and Fowler, "Microservices" (25 March 2014), and Bruce and Pereira, _Microservices in Action_ (Manning, October 2018) are the references. All links on the References slide returned 200 on 16 November 2026.

## The layered Go server (`#/12/1`–`#/12/5`)

- One `main.go` of 76 lines, modelled on `go-lecture/httpserver` (same `ServeMux`, `PathValue`, port 1373; its `model.Student` has `ID`, `FirstName`, `LastName`). The slides split it into three blocks of 21, 21 and 20 lines and indent with two spaces, like lecture 7. The full file is not in the repo; to re-run it, paste the three blocks into one file with `package main` and the imports `encoding/json`, `errors`, `log`, `net/http`, `strconv`.
- Built, vetted and run with Go 1.27.4 (`go.mod` says `go 1.22`, which the method-and-wildcard patterns need). `go build` and `go vet` were clean.
- The "Run It" transcript is a real capture: `GET /students/9531` gave `200` with `Content-Type: application/json` and `{"id":9531,"first_name":"Linus","last_name":"Torvalds"}`; `/42` gave `student not found` and `404`; `/0` gave `student id must be positive` and `400`; `/abc` gave `bad id` and `400`. If you change the code, capture it again.
- `#/4/1` uses the same server as an MVC example (handler = C, `Student` = M, JSON encoding = V), and the REST slide (`#/30`) uses its `GET /students/9531`.

## Notes

- Several `<img>` elements previously had no `alt`; new images need one.
- The "A Real Story 🔥" slide is anecdotal by design; `outbox.svg` after it gives the fix.
- The old third-party rasters (`mvc-1.png`, `mvc-2.gif`, which was really a PNG, `mvc-3.png`, `mvc-4.png`, `mvvm.png`, `multi-layer.png`, `micro.png`, `mongodb.webp`) were redrawn or dropped. The `micro.png` slide repeated the scaling and four-tiers slides and was removed.
- The old prose slides for Consistency, Isolation and Durability became `acid-transfer.svg`; the old "Asynchronous Messages" prose slide was merged into the routing-by-subject slide.

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They have no draw.io source:

| File                  | Slide                                                 | How it was checked                                                                                                                                                                                                                                              |
| --------------------- | ----------------------------------------------------- | --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `mvc-classic.svg`     | `#/5/0` MVC Interactions — view → controller → model  | Same arrows as the old `mvc-1.png`, plus an Excel walk-through (type 5 in B2, C1 = B2 \* 2 recomputes). Conceptual; rendered and inspected.                                                                                                                     |
| `mvc-mediator.svg`    | `#/5/1` controller as mediator (Swing)                | Same arrows as the old `mvc-2.gif`. `person.setName` / `nameLabel.setText` are illustrative; `JLabel.setText` is the real Swing method. Rendered and inspected.                                                                                                 |
| `mvc-cycle.svg`       | `#/5/2` the Wikipedia loop                            | Same four arrows as the old `mvc-3.png` (user → controller → model → view → user), with web labels that match the layered server. Rendered and inspected.                                                                                                       |
| `mvc-full.svg`        | `#/5/3` all the arrows                                | Same six arrows as the old `mvc-4.png`; "grey out Save" illustrates the controller-updates-view arrow. Rendered and inspected.                                                                                                                                  |
| `mvvm.svg`            | `#/6/2` MVVM                                          | Same arrows as the old `mvvm.png`. Values: birthDate 2004-03-01 gives age 22 as of November 2026 (it turns 23 on 1 March 2027); 125000 cents = $1,250.00. Rendered and inspected.                                                                               |
| `mvc-web.svg`         | `#/7` one MVC over browser and server                 | Replaces the slide's bullet list; every item on it (HTML, CSS, client-side scripting, server-side scripting, processing, session, tables) is placed. Conceptual.                                                                                                |
| `multi-layer.svg`     | `#/12/0` Multilayer Architecture                      | Replaces `multi-layer.png` (3 bands of components) with an online-shop example; the data-layer stores match the Data Layer slide (database, messaging). Conceptual.                                                                                             |
| `layered-server.svg`  | `#/12/1` Your Lecture 7 Server, Layered               | Type and method names, the rule, the routes and the 200/404 answers are from the Go run above.                                                                                                                                                                  |
| `acid-transfer.svg`   | `#/26/2` ACID on a Bank Transfer                      | Run in sqlite3 3.54: the transfer gave A 400, B 300; a process killed mid-transaction left A 500, B 200; a 600 debit failed with `CHECK constraint failed: balance >= 0`; two interleaved read-then-write withdrawals gave 300, two `BEGIN IMMEDIATE` ones 200. |
| `outbox.svg`          | `#/26/5` Fixing It: Outbox and Idempotent Consumers   | `INSERT … ON CONFLICT (id) DO NOTHING` run twice in sqlite3 left one row. The outbox, relay, at-least-once redelivery and saga compensation are the standard patterns, not captured from a broker.                                                              |
| `mongodb-replica.svg` | `#/27/2` MongoDB (CP)                                 | Replaces `mongodb.webp`. One primary, BSON/WiredTiger, majority ack after 2 of 3, majority election, 2 s heartbeat: MongoDB write-concern docs and the mongodb deck's measured `rs.conf()`.                                                                     |
| `layers-tiers.svg`    | `#/11` Layers vs. Tiers — 3 layers on 1 tier and on 3 | Conceptual (see below).                                                                                                                                                                                                                                         |
| `esb.svg`             | `#/19` Enterprise service bus — 10 links vs 5         | Conceptual (see below).                                                                                                                                                                                                                                         |
| `monolith-scale.svg`  | `#/23` Scaling: Monolith vs. Microservices            | Conceptual (see below).                                                                                                                                                                                                                                         |
| `four-tiers.svg`      | `#/24` The Four Tiers of a Microservice Application   | Conceptual (see below).                                                                                                                                                                                                                                         |
| `dual-write.svg`      | `#/26/4` What Went Wrong — the "Real Story", drawn    | Conceptual (see below).                                                                                                                                                                                                                                         |
| `cap-partition.svg`   | `#/27/1` CAP During a Partition                       | Conceptual (see below).                                                                                                                                                                                                                                         |
| `sync-async.svg`      | `#/28/2` Synchronous versus asynchronous              | Conceptual (see below).                                                                                                                                                                                                                                         |
| `orch-chor.svg`       | `#/28/3` Orchestration versus choreography            | Conceptual (see below).                                                                                                                                                                                                                                         |
| `traffic.svg`         | `#/31/0` North-South vs. East-West                    | Conceptual. The second east-west curve used to start at Orders and duplicate Orders → Payment; it now runs Users → Payment. Rendered before and after.                                                                                                          |
| `ssr.svg`             | `#/16` Traditional Multi-layer Web App — SSR          | Captured (see below).                                                                                                                                                                                                                                           |
| `csr.svg`             | `#/17` Modern Multi-layer Web App — CSR               | Captured (see below).                                                                                                                                                                                                                                           |
| `rpc-shared.svg`      | `#/28/1` RPC versus shared resources                  | Captured (see below).                                                                                                                                                                                                                                           |
| `pubsub-subjects.svg` | `#/29/0` Asynchronous Messages — routing by subject   | Captured (see below).                                                                                                                                                                                                                                           |

Each new or redrawn SVG was rendered with `rsvg-convert -b '#2b2b2b'` and inspected, and each slide that shows one was screenshotted in headless Chrome at 1280×933 with nothing clipped.

- The conceptual ones were not captured from a run. The checkable facts: 5 systems point to point need n(n − 1)/2 = 10 links; the four tiers (platform, services, boundary, client) are the ones the slide text names, from Bruce and Pereira, _Microservices in Action_; the CP and AP outcomes follow the deck's own definitions of C and A, and agree with the MongoDB (CP) and Cassandra (AP) slides that follow.
- `sync-async.svg` and `orch-chor.svg` replaced the long prose on those
  slides; `four-tiers.svg` replaced the four definition bullets.
- The protocol lists in `traffic.svg` are the same as on the two slides after
  it. Change both together.
- `ssr.svg` and `csr.svg` are captured, not conceptual. A stdlib Go demo
  served the same two-mail inbox both ways; `curl` showed the SSR `GET /`
  already holds the `<li>` items while the CSR one holds only
  `<div id="root"></div>` and a `<script>`, and the server log of a headless
  Chrome load showed SSR `GET /` vs CSR `GET /`, `GET /app.js`,
  `GET /api/inbox` (plus `/favicon.ico` for both, left out). The JSON is the
  real response body. The CSR server is labelled business/API, not
  presentation: the old drawing put presentation on the server in both.
- `rpc-shared.svg`: the RPC values come from a Go `net/rpc` run —
  `client.Call("Payment.Charge", Args{42, 50}, &r)` returned
  `paid order 42: 50`. The old drawing had no server-side stub. The slide now also says that a shared database between microservices is an anti-pattern (database per service; Lewis and Fowler, "Decentralized Data Management").
- `pubsub-subjects.svg`: checked with the `nats` CLI against
  `demo.nats.io` — a publish on `foo` reached the subscriber on `foo` and the
  one on `foo, bar`, and not the one on `bar`. `PUB`/`MSG` are the NATS
  protocol verbs. It complements `sync-async.svg` (timing) with routing;
  keep the two from overlapping.
