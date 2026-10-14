# NATS101

An extra deck (`lecture: false`), 53 slides, 10 vertical stacks, 1 hands-on
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

## Diagrams (hand-written SVG)

These SVGs in `img/` have no draw.io source; they are their own source:

| File                      | Slide                                         |
| ------------------------- | --------------------------------------------- |
| `subject-wildcards.svg`   | Subject Names → Wildcards, Token by Token     |
| `discard-policy.svg`      | Retention → Discard policy (split off limits) |
| `retention-policies.svg`  | Retention → Retention policy                  |
| `exactly-once.svg`        | Exactly once semantics (Cont.)                |
| `jetstream-consumers.svg` | Consumers                                     |

All checked against a local `nats-server` 2.15.1 (`-js`) with `nats.go`:

- `subject-wildcards.svg`: subscribed to each pattern and published `foo`,
  `foo.hello`, `foo.hi.bar`, `foo.hello.bar`, `foo.a.b.c`. `foo.>` did not
  receive `foo`.
- `retention-policies.svg`: limits kept all messages after acks; interest
  kept nothing with no consumers, and dropped a message only after both
  consumers acked it; workqueue dropped acked messages and refused a second
  unfiltered consumer (`multiple non-filtered consumers not allowed`).
- `discard-policy.svg`: `max_msgs: 3`, a fourth publish. Discard old (the
  default) left seq 2–4; discard new returned `maximum messages exceeded`.
- `exactly-once.svg`: the two ack bodies are verbatim server replies to a
  repeated `Nats-Msg-Id` (only the stream name changed); default duplicate
  window is 2m. An `+ACK` sent as a request got an empty reply.
- `jetstream-consumers.svg`: two clients fetching from one durable pull
  consumer got seqs 1 3 5 and 2 4 6 (the exact split depends on timing); a
  consumer with `OptStartSeq: 4` got 4 5 6.

## Notes

- `diag/nats101.xml` is the draw.io source for the PNG diagrams (overview,
  request/reply, queues, HA, slow consumer, ping/pong). Edit it there.
- The title slide uses `data-background-image="img/background.jpg"` — that file
  must exist. A sibling deck once referenced a background that had been deleted.
- Code samples are shell only.
