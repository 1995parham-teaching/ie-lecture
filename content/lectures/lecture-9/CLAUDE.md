# Lecture 9 — Web Application Architectures

61 slides, 8 vertical stacks, 11 diagrams and no code. Topics (TOC indices):
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

- No code blocks at all — this deck is diagrams and prose. `diag/diag.drawio` is
  the source for them.
- Several `<img>` elements previously had no `alt`; new images need one.
- The "A Real Story 🔥" slide is anecdotal by design.
