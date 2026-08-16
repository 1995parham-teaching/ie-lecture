# NATS101

An extra deck (`lecture: false`), 52 slides, 10 vertical stacks, 1 hands-on
section. Follows lecture 9, which introduces messaging patterns and pub/sub.

Arc: history → what it addresses → overview → request/response → queues →
"always available dial tone" → availability → slow consumers → ping/pong →
subject names → **queue subscriptions hands-on** (two workers and a publisher,
three slides of captured terminal) → JetStream (streaming, replay and retention
policies, persistent distributed storage, mirroring, flow control,
exactly-once) → consumers (fast push, horizontally scalable pull with batching).

## Facts worth not re-deriving

- The failure model discussed is **Byzantine** — that word was misspelled in the
  deck.
- The cluster sizing is `R=1` and `R=3`, i.e. replica counts. Those were wrong
  and are now right; do not renumber them casually.
- Nine typos were fixed in a single pass, so surviving oddities are more likely
  deliberate NATS jargon than mistakes. Check the NATS docs before "correcting"
  a term.

## Open item

The **captured transcripts are old**: they show a NATS server built with
`go1.13`/`go1.14`, i.e. roughly nats-server 2.1.x. The behaviour shown is still
correct, but the banners date the deck. Re-capture against a current server if
you want them refreshed — and if you do, re-capture _all_ of them, so the
version is consistent across the hands-on run.

## Notes

- `diag/nats101.xml` is the draw.io source for the diagrams.
- The title slide uses `data-background-image="img/background.jpg"` — that file
  must exist. A sibling deck once referenced a background that had been deleted.
- Code samples are shell only.
