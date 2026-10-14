# Lecture 6 — JSON, Thrift and gRPC

74 slides, 6 vertical stacks. Topics (TOC indices): `0` Introduction ·
`1` Documentation & Validation · `2` Processing (using JavaScript) ·
`3` Thrift & gRPC · `4` Conclusion.

Arc: JSON syntax → why it needs a schema → JSON Schema in depth (string,
numeric, object, array, `$id`, annotations) → a validator → a parser example →
Thrift (definition file, Python client, Java server, handler, the stack, the
wire) → gRPC (service definition, field numbers, protobuf on the wire, one call
over HTTP/2, the four kinds of RPC) → gRPC compared to JSON over REST.

Code samples span **seven languages**: go, java, javascript, json, protobuf,
python, thrift. Each one has to be valid in its own right.

## Facts worth not re-deriving

- The JSON Schema example **is valid**. Its indentation looks wrong on the
  slide, which invites a "fix" — it was parsed and confirmed correct. Leave it.
- "Semantics", not "Symantec" — that typo was in the deck.
- The instructor attribution is **Parham Alvani**.
- Protobuf **field numbers** are the wire identity: renaming a field is safe,
  renumbering it is not. That is the point of the field-numbers slide.

## Diagrams

Hand-written SVGs in `img/`, drawn for the league background (see the root
`CLAUDE.md`). They have no draw.io source:

| File                 | Slide                                         |
| -------------------- | --------------------------------------------- |
| `thrift-stack.svg`   | The Stack — after Java Handler                |
| `thrift-wire.svg`    | On the Wire — `add(1, 1)`, binary vs compact  |
| `protobuf-wire.svg`  | gRPC stack: On the Wire — after Field Numbers |
| `grpc-http2.svg`     | gRPC stack: One Call over HTTP/2              |
| `grpc-streaming.svg` | gRPC stack: Four Kinds of RPC                 |

- `protobuf-wire.svg` bytes come from `protoc --encode=course.Course` on the
  Service Definition `.proto`, with the same values as the Introduction
  example; `protoc --decode_raw` gives the field split. The size bars are
  measured: protobuf 48 B, CBOR 99 B (`cbor2.dumps`, and the same bytes as the
  CBOR slide), minified JSON 126 B. If the example data changes, re-encode.
- `grpc-http2.svg` is a real capture: a grpc-go 1.84 server and client for that
  `.proto` with a tee on the server's `net.Conn`, frames decoded with
  `x/net/http2.Framer` and `hpack`. `:authority` and `user-agent` were left
  out; the DATA bytes are exact (5-byte prefix + the 48-byte Course).
- `grpc-streaming.svg` method names (`ListStudents`, `Enroll`, `Watch`) are not
  in the Service Definition slide. They were compiled with `protoc` and each
  kind was run once in grpc-go, so the signatures are valid if added.
- `thrift-wire.svg` bytes come from Thrift 0.25 Python (`send_add(1, 1)` into a
  `TMemoryBuffer`) for `TBinaryProtocol` (30 B) and `TCompactProtocol` (12 B).
  A full `ping()`/`add()` round trip over `TSocket`/`TSimpleServer` was also
  run. The seqid is 0 because the Python client does not count it up.
- `thrift-stack.svg` uses the class names on the Python Client and Java Server
  slides. The server's `TBinaryProtocol` is not in that code: it is the default
  protocol of `TSimpleServer.Args`. Layer names follow
  thrift.apache.org/docs/concepts (Server, Processor, Protocol, Transport).
- `thrift-efficiency.png` is a chart from an external source and
  `thrift.png` is a logo; both are untouched.

## Cautions

- Any JSON or JSON Schema you add must be run through a parser before it goes on
  a slide — this deck is specifically about schema validity.
- `diag/reference-based-validation.drawio` is the source for the validation
  diagram.
