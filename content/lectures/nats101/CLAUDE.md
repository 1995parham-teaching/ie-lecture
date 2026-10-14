# NATS101

An extra deck (`lecture: false`), 52 slides (plus the generated title slide), 10 vertical stacks, 1 hands-on
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

Every diagram is a hand-written SVG in `img/` and is its own source; the deck
has no draw.io files.

| File                      | Slide                                         |
| ------------------------- | --------------------------------------------- |
| `subject-wildcards.svg`   | Subject Names → Wildcards, Token by Token     |
| `discard-policy.svg`      | Retention → Discard policy (split off limits) |
| `retention-policies.svg`  | Retention → Retention policy                  |
| `exactly-once.svg`        | Exactly once semantics (Cont.)                |
| `jetstream-consumers.svg` | Consumers                                     |
| `overview.svg`            | Overview                                      |
| `request-reply.svg`       | Request/Response                              |
| `queue-group.svg`         | Queue                                         |
| `cluster-failover.svg`    | Availability → Cluster Failover               |
| `slow-consumer.svg`       | Slow Consumer                                 |
| `ping-pong.svg`           | Ping/Pong                                     |

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
- `overview.svg`: raw-socket clients `SUB foo 1`, `SUB foo 7`, `SUB bar 1`;
  `PUB foo 5 hello` gave `MSG foo 1 5` and `MSG foo 7 5`, and nothing on bar.
- `request-reply.svg`: every protocol line is from the server's `-V` trace of a
  `nc.Request` with a worker on `help` and an audit subscriber on `>`. The
  requester subscribes `_INBOX.<prefix>.*` once per connection; each request
  adds a token. **The audit subscriber also receives the reply** (the old
  drawing showed it getting only the request).
- `queue-group.svg`: three `QueueSubscribe("help", "workers")` and one plain
  `Subscribe("help")`; 900 requests split 302/303/295 (varies per run) and the
  plain subscriber got all 900. Wire form `SUB help workers 1`.
- `cluster-failover.svg`: three servers `--cluster_name ha` with `--routes` to
  all three; `/routez` showed each routed to the other two. The client was
  given only `:4222`; `kill` of n0 gave `EOF`, reconnect to n2 after 0.61 s,
  and the subscriber on n2 got 40 of 40.
- `slow-consumer.svg`: a raw client with a 4 KiB receive buffer subscribed and
  never read while a publisher flooded 1 KiB messages. The server logged
  `Slow Consumer Detected: MaxPending of 67108864 Exceeded`, `/connz` gave
  reason `Slow Consumer (Pending Bytes)`, and the client got **no `-ERR`**,
  only the close (the old drawing showed `-ERR 'Slow Consumer'`, which the
  server never sends; checked in `server/client.go`). Defaults from `/varz`:
  `write_deadline` 10 s (the slide used to say two seconds), `max_pending`
  64 MB. The nats.go line is from a handler slower than
  `SetPendingLimits(1000, 1MiB)`: it dropped 4000 and stayed connected.
- `ping-pong.svg`: a Python socket client against `ping_interval: "3s"`,
  `ping_max: 2`; times and lines are the capture. Defaults from `/varz`:
  2 min, 2. (The old `ping-pong.png` was a stock photo of two paddles.)

## Notes

- The product is spelled **JetStream** in prose, headings and lists (the deck
  once mixed in "Jetstream"). `grep -rn Jetstream` over the deck is now empty;
  keep it that way, except inside code, identifiers or URLs that literally use
  another spelling.
- Every slide's prose sits in a block element. The "Retention policies and
  limits" intro was bare text after the `<h2>`; it is now a `<p>`.

- The hand-written "Introduction to NATS" title slide (with `img/background.jpg`)
  was removed: `layouts/lectures/single.html` generates the title slide.
- Code samples are shell only.
