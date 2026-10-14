# Lecture 9 — Web Application Architectures

57 slides after the generated title, 8 vertical stacks, 20 diagrams and no
code. Topics (TOC indices):
`0` MVC & MVVM Design Patterns · `1` Multilayer Design ·
`2` Microservices Architecture.

Arc: MVC → MVVM → patterns in real web apps → layering (presentation, business
logic, data) → traditional vs modern multi-layer → SOA and the ESB → monolith
problems → microservices and their four tiers → what makes them hard →
transactions and ACID → CAP → MongoDB (CP) vs Cassandra (AP) → messaging
patterns (RPC vs shared resources, sync vs async, orchestration vs
choreography) → north-south vs east-west traffic.

This is the deck that sets up **mongodb** and **nats101**, and it is where CAP
is introduced — mongodb repeats it, so keep the two statements consistent.

## Facts worth not re-deriving

- **AngularJS is end-of-life** (and Angular is a different framework). The deck
  used to present it as current.
- The Go frameworks named here were corrected; check any framework claim against
  its current docs before adding one.

## Notes

- No code blocks at all — this deck is diagrams and prose. The MVC, MVVM,
  `multi-layer.png`, `micro.png` and `mongodb.webp` images are third-party
  pictures with no source here.
- Several `<img>` elements previously had no `alt`; new images need one.
- The "A Real Story 🔥" slide is anecdotal by design.

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They have no draw.io source:

| File                  | Slide                                                  |
| --------------------- | ------------------------------------------------------ |
| `layers-tiers.svg`    | Layers vs. Tiers — 3 layers on 1 tier and on 3 tiers   |
| `esb.svg`             | Enterprise service bus — 10 point-to-point links vs 5  |
| `monolith-scale.svg`  | Scaling: Monolith vs. Microservices                    |
| `four-tiers.svg`      | The Four Tiers of a Microservice Application           |
| `dual-write.svg`      | What Went Wrong — the "Real Story", drawn              |
| `cap-partition.svg`   | CAP During a Partition — CP errors, AP returns stale   |
| `sync-async.svg`      | Synchronous versus asynchronous                        |
| `orch-chor.svg`       | Orchestration versus choreography                      |
| `traffic.svg`         | North-South vs. East-West                              |
| `ssr.svg`             | Traditional Multi-layer Web App — SSR request sequence |
| `csr.svg`             | Modern Multi-layer Web App — CSR request sequence      |
| `rpc-shared.svg`      | RPC versus shared resources                            |
| `pubsub-subjects.svg` | Asynchronous Messages — routing by subject             |

- The first nine are conceptual; nothing there was captured from a run. The
  checkable facts: 5 systems point to point need n(n − 1)/2 = 10 links; the four tiers
  (platform, services, boundary, client) are the ones the slide text names,
  from Bruce and Pereira, _Microservices in Action_; the CP and AP outcomes
  follow the deck's own definitions of C and A, and agree with the MongoDB
  (CP) and Cassandra (AP) slides that follow.
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
  `paid order 42: 50`. The old drawing had no server-side stub.
- `pubsub-subjects.svg`: checked with the `nats` CLI against
  `demo.nats.io` — a publish on `foo` reached the subscriber on `foo` and the
  one on `foo, bar`, and not the one on `bar`. `PUB`/`MSG` are the NATS
  protocol verbs. It complements `sync-async.svg` (timing) with routing;
  keep the two from overlapping.
